/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "unk.h"

void MODE_unk()
{
    uint8_t BP_IrqSource = IRQ_SOURCE_SW2, UID[8], Counter1[4], Counter2[4];

    do
    {
        if(BP_IrqSource == IRQ_SOURCE_SW2) // to deal with first start and restart
        {
            ST25TB_TRF7970A_Mode(1);
            LEDS_STATUS_Bitmask(0b000);
            LEDS_SLOTS_Bitmask(0b00000000);
        }

        BP_IrqSource = IRQ_Wait_for(IRQ_SOURCE_SW1 | IRQ_SOURCE_SW2 | IRQ_SOURCE_TIMER, NULL, ST25TB_INITIATOR_DELAY_BEFORE_RETRY);
        if(BP_IrqSource & IRQ_SOURCE_TIMER)
        {
            LED_ON(LED_INDEX_STATUS_BLUE);
            BP_IrqSource = ST25TB_Initiator_Initiate_Select_UID_C1_C2(UID, Counter1, Counter2);
            LED_OFF(LED_INDEX_STATUS_BLUE);

            if(BP_IrqSource == IRQ_SOURCE_NONE)
            {
                TRF7970A_SPI_Write_SingleRegister(TRF79X0_CHIP_STATUS_CTRL_REG, 0x00); // if we let it run on battery :')

                if(!Counter1[0]) // Empty ticket
                {
                    LED_ON(LED_INDEX_STATUS_RED);
                    LED_Slot(0);
                }
                else if(Counter1[0] < 8) // Can be displayed on single LED slot
                {
                    LED_ON(LED_INDEX_STATUS_GREEN);
                    LED_Slot(Counter1[0]);
                }
                else // >= 8, it will use binary to display ON LED slots
                {
                    LED_ON(LED_INDEX_STATUS_BLUE);
                    LEDS_SLOTS_Bitmask(Counter1[0]);
                }

                if(UART_Enabled)
                {
                    st25tb_utils_Display_UIDChip(UID);
                    printf("..." UART_NEWLINE);
                    st25tb_utils_Display_sector_data(Counter1, ST25TB_IDX_COUNTER1);
                    st25tb_utils_Display_sector_data(Counter2, ST25TB_IDX_COUNTER2);
                    printf("..." UART_NEWLINE);
                }

                BP_IrqSource = IRQ_Wait_for(IRQ_SOURCE_SW1 | IRQ_SOURCE_SW2, NULL, 0);
            }
        }
    }
    while (!(BP_IrqSource & IRQ_SOURCE_SW1));

    LED_Slot(FlashStoredData.CurrentSlot);
}
