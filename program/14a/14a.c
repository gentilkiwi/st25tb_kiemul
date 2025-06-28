/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "14a.h"

uint8_t g_ui8_14a_Buffer[0x7f];
uint8_t g_ui8_cb14a_Buffer = 0;

uint8_t K14A_Recv(uint8_t bIsinitiator, uint8_t irqProvided)
{
    uint8_t status = 0;
    if (irqProvided == TRF79X0_IRQ_STATUS_SRX) // Previously '&', but we want to ignore errors
    {
        if (bIsinitiator || (TRF7970A_SPI_Read_SingleRegister(TRF79X0_NFC_TARGET_PROTOCOL_REG) == TRF79X0_NFC_TARGET_PROTOCOL_14A_COMMAND)) // TO DEAL ?
        {
            g_ui8_cb14a_Buffer = TRF7970A_SPI_Read_SingleRegister(TRF79X0_FIFO_STATUS_REG);
            if (g_ui8_cb14a_Buffer && !(g_ui8_cb14a_Buffer & TRF79X0_FIFO_OVERFLOW))
            {
                TRF7970A_SPI_Read_ContinuousRegister(TRF79X0_FIFO_REG, g_ui8_14a_Buffer, g_ui8_cb14a_Buffer);
                status = 1;
            }
        }
    }

    return status;
}

uint8_t K14A_Send(const uint8_t *pcbData, const uint8_t cbData, const uint8_t bIsCRC, const uint8_t brokenBits)
{
    uint8_t status;

    TRF7970A_SPI_Write_Packet_TYPED_BB(pcbData, cbData, bIsCRC ? MK_DC(TRF79X0_TRANSMIT_CRC_CMD) : MK_DC(TRF79X0_TRANSMIT_NO_CRC_CMD), brokenBits);
    if(TRF7970A_SPI_waitIrq() & TRF79X0_IRQ_STATUS_TX)
    {
        TRF7970A_SPI_DirectCommand(TRF79X0_RESET_FIFO_CMD);
        status = 1;
    }
    else
    {
        status = 0;
    }

    return status;
}

uint8_t K14_Initiator_SendRecv(const uint8_t *pui8Payload, const uint8_t ui8Length, const uint8_t bIsCRC, const uint8_t brokenBits, uint16_t timeout_ms)
{
    uint8_t ret, TRF7970A_irqStatus;

    //printf("> "); kprinthex(pui8Payload, ui8Length);
    if(K14A_Send(pui8Payload, ui8Length, bIsCRC, brokenBits))
    {
        ret = IRQ_Wait_for(IRQ_SOURCE_SW1 | IRQ_SOURCE_SW2 | IRQ_SOURCE_TRF7970A | IRQ_SOURCE_TIMER, &TRF7970A_irqStatus, timeout_ms);
        if(!(ret & (IRQ_SOURCE_SW1 | IRQ_SOURCE_SW2 | IRQ_SOURCE_TIMER)))
        {
            if (K14A_Recv(1, TRF7970A_irqStatus))
            {
                ret = IRQ_SOURCE_NONE;
                //printf("< "); kprinthex(g_ui8_14a_Buffer, g_ui8_cb14a_Buffer);
            }
        }
    }
    else
    {
        ret = IRQ_SOURCE_TRF7970A;
    }

    return ret;
}

const uint8_t K14A_TRF7970A_Mode_Initiator_Seq[] = {
    MK_WS(TRF79X0_ISO_CONTROL_REG), TRF79X0_ISO_CONTROL_RX_CRC_N | TRF79X0_ISO_CONTROL_14443A_106K,
    MK_WS(TRF79X0_RX_SPECIAL_SETTINGS_REG), 0xf0,
    MK_WS(TRF79X0_SPECIAL_FUNC_1_REG), 0x00,
    MK_WS(TRF79X0_CHIP_STATUS_CTRL_REG), TRF79X0_STATUS_CTRL_RF_ON,
    MK_WS(TRF79X0_MODULATOR_CONTROL_REG), TRF79X0_MOD_CTRL_MOD_OOK_100,
    MK_WS(TRF79X0_REGULATOR_CONTROL_REG), TRF79X0_REGULATOR_CTRL_VRS_2_7V,
    MK_WS(TRF79X0_FIFO_IRQ_LEVEL), 0x0f,
    MK_WS(TRF79X0_NFC_LOW_DETECTION_LEVEL), 0x00,
    MK_WS(TRF79X0_NFC_TARGET_LEVEL_REG), 0x07,
    MK_RS(TRF79X0_IRQ_STATUS_REG), 0x00,
};

const TRF7970A_MODE K14A_TRF7970A_Mode_Initiator = {
    .seq = K14A_TRF7970A_Mode_Initiator_Seq,
    .cbSec = sizeof(K14A_TRF7970A_Mode_Initiator_Seq),
    .delay = 12,
};
