/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "cli_ref.h"
#include "cli_data.h"

#if defined(REFERENCES_DATA_READY)

const CLI_FUNCTION CLI_REF_Functions[] = {
    {.name = "info",    .function = CLI_REF_info,      .description = "Show all references UID"},

    {.name = "load",    .function = CLI_REF_load,      .description = "Load a reference in current data (index)"},
    {.name = "show",    .function = CLI_REF_show,      .description = "Show reference content (index)"},
    {.name = "dump",    .function = CLI_REF_dump,      .description = "Dump a reference (index)"},
};

const CLI_MODULE CLI_REF_Module = {.name = "ref", .description = "References informations (read only)", .nbFunctions = count_of(CLI_REF_Functions), .Functions = CLI_REF_Functions};

uint8_t CLI_Ref_Get(uint8_t *pRefNumber)
{
    char *strToken;
    uint8_t ret = 0, index;

    strToken = CLI_NextArg();
    if(strToken)
    {
        index = (uint8_t) strtoul(strToken, NULL, 0);
        if (index < REFERENCES_ST25TB_COUNT)
        {
            *pRefNumber = index;
            ret = 1;
        }
        else
        {
            printf("Invalid ref # %hu - valid: [0 ; %hu]" UART_NEWLINE, index, REFERENCES_ST25TB_COUNT - 1);
        }
    }
    else
    {
        printf("ref # needed - valid: [0 ; %hu]" UART_NEWLINE, REFERENCES_ST25TB_COUNT - 1);
    }

    if(ret)
    {
        printf("Using ref #%hu" UART_NEWLINE, *pRefNumber);
    }

    return ret;
}

void CLI_REF_info()
{
    uint8_t i;

    printf(UART_NEWLINE "REFERENCE(S): %hu" UART_NEWLINE, REFERENCES_ST25TB_COUNT);
    for(i = 0; i < REFERENCES_ST25TB_COUNT; i++)
    {
        printf("[ %2hu ] ", i);
        st25tb_utils_Display_UIDChip(REFERENCES_ST25TB[i][REFERENCES_ST25TB_INDEX_UID]);
    }
}

void CLI_REF_show()
{
    uint8_t index;

    if(CLI_Ref_Get(&index))
    {
        st25tb_utils_Display_dump((const uint8_t (*)[4]) REFERENCES_ST25TB[index], REFERENCES_ST25TB_INDEX_UID);
    }
}

void CLI_REF_dump()
{
    uint8_t index;

    if(CLI_Ref_Get(&index))
    {
        st25tb_utils_Display_dump((const uint8_t (*)[4]) REFERENCES_ST25TB[index], REFERENCES_ST25TB_INDEX_UID);
        CLI_BASE64_kprint((const uint8_t *) REFERENCES_ST25TB[index], sizeof(REFERENCES_ST25TB[index]));
    }
}

void CLI_REF_load()
{
    uint8_t ret = 0, index;

    if(CLI_Ref_Get(&index))
    {
        ret = REFERENCES_Load(index);
    }

    if(ret)
    {
        CLI_DATA_show();
    }

    CLI_print_status(ret);
}

#endif
