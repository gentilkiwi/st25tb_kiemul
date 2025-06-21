/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "cli_config.h"
#include "cli_slot.h"

const char lblbDoNotWriteSystem[] = "bDoNotWriteSystem", lblbDoNotWriteCounters[] = "bDoNotWriteCounters", lblbModeEmulateSW2Save[] = "bModeEmulateSW2Save", lblbUARTEnabled[] = "bUARTEnabled";

const CLI_FUNCTION CLI_CONFIG_Functions[] = {
    {.name = "show",                    .function = CLI_CONFIG_show,            .description = "Show config stored in FRAM"},

    {.name = "slot",        .function = CLI_SLOT_change,            .description = "> slot change"},
    {.name = "dnws",        .function = CLI_CONFIG_bDNWSystem,      .description = lblbDoNotWriteSystem},
    {.name = "dnwc",        .function = CLI_CONFIG_bDNWCounters,    .description = lblbDoNotWriteCounters},
    {.name = "esw2save",    .function = CLI_CONFIG_bMEmulSW2Save,   .description = lblbModeEmulateSW2Save},
    {.name = "uart",        .function = CLI_CONFIG_bUART,           .description = lblbUARTEnabled},
};

const CLI_MODULE CLI_CONFIG_Module = {.name = "config", .description = "Configuration from FlashStoredData", .nbFunctions = count_of(CLI_CONFIG_Functions), .Functions = CLI_CONFIG_Functions};

void CLI_CONFIG_show()
{
    printf(
            "FlashStoredData" UART_NEWLINE
            "  CurrentSlot        : %hu" UART_NEWLINE
            "  %s  : %hu" UART_NEWLINE
            "  %s: %hu" UART_NEWLINE
            "  %s: %hu" UART_NEWLINE
            "  %s       : %hu" UART_NEWLINE,
            FlashStoredData.CurrentSlot,
            lblbDoNotWriteSystem, FlashStoredData.bDoNotWriteSystem,
            lblbDoNotWriteCounters, FlashStoredData.bDoNotWriteCounters,
            lblbModeEmulateSW2Save, FlashStoredData.bModeEmulateSW2Save,
            lblbUARTEnabled, FlashStoredData.bUARTEnabled
    );
}

void CLI_CONFIG_GenericAction(uint8_t *pValue, const char *label)
{
    char *strToken;

    strToken = CLI_NextArg();
    if(strToken)
    {
        uint8_t state = SYSCFG0_L;
        SYSCFG0 = FWPW | (state & ~(DFWP | PFWP));

        if((strcmp(strToken, "set") == 0) || strcmp(strToken, "1") == 0)
        {
            *pValue = 1;
        }
        else if((strcmp(strToken, "clear") == 0) || strcmp(strToken, "0") == 0)
        {
            *pValue = 0;
        }

        SYSCFG0 = FWPW | state;
    }

    printf("> %s: %hu" UART_NEWLINE, label, *pValue);
}

void CLI_CONFIG_bDNWSystem()
{
    CLI_CONFIG_GenericAction(&FlashStoredData.bDoNotWriteSystem, lblbDoNotWriteSystem);
}

void CLI_CONFIG_bDNWCounters()
{
    CLI_CONFIG_GenericAction(&FlashStoredData.bDoNotWriteCounters, lblbDoNotWriteCounters);
}

void CLI_CONFIG_bMEmulSW2Save()
{
    CLI_CONFIG_GenericAction(&FlashStoredData.bModeEmulateSW2Save, lblbModeEmulateSW2Save);
}

void CLI_CONFIG_bUART()
{
    CLI_CONFIG_GenericAction(&FlashStoredData.bUARTEnabled, lblbUARTEnabled);
}
