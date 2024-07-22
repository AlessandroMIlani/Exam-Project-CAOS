/* Standard includes. */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include <FreeRTOSConfig.h>
#include "task.h"
#include "queue.h"
#include "hw_types.h"
#include "hw_sysctl.h"
#include "grlib.h"
#include "osram128x64x4.h"
#include "uart.h"

#include "DemoBitmaps.h"
#include "myutils.h"


#define mainOLED_WIDTH 128
#define mainOLED_HEIGHT 64

/* Constants used when writing strings to the display. */
#define mainCHARACTER_HEIGHT				( 9 )
#define mainMAX_ROWS_128					( mainCHARACTER_HEIGHT * 14 )
#define mainMAX_ROWS_96						( mainCHARACTER_HEIGHT * 10 )
#define mainMAX_ROWS_64						( mainCHARACTER_HEIGHT * 7 )
#define mainFULL_SCALE						( 15 )
#define ulSSI_FREQUENCY						( 3500000UL )


int pseudo_rand();
int ChaosDemo(void);

/* Configure the hardware for the demo. */
// static void prvSetupHardware( void );

/* Function prototypes for the OLED access functions. */
extern void OSRAM128x64x4Init( uint32_t ulFrequency );
extern void OSRAM128x64x4StringDraw( const char *pcStr, uint32_t ulX, uint32_t ulY, unsigned char ucLevel );
extern void OSRAM128x64x4Clear( void );



void ChaosDemoTask(void* pvParameters)
{
    /* Functions to access the OLED.  The one used depends on the dev kit
    being used. */
    void ( *vOLEDImageDraw )( const unsigned char *, uint32_t, uint32_t, uint32_t, uint32_t ) = NULL;

    /* Prevent compiler warnings about unused parameters. */
    ( void ) pvParameters;

	/* Map the OLED access functions to the driver functions that are appropriate
	for the evaluation kit being used. */
	configASSERT( ( HWREG( SYSCTL_DID1 ) & SYSCTL_DID1_PRTNO_MASK ) == SYSCTL_DID1_PRTNO_6965 );
	vOLEDImageDraw = OSRAM128x64x4ImageDraw;
    int i = 0;
    int j = pseudo_rand() % 64;
        vTaskDelay(4000 / portTICK_PERIOD_MS);
        vOLEDImageDraw( worm, i, j, 6, 2);
        for(;;)
        {
            i++;
            if (i > 124)
            {
                vOLEDImageDraw( white, i-1, j, 2, 2);
                vOLEDImageDraw( white, i+1, j, 2, 2);
                i = 0;
                j = pseudo_rand() % 64;
            }
            vOLEDImageDraw( worm, i, j, 6, 2);
            //clear the previous pixel
            vOLEDImageDraw( white, i-1, j, 2, 2);
            vTaskDelay(70 / portTICK_PERIOD_MS);
        }

}


void WelcomeTask(void* pvParameters)
{
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

    vOLEDInit( ulSSI_FREQUENCY );

    // print a welcome message in the center of the screen
    char *firstMessage = "Chaos Demo!";

    // Draw the message at the calculated position
    vOLEDStringDraw(firstMessage, 64/2 - 4, 20, mainFULL_SCALE);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    vOLEDClear();
    /* write welcome message in the center of the screen */
	vOLEDImageDraw( chaosBitMap, 0, 0, mainOLED_WIDTH, mainOLED_HEIGHT );
    char *secondMessage = "Press R to reset the image:\n> ";
    char response[10];
    for(;;)
    {
        input(secondMessage, response, 10);
        if (response[0] == 'R' || response[0] == 'r')
        {
            print("Resetting the image...\n");
            vOLEDClear();
            vOLEDImageDraw(chaosBitMap, 0, 0, mainOLED_WIDTH, mainOLED_HEIGHT );
        }
        else
        {
            print("Invalid input. Please press R to reset the image.\n");
        }
        print("wait for 5 seconds...\n");
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}


int ChaosDemo(void)
{
    prvSetupHardware();

    xTaskCreate(WelcomeTask, "Welcome", 100, NULL, tskIDLE_PRIORITY, NULL);
    // create 10 tasks in a loop
    char base_name[] = "ChaosTask";
    int i;
    for ( i = 0; i < 3; i++)
    {
        char task_name[20];
        sprintf(task_name, "%s-%d", base_name, i);
        xTaskCreate(ChaosDemoTask, task_name, 100, NULL, tskIDLE_PRIORITY, NULL);
    }
    // Start the scheduler
    vTaskStartScheduler();

    return 0;
}


int seed = 489354572; // Seed value

int pseudo_rand() {
    // mod 2^31
    seed = (1664525 * seed + 1013904223) % 2147483399;
    // add some randomness
    seed += xTaskGetTickCount();
    return seed;
}