/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "trf7970a.h"

volatile bool g_trf7970a_irq_flag = false;

void TRF7970A_init()
{
    LP_TIMER_delay_Millisecond(10);

    // 6.11 TRF7970A Initialization
    TRF7970A_directCommand(TRF79X0_SOFT_INIT_CMD);
    TRF7970A_directCommand(TRF79X0_IDLE_CMD);
    LP_TIMER_delay_Millisecond(1);
    TRF7970A_directCommand(TRF79X0_RESET_FIFO_CMD);
    TRF7970A_writeSingle(0x00, TRF79X0_CHIP_STATUS_CTRL_REG);
    TRF7970A_clearIrqStatus();
}

void TRF7970A_writeRaw(const uint8_t *pcui8Payload, uint8_t ui8Length)
{
    BP_TRF_SPI_CS_ENABLE();
    while (ui8Length > 0)
    {
        LP_SPI_sendByte(*pcui8Payload);
        pcui8Payload++;
        ui8Length--;
    }
    BP_TRF_SPI_CS_DISABLE();
}

void TRF7970A_directCommand_internal(uint8_t ui8Command)
{
    BP_TRF_SPI_CS_ENABLE();
    LP_SPI_sendByte(ui8Command);
    BP_TRF_SPI_CS_DISABLE();
}

uint8_t TRF7970A_readSingle_internal(uint8_t ui8Register)
{
    uint8_t res;

    BP_TRF_SPI_CS_ENABLE();
    LP_SPI_sendByte(ui8Register);
    res = LP_SPI_receiveByte();
    BP_TRF_SPI_CS_DISABLE();

    return res;
}

void TRF7970A_writeSingle_internal(uint8_t ui8Value, uint8_t ui8Register)
{
    BP_TRF_SPI_CS_ENABLE();
    LP_SPI_sendByte(ui8Register);
    LP_SPI_sendByte(ui8Value);
    BP_TRF_SPI_CS_DISABLE();
}

void TRF7970A_readCont_internal(uint8_t *pui8Payload, uint8_t ui8Register, uint8_t ui8Length)
{
    BP_TRF_SPI_CS_ENABLE();
    LP_SPI_sendByte(ui8Register);
    while (ui8Length > 0)
    {
        *pui8Payload = LP_SPI_receiveByte();
        pui8Payload++;
        ui8Length--;
    }
    BP_TRF_SPI_CS_DISABLE();
}

void TRF7970A_writeCont_internal(uint8_t *pui8Payload, uint8_t ui8Register, uint8_t ui8Length)
{
    BP_TRF_SPI_CS_ENABLE();
    LP_SPI_sendByte(ui8Register);
    while (ui8Length > 0)
    {
        LP_SPI_sendByte(*pui8Payload);
        pui8Payload++;
        ui8Length--;
    }
    BP_TRF_SPI_CS_DISABLE();
}

void TRF7970A_writePacketToTransmit(const uint8_t *pui8Payload, uint8_t ui8Length)
{
    uint8_t ui8LenLowerNibble, ui8LenHigherNibble;
    uint16_t ui16TotalLength = ui8Length;

    ui16TotalLength = ui8Length;
    ui8LenLowerNibble = (ui16TotalLength & 0x0f) << 4;
    ui8LenHigherNibble = (uint8_t) ((ui16TotalLength & 0x0ff0) >> 4);

    BP_TRF_SPI_CS_ENABLE();
    LP_SPI_sendByte(TRF79X0_CONTROL_CMD | TRF79X0_RESET_FIFO_CMD);
    LP_SPI_sendByte(TRF79X0_CONTROL_CMD | TRF79X0_TRANSMIT_CRC_CMD);
    LP_SPI_sendByte(TRF79X0_CONTROL_REG_WRITE | TRF79X0_REG_MODE_CONTINUOUS | TRF79X0_TX_LENGTH_BYTE1_REG);
    LP_SPI_sendByte(ui8LenHigherNibble);   // in TRF79X0_TX_LENGTH_BYTE1_REG
    LP_SPI_sendByte(ui8LenLowerNibble);    // in TRF79X0_TX_LENGTH_BYTE2_REG
    while (ui8Length > 0)
    {
        LP_SPI_sendByte(*pui8Payload);     // in TRF79X0_FIFO_REG and +
        pui8Payload++;
        ui8Length--;
    }
    BP_TRF_SPI_CS_DISABLE();
}

void TRF7970A_ignoreCmd()
{
    TRF7970A_directCommand(TRF79X0_STOP_DECODERS_CMD);
    TRF7970A_directCommand(TRF79X0_RUN_DECODERS_CMD);
}

uint8_t TRF7970A_waitIrq()
{
    g_trf7970a_irq_flag = BP_TRF_READ_IRQ(); // because sometimes it's already in IRQ
    while(!g_trf7970a_irq_flag)
    {
        __low_power_mode_0();
    }
    return TRF7970A_getIrqStatus();
}
