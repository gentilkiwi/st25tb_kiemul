#include "trf79x0.h"

uint8_t g_ui8FifoBuffer[NFC_FIFO_SIZE];
uint8_t g_ui8cbFifoBuffer = 0;

volatile uint8_t g_ui8IrqFlag;
volatile uint8_t g_bBitclockFlag;
volatile uint8_t g_ui8TimeOutFlag;

void TRF79x0_init()
{
    uint8_t ui8RxBuffer[2];

    MOD_DIR_OUT;
    MOD_OFF;

    SLAVE_SELECT_PORT_SET
    SLAVE_SELECT_HIGH

    // Set EN = 0 on the TRF79x0
    TRF_DISABLE
    // Set EN to output direction
    ENABLE_PORT_SET
    // wait until system clock started
    MCU_delayMillisecond(10);
    // Set EN = 1 on the TRF 79xx
    TRF_ENABLE

    SPI_setup();	//
    // Enable an interrupt Low to High transition for the IRQ pin on the TRF7970A
    //
    GPIO_setAsInputPin(TRF_IRQ_PORT, TRF_IRQ);
    GPIO_selectInterruptEdge(TRF_IRQ_PORT, TRF_IRQ, GPIO_LOW_TO_HIGH_TRANSITION);
    GPIO_enableInterrupt(TRF_IRQ_PORT, TRF_IRQ);
    GPIO_clearInterrupt(TRF_IRQ_PORT, TRF_IRQ);

    MCU_delayMillisecond(10);

    // 6.11 TRF7970A Initialization
    TRF79x0_directCommand(TRF79X0_SOFT_INIT_CMD);
    TRF79x0_directCommand(TRF79X0_IDLE_CMD);
    MCU_delayMillisecond(1);
    TRF79x0_directCommand(TRF79X0_RESET_FIFO_CMD);

    TRF79x0_writeSingle(0x00, TRF79X0_MODULATOR_CONTROL_REG);
    TRF79x0_writeSingle(0x00, TRF79X0_REGULATOR_CONTROL_REG);
    TRF79x0_writeSingle(0x00, TRF79X0_NFC_TARGET_LEVEL_REG);

    TRF79x0_writeSingle(0x00, TRF79X0_CHIP_STATUS_CTRL_REG);
    TRF79x0_writeSingle(0x3E, TRF79X0_IRQ_MASK_REG);
    // RX High = 96 bytes , TX Low = 32 bytes
    TRF79x0_writeSingle(0x0F, TRF79X0_FIFO_IRQ_LEVEL);
    TRF79x0_readCont(ui8RxBuffer, TRF79X0_IRQ_STATUS_REG, sizeof(ui8RxBuffer));
}

void TRF79x0_directCommand(uint8_t ui8Command)
{
    SPI_directCommand(ui8Command);
}

void TRF79x0_writeSingle(uint8_t ui8Value, uint8_t ui8Register)
{
    SPI_writeSingle(ui8Value, ui8Register);
}

void TRF79x0_writeCont(uint8_t *pui8Payload, uint8_t ui8Register, uint8_t ui8Length)
{
    SPI_writeCont(pui8Payload, ui8Register, ui8Length);
}

void TRF79x0_readSingle(uint8_t *pui8Value, uint8_t ui8Register)
{
    SPI_readSingle(pui8Value, ui8Register);
}

void TRF79x0_readCont(uint8_t *pui8Payload, uint8_t ui8Register, uint8_t ui8Length)
{
    SPI_readCont(pui8Payload, ui8Register, ui8Length);
}

bool TRF79x0_Send(tTRF79x0_Mode Mode, const uint8_t *pui8Payload, const uint8_t ui8Length)
{
    tTRF79x0_IRQFlag sIrqStatusFlag = IRQ_STATUS_IDLE;
    uint8_t ui8IrqBuffer;

    if (GPIO_getInputPinValue(TRF_IRQ_PORT, TRF_IRQ))
    {
        TRF79x0_readSingle(&ui8IrqBuffer, TRF79X0_IRQ_STATUS_REG);
    }

    MCU_delayMicrosecond((Mode == Initiator) ? 300 : 30);

    SPI_writePacket(pui8Payload, ui8Length, ui8Length);

    while (sIrqStatusFlag != IRQ_STATUS_TX_COMPLETE)
    {
        sIrqStatusFlag = TRF79x0_irqHandler(Mode, 0);
    }

    return (sIrqStatusFlag == IRQ_STATUS_TX_COMPLETE);
}

bool TRF79x0_Initiator_Send_Recv(const uint8_t *pui8Payload, const uint8_t ui8Length, const uint16_t ui16TimeOut)
{
    bool bStatus = false;

    if(TRF79x0_Send(Initiator, pui8Payload, ui8Length))
    {
        if(TRF79x0_irqHandler(Initiator, ui16TimeOut) == IRQ_STATUS_RX_COMPLETE)
        {
            bStatus = true;
        }
    }
    return bStatus;
}

void TRF79x0_ignoreCmd()
{
    TRF79x0_directCommand(TRF79X0_STOP_DECODERS_CMD);
    TRF79x0_directCommand(TRF79X0_RUN_DECODERS_CMD);
}

tTRF79x0_IRQFlag TRF79x0_irqHandler(tTRF79x0_Mode Mode, uint16_t ui16TimeOut)
{
    tTRF79x0_IRQFlag eIrqStatusFlag = IRQ_STATUS_IDLE;
    uint8_t ui8IrqStatus, ui8NFCTargetProtocol;

    volatile uint8_t ui8TempX;

    if (!ui16TimeOut)
    {
        while (!GPIO_getInputPinValue(TRF_IRQ_PORT, TRF_IRQ));
    }

    if (GPIO_getInputPinValue(TRF_IRQ_PORT, TRF_IRQ))
    {
        g_ui8IrqFlag = 1;
    }
    else
    {
        g_ui8IrqFlag = 0;
        MCU_timerInit(ui16TimeOut, (uint8_t*) &g_ui8TimeOutFlag);
    }

    //
    // Check if the IRQ flag has been set
    //
    while ((g_ui8IrqFlag == 0x00) && (g_ui8TimeOutFlag == 0x00));

    MCU_timerDisable();
    if (g_ui8TimeOutFlag == 0x01)
    {
        eIrqStatusFlag = IRQ_STATUS_TIME_OUT;
    }
    else
    {
        if (Mode == Target)
        {
            TRF79x0_readSingle(&ui8NFCTargetProtocol, TRF79X0_NFC_TARGET_PROTOCOL_REG);
            TRF79x0_readSingle(&ui8IrqStatus, TRF79X0_IRQ_STATUS_REG);

            if (((ui8NFCTargetProtocol != TRF79X0_NFC_TARGET_PROTOCOL_RF_COLLISION_LEVEL) && (ui8NFCTargetProtocol != (TRF79X0_NFC_TARGET_PROTOCOL_RF_WAKE_UP | TRF79X0_NFC_TARGET_PROTOCOL_RF_COLLISION_LEVEL | TRF79X0_NFC_TARGET_PROTOCOL_ISO14443B | TRF79X0_NFC_TARGET_PROTOCOL_106KBPS))) || (ui8IrqStatus & IRQ_STATUS_PROTOCOL_ERROR))
            {
                eIrqStatusFlag = IRQ_STATUS_PROTOCOL_ERROR;
            }
        }
        else
        {
            TRF79x0_readSingle(&ui8IrqStatus, TRF79X0_IRQ_STATUS_REG);
        }

        if (eIrqStatusFlag != IRQ_STATUS_PROTOCOL_ERROR)
        {
            if (ui8IrqStatus & IRQ_STATUS_TX_COMPLETE)
            {
                eIrqStatusFlag = IRQ_STATUS_TX_COMPLETE;
                TRF79x0_directCommand(TRF79X0_RESET_FIFO_CMD);
            }
            else if (ui8IrqStatus & IRQ_STATUS_RX_COMPLETE)
            {
                eIrqStatusFlag = IRQ_STATUS_RX_COMPLETE;
                TRF79x0_readSingle(&g_ui8cbFifoBuffer, TRF79X0_FIFO_STATUS_REG);
                if ((g_ui8cbFifoBuffer > 0) && ((g_ui8cbFifoBuffer & TRF79X0_FIFO_OVERFLOW) != TRF79X0_FIFO_OVERFLOW))
                {
                    TRF79x0_readCont(g_ui8FifoBuffer, TRF79X0_FIFO_REG, g_ui8cbFifoBuffer);
                    eIrqStatusFlag = IRQ_STATUS_RX_COMPLETE;
                }
            }
        }
    }

    if (GPIO_getInputPinValue(TRF_IRQ_PORT, TRF_IRQ))
    {
        g_ui8IrqFlag = 1;
    }
    else
    {
        g_ui8IrqFlag = 0;
    }
    g_ui8TimeOutFlag = 0x00;

    return eIrqStatusFlag;
}
