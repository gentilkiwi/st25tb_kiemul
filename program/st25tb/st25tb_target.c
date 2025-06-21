/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "st25tb_target.h"

const uint8_t st25tb_ui8ChipId = 0x42;
const uint8_t ST25TB_TARGET_KIWI_SPECIAL_RETCODE_OK[] = {0xca, 0xfe, 0xba, 0xbe}, ST25TB_TARGET_KIWI_SPECIAL_RETCODE_KO[] = {0xde, 0xca, 0xfb, 0xad};

uint8_t ST25TB_Target_AdjustIdxForSpecialAddr(uint8_t original)
{
    if(original == 0xff)
    {
        original = SLOTS_ST25TB_INDEX_SYSTEM;
    }

    return original;
}

uint8_t ST25TB_Target_ResponseTo()
{
    uint8_t ret, cbData = 0, idx, delay;
    const uint8_t *pcbData = 0;

    switch(g_ui8_ST25TB_Buffer[0])
    {
    case ST25TB_CMD_INITIATE:
    //case ST25TB_CMD_PCALL16:
        if((g_ui8_cbST25TB_Buffer == 2) && ((g_ui8_ST25TB_Buffer[1] == 0x00) || (g_ui8_ST25TB_Buffer[1]) == 4))
        {
            pcbData = &st25tb_ui8ChipId;
            cbData = sizeof(st25tb_ui8ChipId);
            delay = ST25TB_TARGET_DELAY_US_GLOBAL + ST25TB_TARGET_DELAY_US_MEDIUM;
        }
        break;

    case 0x10 | ST25TB_CMD_SLOT_MARKER_MASK: // to *only* deal with Chip_slot_number 1
        if(g_ui8_cbST25TB_Buffer == 1)
        {
            pcbData = &st25tb_ui8ChipId;
            cbData = sizeof(st25tb_ui8ChipId);
            delay = ST25TB_TARGET_DELAY_US_GLOBAL + ST25TB_TARGET_DELAY_US_MEDIUM;
        }
        break;

    case ST25TB_CMD_SELECT:
        if((g_ui8_cbST25TB_Buffer == 2) && (g_ui8_ST25TB_Buffer[1] == st25tb_ui8ChipId))
        {
            pcbData = &st25tb_ui8ChipId;
            cbData = sizeof(st25tb_ui8ChipId);
            delay = ST25TB_TARGET_DELAY_US_GLOBAL + ST25TB_TARGET_DELAY_US_MEDIUM;
        }
        break;

    case ST25TB_CMD_GET_UID:
        if(g_ui8_cbST25TB_Buffer == 1)
        {
            pcbData = SLOTS_ST25TB_Current[SLOTS_ST25TB_INDEX_UID];
            cbData = 2 * sizeof(SLOTS_ST25TB_Current[0]);
            delay = ST25TB_TARGET_DELAY_US_GLOBAL;
        }
        break;

    case ST25TB_CMD_READ_BLOCK:
        if(g_ui8_cbST25TB_Buffer == 2)
        {
            idx = ST25TB_Target_AdjustIdxForSpecialAddr(g_ui8_ST25TB_Buffer[1]);
            if(idx < SLOTS_ST25TB_SECTORS_INTERNAL)
            {
                pcbData = SLOTS_ST25TB_Current[idx];
                cbData = sizeof(SLOTS_ST25TB_Current[0]);
                delay = ST25TB_TARGET_DELAY_US_GLOBAL + ST25TB_TARGET_DELAY_US_SMALL;
            }
        }
        break;

    case ST25TB_CMD_WRITE_BLOCK:
        if(g_ui8_cbST25TB_Buffer == 6)
        {
            idx = ST25TB_Target_AdjustIdxForSpecialAddr(g_ui8_ST25TB_Buffer[1]);
            if(idx < SLOTS_ST25TB_SECTORS_INTERNAL)
            {
                *(uint32_t *) SLOTS_ST25TB_Current[idx] = *(uint32_t *) (g_ui8_ST25TB_Buffer + 2);
            }
            else if(idx == 0xfe)
            {
                switch(g_ui8_ST25TB_Buffer[2])
                {
                case 0xff: // Save to slot
                    idx = (g_ui8_ST25TB_Buffer[3] == 0xff) ? FlashStoredData.CurrentSlot : g_ui8_ST25TB_Buffer[3];
                    pcbData = SLOTS_Save(idx) ? ST25TB_TARGET_KIWI_SPECIAL_RETCODE_OK : ST25TB_TARGET_KIWI_SPECIAL_RETCODE_KO;
                    cbData = 4;
                    break;

                case 0xfe: // Change slot (or get the current with 0xff)
                    if(g_ui8_ST25TB_Buffer[3] == 0xff) // only get the current, no reload
                    {
                        idx = FlashStoredData.CurrentSlot;
                        pcbData = &idx;
                        cbData = 1;
                    }
                    else // real SLOTS_Change
                    {
                        idx = g_ui8_ST25TB_Buffer[3];
                        if(SLOTS_Change(idx))
                        {
                            pcbData = &idx;
                            cbData = 1;
                        }
                        else
                        {
                            pcbData = ST25TB_TARGET_KIWI_SPECIAL_RETCODE_KO;
                            cbData = 4;
                        }
                    }
                    break;

                case 0x00: // Restart / Reset
                    WDTCTL = 0xcafe;
                    break;
                }

                delay = ST25TB_TARGET_DELAY_US_GLOBAL;
            }
        }
        break;

    //case ST25TB_CMD_RESET_TO_INVENTORY:
    //case ST25TB_CMD_COMPLETION:
    }

    if (pcbData && cbData)
    {
        TIMER_delay_Microseconds(delay);
        ret = ST25TB_Send(pcbData, cbData);
    }
    else
    {
        TRF7970A_SPI_DirectCommand(TRF79X0_STOP_DECODERS_CMD);
        __no_operation();
        __no_operation();
        TRF7970A_SPI_DirectCommand(TRF79X0_RUN_DECODERS_CMD);

        ret = 1;
    }

    return ret;
}
