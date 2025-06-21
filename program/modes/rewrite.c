/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "rewrite.h"

void MODE_rewrite()
{
    uint8_t BP_IrqSource = IRQ_SOURCE_SW2;

    do
    {
        if(BP_IrqSource == IRQ_SOURCE_SW2) // to deal with first start and restart
        {
            ST25TB_TRF7970A_Mode(1);
            LEDS_STATUS_Bitmask(0b000);
        }

        BP_IrqSource = IRQ_Wait_for(IRQ_SOURCE_SW1 | IRQ_SOURCE_SW2 | IRQ_SOURCE_TIMER, NULL, ST25TB_INITIATOR_DELAY_BEFORE_RETRY);
        if(BP_IrqSource & IRQ_SOURCE_TIMER)
        {
            LED_ON(LED_INDEX_STATUS_BLUE);
            BP_IrqSource = ST25TB_Initiator_Write_Current_Card();
            LED_OFF(LED_INDEX_STATUS_BLUE);

            if(BP_IrqSource == IRQ_SOURCE_NONE)
            {
                TRF7970A_SPI_Write_SingleRegister(TRF79X0_CHIP_STATUS_CTRL_REG, 0x00); // if we let it run on battery :')

                LED_OFF(LED_INDEX_STATUS_RED);
                LED_ON(LED_INDEX_STATUS_GREEN);

                BP_IrqSource = IRQ_Wait_for(IRQ_SOURCE_SW1 | IRQ_SOURCE_SW2, NULL, 0);

                LED_OFF(LED_INDEX_STATUS_GREEN);
            }
            else if(BP_IrqSource & (IRQ_SOURCE_TRF7970A | IRQ_SOURCE_ST25TB_PROTOCOL_ERR))
            {
                LED_ON(LED_INDEX_STATUS_RED);
            }
        }
    }
    while (!(BP_IrqSource & IRQ_SOURCE_SW1));
}
