#include "nfc_spi.h"

void SPI_SendByte(uint8_t data)
{
    UCB0TXBUF = data;
    while (UCB0STAT & UCBUSY);
}

uint8_t SPI_ReceiveByte()
{
    UCB0TXBUF = 0x00;
    while (UCB0STAT & UCBUSY);
    return UCB0RXBUF;
}

void SPI_setup()
{
    USCI_B_SPI_initMasterParam param = {
        .selectClockSource = USCI_B_SPI_CLOCKSOURCE_SMCLK,
        .clockSourceFrequency = MCLK_FREQ,
        .desiredSpiClock = SPI_CLK_FREQ,
        .msbFirst = USCI_B_SPI_MSB_FIRST,
        .clockPhase = USCI_B_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT,
        .clockPolarity = USCI_B_SPI_CLOCKPOLARITY_INACTIVITY_LOW
    };

    USCI_B_SPI_initMaster(SPI_MODULE_BASE_ADDR, &param);
    GPIO_setAsPeripheralModuleFunctionOutputPin(SPI_PORT, SPI_CLK | SPI_MOSI | SPI_MISO);
    USCI_B_SPI_enable(SPI_MODULE_BASE_ADDR);
}

void SPI_directCommand(uint8_t command)
{
    volatile uint8_t x;

    command &= TRF79X0_ADDRESS_MASK;
    command |= TRF79X0_CONTROL_CMD;

    SLAVE_SELECT_LOW
    SPI_SendByte(command);
    SLAVE_SELECT_HIGH
}

void SPI_readSingle(uint8_t *pbuf, uint8_t reg)
{
    volatile uint8_t x;

    reg &= TRF79X0_ADDRESS_MASK;
    reg |= TRF79X0_CONTROL_REG_READ | TRF79X0_REG_MODE_SINGLE;

    SLAVE_SELECT_LOW
    SPI_SendByte(reg);
    *pbuf = SPI_ReceiveByte();
    SLAVE_SELECT_HIGH
}

void SPI_readCont(uint8_t *pbuf, uint8_t reg, uint8_t length)
{	
	volatile int8_t x;

    reg &= TRF79X0_ADDRESS_MASK;
    reg |= TRF79X0_CONTROL_REG_READ | TRF79X0_REG_MODE_CONTINUOUS;

    SLAVE_SELECT_LOW
    SPI_SendByte(reg);
    while (length > 0)
    {
        *pbuf = SPI_ReceiveByte();
        pbuf++;
        length--;
    }
    SLAVE_SELECT_HIGH
}

void SPI_writeSingle(uint8_t data, uint8_t reg)
{
    volatile int8_t x;

    reg &= TRF79X0_ADDRESS_MASK;
    reg |= TRF79X0_CONTROL_REG_WRITE | TRF79X0_REG_MODE_SINGLE;

    SLAVE_SELECT_LOW
    SPI_SendByte(reg);
    SPI_SendByte(data);
    SLAVE_SELECT_HIGH
}

void SPI_writeCont(uint8_t *pbuf, uint8_t reg, uint8_t length)
{
    volatile int8_t x;

    reg &= TRF79X0_ADDRESS_MASK;
    reg |= TRF79X0_CONTROL_REG_WRITE | TRF79X0_REG_MODE_CONTINUOUS;

    SLAVE_SELECT_LOW
    SPI_SendByte(reg);
    while (length > 0)
    {
        SPI_SendByte(*pbuf);
        pbuf++;
        length--;
    }
    SLAVE_SELECT_HIGH
}

void SPI_writePacket(const uint8_t *pbuf, uint8_t total_length, uint8_t payload_length)
{
    uint8_t ui8LenLowerNibble;
    uint8_t ui8LenHigherNibble;
    uint16_t ui16TotalLength;

    ui16TotalLength = total_length;
    ui8LenLowerNibble = (ui16TotalLength & 0x0f) << 4;
    ui8LenHigherNibble = (uint8_t) ((ui16TotalLength & 0x0ff0) >> 4);

    SLAVE_SELECT_LOW
    SPI_SendByte(TRF79X0_CONTROL_CMD | TRF79X0_RESET_FIFO_CMD);
    SPI_SendByte(TRF79X0_CONTROL_CMD | TRF79X0_TRANSMIT_CRC_CMD);
    SPI_SendByte(TRF79X0_CONTROL_REG_WRITE | TRF79X0_REG_MODE_CONTINUOUS | TRF79X0_TX_LENGTH_BYTE1_REG);
    SPI_SendByte(ui8LenHigherNibble);   // in TRF79X0_TX_LENGTH_BYTE1_REG
    SPI_SendByte(ui8LenLowerNibble);    // in TRF79X0_TX_LENGTH_BYTE2_REG
    while (payload_length > 0)
    {
        SPI_SendByte(*pbuf);            // in TRF79X0_FIFO_REG and +
        pbuf++;
        payload_length--;
    }
    SLAVE_SELECT_HIGH
}
