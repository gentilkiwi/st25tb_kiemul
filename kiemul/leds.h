/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#include "board.h"

typedef struct _LED {
    volatile unsigned char *portOutput;
    uint8_t bit;
} LED, *PLED;

extern const LED LEDS[];

#define LEDS_MODES      LEDS
#define NB_LEDS_MODES   2
//#define LEDS_SLOTS      LEDS_MODES + NB_LEDS_MODES
#define NB_LEDS_SLOTS   0
#define LEDS_STATUS     LEDS_MODES + NB_LEDS_MODES
#define NB_LEDS_STATUS  3

// No LEDS_Init(), handled in board.c
void LEDS_Bitmask(const LED *LEDS_ARRAY, const uint8_t nbLeds, uint8_t bitmask);
void LEDS_Animation();

#define LEDS_MODES_Bitmask(bitmask) LEDS_Bitmask(LEDS_MODES, NB_LEDS_MODES, bitmask)
#define LEDS_SLOTS_Bitmask(bitmask) //
#define LEDS_STATUS_Bitmask(bitmask) LEDS_Bitmask(LEDS_STATUS, NB_LEDS_STATUS, bitmask)

#define LED_Slot(index) LEDS_SLOTS_Bitmask(1 << index)

#define LED_INDEX_STATUS_BLUE       NB_LEDS_MODES + NB_LEDS_SLOTS + 2
#define LED_INDEX_STATUS_GREEN      NB_LEDS_MODES + NB_LEDS_SLOTS + 0
#define LED_INDEX_STATUS_RED        NB_LEDS_MODES + NB_LEDS_SLOTS + 1

#define LED_ON(index)                LED_ON_internal(LEDS[index].portOutput, LEDS[index].bit)
#define LED_OFF(index)               LED_OFF_internal(LEDS[index].portOutput, LEDS[index].bit)
#define LED_TOGGLE(index)            LED_TOGGLE_internal(LEDS[index].portOutput, LEDS[index].bit)

#define LED_ON_internal(p, b)       *p |= b
#define LED_OFF_internal(p, b)      *p &= ~b
#define LED_TOGGLE_internal(p, b)   *p ^= b
