/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#include "st25tb.h"

#define ST25TB_CARDS_INDEX_SYSTEM  0x80
#define ST25TB_CARDS_INDEX_UID     0x81
#define ST25TB_CARDS_INDEX_UID_2   0x82

extern uint8_t ST25TB_CARDS_CurrentCard[0x80 + 1 + 2][4];

void ST25TB_CARDS_toSlot(uint8_t slotNumber);
void ST25TB_CARDS_fromSlot(uint8_t slotNumber); // 76 bytes :')
