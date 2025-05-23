/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "select.h"

void MODE_select()
{
    uint8_t BP_IrqSource, index = FlashStoredData.CurrentSlot;

    LEDS_STATUS_Bitmask(index); //
    do
    {
        BP_IrqSource = IRQ_Wait_for(IRQ_SOURCE_SW1 | IRQ_SOURCE_SW2, NULL, 0);
        if(BP_IrqSource & IRQ_SOURCE_SW2)
        {
            index++;
            if(index >= SLOTS_ST25TB_COUNT)
            {
                index = 0;
            }
            SLOTS_Change(index);
            LEDS_STATUS_Bitmask(index); //

            TIMER_delay_Milliseconds(150);
        }
    }
    while (!(BP_IrqSource & IRQ_SOURCE_SW1));
}
