/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "st25tb_initiator.h"

uint8_t ST25TB_Initiator_CMD_Initiate(uint8_t *pui8ChipId);
uint8_t ST25TB_Initiator_CMD_Select(const uint8_t ui8ChipId);
uint8_t ST25TB_Initiator_CMD_Get_Uid(uint8_t pui8Data[8]);
uint8_t ST25TB_Initiator_CMD_CONFIRMED_Get_Uid(uint8_t pui8Data[8]);
uint8_t ST25TB_Initiator_CMD_Completion();
uint8_t ST25TB_Initiator_CMD_Read_Block(const uint8_t ui8BlockIdx, uint8_t pui8Data[4]);
uint8_t ST25TB_Initiator_CMD_CONFIRMED_Read_Block(const uint8_t ui8BlockIdx, uint8_t pui8Data[4]);
uint8_t ST25TB_Initiator_CMD_Write_Block(const uint8_t ui8BlockIdx, const uint8_t pui8Data[4]);
uint8_t ST25TB_Initiator_CMD_CONFIRMED_Write_Block(const uint8_t ui8BlockIdx, const uint8_t pui8Data[4]);

uint8_t ST25TB_Initiator_Read_Card()
{
    uint8_t BP_IrqSource, ui8ChipId, i;

    BP_IrqSource = ST25TB_Initiator_CMD_Initiate(&ui8ChipId);
    if(BP_IrqSource == BP_IRQ_SOURCE_NONE)
    {
        BP_IrqSource = ST25TB_Initiator_CMD_Select(ui8ChipId);
        if(BP_IrqSource == BP_IRQ_SOURCE_NONE)
        {
            BP_IrqSource = ST25TB_Initiator_CMD_CONFIRMED_Get_Uid((uint8_t *) ST25TB_CARDS_CurrentCard[ST25TB_CARDS_INDEX_UID]);
            if(BP_IrqSource == BP_IRQ_SOURCE_NONE)
            {
                for(i = 0x00; (i < 0x10) && (BP_IrqSource == BP_IRQ_SOURCE_NONE); i++)
                {
                    BP_IrqSource = ST25TB_Initiator_CMD_CONFIRMED_Read_Block(i, ST25TB_CARDS_CurrentCard[i]);
                }

                if(BP_IrqSource == BP_IRQ_SOURCE_NONE)
                {
                    BP_IrqSource = ST25TB_Initiator_CMD_CONFIRMED_Read_Block(0xff, ST25TB_CARDS_CurrentCard[ST25TB_CARDS_INDEX_SYSTEM]);
                }
            }
            ST25TB_Initiator_CMD_Completion();
        }
    }

    return BP_IrqSource;
}

uint8_t ST25TB_Initiator_Write_Card()
{
    uint8_t BP_IrqSource, ui8ChipId, ui8UID[8], i;

    BP_IrqSource = ST25TB_Initiator_CMD_Initiate(&ui8ChipId);
    if(BP_IrqSource == BP_IRQ_SOURCE_NONE)
    {
        BP_IrqSource = ST25TB_Initiator_CMD_Select(ui8ChipId);
        if(BP_IrqSource == BP_IRQ_SOURCE_NONE)
        {
            BP_IrqSource = ST25TB_Initiator_CMD_Get_Uid(ui8UID);
            if(BP_IrqSource == BP_IRQ_SOURCE_NONE)
            {
                if ((*(uint64_t*) ui8UID) == (*(uint64_t*) ST25TB_CARDS_CurrentCard[ST25TB_CARDS_INDEX_UID]))
                {
                    for(i = 0x00; (i < 0x10) && (BP_IrqSource == BP_IRQ_SOURCE_NONE); i++)
                    {
#if defined(ST25TB_DO_NOT_WRITE_DANGEROUS_SECTOR)
                        if((i == 5) || (i == 6))
                        {
                            continue;
                        }
#endif
                        BP_IrqSource = ST25TB_Initiator_CMD_CONFIRMED_Write_Block(i, ST25TB_CARDS_CurrentCard[i]);
                    }
#if !defined(ST25TB_DO_NOT_WRITE_DANGEROUS_SECTOR)
                    if(BP_IrqSource == BP_IRQ_SOURCE_NONE)
                    {
                        BP_IrqSource = ST25TB_Initiator_CMD_CONFIRMED_Write_Block(0xff, ST25TB_CARDS_CurrentCard[ST25TB_CARDS_INDEX_SYSTEM]);
                    }
#endif
                }
                else
                {
                    BP_IrqSource = BP_IRQ_SOURCE_ST25TB_PROTOCOL_ERR;
                }
            }
            ST25TB_Initiator_CMD_Completion();
        }
    }

    return BP_IrqSource;
}

uint8_t ST25TB_Initiator_SendRecv(const uint8_t *pui8Payload, const uint8_t ui8Length, uint16_t timeout_ms)
{
    uint8_t ret, TRF7970A_irqStatus;
    if(ST25TB_Send(pui8Payload, ui8Length))
    {
        ret = BP_Wait_for_Buttons_or_TRF7970A_or_Timeout(&TRF7970A_irqStatus, timeout_ms);
        if(!(ret & (BP_IRQ_SOURCE_LP_S1 | BP_IRQ_SOURCE_LP_S2 | BP_IRQ_SOURCE_TIMER)))
        {
            if (ret & BP_IRQ_SOURCE_TRF7970A)
            {
                if (ST25TB_Recv(true, TRF7970A_irqStatus))
                {
                    ret = BP_IRQ_SOURCE_NONE;
                }
            }
        }
    }
    else
    {
        ret = BP_IRQ_SOURCE_TRF7970A;
    }

    return ret;
}

const uint8_t ST25TB_Initiator_CMD_Initiate_data[] = { ST25TB_CMD_INITIATE, 0x00 };
uint8_t ST25TB_Initiator_CMD_Initiate(uint8_t *pui8ChipId)
{
    uint8_t ret;

    ret = ST25TB_Initiator_SendRecv(ST25TB_Initiator_CMD_Initiate_data, sizeof(ST25TB_Initiator_CMD_Initiate_data), 2);
    if (ret == BP_IRQ_SOURCE_NONE)
    {
        if (g_ui8cbFifoBuffer == 1)
        {
            *pui8ChipId = *g_ui8FifoBuffer;
            ret = BP_IRQ_SOURCE_NONE;
        }
        else
        {
            ret = BP_IRQ_SOURCE_ST25TB_PROTOCOL_ERR;
        }
    }

    return ret;
}

uint8_t ST25TB_Initiator_CMD_Select(const uint8_t ui8ChipId)
{
    uint8_t ret, ST25TB_Initiator_CMD_Select_data[] = { ST25TB_CMD_SELECT, ui8ChipId };

    ret = ST25TB_Initiator_SendRecv(ST25TB_Initiator_CMD_Select_data, sizeof(ST25TB_Initiator_CMD_Select_data), 2);
    if (ret == BP_IRQ_SOURCE_NONE)
    {
        if((g_ui8cbFifoBuffer == 1) && (ui8ChipId == g_ui8FifoBuffer[0]))
        {
            ret = BP_IRQ_SOURCE_NONE;
        }
        else
        {
            ret = BP_IRQ_SOURCE_ST25TB_PROTOCOL_ERR;
        }
    }

    return ret;
}

const uint8_t ST25TB_Initiator_CMD_Get_Uid_data[] = { ST25TB_CMD_GET_UID };
uint8_t ST25TB_Initiator_CMD_Get_Uid(uint8_t pui8Data[8])
{
    uint8_t ret;

    ret = ST25TB_Initiator_SendRecv(ST25TB_Initiator_CMD_Get_Uid_data, sizeof(ST25TB_Initiator_CMD_Get_Uid_data), 5);
    if (ret == BP_IRQ_SOURCE_NONE)
    {
        if (g_ui8cbFifoBuffer == sizeof(uint64_t))
        {
            *(uint64_t *) pui8Data = *(uint64_t *) g_ui8FifoBuffer;
            ret = BP_IRQ_SOURCE_NONE;
            LP_delayMillisecond(1);
        }
        else
        {
            ret = BP_IRQ_SOURCE_ST25TB_PROTOCOL_ERR;
        }
    }

    return ret;
}

uint8_t ST25TB_Initiator_CMD_CONFIRMED_Get_Uid(uint8_t pui8Data[8])
{
    uint8_t ret, buffer[8];

    ret = ST25TB_Initiator_CMD_Get_Uid(buffer);
    if (ret == BP_IRQ_SOURCE_NONE)
    {
        ret = ST25TB_Initiator_CMD_Get_Uid(pui8Data);
        if (ret == BP_IRQ_SOURCE_NONE)
        {
            if ((*(uint64_t*) buffer) != (*(uint64_t*) pui8Data))
            {
                ret = BP_IRQ_SOURCE_ST25TB_PROTOCOL_ERR;
            }
        }
    }

    return ret;
}

const uint8_t ST25TB_Initiator_CMD_Completion_data[] = { ST25TB_CMD_COMPLETION };
uint8_t ST25TB_Initiator_CMD_Completion()
{
    uint8_t ret;

    if(ST25TB_Send(ST25TB_Initiator_CMD_Completion_data, sizeof(ST25TB_Initiator_CMD_Completion_data)))
    {
        ret = BP_IRQ_SOURCE_NONE;
    }
    else
    {
        ret = BP_IRQ_SOURCE_TRF7970A;
    }

    return ret;
}

uint8_t ST25TB_Initiator_CMD_Read_Block(const uint8_t ui8BlockIdx, uint8_t pui8Data[4])
{
    uint8_t ret, ST25TB_Initiator_CMD_Read_Block_data[] = { ST25TB_CMD_READ_BLOCK, ui8BlockIdx };

    ret = ST25TB_Initiator_SendRecv(ST25TB_Initiator_CMD_Read_Block_data, sizeof(ST25TB_Initiator_CMD_Read_Block_data), 5);
    if (ret == BP_IRQ_SOURCE_NONE)
    {
        if(g_ui8cbFifoBuffer == sizeof(uint32_t))
        {
            *((uint32_t *) pui8Data) = *(uint32_t *) g_ui8FifoBuffer;
            ret = BP_IRQ_SOURCE_NONE;
            LP_delayMillisecond(4);
        }
        else
        {
            ret = BP_IRQ_SOURCE_ST25TB_PROTOCOL_ERR;
        }
    }

    return ret;
}

uint8_t ST25TB_Initiator_CMD_CONFIRMED_Read_Block(const uint8_t ui8BlockIdx, uint8_t pui8Data[4])
{
    uint8_t ret, buffer[4];

    ret = ST25TB_Initiator_CMD_Read_Block(ui8BlockIdx, buffer);
    if (ret == BP_IRQ_SOURCE_NONE)
    {
        ret = ST25TB_Initiator_CMD_Read_Block(ui8BlockIdx, pui8Data);
        if (ret == BP_IRQ_SOURCE_NONE)
        {
            if ((*(uint32_t*) buffer) != (*(uint32_t*) pui8Data))
            {
                ret = BP_IRQ_SOURCE_ST25TB_PROTOCOL_ERR;
            }
        }
    }

    return ret;
}

uint8_t ST25TB_Initiator_CMD_Write_Block(const uint8_t ui8BlockIdx, const uint8_t pui8Data[4])
{
    uint8_t ret, ST25TB_Initiator_CMD_Write_Block_data[2 + 4] = { ST25TB_CMD_WRITE_BLOCK, ui8BlockIdx };

    *(uint32_t *) (ST25TB_Initiator_CMD_Write_Block_data + 2) = *((uint32_t *) pui8Data);
    if (ST25TB_Send(ST25TB_Initiator_CMD_Write_Block_data, sizeof(ST25TB_Initiator_CMD_Write_Block_data)))
    {
        ret = BP_IRQ_SOURCE_NONE;
        LP_delayMillisecond(((ui8BlockIdx == 5) || (ui8BlockIdx == 6)) ? ST25TB_DELAY_WRITE_TIME_COUNTER : ST25TB_DELAY_WRITE_TIME_EEPROM);
    }
    else
    {
        ret = BP_IRQ_SOURCE_TRF7970A;
    }

    return ret;
}

uint8_t ST25TB_Initiator_CMD_CONFIRMED_Write_Block(const uint8_t ui8BlockIdx, const uint8_t pui8Data[4])
{
    uint8_t ret, buffer[4];

    ret = ST25TB_Initiator_CMD_Write_Block(ui8BlockIdx, pui8Data);
    if (ret == BP_IRQ_SOURCE_NONE)
    {
        ret = ST25TB_Initiator_CMD_Read_Block(ui8BlockIdx, buffer);
        if (ret == BP_IRQ_SOURCE_NONE)
        {
            if ((*(uint32_t*) buffer) != (*(uint32_t*) pui8Data))
            {
                ret = BP_IRQ_SOURCE_ST25TB_PROTOCOL_ERR;
            }
        }
    }

    return ret;
}
