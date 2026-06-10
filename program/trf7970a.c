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

void TRF7970A_mode(const TRF7970A_MODE * pMode)
{
    TRF_IRQ_DISABLE();
    TRF7970A_SPI_DirectCommand(TRF79X0_SOFT_INIT_CMD);
    __no_operation();
    __no_operation();
    TRF7970A_SPI_DirectCommand(TRF79X0_IDLE_CMD);
    TIMER_delay_Milliseconds(2);
    TRF7970A_SPI_Send_raw(pMode->seq, pMode->cbSec);
    TIMER_delay_Milliseconds(pMode->delay);
    TRF_IRQ_ENABLE();
}

void TRF7970A_SPI_Send_raw(const uint8_t *pcbData, uint8_t cbData)
{
    TRF_CS_ENABLE();
#if defined(__msp430)
    while(cbData > 0)
    {
        TRF_SPI_SEND(*pcbData++);
        cbData--;
    }
#elif defined(STM32F405xx)
    HAL_SPI_Transmit(SPI_INTERNAL_HANDLE, (uint8_t *) pcbData, cbData, HAL_MAX_DELAY);
#else
#error Not supported
#endif
    TRF_CS_DISABLE();
}

void TRF7970A_SPI_DirectCommand_internal(uint8_t CommandCode_Preparred) // be careful, optimization make multiple direct commands too fast, a cycle between can help...
{
    TRF_CS_ENABLE();
#if defined(__msp430)
    TRF_SPI_SEND(CommandCode_Preparred);
#elif defined(STM32F405xx)
    HAL_SPI_Transmit(SPI_INTERNAL_HANDLE, &CommandCode_Preparred, 1, HAL_MAX_DELAY);
#else
#error Not supported
#endif
    TRF_CS_DISABLE();
}

uint8_t TRF7970A_SPI_Read_SingleRegister_internal(uint8_t Register_Prepared)
{
    uint8_t res;

    TRF_CS_ENABLE();
#if defined(__msp430)
    TRF_SPI_SEND(Register_Prepared);
    TRF_SPI_RECV(res);
#elif defined(STM32F405xx)
    uint8_t buffer[2] = {Register_Prepared, };
    HAL_SPI_TransmitReceive(SPI_INTERNAL_HANDLE, buffer, buffer, sizeof(buffer), HAL_MAX_DELAY);
    res = buffer[1];
#else
#error Not supported
#endif
    TRF_CS_DISABLE();

    return res;
}

void TRF7970A_SPI_Write_SingleRegister_internal(uint8_t Register_Prepared, const uint8_t Value)
{
    TRF_CS_ENABLE();
#if defined(__msp430)
    TRF_SPI_SEND(Register_Prepared);
    TRF_SPI_SEND(Value);
#elif defined(STM32F405xx)
    uint8_t buffer[2] = {Register_Prepared, Value};
    HAL_SPI_Transmit(SPI_INTERNAL_HANDLE, buffer, sizeof(buffer), HAL_MAX_DELAY);
#else
#error Not supported
#endif
    TRF_CS_DISABLE();
}

void TRF7970A_SPI_Read_ContinuousRegister_internal(uint8_t Register_Prepared, uint8_t *pbData, uint8_t cbData)
{
    TRF_CS_ENABLE();
#if defined(__msp430)
    TRF_SPI_SEND(Register_Prepared);
    while(cbData > 0)
    {
        TRF_SPI_RECV(*pbData++);
        cbData--;
    }
#elif defined(STM32F405xx)
    HAL_SPI_Transmit(SPI_INTERNAL_HANDLE, &Register_Prepared, 1, HAL_MAX_DELAY);
    HAL_SPI_Receive(SPI_INTERNAL_HANDLE, pbData, cbData, HAL_MAX_DELAY);
#else
#error Not supported
#endif
    TRF_CS_DISABLE();
}

void TRF7970A_SPI_Write_Packet_TYPED_BB(const uint8_t *pcbData, uint8_t cbData, const uint8_t type, const uint8_t brokenBits)
{
    uint8_t ui8LenLowerNibble, ui8LenHigherNibble;
    uint16_t ui16TotalLength = cbData;

    if(brokenBits)
    {
        ui8LenLowerNibble = ((brokenBits & 0x07) << 1) | 0x01;
        ui16TotalLength--;
    }
    else
    {
        ui8LenLowerNibble = 0;
    }

    ui8LenLowerNibble |= (ui16TotalLength & 0x0f) << 4;
    ui8LenHigherNibble = (uint8_t) ((ui16TotalLength & 0x0ff0) >> 4);

    TRF_CS_ENABLE(); // TODO, see send raw ?
#if defined(__msp430)
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
#elif defined(STM32F405xx)
    uint8_t buffer[5] = {
        MK_DC(TRF79X0_RESET_FIFO_CMD),
        type,
        MK_WC(TRF79X0_TX_LENGTH_BYTE1_REG),
		ui8LenHigherNibble, // in TRF79X0_TX_LENGTH_BYTE1_REG
        ui8LenLowerNibble   // in TRF79X0_TX_LENGTH_BYTE2_REG
    };
    HAL_SPI_Transmit(SPI_INTERNAL_HANDLE, buffer, sizeof(buffer), HAL_MAX_DELAY);
    HAL_SPI_Transmit(SPI_INTERNAL_HANDLE, (uint8_t *) pcbData, cbData, HAL_MAX_DELAY);
#endif
    TRF_CS_DISABLE();
}

uint8_t TRF7970A_SPI_waitIrq()
{
    while(!(IRQ_Global & IRQ_SOURCE_TRF7970A))
    {
        __emptyloop();
    }
    IRQ_Global &= ~IRQ_SOURCE_TRF7970A;

    return TRF7970A_getIrqStatus();
}
