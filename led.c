#include "led.h"

void LED_init()
{
    GPIO_setAsOutputPin(LED1);
    GPIO_setAsOutputPin(LED2);

    GPIO_setAsOutputPin(D2);
    GPIO_setAsOutputPin(D3);
    GPIO_setAsOutputPin(D4);

    LED_OFF(LED1);
    LED_OFF(LED2);

    LED_OFF(D2);
    LED_OFF(D3);
    LED_OFF(D4);
}
