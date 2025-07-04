/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "cli_slot.h"
#if !defined(__MSP430FR2673__)
#include "cli_data.h"

const CLI_FUNCTION CLI_SLOT_Functions[] = {
    {.name = "info",    .function = CLI_SLOT_info,      .description = "Show all slots UID"},

    {.name = "load",    .function = CLI_SLOT_load,      .description = "Load a slot in current data (selected or index)"},
    {.name = "show",    .function = CLI_SLOT_show,      .description = "Show a slot (selected or index)"},
    {.name = "dump",    .function = CLI_SLOT_dump,      .description = "Dump a slot (selected or index)"},

    {.name = "save",    .function = CLI_SLOT_save,      .description = "Save current data in a slot (selected or index)"},
    {.name = "change",  .function = CLI_SLOT_change,    .description = "Change a slot"},

    {.name = "trace",   .function = CLI_SLOT_trace,     .description = "List the current trace saved in FRAM"},
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


void CLI_SLOT_trace_desc(uint8_t cb, uint8_t *data)
{
    char *rep = "?";

    if (!(cb & 0x80))
    {
        cb &= 0x7f;
        if (cb == 2)
        {
            if (data[0] == ST25TB_CMD_INITIATE)
            {
                if (data[1] == 0x00)
                {
                    rep = "INITIATE";
                }
                else if (data[1] == 0x04)
                {
                    rep = "PCALL16";
                }
            }
            else if(data[0] == ST25TB_CMD_SELECT)
            {
                printf("SELECT: %hu/0x%hx", data[1], data[1]);
                rep = NULL;
            }
            else if(data[0] == ST25TB_CMD_READ_BLOCK)
            {
                printf("READ_BLOCK : %3hu/0x%02X", data[1], data[1]);
                rep = NULL;
            }
        }
        else if(cb == 1)
        {
            if(data[0] == ST25TB_CMD_GET_UID)
            {
                rep = "GET_UID";
            }
            else if(data[0] == ST25TB_CMD_RESET_TO_INVENTORY)
            {
                rep = "RESET_TO_INVENTORY";
            }
            else if(data[0] == ST25TB_CMD_COMPLETION)
            {
                rep = "COMPLETION";
            }
            else if(data[0] == ST25TB_CMD_AUTHENTICATE)
            {
                rep = "AUTHENTICATE(?)";
            }
            else if((data[0] & ST25TB_CMD_SLOT_MARKER_MASK) == ST25TB_CMD_SLOT_MARKER_MASK)
            {
                printf("SLOT_MARKER_MASK: %hu/0x%hx", data[0] >> 4, data[0] >> 4);
                rep = NULL;
            }
        }
        else if((cb == 6) && (data[0] == ST25TB_CMD_WRITE_BLOCK))
        {
            printf("WRITE_BLOCK: %3hu/0x%02X | %02hX %02hX %02hX %02hX | %02hX%02hX%02hX%02hX", data[1], data[1], data[2], data[3], data[4], data[5], data[5], data[4], data[3], data[2]);
            rep = NULL;
        }

        printf("%s ; ", rep ? rep : "");
    }
}

void CLI_SLOT_trace()
{
    uint16_t i = 0;
    uint8_t c;

    printf("Trace :" UART_NEWLINE "  buffer: %u" UART_NEWLINE "  count : %u" UART_NEWLINE UART_NEWLINE, sizeof(FlashStoredData.ST25TB_Trace), FlashStoredData.ST25TB_cbTrace);

    if(CLI_NextArg())
    {
        SLOTS_Trace_Clear();
        printf("> Reset!" UART_NEWLINE);
    }
    else if(FlashStoredData.ST25TB_cbTrace)
    {
        for(i = 0; i < FlashStoredData.ST25TB_cbTrace; )
        {
            c = FlashStoredData.ST25TB_Trace[i];
            i += 1;
            printf("%c ", (c & 0x80) ? '>' : '<');
            CLI_SLOT_trace_desc(c, FlashStoredData.ST25TB_Trace + i);
            c &= 0x7f;
            kprinthex(FlashStoredData.ST25TB_Trace + i, c);
            i += c;
        }
    }
}
#endif
