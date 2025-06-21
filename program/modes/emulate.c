/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "emulate.h"

void MODE_emulate()
{
    uint8_t bContinueStateMachine, bExitMode = 0, BP_IrqSource, TRF7970A_irqStatus;

    do
    {
        ST25TB_TRF7970A_Mode(0);
        TRF7970A_SPI_DirectCommand(TRF79X0_RUN_DECODERS_CMD);

        do
        {
            bContinueStateMachine = 0;
            BP_IrqSource = IRQ_Wait_for(IRQ_SOURCE_SW1 | IRQ_SOURCE_SW2 | IRQ_SOURCE_TRF7970A, &TRF7970A_irqStatus, 0);
            if(BP_IrqSource & IRQ_SOURCE_SW1)
            {
                bExitMode = 1;
            }
            else if(BP_IrqSource & IRQ_SOURCE_TRF7970A)
            {
                if (ST25TB_Recv(0, TRF7970A_irqStatus))
                {
                    bContinueStateMachine = ST25TB_Target_ResponseTo();
                }
            }
            else if(FlashStoredData.bModeEmulateSW2Save && (BP_IrqSource & IRQ_SOURCE_SW2) && FlashStoredData.CurrentSlot) // Slot #0 is forbidden
            {
                LED_ON(LED_INDEX_STATUS_BLUE);
                SLOTS_Save_Current();
                TIMER_delay_Milliseconds(500);
                LED_OFF(LED_INDEX_STATUS_BLUE);
            }
        }
        while (bContinueStateMachine);
    }
    while (!bExitMode);
}
