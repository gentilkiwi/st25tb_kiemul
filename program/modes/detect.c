/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "detect.h"

void MODE_detect()
{
    uint8_t BP_IrqSource = IRQ_SOURCE_SW2, UID[8], index;

    do
    {
        if(BP_IrqSource == IRQ_SOURCE_SW2) // to deal with first start and restart
        {
            ST25TB_TRF7970A_Mode(1);
            LEDS_STATUS_Bitmask(0b000);
            LEDS_SLOTS_Bitmask(0b00000000);
            index = SLOTS_FIND_INVALID_INDEX;
        }

        BP_IrqSource = IRQ_Wait_for(IRQ_SOURCE_SW1 | IRQ_SOURCE_SW2 | IRQ_SOURCE_TIMER, NULL, ST25TB_INITIATOR_DELAY_BEFORE_RETRY);
        if(BP_IrqSource & IRQ_SOURCE_TIMER)
        {
            LED_ON(LED_INDEX_STATUS_BLUE);
            BP_IrqSource = ST25TB_Initiator_Initiate_Select_UID_C1_C2(UID, NULL, NULL);
            LED_OFF(LED_INDEX_STATUS_BLUE);

            if(BP_IrqSource == IRQ_SOURCE_NONE)
            {
                TRF7970A_SPI_Write_SingleRegister(TRF79X0_CHIP_STATUS_CTRL_REG, 0x00); // if we let it run on battery :')

                LED_ON(LED_INDEX_STATUS_GREEN);
                index = SLOTS_FindByUID(UID);
                if(index != SLOTS_FIND_INVALID_INDEX)
                {
                    SLOTS_Change(index);
#if defined(__MSP430FR2476__) // we don't show the slot with a LED here, so we use LED_BLUE to signal
                    LED_ON(LED_INDEX_STATUS_BLUE);
#endif
                    kprintf("|%s| Detected in slot %hu" UART_NEWLINE, __FUNCTION__, index);
                }
#if defined(REFERENCES_DATA_READY)
                if(REFERENCES_FindByUID(UID) != REFERENCES_FIND_INVALID_INDEX)
                {
                    LED_ON(LED_INDEX_STATUS_RED);
                    kprintf("|%s| Detected in REFERENCES" UART_NEWLINE, __FUNCTION__);
                }
#endif
                BP_IrqSource = IRQ_Wait_for(IRQ_SOURCE_SW1 | IRQ_SOURCE_SW2, NULL, 0);
            }
        }
    }
    while (!(BP_IrqSource & IRQ_SOURCE_SW1));

    if(index == SLOTS_FIND_INVALID_INDEX)
    {
        LED_Slot(FlashStoredData.CurrentSlot);
    }
}
