/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "cli_data.h"
#include "cli_slot.h"

const CLI_FUNCTION CLI_DATA_Functions[] = {
    {.name = "info",    .function = CLI_DATA_info,      .description = "Show current data UID"},

    {.name = "load",    .function = CLI_DATA_load,      .description = "Load data from a Base64 blob (dump)"},
    {.name = "show",    .function = CLI_DATA_show,      .description = "Show current data"},
    {.name = "dump",    .function = CLI_DATA_dump,      .description = "Dump current data (Base64)"},
    {.name = "uid",     .function = CLI_DATA_uid,       .description = "Change UID in current data"},
    {.name = "rdbl",    .function = CLI_DATA_rdbl,      .description = "Read a block of current data (block_number)"},
    {.name = "wrbl",    .function = CLI_DATA_wrbl,      .description = "Write a value in a block of current data (block_number value)"},

    {.name = "emul",    .function = CLI_DATA_emul,      .description = "Emulate current data"},

    {.name = "save",    .function = CLI_SLOT_save,      .description = "> slot save"},

};

const CLI_MODULE CLI_DATA_Module = {.name = "data", .description = "Current data in RAM", .nbFunctions = count_of(CLI_DATA_Functions), .Functions = CLI_DATA_Functions};

void CLI_DATA_info()
{
    printf(UART_NEWLINE "DATA" UART_NEWLINE "[ -- ] ");
    st25tb_utils_Display_UIDChip(SLOTS_ST25TB_Current[SLOTS_ST25TB_INDEX_UID]);
}

#define BASE64_4K_MAX_TO_DECODE     700
#define BASE64_2K_MAX_TO_DECODE     360
#define BASE64_512_MAX_TO_DECODE    104

#if defined(SLOTS_ST25TB_SUPPORT_4K)
#define BASE64_MAX_TO_DECODE    BASE64_4K_MAX_TO_DECODE
#elif defined(SLOTS_ST25TB_SUPPORT_2K)
#define BASE64_MAX_TO_DECODE    BASE64_2K_MAX_TO_DECODE
#elif defined(SLOTS_ST25TB_SUPPORT_512)
#define BASE64_MAX_TO_DECODE    BASE64_512_MAX_TO_DECODE
#else
#error No ST25TB support selected
#endif

void CLI_DATA_load()
{
    char *strToken;
    uint16_t cbEncoded;
    int16_t cbDecoded;
    void *pvData;
    uint8_t ret;

    strToken = CLI_NextArg();
    if(strToken)
    {
        cbEncoded = strlen(strToken);
        if((cbEncoded >= BASE64_512_MAX_TO_DECODE) && (cbEncoded <= BASE64_MAX_TO_DECODE))
        {
            printf("> Load from CLI (base64 - %u)..." UART_NEWLINE, cbEncoded);
            cbDecoded = CLI_BASE64_decode(strToken, cbEncoded, (uint8_t *) SLOTS_ST25TB_Current);
            if(cbDecoded != SLOTS_ST25TB_SIZE_INTERNAL)
            {
                pvData = NULL;

                printf("> Returned size (%i) is != from expected size (%u), will try to adjust SYSTEM & UID..." UART_NEWLINE "> ", cbDecoded, SLOTS_ST25TB_SIZE_INTERNAL);
#if defined(SLOTS_ST25TB_SUPPORT_4K)
                if(cbDecoded == SLOTS_ST25TB_2K_SIZE_INTERNAL)
                {
                    pvData = SLOTS_ST25TB_Current[SLOTS_ST25TB_2K_INDEX_SYSTEM];
                }
                else
#endif
#if defined(SLOTS_ST25TB_SUPPORT_4K) || defined(SLOTS_ST25TB_SUPPORT_2K)
                if(cbDecoded == SLOTS_ST25TB_512_SIZE_INTERNAL)
                {
                    pvData = SLOTS_ST25TB_Current[SLOTS_ST25TB_512_INDEX_SYSTEM];
                }
                else
#endif
                {
                    pvData = NULL;
                    printf("Error with returned size: %i" UART_NEWLINE, cbDecoded);
                }

                if(pvData)
                {
                    memcpy(SLOTS_ST25TB_Current[SLOTS_ST25TB_INDEX_SYSTEM], pvData, 3 * 4);
                    memset(pvData, 0x00, 3 * 4);
                    ret = 1;
                    printf("Fixed!" UART_NEWLINE);
                }
            }
            else
            {
                ret = 1;
            }

            if(ret)
            {
                CLI_DATA_show();
            }
        }
        else printf("Argument size is %u ; valid in [%u ; %u]" UART_NEWLINE, cbEncoded, BASE64_512_MAX_TO_DECODE, BASE64_MAX_TO_DECODE);
    }
}


void CLI_DATA_dump()
{
    CLI_DATA_show();
    CLI_BASE64_kprint((const uint8_t *) SLOTS_ST25TB_Current, SLOTS_ST25TB_SIZE_INTERNAL);
}

void CLI_DATA_show()
{
    printf("DATA (ram) ..." UART_NEWLINE);
    st25tb_utils_Display_dump((const uint8_t (*)[4]) SLOTS_ST25TB_Current, SLOTS_ST25TB_INDEX_UID);
}

void CLI_DATA_uid()
{
    char *strToken;
    uint64_t uid;

    printf("Current ");
    st25tb_utils_Display_UIDChip(SLOTS_ST25TB_Current[SLOTS_ST25TB_INDEX_UID]);
    strToken = CLI_NextArg();
    if(strToken)
    {
        if(strlen(strToken) == 16)
        {
            uid = strtoull(strToken, NULL, 16);
            if(uid)
            {
                *(uint64_t *) SLOTS_ST25TB_Current[SLOTS_ST25TB_INDEX_UID] = uid;
                printf("**New** ");
                st25tb_utils_Display_UIDChip(SLOTS_ST25TB_Current[SLOTS_ST25TB_INDEX_UID]);
            }
        }
        else
        {
            printf("Invalid UID size, 16 is needed" UART_NEWLINE);
        }
    }
}

void CLI_DATA_rdbl()
{
    uint8_t blockNumber;

    if(CLI_BlockNumber_Value(NULL, &blockNumber, NULL))
    {
        st25tb_utils_Display_sector((const uint8_t (*)[4]) SLOTS_ST25TB_Current, blockNumber);
    }
}

void CLI_DATA_wrbl()
{
    uint8_t blockNumber, Value[4];
    if(CLI_BlockNumber_Value(NULL, &blockNumber, Value))
    {
        printf("Cur: ");
        st25tb_utils_Display_sector((const uint8_t (*)[4]) SLOTS_ST25TB_Current, blockNumber);
        st25tb_utils_Write_sector((const uint8_t (*)[4]) SLOTS_ST25TB_Current, blockNumber, Value);
        printf("Now: ");
        st25tb_utils_Display_sector((const uint8_t (*)[4]) SLOTS_ST25TB_Current, blockNumber);
    }
}

void CLI_DATA_emul()
{
    uint8_t bContinueStateMachine, bExitMode = 0, BP_IrqSource, TRF7970A_irqStatus;

    printf("Emulation of current data with ");
    st25tb_utils_Display_UIDChip(SLOTS_ST25TB_Current[SLOTS_ST25TB_INDEX_UID]);
    printf("> ENTER / ESC / CTRL+C to stop" UART_NEWLINE);

    do
    {
        ST25TB_TRF7970A_Mode(0);
        TRF7970A_SPI_DirectCommand(TRF79X0_RUN_DECODERS_CMD);
        LED_ON(LED_INDEX_STATUS_BLUE);
        do
        {
            bContinueStateMachine = 0;
            BP_IrqSource = IRQ_Wait_for(IRQ_SOURCE_UART_RX | IRQ_SOURCE_TRF7970A, &TRF7970A_irqStatus, 0);
            if (BP_IrqSource & IRQ_SOURCE_UART_RX)
            {
                bExitMode = 1;
            }
            else if (BP_IrqSource & IRQ_SOURCE_TRF7970A)
            {
                if (ST25TB_Recv(0, TRF7970A_irqStatus))
                {
                    bContinueStateMachine = ST25TB_Target_ResponseTo();
                }
            }
        }
        while (bContinueStateMachine);
        LED_OFF(LED_INDEX_STATUS_BLUE);
    }
    while (!bExitMode);
}
