/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "cli_std.h"

void CLI_STD_test();

const CLI_FUNCTION CLI_STD_Functions[] = {
    {.name = "cls",     .function = CLI_STD_cls,            .description = "Clear screen"},
    {.name = "reboot",  .function = CLI_STD_reboot,         .description = "Restart the chip"},
    {.name = "coffee",  .function = CLI_STD_coffee,         .description = "Please, make me a coffee!"},
    {.name = "answer",  .function = CLI_STD_answer,         .description = "Answer to the Ultimate Question of Life, the Universe, and Everything"},
    {.name = "temp",    .function = CLI_STD_temperature,    .description = "Get the internal temperature"},
    {.name = "leds",    .function = LEDS_Animation,         .description = "LEDS animation"},
    {.name = "mem",     .function = CLI_STD_memory,         .description = "Raw memory dump (maybe dangerous?)"},
//  {.name = "test",    .function = CLI_STD_test,           .description = "Test routine (you don\'t want to see this !)"},
};

const CLI_MODULE CLI_STD_Module = {.name = "std", .description = "Basic commands", .nbFunctions = count_of(CLI_STD_Functions), .Functions = CLI_STD_Functions};

const char CLS[] = "\x1b[2J\x1b[3J\x1b[H";
const char COFFEE[] = UART_NEWLINE "    ( (" UART_NEWLINE "     ) )" UART_NEWLINE "  .______." UART_NEWLINE "  |      |]" UART_NEWLINE "  \\      /" UART_NEWLINE "   `----'" UART_NEWLINE;
const char ANSWER[] = "42." UART_NEWLINE;

void CLI_STD_cls()
{
    printf(CLS);
}

void CLI_STD_reboot()
{
    WDTCTL = 0xcafe;
}

void CLI_STD_coffee()
{
    printf(COFFEE);
}

void CLI_STD_answer()
{
    printf(ANSWER);
}

void CLI_STD_temperature()
{
    uint8_t i;
    uint16_t degC;

    ADC_TEMP_Enable();

    for (i = 0; i < 50; i++)
    {
        ADC_TEMP_Get_RAW();
    }

    degC = ADC_TEMP_Get();
    printf("%i.%hu degC" UART_NEWLINE, degC / 10, degC % 10);

    ADC_TEMP_Disable();
}

void CLI_STD_memory()
{
    const char* strToken;
    uintptr_t addr;
    uint16_t len = 1;

    strToken = CLI_NextArg();
    if(strToken)
    {
        addr = strtoul(strToken, NULL, 16);

        strToken = CLI_NextArg();
        if(strToken)
        {
            len = strtoul(strToken, NULL, 0);
        }
        printf("Memory @ 0x%lx for %u byte(s)" UART_NEWLINE, addr, len);
        kprinthex(*(const void **) &addr, len);
    }
    else printf("Need a memory address, like 0x8000" UART_NEWLINE);
}

void CLI_STD_test()
{
    ;
}
