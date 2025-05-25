/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "field.h"

const uint8_t FIELD_FULL_BITMASK[] = {
    0b00000 /* 0 */, 0b00001 /* 1 */, 0b00001 /* 2 */, 0b00011 /* 3 */, // -- on MODES leds
    0b00011 /* 4 */, 0b00111 /* 5 */, 0b01111 /* 6 */, 0b11111 /* 7 */, // -- on STATUS leds
};

void MODE_field()
{
    uint8_t reg = 0;

    LEDS_Bitmask(LEDS, NB_LEDS, 0b00000);

    TRF7970A_SPI_Write_SingleRegister(TRF79X0_CHIP_STATUS_CTRL_REG, TRF79X0_STATUS_CTRL_RECEIVER_ON);
    __no_operation();
    __no_operation();

    IRQ_Global &= ~IRQ_SOURCE_SW1;
    do
    {
        TRF7970A_SPI_DirectCommand(TRF79X0_TEST_EXTERNAL_RF_CMD);
        TIMER_delay_Milliseconds(100);
        reg = TRF7970A_SPI_Read_SingleRegister(TRF79X0_RSSI_LEVEL_REG);
        LEDS_Bitmask(LEDS, NB_LEDS, FIELD_FULL_BITMASK[reg & 0b111]);
    } while(!(IRQ_Global & IRQ_SOURCE_SW1));

    LEDS_Bitmask(LEDS, NB_LEDS, 0b00000);
}
