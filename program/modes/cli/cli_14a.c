/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "cli_14a.h"
#if !defined(__MSP430FR2673__)
#include "../../14a/14a.h"

const CLI_FUNCTION CLI_14A_Functions[] = {
    {.name = "info",    .function = CLI_14A_info,           .description = "ISO 14443-3A anticolison + RATS"},
    {.name = "emul",    .function = CLI_14A_emul,           .description = "ISO 14443-3A basic emulation"},
};

const CLI_MODULE CLI_14A_Module = {.name = "14a", .description = "ISO 14443A", .nbFunctions = count_of(CLI_14A_Functions), .Functions = CLI_14A_Functions};

void CLI_14A_info()
{
    uint16_t ATQA;
    uint8_t ret, UID[10], cbUID, SAK;

    TRF7970A_mode(&K14A_TRF7970A_Mode_Initiator);
    ret = K14A3_Anticoll(&ATQA, UID, &cbUID, &SAK);
    if (ret == IRQ_SOURCE_NONE)
    {
        printf("ATQA: 0x%04x / %02hx %02hx" UART_NEWLINE "SAK : 0x%02hx" UART_NEWLINE "UID : ", ATQA, ((uint8_t*) &ATQA)[0], ((uint8_t*) &ATQA)[1], SAK);
        kprinthex(UID, cbUID);
        if (SAK & 0x20)
        {
            ret = K14A4_Rats();
            if(ret == IRQ_SOURCE_NONE)
            {
                printf("RATS: ");
                kprinthex(g_ui8_14a_Buffer, g_ui8_cb14a_Buffer);
            }
        }
    }
    TRF7970A_SPI_Write_SingleRegister(TRF79X0_CHIP_STATUS_CTRL_REG, 0x00); // if we let it run on battery :')
}

const T3A_INFOS t3a_infos_test10 = {
    .ATQA = 0x0004,
    .cbUID = 10,
    .UID = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa},
    .SAK = 0x00,
};

void CLI_14A_emul()
{
    uint8_t bContinueStateMachine, bExitMode = 0, BP_IrqSource, TRF7970A_irqStatus, bIsActivated;

    K14A3_TG_Prepare_AC_Buffer(&t3a_infos_test10);

    printf("ATQA: 0x%04x / %02hx %02hx" UART_NEWLINE "SAK : 0x%02hx" UART_NEWLINE "UID : ", t3a_infos_test10.ATQA, ((uint8_t*) &t3a_infos_test10.ATQA)[0], ((uint8_t*) &t3a_infos_test10.ATQA)[1], t3a_infos_test10.SAK);
    kprinthex(t3a_infos_test10.UID, t3a_infos_test10.cbUID);
    printf("> ENTER / ESC / CTRL+C or SW2 to stop" UART_NEWLINE);
    do
    {
        TRF7970A_mode(&K14A_TRF7970A_Mode_Target);
        TRF7970A_SPI_DirectCommand(TRF79X0_RUN_DECODERS_CMD);
        LED_ON(LED_INDEX_STATUS_BLUE);

        bIsActivated = 0;
        do
        {
            bContinueStateMachine = 0;
            BP_IrqSource = IRQ_Wait_for(IRQ_SOURCE_SW2 | IRQ_SOURCE_UART_RX | IRQ_SOURCE_TRF7970A, &TRF7970A_irqStatus, 0);
            if (BP_IrqSource & (IRQ_SOURCE_UART_RX | IRQ_SOURCE_SW2))
            {
                bExitMode = 1;
            }
            else if (BP_IrqSource & IRQ_SOURCE_TRF7970A)
            {
                if (K14A_Recv(0, TRF7970A_irqStatus))
                {
                   K14A3_TG_AC_AnswerTo(&bIsActivated);
                   bContinueStateMachine = 1;
                }
            }
        }
        while (bContinueStateMachine);
        LED_OFF(LED_INDEX_STATUS_BLUE);
    }
    while (!bExitMode);

}
#endif
