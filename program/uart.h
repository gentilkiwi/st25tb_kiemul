/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#include <msp430.h>
#include <stdint.h>
#if !defined(__MSP430FR2673__)
#include <stdio.h>

extern uint8_t UART_Enabled;

#define UART_NEWLINE    "\r\n"

void UART_TX(const uint8_t transmitData);
void UART_Redirect_std();
void kprinthex(const void *lpData, const uint16_t cbData);

#define kprintf(...)    do{ if(UART_Enabled) printf(__VA_ARGS__); } while(0)
#else
#define UART_Enabled    0
#define printf(...)
#define kprintf(...)
#endif
