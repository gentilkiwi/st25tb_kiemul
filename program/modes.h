/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#include "board.h"

typedef void (* PMODE_FUNCTION) ();
typedef struct _KAKI_MODE {
    const PMODE_FUNCTION function;
    const uint8_t ledsModesBitmask;
    const char* Name;
} KAKI_MODE, *PKAKI_MODE;

#include "st25tb/st25tb.h"

#include "modes/emulate.h"
#include "modes/rewrite.h"
#include "modes/detect.h"
#include "modes/select.h"
#include "modes/learn.h"
#include "modes/unk.h"
#include "modes/tear.h"
#include "modes/field.h"
#include "modes/cli.h"
