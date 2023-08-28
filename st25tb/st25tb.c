#include "st25tb.h"

uint8_t g_ui8FifoBuffer[0x20];
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

void ST25TB_TRF7970A_Mode(bool bIsInitiator)
{
    TRF7970A_directCommand(TRF79X0_SOFT_INIT_CMD);
    TRF7970A_directCommand(TRF79X0_IDLE_CMD);
    LP_delayMillisecond(2);
    TRF7970A_writeSingle(bIsInitiator ? 0x0c : 0x25, TRF79X0_ISO_CONTROL_REG);
    TRF7970A_writeSingle(0xf0, TRF79X0_RX_SPECIAL_SETTINGS_REG); // test 0 ?
    TRF7970A_writeSingle(TRF79X0_STATUS_CTRL_RF_ON, TRF79X0_CHIP_STATUS_CTRL_REG);
    TRF7970A_writeSingle(TRF79X0_MOD_CTRL_MOD_ASK_10, TRF79X0_MODULATOR_CONTROL_REG);

    TRF7970A_writeSingle(0x00, TRF79X0_REGULATOR_CONTROL_REG);
    TRF7970A_writeSingle(0x0f, TRF79X0_FIFO_IRQ_LEVEL);
    TRF7970A_writeSingle(0x03, TRF79X0_NFC_LOW_DETECTION_LEVEL);
    TRF7970A_writeSingle(0x07, TRF79X0_NFC_TARGET_LEVEL_REG);

    TRF7970A_clearIrqStatus();
    if(bIsInitiator)
    {
        LP_delayMillisecond(2);
    }
    else
    {
        TRF7970A_directCommand(TRF79X0_RUN_DECODERS_CMD);
    }
}
