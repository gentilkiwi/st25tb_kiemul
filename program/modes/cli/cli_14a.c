/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "cli_14a.h"
#if !defined(__MSP430FR2673__)
#include "../../14a/14a.h"

const CLI_FUNCTION CLI_14A_Functions[] = {
    {.name = "info",    .function = CLI_14A_info,           .description = "3A Anticoll"},
};

const CLI_MODULE CLI_14A_Module = {.name = "14a", .description = "14A", .nbFunctions = count_of(CLI_14A_Functions), .Functions = CLI_14A_Functions};

void CLI_14A_info()
{
    uint16_t ATQA;
     uint8_t ret, UID[10], cbUID, SAK;

     TRF7970A_mode(&K14A_TRF7970A_Mode_Initiator);
     ret = K14A3_Anticoll(&ATQA, UID, &cbUID, &SAK);
     if(ret == IRQ_SOURCE_NONE)
     {
         printf("ATQA: 0x%04x / %02hx %02hx" UART_NEWLINE "SAK : 0x%02hx" UART_NEWLINE "UID : ", ATQA, ((uint8_t *) &ATQA)[0], ((uint8_t *) &ATQA)[1], SAK);
         kprinthex(UID, cbUID);
     }

     TIMER_delay_Milliseconds(10);

     TRF7970A_SPI_Write_SingleRegister(TRF79X0_CHIP_STATUS_CTRL_REG, 0x00); // if we let it run on battery :')
}

#endif
