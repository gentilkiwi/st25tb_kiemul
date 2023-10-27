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
 * +3.3V |  1 | 21 | +5V           P2.5 | 40 | 20 | GND
 *  P6.5 |  2 | 22 | GND           P2.4 | 39 | 19 | P2.0
 *  P3.4 |  3 | 23 | P6.0          P1.5 | 38 | 18 | P2.2
 *  P3.3 |  4 | 24 | P6.1          P1.4 | 37 | 17 | P7.4
 *  P1.6 |  5 | 25 | P6.2          P1.3 | 36 | 16 | RST/SBWTDIO
 *  P6.6 |  6 | 26 | P6.3          P1.2 | 35 | 15 | P3.0
 *  P3.2 |  7 | 27 | P6.4          P4.3 | 34 | 14 | P3.1
 *  P2.7 |  8 | 28 | P7.0          P4.0 | 33 | 13 | P2.6
 *  P4.2 |  9 | 29 | P3.6          P3.7 | 32 | 12 | P2.3
 *  P4.1 | 10 | 30 | P3.5          P8.2 | 31 | 11 | P8.1
 *       |----|----|                    |----|----|
 */

// J1
#define LP_BP_HEADER_01    // +3.3V
#define LP_BP_HEADER_02    GPIO_PORT_P6, GPIO_PIN5 // P6.5 - Analog In
#define LP_BP_HEADER_03    GPIO_PORT_P3, GPIO_PIN4 // P3.4 - UART RX (-> MCU)
#define LP_BP_HEADER_04    GPIO_PORT_P3, GPIO_PIN3 // P3.3 - UART TX (<- MCU)
#define LP_BP_HEADER_05    GPIO_PORT_P1, GPIO_PIN6 // P1.6 - GPIO(!)
#define LP_BP_HEADER_06    GPIO_PORT_P6, GPIO_PIN6 // P6.6 - Analog In
#define LP_BP_HEADER_07    GPIO_PORT_P3, GPIO_PIN2 // P3.2 - SPI CLK
#define LP_BP_HEADER_08    GPIO_PORT_P2, GPIO_PIN7 // P2.7 - GPIO (!)
#define LP_BP_HEADER_09    GPIO_PORT_P4, GPIO_PIN2 // P4.2 - I2C SCL
#define LP_BP_HEADER_10    GPIO_PORT_P4, GPIO_PIN1 // P4.1 - I2C SDA
// J2
#define LP_BP_HEADER_20    // GND
#define LP_BP_HEADER_19    GPIO_PORT_P2, GPIO_PIN0 // P2.0 - GPIO(!)/PWM
#define LP_BP_HEADER_18    GPIO_PORT_P2, GPIO_PIN2 // P2.2 - GPIO(!)/SPI CS
#define LP_BP_HEADER_17    GPIO_PORT_P7, GPIO_PIN4 // P7.4 - GPIO/NC
#define LP_BP_HEADER_16    // RST/SBWTDIO
#define LP_BP_HEADER_15    GPIO_PORT_P3, GPIO_PIN0 // P3.0 - SPI MOSI
#define LP_BP_HEADER_14    GPIO_PORT_P3, GPIO_PIN1 // P3.1 - SPI MISO
#define LP_BP_HEADER_13    GPIO_PORT_P2, GPIO_PIN6 // P2.6 - GPIO(!)/SPI CS
#define LP_BP_HEADER_12    GPIO_PORT_P2, GPIO_PIN3 // P2.3 - GPIO(!)/SPI CS
#define LP_BP_HEADER_11    GPIO_PORT_P8, GPIO_PIN1 // GPIO(!)
// J3 - TODO
// J4 - TODO

#define LP_LED1            GPIO_PORT_P1, GPIO_PIN0 // P1.0
#define LP_LED2            GPIO_PORT_P4, GPIO_PIN7 // P4.7

#define LP_LED_GREEN       LP_LED2
#define LP_LED_RED         LP_LED1

#define LP_S1              GPIO_PORT_P2, GPIO_PIN1 // P2.1
#define LP_S2              GPIO_PORT_P1, GPIO_PIN1 // P1.1

#define LP_XT1_FREQ        32768
#define LP_XT1_IN          GPIO_PORT_P5, GPIO_PIN4 // P5.4
#define LP_XT1_OUT         GPIO_PORT_P5, GPIO_PIN5 // P5.5

#define LP_XT2_FREQ        4000000
#define LP_XT2_IN          GPIO_PORT_P5, GPIO_PIN2 // P5.2
#define LP_XT2_OUT         GPIO_PORT_P5, GPIO_PIN3 // P5.3

#define LP_MCU_FREQ        25000000

#define LP_TIMER_A_MICRO_DIVISOR TIMER_A_CLOCKSOURCE_DIVIDER_5  // at 25 MHz -> 5
#define LP_TIMER_A_MICRO_MULTIPL 5
