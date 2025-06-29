/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#include "14a.h"

typedef struct _T3A_INFOS {
    uint16_t ATQA;
    uint8_t cbUID;
    uint8_t UID[10];
    uint8_t SAK;
} T3A_INFOS, *PT3A_INFOS;

void K14A3_TG_Prepare_AC_Buffer(const T3A_INFOS *pInfos);
uint8_t K14A3_TG_AC_AnswerTo(uint8_t *pbIsActivated);
void K14A3_TG_AC_BackToNormal();
