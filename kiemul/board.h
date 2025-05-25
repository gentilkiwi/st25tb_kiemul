/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#include <msp430fr2476.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "slots.h"
#include "references.h"
#include "leds.h"
#include "trf7970a.h"
#include "uart.h"

extern volatile uint8_t IRQ_Global;

void BOARD_init();

uint16_t RAND_Generate();

#define TIMER_stop()                    TA0CTL &= ~(TAIE | MC)
#define TIMER_delay_Milliseconds(n_ms)  TIMER_delay_Milliseconds_internal((n_ms) * 33)
#define TIMER_start_Milliseconds(n_ms)  TIMER_start_Milliseconds_internal((n_ms) * 33)
#define TIMER_delay_Microseconds(n_us)  TIMER_delay_Microseconds_internal((n_us) * 2)

void TIMER_delay_Milliseconds_internal(uint16_t n_unit_ms); // max is UINT16_MAX ( 1985 ms * 33 = ~ UINT16_MAX )
void TIMER_start_Milliseconds_internal(uint16_t n_unit_ms); // max is UINT16_MAX ( 1985 ms * 33 = ~ UINT16_MAX )
void TIMER_delay_Microseconds_internal(uint16_t n_unit_us); // max is UINT16_MAX ( 32767 us * 2 = ~ UINT16_MAX )

#define IRQ_SOURCE_NONE                 0x00
#define IRQ_SOURCE_TRF7970A             0x01
#define IRQ_SOURCE_SW1                  0x02
#define IRQ_SOURCE_SW2                  0x04
#define IRQ_SOURCE_TIMER                0x08
#define IRQ_SOURCE_ST25TB_PROTOCOL_ERR  0x10

uint8_t IRQ_Wait_for(uint8_t IRQWanted, uint8_t *pTRF7970A_irqStatus, uint16_t timeout_ms);

#define count_of(a) (sizeof(a)/sizeof((a)[0]))

#define TRF_CS_PORT     P1OUT
#define TRF_CS_BIT      BIT3

#define TRF_EN_PORT     P1OUT
#define TRF_EN_BIT      BIT2

#define TRF_IRQ_PORT    P2IN
#define TRF_IRQ_IFG     P2IFG
#define TRF_IRQ_IE      P2IE
#define TRF_IRQ_BIT     BIT1
