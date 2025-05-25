/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "leds.h"

const LED LEDS[NB_LEDS] = {
    // LEDS_MODES
    /* 0 */ {&P1OUT, BIT0}, // LED_MOD_GREEN
    /* 1 */ {&P5OUT, BIT1}, // LED_MOD_RED
    // LEDS_SLOTS
    // LEDS_STATUS
    /* 0 */ {&P4OUT, BIT2}, // LED_STATUS_GREEN
    /* 1 */ {&P2OUT, BIT7}, // LED_STATUS_RED
    /* 2 */ {&P2OUT, BIT4}, // LED_STATUS_BLUE
};

void LEDS_Bitmask(const LED *LEDS_ARRAY, const uint8_t nbLeds, uint8_t bitmask)
{
    uint8_t i;

    for(i = 0; i < nbLeds; i++, bitmask >>= 1)
    {
        if(bitmask & 0b00000001)
        {
            *LEDS_ARRAY[i].portOutput |= LEDS_ARRAY[i].bit;
        }
        else
        {
            *LEDS_ARRAY[i].portOutput &= ~LEDS_ARRAY[i].bit;
        }
    }
}

void LEDS_Animation()
{
    uint8_t i;

    for(i = 0; i < NB_LEDS; i++)
    {
        LED_ON(i);
        TIMER_delay_Milliseconds(10);
        LED_OFF(i);
    }
}
