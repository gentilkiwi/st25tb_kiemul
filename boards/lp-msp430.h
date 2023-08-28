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

void LP_init();

void LP_timerInit(uint16_t timeout_ms);
void LP_timerDisable();
void LP_delayMillisecond(uint32_t n_ms);
void LP_delayMicrosecond(uint32_t n_us);

void LP_SPI_init(uint32_t desiredSpiClock);
void LP_SPI_sendByte(uint8_t data);
uint8_t LP_SPI_receiveByte();

#define LED_ON(x)      GPIO_setOutputHighOnPin(x)
#define LED_OFF(x)     GPIO_setOutputLowOnPin(x)
#define LED_TOGGLE(x)  GPIO_toggleOutputOnPin(x)
#define LED_SET(led, bIsOn) (bIsOn ? GPIO_setOutputHighOnPin : GPIO_setOutputLowOnPin)(led);

void LP_BUTTON_WaitFor_LP_S1();
void LP_BUTTON_WaitFor_LP_S2();
bool LP_BUTTON_WaitFor_LP_S1_or_LP_S2(); // LP_S1, true, LP_S2, false

// TODO: better
extern volatile bool g_trf7970a_irq_flag;


#define DEBUG_PIN               LP_BP_HEADER_19
