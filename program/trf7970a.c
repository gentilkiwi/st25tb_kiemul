/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "trf7970a.h"

void TRF7970A_init()
{
    TRF_CS_DISABLE(); // just in case

    TRF_DISABLE();
    TIMER_delay_Milliseconds(10);
    TRF_ENABLE();
    TIMER_delay_Milliseconds(10);
    // 6.11 TRF7970A Initialization
    TRF7970A_SPI_DirectCommand(TRF79X0_SOFT_INIT_CMD);
    __no_operation();
    __no_operation();
    TRF7970A_SPI_DirectCommand(TRF79X0_IDLE_CMD);
    TIMER_delay_Milliseconds(1);
    TRF7970A_SPI_DirectCommand(TRF79X0_RESET_FIFO_CMD);
    TRF7970A_SPI_Write_SingleRegister(TRF79X0_CHIP_STATUS_CTRL_REG, 0x00);
    TRF7970A_clearIrqStatus();

    TRF_IRQ_ENABLE();
}

void TRF7970A_SPI_Send_raw(const uint8_t *pcbData, uint8_t cbData)
{
    TRF_CS_ENABLE();
    while(cbData > 0)
    {
        TRF_SPI_SEND(*pcbData++);
        cbData--;
    }
    TRF_CS_DISABLE();
}

void TRF7970A_SPI_DirectCommand_internal(uint8_t CommandCode_Preparred) // be careful, optimization make multiple direct commands too fast, a cycle between can help...
{
    TRF_CS_ENABLE();
    TRF_SPI_SEND(CommandCode_Preparred);
    TRF_CS_DISABLE();
}

uint8_t TRF7970A_SPI_Read_SingleRegister_internal(uint8_t Register_Prepared)
{
    uint8_t res;

    TRF_CS_ENABLE();
    TRF_SPI_SEND(Register_Prepared);
    TRF_SPI_RECV(res);
    TRF_CS_DISABLE();

    return res;
}

void TRF7970A_SPI_Write_SingleRegister_internal(uint8_t Register_Prepared, const uint8_t Value)
{
    TRF_CS_ENABLE();
    TRF_SPI_SEND(Register_Prepared);
    TRF_SPI_SEND(Value);

    TRF_CS_DISABLE();
}

void TRF7970A_SPI_Read_ContinuousRegister_internal(uint8_t Register_Prepared, uint8_t *pbData, uint8_t cbData)
{
    TRF_CS_ENABLE();
    TRF_SPI_SEND(Register_Prepared);
    while(cbData > 0)
    {
        TRF_SPI_RECV(*pbData++);
        cbData--;
    }
    TRF_CS_DISABLE();
}

void TRF7970A_SPI_Write_Packet_TYPED(const uint8_t *pcbData, uint8_t cbData, const uint8_t type)
{
    uint8_t ui8LenLowerNibble, ui8LenHigherNibble;
    uint16_t ui16TotalLength = cbData;

    ui8LenLowerNibble = (ui16TotalLength & 0x0f) << 4;
    ui8LenHigherNibble = (uint8_t) ((ui16TotalLength & 0x0ff0) >> 4);

    TRF_CS_ENABLE();
    TRF_SPI_SEND(MK_DC(TRF79X0_RESET_FIFO_CMD));
    TRF_SPI_SEND(type);
    TRF_SPI_SEND(MK_WC(TRF79X0_TX_LENGTH_BYTE1_REG));
    TRF_SPI_SEND(ui8LenHigherNibble); // in TRF79X0_TX_LENGTH_BYTE1_REG
    TRF_SPI_SEND(ui8LenLowerNibble);  // in TRF79X0_TX_LENGTH_BYTE2_REG
    while(cbData > 0)
    {
        TRF_SPI_SEND(*pcbData++);
        cbData--;
    }
    TRF_CS_DISABLE();
}

uint8_t TRF7970A_SPI_waitIrq()
{
    while(!(IRQ_Global & IRQ_SOURCE_TRF7970A))
    {
        __low_power_mode_0();
    }
    IRQ_Global &= ~IRQ_SOURCE_TRF7970A;

    return TRF7970A_getIrqStatus();
}
