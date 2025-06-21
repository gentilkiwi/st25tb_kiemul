/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#include "../cli.h"

#if defined(REFERENCES_DATA_READY)

extern const CLI_MODULE CLI_REF_Module;

void CLI_REF_info();
void CLI_REF_load();
void CLI_REF_show();
void CLI_REF_dump();

#endif
