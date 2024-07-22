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

/* The period of the system clock in nano seconds.  This is used to calculate
the jitter time in nano seconds. */
#define mainNS_PER_CLOCK					( ( uint32_t ) ( ( 1.0 / ( double ) configCPU_CLOCK_HZ ) * 1000000000.0 ) )

/* Constants used when writing strings to the display. */
#define mainCHARACTER_HEIGHT				( 9 )
#define mainCHARACTER_WIDTH					( 6 )
#define mainMAX_ROWS_128					( mainCHARACTER_HEIGHT * 14 )
#define mainMAX_ROWS_96						( mainCHARACTER_HEIGHT * 10 )
#define mainMAX_ROWS_64						( mainCHARACTER_HEIGHT * 7 )
#define mainFULL_SCALE						( 15 )
#define ulSSI_FREQUENCY						( 3500000UL )

/*-----------------------------------------------------------*/


/*-----------------------------------------------------------*/
/*
 * Hook functions that can get called by the kernel.
 */
void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName );
void vApplicationTickHook( void );

/*-----------------------------------------------------------*/


/* The OLED task. */
static void prvOLEDTask( void *pvParameters );

/* The task that sends messages to the OLED task. */
void prvWriterTask(void *pvParameters);

/* The queue used to send messages to the OLED task. */
static QueueHandle_t xOLEDQueue;

/* Configure the hardware for the demo. */
static void prvSetupHardware( void );

/*-----------------------------------------------------------*/
/*
 * Basic polling UART write function.
 */
static void prvPrintString( const char * pcString );

/*-----------------------------------------------------------*/

/* Welcome message to be displayed. */
const char * const InputWelcomeMessage = "Write in the OLED!";

/* Function prototypes for the OLED access functions. */
extern void OSRAM128x64x4Init( uint32_t ulFrequency );
extern void OSRAM128x64x4StringDraw( const char *pcStr, uint32_t ulX, uint32_t ulY, unsigned char ucLevel );
extern void OSRAM128x64x4Clear( void );

/*-----------------------------------------------------------*/

int InputDemo( void )
{
    prvSetupHardware();

	vStartEventGroupTasks();

    /* Create the queue used by the OLED task. */
    xOLEDQueue = xQueueCreate( mainOLED_QUEUE_SIZE, sizeof( char * ) );

    xTaskCreate( prvWriterTask, "Write", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL );

    /* Start the OLED task. */
    xTaskCreate( prvOLEDTask, "OLED", mainOLED_TASK_STACK_SIZE, NULL, mainOLED_TASK_PRIORITY, NULL );

    /* Start the scheduler. */
    vTaskStartScheduler();

    /* Will only get here if there was insufficient memory to create the idle task. */
    for( ;; );
}

/*-----------------------------------------------------------*/



void prvWriterTask(void *pvParameters)
{
	/* Prevent compiler warnings about unused parameters. */
	( void ) pvParameters;

    	while(1)
	{
		char *s = pvPortMalloc(100 * sizeof(char));
		input("\n Press a key or paste a string:\n> ", s, 100);
		print(s);
		xQueueSend(xOLEDQueue, &s, portMAX_DELAY);
		vPortFree(s);

	}
}

/*-----------------------------------------------------------*/

/* basic display function*/
static void prvOLEDTask( void *pvParameters )
{
    const char *pcMessage;
    uint32_t ulY, ulMaxY, ulX, ulMaxX;

    /* Functions to access the OLED.  The one used depends on the dev kit
    being used. */
    void ( *vOLEDInit )( uint32_t ) = NULL;
    void ( *vOLEDStringDraw )( const char *, uint32_t, uint32_t, unsigned char ) = NULL;
    void ( *vOLEDImageDraw )( const unsigned char *, uint32_t, uint32_t, uint32_t, uint32_t ) = NULL;
    void ( *vOLEDClear )( void ) = NULL;



    /* Prevent compiler warnings about unused parameters. */
    ( void ) pvParameters;

	/* Map the OLED access functions to the driver functions that are appropriate
	for the evaluation kit being used. */
	configASSERT( ( HWREG( SYSCTL_DID1 ) & SYSCTL_DID1_PRTNO_MASK ) == SYSCTL_DID1_PRTNO_6965 );
	vOLEDInit = OSRAM128x64x4Init;
	vOLEDStringDraw = OSRAM128x64x4StringDraw;
	vOLEDImageDraw = OSRAM128x64x4ImageDraw;
	vOLEDClear = OSRAM128x64x4Clear;
	ulMaxY = mainMAX_ROWS_64;
	ulMaxX = 120;
	ulY = ulMaxY;

	/* Initialise the OLED and display a startup message. */
	vOLEDInit( ulSSI_FREQUENCY );

    // print a welcome message in the center of the screen
    char *firstMessage = "Input Demo!";

    // Draw the message at the calculated position
    vOLEDStringDraw(firstMessage, 64/2 - 4, 20, mainFULL_SCALE);

    vTaskDelay(pdMS_TO_TICKS(5000));

    vOLEDClear();

    vOLEDStringDraw( InputWelcomeMessage, 10, 0, mainFULL_SCALE );
    ulY = mainCHARACTER_HEIGHT;
	ulX = 0;
	for(;;)
	{
		/* Wait for a message to arrive that requires displaying. */
		xQueueReceive( xOLEDQueue, &pcMessage, portMAX_DELAY );

		/*check number of char in the message*/
		int len = strlen(pcMessage);
		/*check if the char is a backspace or canc*/
		if(pcMessage[len-1] == 0x08 || pcMessage[len-1] == 0x7F)
		{
			if(ulX > 0)
			{
				vOLEDStringDraw(" ", ulX, ulY, mainFULL_SCALE);
				ulX -= mainCHARACTER_WIDTH;
			}
			else
			{
				vOLEDStringDraw(" ", ulX, ulY, mainFULL_SCALE);
				if(ulY >= mainCHARACTER_HEIGHT)
				{
					ulY -= mainCHARACTER_HEIGHT;
					ulX = ulMaxX - mainCHARACTER_WIDTH;
					vOLEDStringDraw(" ", ulX, ulY, mainFULL_SCALE);
				}
			}
		}
		else
		{
			if(len*mainCHARACTER_WIDTH < ulMaxX-ulX)
			{
				ulX += len*mainCHARACTER_WIDTH;
			}
			else
			{
				if(ulY > ulMaxY-mainCHARACTER_HEIGHT-1)
				{
					ulY = mainCHARACTER_HEIGHT;
					vOLEDClear();
					vOLEDStringDraw( InputWelcomeMessage, 10, 0, mainFULL_SCALE );
				}
				else
				{
					ulY += mainCHARACTER_HEIGHT;
				}
				ulX = 6;
			}
			vOLEDStringDraw(pcMessage, ulX, ulY, mainFULL_SCALE);
		}
	}
}

/*-----------------------------------------------------------*/

