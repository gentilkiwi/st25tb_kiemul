#pragma once
#include <msp430.h>
#include <gpio.h>

#define LED1    GPIO_PORT_P1, GPIO_PIN0
#define LED2    GPIO_PORT_P4, GPIO_PIN7

#define D2      GPIO_PORT_P8, GPIO_PIN1
#define D3      GPIO_PORT_P2, GPIO_PIN3
#define D4      GPIO_PORT_P2, GPIO_PIN6

#define LED_ON(x)   GPIO_setOutputHighOnPin(x)
#define LED_OFF(x)  GPIO_setOutputLowOnPin(x)

extern void LED_init();
