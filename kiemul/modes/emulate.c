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
        }
        while (bContinueStateMachine);
    }
    while (!bExitMode);
}
