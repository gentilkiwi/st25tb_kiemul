/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "st25tb.h"

uint8_t g_ui8FifoBuffer[0x10];
uint8_t g_ui8cbFifoBuffer = 0;

bool ST25TB_Recv(bool bIsinitiator, uint8_t irqProvided)
{
    bool status = false;
    if (irqProvided & TRF79X0_IRQ_STATUS_SRX)
    {
        if (bIsinitiator || (TRF7970A_readSingle(TRF79X0_NFC_TARGET_PROTOCOL_REG) == TRF79X0_NFC_TARGET_PROTOCOL_14B_COMMAND))
        {
            g_ui8cbFifoBuffer = TRF7970A_readSingle(TRF79X0_FIFO_STATUS_REG);
            if (g_ui8cbFifoBuffer && !(g_ui8cbFifoBuffer & TRF79X0_FIFO_OVERFLOW))
            {
                TRF7970A_readCont(g_ui8FifoBuffer, TRF79X0_FIFO_REG, g_ui8cbFifoBuffer);
                status = true;
            }
        }
    }

    return status;
}

bool ST25TB_Send(const uint8_t *pui8Payload, const uint8_t ui8Length)
{
    bool status;

    TRF7970A_writePacketToTransmit(pui8Payload, ui8Length);
    if(TRF7970A_waitIrq() & TRF79X0_IRQ_STATUS_TX)
    {
        TRF7970A_directCommand(TRF79X0_RESET_FIFO_CMD);
        status = true;
    }
    else
    {
        status = false;
    }

    return status;
}


const uint8_t Mode_Initiator[] = {
    MK_WS(TRF79X0_ISO_CONTROL_REG), 0x0c,
    MK_WS(TRF79X0_RX_SPECIAL_SETTINGS_REG), 0xf0,
    MK_WS(TRF79X0_CHIP_STATUS_CTRL_REG), TRF79X0_STATUS_CTRL_RF_ON,
    MK_WS(TRF79X0_MODULATOR_CONTROL_REG), TRF79X0_MOD_CTRL_MOD_ASK_10,
    MK_WS(TRF79X0_REGULATOR_CONTROL_REG), TRF79X0_REGULATOR_CTRL_VRS_2_7V,
    MK_WS(TRF79X0_FIFO_IRQ_LEVEL), 0x0f,
    MK_WS(TRF79X0_NFC_LOW_DETECTION_LEVEL), 0x03,
    MK_WS(TRF79X0_NFC_TARGET_LEVEL_REG), 0x07,
    MK_RS(TRF79X0_IRQ_STATUS_REG), 0x00,
};

const uint8_t Mode_Target[] = {
    MK_WS(TRF79X0_ISO_CONTROL_REG), 0x25,
    MK_WS(TRF79X0_RX_SPECIAL_SETTINGS_REG), 0xf0,
    MK_WS(TRF79X0_CHIP_STATUS_CTRL_REG), TRF79X0_STATUS_CTRL_RF_ON,
    MK_WS(TRF79X0_MODULATOR_CONTROL_REG), TRF79X0_MOD_CTRL_MOD_ASK_10,
    MK_WS(TRF79X0_REGULATOR_CONTROL_REG), TRF79X0_REGULATOR_CTRL_VRS_2_7V,
    MK_WS(TRF79X0_FIFO_IRQ_LEVEL), 0x0f,
    MK_WS(TRF79X0_NFC_LOW_DETECTION_LEVEL), 0x03,
    MK_WS(TRF79X0_NFC_TARGET_LEVEL_REG), 0x07,
    MK_RS(TRF79X0_IRQ_STATUS_REG), 0x00,
    MK_DC(TRF79X0_RUN_DECODERS_CMD),
};

void ST25TB_TRF7970A_Mode(bool bIsInitiator)
{
    TRF7970A_directCommand(TRF79X0_SOFT_INIT_CMD);
    TRF7970A_directCommand(TRF79X0_IDLE_CMD);
    LP_TIMER_delay_Millisecond(2);

    if(bIsInitiator)
    {
        TRF7970A_writeRaw(Mode_Initiator, sizeof(Mode_Initiator));
        LP_TIMER_delay_Millisecond(2);
    }
    else
    {
        TRF7970A_writeRaw(Mode_Target, sizeof(Mode_Target));
    }
}
