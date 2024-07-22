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
/* #include "timers.h" */

/* Hardware library includes. */
#include "hw_memmap.h"
#include "hw_types.h"
#include "hw_sysctl.h"
#include "sysctl.h"
#include "gpio.h"
#include "grlib.h"
#include "uart.h"
#include "hw_uart.h"
#include "myutils.h"

#define ENABLE_TRACING 2

/*-----------------------------------------------------------*/

/* The time between cycles of the 'check' functionality (defined within the
tick hook. */
#define mainCHECK_DELAY ((TickType_t)5000 / portTICK_PERIOD_MS)

/* Task priorities. */
#define mainCHECK_TASK_PRIORITY (tskIDLE_PRIORITY + 3)
#define mainSEM_TEST_PRIORITY (tskIDLE_PRIORITY + 1)
#define mainCREATOR_TASK_PRIORITY (tskIDLE_PRIORITY + 3)
#define mainGEN_QUEUE_TASK_PRIORITY (tskIDLE_PRIORITY)

/* Dimensions the buffer into which the jitter time is written. */
#define mainMAX_MSG_LEN 25

/* The period of the system clock in nano seconds.  This is used to calculate
the jitter time in nano seconds. */
#define mainNS_PER_CLOCK ((uint32_t)((1.0 / (double)configCPU_CLOCK_HZ) * 1000000000.0))

/* Constants used when writing strings to the display. */
#define mainCHARACTER_HEIGHT (9)
#define lineSpacing (4)
#define mainMAX_ROWS_128 (mainCHARACTER_HEIGHT * 14)
#define mainMAX_ROWS_96 (mainCHARACTER_HEIGHT * 10)
#define mainMAX_ROWS_64 (mainCHARACTER_HEIGHT * 7)
#define mainFULL_SCALE (15)
#define ulSSI_FREQUENCY (3500000UL)

/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*
 * Hook functions that can get called by the kernel.
 */
void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName);
void vApplicationTickHook(void);

void prvSetupHardware(void);

void vStartEventGroupTasks(void);

void Task_1(void *pvParameters);
void Task_2(void *pvParameters);
void Task_3(void *pvParameters);

#define CAPACITY_LONG 11
#define CAPACITY_MED 3
#define CAPACITY_SHORT 2

/*-----------------------------------------------------------*
/* Tasks Handlers */
TaskHandle_t Task_1_Handler = NULL;
TaskHandle_t Task_2_Handler = NULL;
TaskHandle_t Task_3_Handler = NULL;

/* Tasks Periods */
int Task1_P = 40;
int Task2_P = 8;
int Task3_P = 6;
int Total_Ticks = 0;

/* The task to be created */
void Task_1(void *pvParameters)
{
	int first = 1;
	int xInitWakeTime;
	int xSingleTime;
	int i;
	for (;;)
	{
		i = 0;
		// the first time, consider the start time as 0
		if (first == 1)
		{
			first = 0;
			xInitWakeTime = 0;
		}
		else
		{
			xInitWakeTime = xTaskGetTickCountFromISR();
		}
		while (i < CAPACITY_LONG)
		{
			xSingleTime = xTaskGetTickCount();
			while (xTaskGetTickCount() - xSingleTime < 1);
			i++;
		}

		int xLastWakeTime = xTaskGetTickCount();

#ifdef ENABLE_TRACING
		Log("Task 1: Start %d, End: %d,", xInitWakeTime, xLastWakeTime);
#endif
		vTaskDelayUntil(&xInitWakeTime, Task1_P);
	}
}

void Task_2(void *pvParameters)
{
	int first = 1;
	int xInitWakeTime;
	int xSingleTime;
	int i;
	for (;;)
	{
		i = 0;
		// the first time, consider the start time as 0
		if (first == 1)
		{
			first = 0;
			xInitWakeTime = 0;
		}
		else
		{
			xInitWakeTime = xTaskGetTickCountFromISR();
		}
		while (i < CAPACITY_MED)
		{
			xSingleTime = xTaskGetTickCount();
			while (xTaskGetTickCount() - xSingleTime < 1);
			i++;
		}

		int xLastWakeTime = xTaskGetTickCount();

#ifdef ENABLE_TRACING
		Log("Task 2: Start %d, End: %d,", xInitWakeTime, xLastWakeTime);
#endif
		vTaskDelayUntil(&xInitWakeTime, Task2_P);
	}
}
void Task_3(void *pvParameters)
{
	int first = 1;
	int xInitWakeTime;
	int xSingleTime;
	int i;
	for (;;)
	{
		i = 0;
		// the first time, consider the start time as 0
		if (first == 1)
		{
			first = 0;
			xInitWakeTime = 0;
		}
		else
		{
			xInitWakeTime = xTaskGetTickCountFromISR();
		}
		while (i < CAPACITY_SHORT)
		{
			xSingleTime = xTaskGetTickCount();
			while (xTaskGetTickCount() - xSingleTime < 1);
			i++;
		}

		int xLastWakeTime = xTaskGetTickCount();

#ifdef ENABLE_TRACING
		Log("Task 3: Start %d, End: %d,", xInitWakeTime, xLastWakeTime);
#endif
		vTaskDelayUntil(&xInitWakeTime, Task3_P);
	}
}
/*-----------------------------------------------------------*/
int main(void)
{
	prvSetupHardware();

	xTaskPeriodicCreate(Task_1, "Task 1", 100, (void *)0, 1, &Task_1_Handler, Task1_P);
	xTaskPeriodicCreate(Task_2, "Task 2", 100, (void *)0, 1, &Task_2_Handler, Task2_P);
	xTaskPeriodicCreate(Task_3, "Task 3", 100, (void *)0, 1, &Task_3_Handler, Task3_P);

	Log("Starting scheduler");

	vTaskStartScheduler();
}
/*-----------------------------------------------------------*/
volatile char *pcOverflowedTask = NULL; /* Prevent task name being optimised away. */
void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
{
	(void)pxTask;
	pcOverflowedTask = pcTaskName;
	vAssertCalled(__FILE__, __LINE__);
	for (;;)
		;
}
/*-----------------------------------------------------------*/

void vApplicationTickHook(void)
{
	// /* This function will be called by each tick interrupt if
	// configUSE_TICK_HOOK is set to 1 in FreeRTOSConfig.h.  User code can be
	// added here, but the tick hook is called from an interrupt context, so
	// code must not attempt to block, and only the interrupt safe FreeRTOS API
	// functions can be used (those that end in FromISR()). */
	Total_Ticks = (int)xTaskGetTickCount();
	Log("Tick %d,", Total_Ticks);
}
/*-----------------------------------------------------------*/

void vAssertCalled(const char *pcFile, uint32_t ulLine)
{
	volatile uint32_t ulSetTo1InDebuggerToExit = 0;

	taskENTER_CRITICAL();
	{
		while (ulSetTo1InDebuggerToExit == 0)
		{
			/* Nothing to do here.  Set the loop variable to a non zero value in
			the debugger to step out of this function to the point that caused
			the assertion. */
			(void)pcFile;
			(void)ulLine;
		}
	}
	taskEXIT_CRITICAL();
}
/*-----------------------------------------------------------*/

/* configUSE_STATIC_ALLOCATION is set to 1, so the application must provide an
implementation of vApplicationGetIdleTaskMemory() to provide the memory that is
used by the Idle task. */
void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize)
{
	/* If the buffers to be provided to the Idle task are declared inside this
	function then they must be declared static - otherwise they will be allocated on
	the stack and so not exists after this function exits. */
	static StaticTask_t xIdleTaskTCB;
	static StackType_t uxIdleTaskStack[configMINIMAL_STACK_SIZE];

	/* Pass out a pointer to the StaticTask_t structure in which the Idle task's
	state will be stored. */
	*ppxIdleTaskTCBBuffer = &xIdleTaskTCB;

	/* Pass out the array that will be used as the Idle task's stack. */
	*ppxIdleTaskStackBuffer = uxIdleTaskStack;

	/* Pass out the size of the array pointed to by *ppxIdleTaskStackBuffer.
	Note that, as the array is necessarily of type StackType_t,
	configMINIMAL_STACK_SIZE is specified in words, not bytes. */
	*pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

/*-----------------------------------------------------------*/
void prvSetupHardware(void)
{
	/* If running on Rev A2 silicon, turn the LDO voltage up to 2.75V.  This is
	a workaround to allow the PLL to operate reliably. */
	if (DEVICE_IS_REVA2)
	{
		SysCtlLDOSet(SYSCTL_LDO_2_75V);
	}

	/* Set the clocking to run from the PLL at 50 MHz */
	SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_8MHZ);

	/* Initialise the UART - QEMU usage does not seem to require this
	initialisation. */
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
	UARTEnable(UART0_BASE);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
	UARTEnable(UART1_BASE);
}
/*-----------------------------------------------------------*/
