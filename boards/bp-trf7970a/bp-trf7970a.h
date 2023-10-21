/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#include "../lp-msp430.h"

//#define BP_LED1            // always powered
#define BP_LED2            LP_BP_HEADER_11
#define BP_LED3            LP_BP_HEADER_12
#define BP_LED4            LP_BP_HEADER_13

#define BP_TRF_SPI_MOSI    LP_BP_HEADER_15
#define BP_TRF_SPI_MISO    LP_BP_HEADER_14
#define BP_TRF_SPI_CLK     LP_BP_HEADER_07
#define BP_TRF_SPI_CS      LP_BP_HEADER_09
#define BP_TRF_EN          LP_BP_HEADER_10
#define BP_TRF_IRQ         LP_BP_HEADER_18

#define BP_TRF_SPI_FREQ    4000000

#define BP_TRF_EN_ENABLE()        GPIO_setOutputHighOnPin(BP_TRF_EN);
#define BP_TRF_EN_DISABLE()       GPIO_setOutputLowOnPin(BP_TRF_EN);

#define BP_TRF_SPI_CS_ENABLE()    GPIO_setOutputLowOnPin(BP_TRF_SPI_CS)
#define BP_TRF_SPI_CS_DISABLE()   GPIO_setOutputHighOnPin(BP_TRF_SPI_CS)

#define BP_IRQ_SOURCE_NONE                 0x00
#define BP_IRQ_SOURCE_TRF7970A             0x01
#define BP_IRQ_SOURCE_LP_S1                0x02
#define BP_IRQ_SOURCE_LP_S2                0x04
#define BP_IRQ_SOURCE_TIMER                0x08
#define BP_IRQ_SOURCE_ST25TB_PROTOCOL_ERR  0x10

#define BP_LED_BLUE        BP_LED2
#define BP_LED_RED         BP_LED3
#define BP_LED_GREEN       BP_LED4

void BP_init();
uint8_t BP_Wait_for_Buttons_or_TRF7970A(uint8_t *pTRF7970A_irqStatus);
uint8_t BP_Wait_for_Buttons_or_TRF7970A_or_Timeout(uint8_t *pTRF7970A_irqStatus, uint16_t timeout_ms);
uint8_t BP_Wait_for_Buttons();
