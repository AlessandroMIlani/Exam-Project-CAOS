/*
 * FreeRTOS V202212.01
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */


/* Standard includes. */
#include <stdio.h>
#include <string.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

/* Hardware library includes. */
#include "hw_memmap.h"
#include "hw_types.h"
#include "hw_sysctl.h"
#include "hw_uart.h"
#include "sysctl.h"
#include "gpio.h"
#include "grlib.h"
#include "osram128x64x4.h"
#include "uart.h"

#include "myutils.h"
/*-----------------------------------------------------------*/

/* The time between cycles of the 'check' functionality (defined within the
tick hook. */
#define mainCHECK_DELAY						( ( TickType_t ) 5000 / portTICK_PERIOD_MS )

/* Task stack size. */
#define mainOLED_TASK_STACK_SIZE       ( configMINIMAL_STACK_SIZE + 40 )

/* Task priorities. */
#define mainOLED_TASK_PRIORITY         ( tskIDLE_PRIORITY + 1 )

/* The queue used to send messages to the OLED task. */
static QueueHandle_t xOLEDQueue;


#define bmpBITMAP_WIDTH 128
#define bmpBITMAP_HEIGHT 50
/*-----------------------------------------------------------*/
/* The maximum number of message that can be waiting for display at any one
time. */
#define mainOLED_QUEUE_SIZE					( 3 )

/* Dimensions the buffer into which the jitter time is written. */
#define mainMAX_MSG_LEN						25

/* Constants used when writing strings to the display. */
#define mainCHARACTER_HEIGHT				( 9 )
#define mainMAX_ROWS_128					( mainCHARACTER_HEIGHT * 14 )
#define mainMAX_ROWS_96						( mainCHARACTER_HEIGHT * 10 )
#define mainMAX_ROWS_64						( mainCHARACTER_HEIGHT * 7 )
#define mainFULL_SCALE						( 15 )
#define ulSSI_FREQUENCY						( 3500000UL )

/*-----------------------------------------------------------*/

#define N_COMP 9

/*-----------------------------------------------------------*/

/* The OLED task. */
static void prvOLEDTask( void *pvParameters );

/* The task that sends messages to the OLED task. */
void prvCompetitiveTask(void *pvParameters);

/* The queue used to send messages to the OLED task. */
static QueueHandle_t xOLEDQueue;

/*-----------------------------------------------------------*/

/* Configure the hardware for the demo. */
static void prvSetupHardware( void );

/* Welcome message to be displayed. */
const char * const DisplayWelcomeMessage = "Display Demo";

/* Function prototypes for the OLED access functions. */
extern void OSRAM128x64x4Init( uint32_t ulFrequency );
extern void OSRAM128x64x4StringDraw( const char *pcStr, uint32_t ulX, uint32_t ulY, unsigned char ucLevel );
extern void OSRAM128x64x4Clear( void );

/*-----------------------------------------------------------*/

int DisplayDemo( void )
{
    prvSetupHardware();

    /* Create the queue used by the OLED task. */
    xOLEDQueue = xQueueCreate( mainOLED_QUEUE_SIZE, sizeof( char * ) );

    // create semaphore
    SemaphoreHandle_t xSemaphore = xSemaphoreCreateBinary();
    xSemaphoreGive(xSemaphore);

    char baseName[] = "Competitor";
    int i;
    for (i = 0; i < N_COMP; i++)
    {
        char taskName[20];
        sprintf(taskName, "%s%d", baseName, i);
        xTaskCreate(prvCompetitiveTask, taskName, configMINIMAL_STACK_SIZE, (void*)xSemaphore, tskIDLE_PRIORITY, NULL);
    }


    /* Start the OLED task. */
    xTaskCreate( prvOLEDTask, "OLED", mainOLED_TASK_STACK_SIZE, NULL, mainOLED_TASK_PRIORITY, NULL );

    /* Start the scheduler. */
    vTaskStartScheduler();

    /* Will only get here if there was insufficient memory to create the idle task. */
    for( ;; );
}

/*-----------------------------------------------------------*/

void prvCompetitiveTask(void *pvParameters)
{
    SemaphoreHandle_t xSemaphore = (SemaphoreHandle_t)pvParameters;
    // use task name to create message
    const char* message = pcTaskGetName(NULL);
    while (1)
    {
        if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdPASS)
        {
            // Add string to queue
            xQueueSend(xOLEDQueue, &message, 0);

            // wait to fake work
            vTaskDelay(pdMS_TO_TICKS(100));

            // Release semaphore
            xSemaphoreGive(xSemaphore);
        }

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

/*-----------------------------------------------------------*/

/* basic display function*/
static void prvOLEDTask( void *pvParameters )
{
    const char *pcMessage;
    uint32_t ulY, ulMaxY;
    static char cMessage[ mainMAX_MSG_LEN ];

    /* Functions to access the OLED.  The one used depends on the dev kit
    being used. */
    void ( *vOLEDInit )( uint32_t ) = NULL;
    void ( *vOLEDStringDraw )( const char *, uint32_t, uint32_t, unsigned char ) = NULL;
    void ( *vOLEDClear )( void ) = NULL;

    /* Prevent compiler warnings about unused parameters. */
    ( void ) pvParameters;

	/* Map the OLED access functions to the driver functions that are appropriate
	for the evaluation kit being used. */
	configASSERT( ( HWREG( SYSCTL_DID1 ) & SYSCTL_DID1_PRTNO_MASK ) == SYSCTL_DID1_PRTNO_6965 );
	vOLEDInit = OSRAM128x64x4Init;
	vOLEDStringDraw = OSRAM128x64x4StringDraw;
	vOLEDClear = OSRAM128x64x4Clear;
	ulMaxY = mainMAX_ROWS_64;
	ulY = ulMaxY;

	/* Initialise the OLED and display a startup message. */
	vOLEDInit( ulSSI_FREQUENCY );

	for( ;; )
	{
		/* Wait for a message to arrive that requires displaying. */
		xQueueReceive( xOLEDQueue, &pcMessage, portMAX_DELAY );

		/* Write the message on the next available row. */
		ulY += mainCHARACTER_HEIGHT;
		if( ulY >= ulMaxY )
		{
			ulY = mainCHARACTER_HEIGHT;
			vOLEDClear();
			vOLEDStringDraw( DisplayWelcomeMessage, 64/2 - 4, 0, mainFULL_SCALE );
		}

		/* Display the message along with the maximum jitter time from the
		high priority time test. */
		sprintf( cMessage, "%s", pcMessage);
		vOLEDStringDraw( cMessage, 0, ulY, mainFULL_SCALE );

	}
}

/*-----------------------------------------------------------*/
