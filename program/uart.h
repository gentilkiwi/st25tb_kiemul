/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#include "board.h"
#if defined(ST25TB_HAVE_CLI)

#if !defined(__int64_t_defined)
#  define __int64_t_defined 1
#endif
#if !defined(__have_longlong64)
#  define __have_longlong64 1
#endif


#include <stdio.h>
#include <inttypes.h>

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
