/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#include "../lp-msp430.h"

/*
 *       |----|----|                    |----|----|
 *       | J1 | J3 |                    | J4 | J2 |
 *       |----|----|                    |----|----|
 * +3.3V |  1 | 21 | +5V           P5.2 | 40 | 20 | GND
 *  P1.6 |  2 | 22 | GND           P5.1 | 39 | 19 | P4.6
 *  P2.5 |  3 | 23 | P1.7          P5.0 | 38 | 18 | P2.1
 *  P2.6 |  4 | 24 | P4.3          P4.7 | 37 | 17 | P2.0
 *  P2.2 |  5 | 25 | P4.4          P6.0 | 36 | 16 | RST/SBWTDIO
 *  P5.4 |  6 | 26 | P5.3          P3.3 | 35 | 15 | P3.2
 *  P3.5 |  7 | 27 | P1.0          P6.1 | 34 | 14 | P3.6
 *  P4.5 |  8 | 28 | P1.1          P6.2 | 33 | 13 | P4.2
 *  P1.3 |  9 | 29 | P5.7          P4.1 | 32 | 12 | P2.7
 *  P1.2 | 10 | 30 | P3.7          P3.1 | 31 | 11 | P2.4
 *       |----|----|                    |----|----|
 */

// J1
#define LP_BP_HEADER_01    // +3.3V
#define LP_BP_HEADER_02    GPIO_PORT_P1, GPIO_PIN6 // P1.6 - Analog In
#define LP_BP_HEADER_03    GPIO_PORT_P2, GPIO_PIN5 // P2.5 - UART RX (-> MCU)
#define LP_BP_HEADER_04    GPIO_PORT_P2, GPIO_PIN6 // P2.6 - UART TX (<- MCU)
#define LP_BP_HEADER_05    GPIO_PORT_P2, GPIO_PIN2 // P2.2 - GPIO(!)
#define LP_BP_HEADER_06    GPIO_PORT_P5, GPIO_PIN4 // P5.4 - Analog In
#define LP_BP_HEADER_07    GPIO_PORT_P3, GPIO_PIN5 // P3.5 - SPI CLK
#define LP_BP_HEADER_08    GPIO_PORT_P4, GPIO_PIN5 // P4.5 - GPIO (!)
#define LP_BP_HEADER_09    GPIO_PORT_P1, GPIO_PIN3 // P1.3 - I2C SCL
#define LP_BP_HEADER_10    GPIO_PORT_P1, GPIO_PIN2 // P1.2 - I2C SDA
// J2
#define LP_BP_HEADER_20    // GND
#define LP_BP_HEADER_19    GPIO_PORT_P4, GPIO_PIN6 // P4.6 - GPIO(!)/PWM
#define LP_BP_HEADER_18    GPIO_PORT_P2, GPIO_PIN1 // P2.1 - GPIO(!)/SPI CS
#define LP_BP_HEADER_17    GPIO_PORT_P2, GPIO_PIN0 // P2.0 - GPIO/NC
#define LP_BP_HEADER_16    // RST/SBWTDIO
#define LP_BP_HEADER_15    GPIO_PORT_P3, GPIO_PIN2 // P3.2 - SPI MOSI
#define LP_BP_HEADER_14    GPIO_PORT_P3, GPIO_PIN6 // P3.6 - SPI MISO
#define LP_BP_HEADER_13    GPIO_PORT_P4, GPIO_PIN2 // P4.2 - GPIO(!)/SPI CS
#define LP_BP_HEADER_12    GPIO_PORT_P2, GPIO_PIN7 // P2.7 - GPIO(!)/SPI CS
#define LP_BP_HEADER_11    GPIO_PORT_P2, GPIO_PIN4 // P2.4 - GPIO(!)
// J3 - TODO
// J4 - TODO

#define LP_LED1            GPIO_PORT_P1, GPIO_PIN0 // P1.0
#define LP_LED2_RED        GPIO_PORT_P5, GPIO_PIN1 // P5.1
#define LP_LED2_GREEN      GPIO_PORT_P5, GPIO_PIN0 // P5.0
#define LP_LED2_BLUE       GPIO_PORT_P4, GPIO_PIN7 // P4.7

#define LP_LED2            LP_LED2_RED // to be compatible

#define LP_LED_GREEN       LP_LED1
#define LP_LED_RED         LP_LED2

#define LP_S1              GPIO_PORT_P4, GPIO_PIN0 // P4.0
#define LP_S2              GPIO_PORT_P2, GPIO_PIN3 // P2.3

#define LP_XT1_FREQ        32768 // XT1 is not connected ! - use internal
#define LP_XT1_IN          GPIO_PORT_P2, GPIO_PIN1 // P2.1
#define LP_XT1_OUT         GPIO_PORT_P2, GPIO_PIN0 // P2.0

#define LP_MCU_FREQ        16000000

#define LP_TIMER_A_MICRO_DIVISOR TIMER_A_CLOCKSOURCE_DIVIDER_16  // at 16 MHz -> 1
#define LP_TIMER_A_MICRO_MULTIPL 1

#define LP_BP_HEADER_09_SET() P1OUT |= BIT3
#define LP_BP_HEADER_09_CLR() P1OUT &= ~BIT3
#define LP_BP_HEADER_18_VAL() (P2IN & BIT1)

#if defined(KIWI_LIGHT_PCB)
/*
 * 1. This temporary card is using a MSP430FR2476TRHB* instead of MSP430FR2476TRHA*
 * So: PIN used by LP_LED2 (R, G, B) are *NOT* available, I use P1.1 instead here
 *
 * 2. I switched Green and Red LED in the BoosterPack part (oups)
 *
 * Below defines are here to fix on this particular card (~ only for me) by defining KIWI_LIGHT_PCB
 *
 */
#undef  LP_LED2
#define LP_LED2            GPIO_PORT_P1, GPIO_PIN1 // P1.1

#undef  LP_BP_HEADER_12
#define LP_BP_HEADER_12    GPIO_PORT_P4, GPIO_PIN2 // P4.2 - GPIO(!)/SPI CS

#undef  LP_BP_HEADER_13
#define LP_BP_HEADER_13    GPIO_PORT_P2, GPIO_PIN7 // P2.7 - GPIO(!)/SPI CS

#endif
