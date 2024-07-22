#ifndef CAEOS_PROJECT_MYUTILS_H
#define CAEOS_PROJECT_MYUTILS_H

#include "hw_memmap.h"
#include "hw_types.h"
#include "hw_sysctl.h"
#include "hw_uart.h"
#include "sysctl.h"
#include "gpio.h"
#include "grlib.h"
#include "osram128x64x4.h"
#include "rit128x96x4.h"
#include "uart.h"

#define IMAGE_WIDTH 128
#define IMAGE_HEIGHT 64

static void print(const char *src) {
    if (!src || !*src ) {
        UARTCharPut(UART0_BASE, '\n');
        return;
    }
    while (*src) {
        UARTCharPut(UART0_BASE, *src);
        src++;
    }
}

static void input(const char *prompt, char *dst, int size) {
    print(prompt);
    char *p = dst;
    char c;
    do {
        c = (char)UARTCharGet(UART0_BASE);
        if (c == '\r' || c == '\n') { // Check for newline characters
            break;
        }
        *(p++) = c;
    } while ((size == -1 || (p - dst) < size - 1) && UARTCharsAvail(UART0_BASE)); // -1 to reserve space for null terminator
    *p = 0; // Null terminate the string
}


#endif //CAEOS_PROJECT_MYUTILS_H
