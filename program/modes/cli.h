/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#include <stdlib.h>
#include "../modes.h"

typedef struct _CLI_FUNCTION {
    const char *name;
    const PMODE_FUNCTION function;
    const char *description;
} CLI_FUNCTION, *PCLI_FUNCTION;

typedef struct _CLI_MODULE {
    const char *name;
    const char *description;
    const uint16_t nbFunctions;
    const CLI_FUNCTION *Functions;
} CLI_MODULE, *PCLI_MODULE;

void MODE_cli();
_CODE_ACCESS char *CLI_NextArg();
void CLI_BASE64_kprint(const uint8_t *src, uint16_t srclen);
int16_t CLI_BASE64_decode(const char *src, uint16_t srclen, uint8_t *dst);
void CLI_print_status(const uint8_t ret);
uint8_t CLI_BlockNumber_Value(const char *strToken, uint8_t *pBlockNumber, uint8_t Value[4]);
