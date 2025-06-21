/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "cli_slot.h"
#include "cli_data.h"

const CLI_FUNCTION CLI_SLOT_Functions[] = {
    {.name = "info",    .function = CLI_SLOT_info,      .description = "Show all slots UID"},

    {.name = "load",    .function = CLI_SLOT_load,      .description = "Load a slot in current data (selected or index)"},
    {.name = "show",    .function = CLI_SLOT_show,      .description = "Show a slot (selected or index)"},
    {.name = "dump",    .function = CLI_SLOT_dump,      .description = "Dump a slot (selected or index)"},

    {.name = "save",    .function = CLI_SLOT_save,      .description = "Save current data in a slot (selected or index)"},
    {.name = "change",  .function = CLI_SLOT_change,    .description = "Change a slot"},
};

const CLI_MODULE CLI_SLOT_Module = {.name = "slot", .description = "Slots manipulation (FRAM stored)", .nbFunctions = count_of(CLI_SLOT_Functions), .Functions = CLI_SLOT_Functions};

uint8_t CLI_SLOT_Get(uint8_t *pSlotNumber)
{
    char *strToken;
    uint8_t ret = 0, index;

    strToken = CLI_NextArg();
    if(strToken)
    {
        index = (uint8_t) strtoul(strToken, NULL, 0);
        if (index < SLOTS_ST25TB_COUNT)
        {
            *pSlotNumber = index;
            ret = 1;
        }
        else
        {
            printf("Invalid slot number %hu - valid: [0 ; %hu]" UART_NEWLINE, index, SLOTS_ST25TB_COUNT - 1);
        }
    }
    else
    {
        printf("No slot number, using current one..." UART_NEWLINE);
        *pSlotNumber = FlashStoredData.CurrentSlot;
        ret = 1;
    }

    if(ret)
    {
        printf("Using slot #%hu" UART_NEWLINE, *pSlotNumber);
    }

    return ret;
}

void CLI_SLOT_info()
{
    uint8_t i;

    printf(UART_NEWLINE "SLOT(S): %hu (current is #%hu)" UART_NEWLINE, SLOTS_ST25TB_COUNT, FlashStoredData.CurrentSlot);
    for(i = 0; i < SLOTS_ST25TB_COUNT; i++)
    {
        printf("[%c%2hu%c] ", (FlashStoredData.CurrentSlot == i) ? '*' : ' ', i, memcmp(FlashStoredData.Slots[i], SLOTS_ST25TB_Current, SLOTS_ST25TB_SIZE_INTERNAL) ? ' ' : '=');
        st25tb_utils_Display_UIDChip(FlashStoredData.Slots[i][SLOTS_ST25TB_INDEX_UID]);
    }
    printf("*: current, =: same as current data" UART_NEWLINE);
}

void CLI_SLOT_show()
{
    uint8_t index;

    if(CLI_SLOT_Get(&index))
    {
        st25tb_utils_Display_dump((const uint8_t (*)[4]) FlashStoredData.Slots[index], SLOTS_ST25TB_INDEX_UID);
    }
}

void CLI_SLOT_dump()
{
    uint8_t index;

    if(CLI_SLOT_Get(&index))
    {
        st25tb_utils_Display_dump((const uint8_t (*)[4]) FlashStoredData.Slots[index], SLOTS_ST25TB_INDEX_UID);
        CLI_BASE64_kprint((const uint8_t *) FlashStoredData.Slots[index], SLOTS_ST25TB_SIZE_INTERNAL);
    }
}

void CLI_SLOT_save()
{
    uint8_t ret = 0, index;

    if(CLI_SLOT_Get(&index))
    {
        ret = SLOTS_Save(index);
    }

    CLI_print_status(ret);
}

void CLI_SLOT_load()
{
    uint8_t ret = 0, index;

    if(CLI_SLOT_Get(&index))
    {
        ret = SLOTS_Load(index);
    }

    if(ret)
    {
        CLI_DATA_show();
    }

    CLI_print_status(ret);
}

void CLI_SLOT_change()
{
    uint8_t ret = 0, index;

    if(CLI_SLOT_Get(&index))
    {
        ret = SLOTS_Change(index);
    }

    CLI_print_status(ret);
}
