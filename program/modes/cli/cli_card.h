/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#include "../cli.h"

//#define CLI_CARD_MORE_VERBOSE_OPERATIONS

extern const CLI_MODULE CLI_CARD_Module;

void CLI_CARD_load();
void CLI_CARD_show();
void CLI_CARD_dump();
void CLI_CARD_uid();
void CLI_CARD_rdbl();
void CLI_CARD_wrbl();

void CLI_CARD_write();
void CLI_CARD_tear();
