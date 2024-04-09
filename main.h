/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#include "boards/bp-trf7970a/trf7970a.h"
#include "st25tb/st25tb_target.h"
//#define ST25TB_DO_NOT_WRITE_DANGEROUS_SECTOR
#include "st25tb/st25tb_initiator.h"
//#define CANARD_ENDORMI_FLAVOR

#define ST25TB_KIEMUL_LED_ANIMATION

#if defined(ST25TB_KIEMUL_LED_ANIMATION)
#define LED_ACTION_DELAY   15 // DO NOT TOUCH !
void LED_Startup();
void LED_ChangeMode();
#endif

bool MOD_Emulate_VirtualCard();
bool MOD_Write_VirtualToCard();
bool MOD_Read_CardToFlash();

typedef bool (* PMODE_FUNCTION) ();
typedef struct _KIEMUL_MODE {
    const PMODE_FUNCTION current;
    const struct _KIEMUL_MODE *prev;
    const struct _KIEMUL_MODE *next;
    const bool bLedGreen;
    const bool bLedRed;
} KIEMUL_MODE, PKIEMUL_MODE;
