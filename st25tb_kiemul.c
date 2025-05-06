/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "kiemul/board.h"
#include "kiemul/modes.h"

const KAKI_MODE Modes[] = {
    {.function = MODE_emulate,  .ledsModesBitmask = 0b01},
    {.function = MODE_rewrite,  .ledsModesBitmask = 0b10},
};

const KAKI_MODE Modes_2[] = {
    {.function = MODE_detect,   .ledsModesBitmask = 0b01},
    {.function = MODE_select,   .ledsModesBitmask = 0b10},
    {.function = MODE_learn,    .ledsModesBitmask = 0b11},
    {.function = MODE_tear,     .ledsModesBitmask = 0b00},
};

void main(void)
{
    uint8_t maxModes;
    const KAKI_MODE  *pMode, *cMode;

    BOARD_init();
    TRF7970A_init();
    LEDS_Animation();
    SLOTS_Change(FlashStoredData.CurrentSlot);

    if(P4IN & BIT0) // 14A Modes and LEARN only available if pushing MODE at startup
    {
        pMode = cMode = Modes;
        maxModes = count_of(Modes);
    }
    else
    {
        pMode = cMode = Modes_2;
        maxModes = count_of(Modes_2);
    }

    while(true)
    {
        g_irq_SW1 = false;
        g_irq_SW2 = false;
        LEDS_MODES_Bitmask(cMode->ledsModesBitmask);
        LEDS_STATUS_Bitmask(0);

        cMode->function();

        __no_operation();
        TRF7970A_SPI_DirectCommand(TRF79X0_STOP_DECODERS_CMD);
        __no_operation();
        __no_operation();
        TRF7970A_SPI_Write_SingleRegister(TRF79X0_CHIP_STATUS_CTRL_REG, 0x00);
        cMode++;
        if(cMode >= (pMode + maxModes))
        {
            cMode = pMode + 0;
        }
        TIMER_delay_Milliseconds(150);
    }
}
