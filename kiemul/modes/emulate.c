/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "emulate.h"

void MODE_emulate()
{
    bool bContinueStateMachine, bExitMode = false;
    uint8_t BP_IrqSource, TRF7970A_irqStatus;

    do
    {
        ST25TB_TRF7970A_Mode(false);
        TRF7970A_SPI_DirectCommand(TRF79X0_RUN_DECODERS_CMD);

        do
        {
            bContinueStateMachine = false;
            BP_IrqSource = IRQ_Wait_for_SW1_or_SW2_or_TRF(&TRF7970A_irqStatus);
            if(BP_IrqSource & IRQ_SOURCE_SW1)
            {
                bExitMode = true;
            }
            else if(BP_IrqSource & IRQ_SOURCE_TRF7970A)
            {
                if (ST25TB_Recv(false, TRF7970A_irqStatus))
                {
                    bContinueStateMachine = ST25TB_Target_ResponseTo();
                }
            }
#if defined(MODE_EMULATE_SW2_SAVE)
            else if((BP_IrqSource & IRQ_SOURCE_SW2) && FlashStoredData.CurrentSlot) // Slot #0 is forbidden
            {
                LED_ON(LED_INDEX_STATUS_BLUE);
                SLOTS_Save_Current();
                TIMER_delay_Milliseconds(500);
                LED_OFF(LED_INDEX_STATUS_BLUE);
            }
#endif
        }
        while (bContinueStateMachine);
    }
    while (!bExitMode);
}
