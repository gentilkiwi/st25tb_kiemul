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
#elif defined(__MSP430FR2673__)
    // LEDS_MODES
    /* 0 */ {&P1OUT, BIT5}, // LED_MOD_EMULATE
    /* 1 */ {&P1OUT, BIT6}, // LED_MOD_REWRITE
    /* 2 */ {&P1OUT, BIT7}, // LED_MOD_DETECT
    /* 3 */ {&P1OUT, BIT0}, // LED_MOD_LEARN
    /* 4 */ {&P1OUT, BIT1}, // LED_MOD_UNK
    // LEDS_SLOTS
    /* 0 */ {&P1OUT, BIT2}, // LED_SLOT0
    /* 1 */ {&P1OUT, BIT3}, // LED_SLOT1
    /* 2 */ {&P2OUT, BIT2}, // LED_SLOT2
    /* 3 */ {&P3OUT, BIT0}, // LED_SLOT3
    /* 4 */ {&P3OUT, BIT3}, // LED_SLOT4
    /* 5 */ {&P2OUT, BIT3}, // LED_SLOT5
    /* 6 */ {&P3OUT, BIT4}, // LED_SLOT6
    /* 7 */ {&P3OUT, BIT1}, // LED_SLOT7
    // LEDS_STATUS
    /* 0 */ {&P3OUT, BIT7}, // LED_STATUS_BLUE
    /* 1 */ {&P4OUT, BIT0}, // LED_STATUS_GREEN
    /* 2 */ {&P4OUT, BIT1}, // LED_STATUS_RED
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
#elif defined(STM32F405xx)
    // LEDS_MODES
    /* 0 */ {LED_MOD_EMULATE_GPIO_Port, LED_MOD_EMULATE_Pin},
    /* 1 */ {LED_MOD_REWRITE_GPIO_Port, LED_MOD_REWRITE_Pin},
    /* 2 */ {LED_MOD_DETECT_GPIO_Port, LED_MOD_DETECT_Pin},
    /* 3 */ {LED_MOD_LEARN_GPIO_Port, LED_MOD_LEARN_Pin},
    /* 4 */ {LED_MOD_UNK_GPIO_Port, LED_MOD_UNK_Pin},
    // LEDS_SLOTS
    /* 0 */ {LED_SLOT0_GPIO_Port, LED_SLOT0_Pin},
    /* 1 */ {LED_SLOT1_GPIO_Port, LED_SLOT1_Pin},
    /* 2 */ {LED_SLOT2_GPIO_Port, LED_SLOT2_Pin},
    /* 3 */ {LED_SLOT3_GPIO_Port, LED_SLOT3_Pin},
    /* 4 */ {LED_SLOT4_GPIO_Port, LED_SLOT4_Pin},
    /* 5 */ {LED_SLOT5_GPIO_Port, LED_SLOT5_Pin},
    /* 6 */ {LED_SLOT6_GPIO_Port, LED_SLOT6_Pin},
    /* 7 */ {LED_SLOT7_GPIO_Port, LED_SLOT7_Pin},
    // LEDS_STATUS
    /* 0 */ {LED_STATUS_BLUE_GPIO_Port, LED_STATUS_BLUE_Pin},
    /* 1 */ {LED_STATUS_GREEN_GPIO_Port, LED_STATUS_GREEN_Pin},
    /* 2 */ {LED_STATUS_RED_GPIO_Port, LED_STATUS_RED_Pin},
#elif defined(PICO_BOARD)
    // LEDS_MODES
    /* 0 */ {PIKO_GPIO_LED_MOD_EMULATE},  // LED_MOD_EMULATE
    /* 1 */ {PIKO_GPIO_LED_MOD_REWRITE},  // LED_MOD_REWRITE
    /* 2 */ {PIKO_GPIO_LED_MOD_DETECT},   // LED_MOD_DETECT
    /* 3 */ {PIKO_GPIO_LED_MOD_LEARN},    // LED_MOD_LEARN
    /* 4 */ {PIKO_GPIO_LED_MOD_UNK},      // LED_MOD_UNK
    // LEDS_SLOTS
    /* 0 */ {PIKO_GPIO_LED_SLOT0},        // LED_SLOT0
    /* 1 */ {PIKO_GPIO_LED_SLOT1},        // LED_SLOT1
    /* 2 */ {PIKO_GPIO_LED_SLOT2},        // LED_SLOT2
    /* 3 */ {PIKO_GPIO_LED_SLOT3},        // LED_SLOT3
    /* 4 */ {PIKO_GPIO_LED_SLOT4},        // LED_SLOT4
    /* 5 */ {PIKO_GPIO_LED_SLOT5},        // LED_SLOT5
    /* 6 */ {PIKO_GPIO_LED_SLOT6},        // LED_SLOT6
    /* 7 */ {PIKO_GPIO_LED_SLOT7},        // LED_SLOT7
    // LEDS_STATUS
    /* 0 */ {PIKO_GPIO_LED_STATUS_BLUE},  // LED_STATUS_BLUE
    /* 1 */ {PIKO_GPIO_LED_STATUS_GREEN}, // LED_STATUS_GREEN
    /* 2 */ {PIKO_GPIO_LED_STATUS_RED},   // LED_STATUS_RED
#endif
};

void LEDS_Bitmask(const LED *LEDS_ARRAY, const uint8_t nbLeds, uint8_t bitmask)
{
    uint8_t i;

    for(i = 0; i < nbLeds; i++, bitmask >>= 1)
    {
#if defined(__msp430)
        if(bitmask & 0b00000001)
        {
            *LEDS_ARRAY[i].portOutput |= LEDS_ARRAY[i].bit;
        }
        else
        {
            *LEDS_ARRAY[i].portOutput &= ~LEDS_ARRAY[i].bit;
        }
#elif defined(STM32F405xx)
        HAL_GPIO_WritePin(LEDS_ARRAY[i].portOutput, LEDS_ARRAY[i].bit, bitmask & 0b00000001);
#elif defined(PICO_BOARD)
        gpio_put(LEDS_ARRAY[i].gpio, bitmask & 0b00000001);
#endif
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
