/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#if defined(STM32F405xx)
#include "usbd_cdc_if.h"
#include "main.h"
#else
#include <msp430.h>
#endif
#include <stdint.h>
#include <string.h>

#if defined(__MSP430FR2476__)
#define ST25TB_BOARD_NAME       "ST25TB kiemul"
#define ST25TB_MCU_NAME         "MSP430FR2476"

#define ST25TB_HAVE_CLI
#elif defined(__MSP430FR2673__)
#define ST25TB_BOARD_NAME       "ST25TB kameleon"
#define ST25TB_MCU_NAME         "MSP430FR2673"

#define ST25TB_HAVE_FULL_LEDS
#elif defined(__MSP430FR2676__)
#define ST25TB_BOARD_NAME       "ST25TB kiwi"
#define ST25TB_MCU_NAME         "MSP430FR2676"

#define ST25TB_HAVE_CLI
#define ST25TB_HAVE_FULL_LEDS
#elif defined(STM32F405xx)
#define ST25TB_BOARD_NAME       "ST25TB kameleon"
#define ST25TB_MCU_NAME         "HydraBus (STM32F405)"

#define ST25TB_HAVE_CLI
#define ST25TB_HAVE_FULL_LEDS
#else
#error unknown board?
#endif
#define ST25TB_FW_VERSION       "2.2"

#include "uart.h"
#include "slots.h"
#include "references.h"
#include "leds.h"
#include "trf7970a.h"

#if defined(ST25TB_HAVE_CLI)
extern char UART_RX_BUFFER[0x300];
extern uint16_t cbRxBuffer;
int16_t ADC_TEMP_Get();
uint16_t CRC16_CCIT(const uint8_t *data, uint16_t cbData);
#endif

extern volatile uint8_t IRQ_Global;

void TIMER_delay_Milliseconds_internal(uint16_t n_unit_ms);
void TIMER_start_Milliseconds_internal(uint16_t n_unit_ms);
void TIMER_delay_Microseconds_internal(uint16_t n_unit_us);

#define IRQ_SOURCE_NONE                 0x00
#define IRQ_SOURCE_TRF7970A             0x01
#define IRQ_SOURCE_SW1                  0x02
#define IRQ_SOURCE_SW2                  0x04
#define IRQ_SOURCE_TIMER                0x08
#define IRQ_SOURCE_ST25TB_PROTOCOL_ERR  0x10
#if defined(ST25TB_HAVE_CLI)
#define IRQ_SOURCE_UART_RX              0x20
#endif

uint8_t IRQ_Wait_for(uint8_t IRQWanted, uint8_t *pTRF7970A_irqStatus, uint16_t timeout_ms);
#define count_of(a) (sizeof(a)/sizeof((a)[0]))

#if defined(__msp430)
void BOARD_init();
uint16_t RAND_Generate();
#define MCU_RESET()                     WDTCTL = 0xcafe;

#define TIMER_stop()                    TA0CTL &= ~(TAIE | MC)
#define TIMER_delay_Milliseconds(n_ms)  TIMER_delay_Milliseconds_internal((n_ms) * 33) // max is UINT16_MAX ( 1985 ms * 33 = ~ UINT16_MAX )
#define TIMER_start_Milliseconds(n_ms)  TIMER_start_Milliseconds_internal((n_ms) * 33) // max is UINT16_MAX ( 1985 ms * 33 = ~ UINT16_MAX )
#define TIMER_delay_Microseconds(n_us)  TIMER_delay_Microseconds_internal((n_us) * 2)  // max is UINT16_MAX ( 32767 us * 2 = ~ UINT16_MAX )

#define SW1_IS_PRESSED()                (!(SW1_PORT & SW1_BIT))
#define SW2_IS_PRESSED()                (!(SW2_PORT & SW2_BIT))

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
#elif defined(__MSP430FR2673__)
#define SW1_PORT                        P1IN
#define SW1_BIT                         BIT4

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

#if defined(ST25TB_HAVE_CLI)
#define UART_ENABLE_RX_IRQ()            do{ UCA0IE = UCRXIE_1 ;} while(0)
#define UART_DISABLE_RX_IRQ()           do{ UCA0IE = 0; } while(0)

#define CRC_VALUE                       (*(uint16_t *)(TLVMEM_START + 0x02))
#define DEVICE_ID                       (*(uint16_t *)(TLVMEM_START + 0x04))

#define DIE_LOT_WAFER_ID                (*(uint32_t *)(TLVMEM_START + 0x0a))
#define DIE_LOT_WAFER_X_POS             (*(uint16_t *)(TLVMEM_START + 0x0e))
#define DIE_LOT_WAFER_Y_POS             (*(uint16_t *)(TLVMEM_START + 0x10))

#define CALADC_15V_30C                  (*(uint16_t *)(TLVMEM_START + 0x1a))
#define CALADC_15V_105C                 (*(uint16_t *)(TLVMEM_START + 0x1c))
#endif

#define __emptyloop()   __low_power_mode_0()

#elif defined(STM32F405xx)
extern volatile uint8_t isUSBCDCWanted;

extern SPI_HandleTypeDef hspi2;
extern TIM_HandleTypeDef htim6;
extern RNG_HandleTypeDef hrng;
extern ADC_HandleTypeDef hadc1;
extern USBD_HandleTypeDef hUsbDeviceFS;

#define SPI_INTERNAL_HANDLE		(&hspi2)
#define TIMER_INTERNAL_HANDLE	(&htim6)

#define BOARD_init()
#define RAND_Generate() HAL_RNG_GetRandomNumber(&hrng) //rand()
#define MCU_RESET()		HAL_NVIC_SystemReset()

#define TIMER_stop()                      	HAL_TIM_Base_Stop_IT(TIMER_INTERNAL_HANDLE)
#define TIMER_delay_Milliseconds(n_ms)      TIMER_delay_Milliseconds_internal((n_ms) * 100)
#define TIMER_start_Milliseconds(n_ms)  	TIMER_start_Milliseconds_internal((n_ms) * 100)
#define TIMER_delay_Microseconds(n_us)      TIMER_delay_Microseconds_internal((n_us) * 84)

#define SW1_IS_PRESSED()                (HAL_GPIO_ReadPin(K1_GPIO_Port, K1_Pin) == GPIO_PIN_SET)
#define SW2_IS_PRESSED()                (HAL_GPIO_ReadPin(UBTN_GPIO_Port, UBTN_Pin) == GPIO_PIN_SET)

extern char UART_RX_BUFFER[0x300];
extern uint16_t cbRxBuffer;

#if defined(ST25TB_HAVE_CLI)
#define UART_ENABLE_RX_IRQ()            isUSBCDCWanted = 1
#define UART_DISABLE_RX_IRQ()           isUSBCDCWanted = 0
#endif

//#define __low_power_mode_0              tight_loop_contents
#define __no_operation()                __asm__("nop")
#define __emptyloop()
//extern int __flash_binary_start, __flash_binary_end;
#endif
