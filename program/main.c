/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "modes.h"

void main(void)
{
    uint16_t calculatedCRC;

    MODES_init();
#if defined(ST25TB_HAVE_CLI)
    calculatedCRC = CRC16_CCIT((const uint8_t *)(TLVMEM_START + 0x04), 0xf4);
    printf("CRC Value   : r:0x%04" PRIx16 " c:0x%04" PRIx16 " - %s" UART_NEWLINE
            "Device ID   : 0x%04" PRIx16 UART_NEWLINE
            "Lot wafer ID: 0x%08" PRIx32 " (x:%" PRIu16 "/y:%" PRIu16 ")" UART_NEWLINE
            "SYSRSTIV    : 0x%04" PRIx16 UART_NEWLINE
            , CRC_VALUE, calculatedCRC, (CRC_VALUE == calculatedCRC) ? "OK" : "KO"
            , DEVICE_ID
            , DIE_LOT_WAFER_ID, DIE_LOT_WAFER_X_POS, DIE_LOT_WAFER_Y_POS
            , SYSRSTIV
    );
#endif
    MODES_main_loop();
}
