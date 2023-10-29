/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#include "driverlib.h"
#if defined(__MSP430F5529__)
#include "lp-msp430f5529/lp-msp430f5529.h"
#elif defined(__MSP430FR2476__)
#include "lp-msp430fr2476/lp-msp430fr2476.h"
#else
#error Target is not supported !
#endif

#define LP_BP_UART_RX          LP_BP_HEADER_03
#define LP_BP_UART_TX          LP_BP_HEADER_04

#define LP_BP_HEADER_SPI_MOSI  LP_BP_HEADER_15
#define LP_BP_HEADER_SPI_MISO  LP_BP_HEADER_14
#define LP_BP_HEADER_SPI_CLK   LP_BP_HEADER_07

#define LP_BP_HEADER_I2C_SCL   LP_BP_HEADER_09
#define LP_BP_HEADER_I2C_SDA   LP_BP_HEADER_10

extern volatile bool g_irq_Timer_TimeOut, g_button_LP_S1_pressed, g_button_LP_S2_pressed;
// TODO: better
extern volatile bool g_trf7970a_irq_flag;

void LP_init();

inline void LP_TIMER_Disable();
void LP_TIMER_StartTimer_internal(uint16_t n_unit_ms); // max is UINT16_MAX ( 1985 ms * 33 = ~ UINT16_MAX )
void LP_TIMER_delay_Millisecond_internal(uint16_t n_unit_ms); // max is UINT16_MAX ( 1985 ms * 33 = ~ UINT16_MAX )
inline void LP_TIMER_delay_Microsecond_internal(uint16_t n_unit_us); // see implementations

#define LP_TIMER_StartTimer(n_ms)           LP_TIMER_StartTimer_internal(timeout_ms * 33)
#define LP_TIMER_delay_Millisecond(n_ms)    LP_TIMER_delay_Millisecond_internal(n_ms * 33)
#define LP_TIMER_delay_Microsecond(n_us)    LP_TIMER_delay_Microsecond_internal(n_us * LP_TIMER_A_MICRO_MULTIPL)

void LP_SPI_init(uint32_t desiredSpiClock);
inline void LP_SPI_sendByte(uint8_t data);
inline uint8_t LP_SPI_receiveByte();

#define LED_ON(x)      GPIO_setOutputHighOnPin(x)
#define LED_OFF(x)     GPIO_setOutputLowOnPin(x)
#define LED_TOGGLE(x)  GPIO_toggleOutputOnPin(x)
#define LED_SET(led, bIsOn) (bIsOn ? GPIO_setOutputHighOnPin : GPIO_setOutputLowOnPin)(led);

void LP_BUTTON_WaitFor_LP_S1();
void LP_BUTTON_WaitFor_LP_S2();
bool LP_BUTTON_WaitFor_LP_S1_or_LP_S2(); // LP_S1, true, LP_S2, false
