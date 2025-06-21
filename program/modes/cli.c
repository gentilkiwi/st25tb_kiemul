/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#include "cli.h"
#include "cli/cli_std.h"
#include "cli/cli_config.h"
#include "cli/cli_dump.h"
#include "cli/cli_slot.h"
#include "cli/cli_ref.h"
#include "cli/cli_data.h"
#include "cli/cli_card.h"

const CLI_MODULE * CLI_Modules[] = {
    //&CLI_STD_Module,
    &CLI_CONFIG_Module,
    &CLI_DUMP_Module,
    &CLI_SLOT_Module,
#if defined(REFERENCES_DATA_READY)
    &CLI_REF_Module,
#endif
    &CLI_DATA_Module,
    &CLI_CARD_Module,
};

void MODE_cli_Module(const CLI_MODULE * Module, const char* strToken)
{
    uint8_t i, bIsFound = 0;

    if(!strToken)
    {
        strToken = CLI_NextArg();
    }

    if(strToken)
    {
        for(i = 0; i < Module->nbFunctions; i++)
        {
            if(strcmp(strToken, Module->Functions[i].name) == 0)
            {
                bIsFound = 1;
                Module->Functions[i].function();
                break;
            }
        }
    }

    if(!bIsFound)
    {
        printf("Module %s -- %s" UART_NEWLINE, Module->name, Module->description);
        for(i = 0; i < Module->nbFunctions; i++)
        {
            printf(" %-8s -- %s" UART_NEWLINE, Module->Functions[i].name, Module->Functions[i].description);
        }
    }

    printf(UART_NEWLINE);
}

const char CLI_SEPARATORS[] = " ";
void MODE_cli()
{
    uint8_t BP_IrqSource, i, bIsFound;
    char *strToken;

    printf(UART_NEWLINE "Welcome to the CLI!" UART_NEWLINE);
    LEDS_STATUS_Bitmask(0b000);

    if(!UART_Enabled)
    {
        printf("> UART was disabled and has been temporarily re-enabled" UART_NEWLINE);
        UART_Enabled = 1;
    }

    printf(UART_NEWLINE);

    do
    {
        printf("msp # ");

        BP_IrqSource = IRQ_Wait_for(IRQ_SOURCE_UART_RX | IRQ_SOURCE_SW1, NULL, 0);
        if(BP_IrqSource == IRQ_SOURCE_UART_RX)
        {
            printf(UART_NEWLINE);
            if(cbRxBuffer)
            {
                strToken = strtok(UART_RX_BUFFER, CLI_SEPARATORS);
                if(strToken)
                {
                    bIsFound = 0;

                    for(i = 0; i < count_of(CLI_Modules); i++)
                    {
                        if(strcmp(strToken, CLI_Modules[i]->name) == 0)
                        {
                            bIsFound = 1;
                            MODE_cli_Module(CLI_Modules[i], NULL);
                            break;
                        }
                    }

                    if(!bIsFound)
                    {
                        MODE_cli_Module(&CLI_STD_Module, strToken);
                    }
                }
            }
        }
    }
    while (!(BP_IrqSource & IRQ_SOURCE_SW1));

    UART_Enabled = FlashStoredData.bUARTEnabled;
    SLOTS_Load_Current();
}

_CODE_ACCESS char *CLI_NextArg()
{
    return strtok(NULL, CLI_SEPARATORS);
}


static const char base64_table[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
/*
int CLI_BASE64_encode(const uint8_t *src, int srclen, char *dst)
{
    uint32_t ac = 0;
    int bits = 0;
    int i;
    char *cp = dst;

    for (i = 0; i < srclen; i++) {
        ac = (ac << 8) | src[i];
        bits += 8;
        do {
            bits -= 6;
            *cp++ = base64_table[(ac >> bits) & 0x3f];
        } while (bits >= 6);
    }
    if (bits) {
        *cp++ = base64_table[(ac << (6 - bits)) & 0x3f];
        bits -= 6;
    }
    while (bits < 0) {
        *cp++ = '=';
        bits += 2;
    }
    return cp - dst;
}
*/
void CLI_BASE64_kprint(const uint8_t *src, uint16_t srclen)
{
    uint32_t ac = 0;
    uint16_t i;
    int bits = 0;

    printf("Base64 data: ");

    for (i = 0; i < srclen; i++)
    {
        ac = (ac << 8) | src[i];
        bits += 8;
        do
        {
            bits -= 6;
            printf("%c", base64_table[(ac >> bits) & 0x3f]);
        } while (bits >= 6);
    }

    if (bits)
    {
        printf("%c", base64_table[(ac << (6 - bits)) & 0x3f]);
        bits -= 6;
    }

    while (bits < 0)
    {
        printf("=");
        bits += 2;
    }

    printf(UART_NEWLINE);
}

int16_t CLI_BASE64_decode(const char *src, uint16_t srclen, uint8_t *dst)
{
    uint32_t ac = 0;
    int bits = 0, i;
    uint8_t *bp = dst;

    for (i = 0; i < srclen; i++)
    {
        const char *p = strchr(base64_table, src[i]);

        if (src[i] == '=')
        {
            ac = (ac << 6);
            bits += 6;
            if (bits >= 8)
            {
                bits -= 8;
            }
            continue;
        }
        if (p == NULL || src[i] == 0)
        {
            return -1;
        }
        ac = (ac << 6) | (p - base64_table);
        bits += 6;
        if (bits >= 8)
        {
            bits -= 8;
            *bp++ = (uint8_t)(ac >> bits);
        }
    }
    if (ac & ((1 << bits) - 1))
    {
        return -1;
    }

    return bp - dst;
}

void CLI_print_status(const uint8_t ret)
{
    printf("> %s" UART_NEWLINE, ret ? "OK!" : "KO");
}

uint8_t CLI_BlockNumber_Value(const char *strToken, uint8_t *pBlockNumber, uint8_t Value[4])
{
    uint8_t ret = 0;
    uint32_t data;

    if(!strToken)
    {
        strToken = CLI_NextArg();
    }

    if(strToken)
    {
        *pBlockNumber = (uint8_t ) strtoul(strToken, NULL, 0);
        printf("Using block# %hu" UART_NEWLINE, *pBlockNumber);

        if(!Value)
        {
            ret = 1;
        }
        else
        {
            strToken = CLI_NextArg();
            if (strToken)
            {
                data = strtoul(strToken, NULL, 16);
                *(uint32_t *) Value = data;
                printf("Using data : %02X %02X %02X %02X -- %08lX" UART_NEWLINE, Value[0], Value[1], Value[2], Value[3], *(uint32_t *) Value);

                ret = 1;
            }
            else
            {
                printf("A new data (hex) is needed" UART_NEWLINE);
            }
        }
    }
    else
    {
        printf("A block number # is needed" UART_NEWLINE);
    }

    return ret;
}
