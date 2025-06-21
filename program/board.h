/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#include <msp430.h>
#include <stdint.h>
#include <string.h>

#if defined(__MSP430FR2476__)
#define ST25TB_BOARD_NAME       "ST25TB kiemul"
#define ST25TB_BOARD_VERSION    "0.1"
#define ST25TB_MCU_NAME         "MSP430FR2476"
#elif defined(__MSP430FR2676__)
#define ST25TB_BOARD_NAME       "ST25TB kiwi"
#define ST25TB_BOARD_VERSION    "0.1"
#define ST25TB_MCU_NAME         "MSP430FR2676"
#else
#error unknown board?
#endif

#include "uart.h"
#include "slots.h"
#include "references.h"
#include "leds.h"
#include "trf7970a.h"

extern volatile uint8_t IRQ_Global;
extern char UART_RX_BUFFER[0x300];
extern uint16_t cbRxBuffer;

void BOARD_init();

void ADC_TEMP_Enable();
void ADC_TEMP_Disable();
uint16_t ADC_TEMP_Get_RAW();
int16_t ADC_TEMP_Get();

uint16_t RAND_Generate();
uint16_t CRC16_CCIT(const uint8_t *data, uint16_t cbData);

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
#define IRQ_SOURCE_UART_RX              0x20

uint8_t IRQ_Wait_for(uint8_t IRQWanted, uint8_t *pTRF7970A_irqStatus, uint16_t timeout_ms);

#define count_of(a) (sizeof(a)/sizeof((a)[0]))

#define SW1_IS_PRESSED()                (!(SW1_PORT & SW1_BIT))
#define SW2_IS_PRESSED()                (!(SW2_PORT & SW2_BIT))

#define UART_ENABLE_RX_IRQ()            do{ UCA0IE = UCRXIE_1 ;} while(0)
#define UART_DISABLE_RX_IRQ()           do{ UCA0IE = 0; } while(0)

#define CRC_VALUE                       (*(uint16_t *)(TLVMEM_START + 0x02))
#define DEVICE_ID                       (*(uint16_t *)(TLVMEM_START + 0x04))

#define DIE_LOT_WAFER_ID                (*(uint32_t *)(TLVMEM_START + 0x0a))
#define DIE_LOT_WAFER_X_POS             (*(uint16_t *)(TLVMEM_START + 0x0e))
#define DIE_LOT_WAFER_Y_POS             (*(uint16_t *)(TLVMEM_START + 0x10))

#define CALADC_15V_30C                  (*(uint16_t *)(TLVMEM_START + 0x1a))
#define CALADC_15V_105C                 (*(uint16_t *)(TLVMEM_START + 0x1c))

#if defined(__MSP430FR2476__)
#define SW1_PORT                        P4IN
#define SW1_BIT                         BIT0

#define SW2_PORT                        P2IN
#define SW2_BIT                         BIT3

#define TRF_CS_PORT                     P1OUT
#define TRF_CS_BIT                      BIT3

#define TRF_EN_PORT                     P1OUT
#define TRF_EN_BIT                      BIT2

#define TRF_IRQ_PORT                    P2IN
#define TRF_IRQ_IFG                     P2IFG
#define TRF_IRQ_IE                      P2IE
#define TRF_IRQ_BIT                     BIT1
#elif defined(__MSP430FR2676__)
#define SW1_PORT                        P1IN
#define SW1_BIT                         BIT6

#define SW2_PORT                        P4IN
#define SW2_BIT                         BIT2

#define TRF_CS_PORT                     P2OUT
#define TRF_CS_BIT                      BIT0

#define TRF_EN_PORT                     P2OUT
#define TRF_EN_BIT                      BIT7

#define TRF_IRQ_PORT                    P2IN
#define TRF_IRQ_IFG                     P2IFG
#define TRF_IRQ_IE                      P2IE
#define TRF_IRQ_BIT                     BIT1
#endif
