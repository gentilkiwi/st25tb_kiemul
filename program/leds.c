/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "leds.h"

const LED LEDS[NB_LEDS] = {
#if defined(__MSP430FR2476__)
    // LEDS_MODES
    /* 0 */ {&P1OUT, BIT0}, // LED_MOD_GREEN
    /* 1 */ {&P5OUT, BIT1}, // LED_MOD_RED
    // LEDS_STATUS
    /* 0 */ {&P4OUT, BIT2}, // LED_STATUS_GREEN
    /* 1 */ {&P2OUT, BIT7}, // LED_STATUS_RED
    /* 2 */ {&P2OUT, BIT4}, // LED_STATUS_BLUE
#elif defined(__MSP430FR2676__)
    // LEDS_MODES
    /* 0 */ {&P1OUT, BIT7}, // LED_MOD_EMULATE
    /* 1 */ {&P1OUT, BIT0}, // LED_MOD_REWRITE
    /* 2 */ {&P1OUT, BIT1}, // LED_MOD_DETECT
    /* 3 */ {&P1OUT, BIT2}, // LED_MOD_LEARN
    /* 4 */ {&P1OUT, BIT3}, // LED_MOD_UNK
    // LEDS_SLOTS
    /* 0 */ {&P2OUT, BIT2}, // LED_SLOT0
    /* 1 */ {&P3OUT, BIT0}, // LED_SLOT1
    /* 2 */ {&P3OUT, BIT3}, // LED_SLOT2
    /* 3 */ {&P2OUT, BIT3}, // LED_SLOT3
    /* 4 */ {&P3OUT, BIT4}, // LED_SLOT4
    /* 5 */ {&P3OUT, BIT1}, // LED_SLOT5
    /* 6 */ {&P2OUT, BIT4}, // LED_SLOT6
    /* 7 */ {&P2OUT, BIT5}, // LED_SLOT7
    // LEDS_STATUS
    /* 0 */ {&P3OUT, BIT7}, // LED_STATUS_BLUE
    /* 1 */ {&P4OUT, BIT0}, // LED_STATUS_GREEN
    /* 2 */ {&P4OUT, BIT1}, // LED_STATUS_RED
#endif
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
