/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "cli_card.h"
#include "cli_data.h"

const CLI_FUNCTION CLI_CARD_Functions[] = {
    {.name = "load",    .function = CLI_CARD_load,      .description = "Read a card and load it in current data"},
    {.name = "show",    .function = CLI_CARD_show ,     .description = "Read a card and show content"},
    {.name = "dump",    .function = CLI_CARD_dump,      .description = "Read a card and load it in current data, then Base64 it"},
    {.name = "uid",     .function = CLI_CARD_uid,       .description = "Read the UID from a card"},
    {.name = "rdbl",    .function = CLI_CARD_rdbl,      .description = "Read a block of a card (block_number)"},
    {.name = "wrbl",    .function = CLI_CARD_wrbl,      .description = "Write a value in a block of a card (block_number value)"},

    {.name = "write",   .function = CLI_CARD_write,     .description = "Write the current data to a card (if UID is the same)"},
    {.name = "tear",    .function = CLI_CARD_tear,      .description = "Tear-off counters (5/6)"},

    {.name = "emul",    .function = CLI_DATA_emul,      .description = "> data emul"},
};

const CLI_MODULE CLI_CARD_Module = {.name = "card", .description = "Real card/reader interaction with the TRF7970A", .nbFunctions = count_of(CLI_CARD_Functions), .Functions = CLI_CARD_Functions};

void CLI_CARD_ERR_irqSource(const uint8_t BP_IrqSource)
{
    if(BP_IrqSource & IRQ_SOURCE_TRF7970A)
    {
        printf("TRF7970A communication error ; ");
    }

    if(BP_IrqSource & IRQ_SOURCE_ST25TB_PROTOCOL_ERR)
    {
        printf("ST25TB application error (not same value?) ; ");
    }

    if(BP_IrqSource & IRQ_SOURCE_TIMER)
    {
        printf("TIMER no response ; ");
    }

    printf(UART_NEWLINE);
}

void CLI_CARD_leave()
{
    TRF7970A_SPI_Write_SingleRegister(TRF79X0_CHIP_STATUS_CTRL_REG, 0x00); // if we let it run on battery :')
}

uint8_t CLI_CARD_Get()
{
    uint8_t ret = 0, i, BP_IrqSource, ui8ChipId;

    ST25TB_TRF7970A_Mode(1);
    LEDS_STATUS_Bitmask(0b000);

    for(i = 0; i < 3; i++)
    {
#if defined(CLI_CARD_MORE_VERBOSE_OPERATIONS)
        printf("> Initiate - ");
#endif
        LED_ON(LED_INDEX_STATUS_BLUE);
        BP_IrqSource = ST25TB_Initiator_CMD_Initiate(&ui8ChipId);
        LED_OFF(LED_INDEX_STATUS_BLUE);

        if(BP_IrqSource == IRQ_SOURCE_NONE)
        {
#if defined(CLI_CARD_MORE_VERBOSE_OPERATIONS)
            printf("OK - (ChipId 0x%02hX)" UART_NEWLINE "> Select - ", ui8ChipId);
#endif
            BP_IrqSource = ST25TB_Initiator_CMD_Select(ui8ChipId);
            if(BP_IrqSource == IRQ_SOURCE_NONE)
            {
#if defined(CLI_CARD_MORE_VERBOSE_OPERATIONS)
                printf("OK" UART_NEWLINE);
#endif
                ret = 1;
                break;
            }
            else
            {
#if !defined(CLI_CARD_MORE_VERBOSE_OPERATIONS)
                printf("Error with Select(0x%02hX): ", ui8ChipId);
#endif
                CLI_CARD_ERR_irqSource(BP_IrqSource);
            }
        }
        else
        {
#if !defined(CLI_CARD_MORE_VERBOSE_OPERATIONS)
            printf("Error with Initiate: ");
#endif
            CLI_CARD_ERR_irqSource(BP_IrqSource);
        }

        TIMER_delay_Milliseconds(ST25TB_INITIATOR_DELAY_BEFORE_RETRY);
    }

    if(!ret)
    {
        CLI_CARD_leave();
    }

    return ret;
}

uint8_t CLI_CARD_CMD_UID(uint8_t pui8Data[8])
{
    uint8_t ret = 0, BP_IrqSource, ui8Data[8];
#if defined(CLI_CARD_MORE_VERBOSE_OPERATIONS)
    printf("> Get_UID - ");
#endif
    BP_IrqSource = ST25TB_Initiator_CMD_CONFIRMED_Get_Uid(ui8Data);
    if(BP_IrqSource == IRQ_SOURCE_NONE)
    {
#if defined(CLI_CARD_MORE_VERBOSE_OPERATIONS)
        printf("OK - ");
        st25tb_utils_Display_UIDChip(ui8Data);
#endif
        if(pui8Data)
        {
            *(uint64_t *) pui8Data = *(uint64_t *)ui8Data;
        }

        ret = 1;
    }
    else
    {
#if !defined(CLI_CARD_MORE_VERBOSE_OPERATIONS)
        printf("Error with Get_UID: ");
#endif
        CLI_CARD_ERR_irqSource(BP_IrqSource);
    }

    return ret;
}

uint8_t CLI_CARD_CMD_Read_Block(const uint8_t ui8BlockIdx, uint8_t pui8Data[4])
{
    uint8_t ret = 0, BP_IrqSource, buffer[4];
#if defined(CLI_CARD_MORE_VERBOSE_OPERATIONS)
    printf("> Read_Block - %3hu - ", ui8BlockIdx);
#endif
    BP_IrqSource = ST25TB_Initiator_CMD_CONFIRMED_Read_Block(ui8BlockIdx, buffer);
    if(BP_IrqSource == IRQ_SOURCE_NONE)
    {
#if defined(CLI_CARD_MORE_VERBOSE_OPERATIONS)
        printf("OK - %02X %02X %02X %02X - %08lX" UART_NEWLINE, buffer[0], buffer[1], buffer[2], buffer[3], *(uint32_t *) buffer);
#endif
        if(pui8Data)
        {
            *(uint32_t *) pui8Data = *(uint32_t *)buffer;
        }
        ret = 1;
    }
    else
    {
#if !defined(CLI_CARD_MORE_VERBOSE_OPERATIONS)
        printf("Error when reading block # %hu: ", ui8BlockIdx);
#endif
        CLI_CARD_ERR_irqSource(BP_IrqSource);
    }

    return ret;
}

uint8_t CLI_CARD_CMD_Write_Block(const uint8_t ui8BlockIdx, const uint8_t pui8Data[4])
{
    uint8_t ret = 0, BP_IrqSource;
#if defined(CLI_CARD_MORE_VERBOSE_OPERATIONS)
    printf("> Write_Block - %3hu - %02X %02X %02X %02X - %08lX - ", ui8BlockIdx, pui8Data[0], pui8Data[1], pui8Data[2], pui8Data[3], *(uint32_t *) pui8Data);
#endif
    BP_IrqSource = ST25TB_Initiator_CMD_CONFIRMED_Write_Block(ui8BlockIdx, pui8Data);
    if (BP_IrqSource == IRQ_SOURCE_NONE)
    {
#if defined(CLI_CARD_MORE_VERBOSE_OPERATIONS)
        printf("OK" UART_NEWLINE);
#endif
        ret = 1;
    }
    else
    {
#if !defined(CLI_CARD_MORE_VERBOSE_OPERATIONS)
        printf("Error when writing block # %hu with value %02X %02X %02X %02X / %08lX : ", ui8BlockIdx, pui8Data[0], pui8Data[1], pui8Data[2], pui8Data[3], *(uint32_t *) pui8Data);
#endif
        CLI_CARD_ERR_irqSource(BP_IrqSource);
    }

    return ret;
}

void CLI_CARD_load()
{
    uint8_t nbSectors, i;

    if(CLI_CARD_Get())
    {
        if(CLI_CARD_CMD_UID((uint8_t *) (SLOTS_ST25TB_Current + SLOTS_ST25TB_INDEX_UID)))
        {
            nbSectors = ST25TB_Initiator_ValidateAndGetNBSectorsFromUID((uint8_t *) SLOTS_ST25TB_Current[SLOTS_ST25TB_INDEX_UID], NULL);
            printf("Sectors: %hu" UART_NEWLINE, nbSectors);
            if(nbSectors && (nbSectors <= SLOTS_ST25TB_SECTORS))
            {
                for(i = 0; i < nbSectors; i++)
                {
                    CLI_CARD_CMD_Read_Block(i, SLOTS_ST25TB_Current[i]);
                }
                CLI_CARD_CMD_Read_Block(ST25TB_IDX_SYSTEM, SLOTS_ST25TB_Current[SLOTS_ST25TB_INDEX_SYSTEM]);
            }

            CLI_DATA_show();
        }

        CLI_CARD_leave();
    }
}

void CLI_CARD_show()
{
    uint8_t UID[8], nbSectors, i, Value[4];

    if(CLI_CARD_Get())
    {
        if(CLI_CARD_CMD_UID(UID))
        {
            st25tb_utils_Display_UIDChip(UID);
            nbSectors = ST25TB_Initiator_ValidateAndGetNBSectorsFromUID(UID, NULL);
            printf("Sectors: %hu" UART_NEWLINE, nbSectors);
            if(nbSectors)
            {
                for(i = 0; i < nbSectors; i++)
                {
                    if(CLI_CARD_CMD_Read_Block(i, Value))
                    {
                        st25tb_utils_Display_sector_data(Value, i);
                    }
                }
                if(CLI_CARD_CMD_Read_Block(ST25TB_IDX_SYSTEM, Value))
                {
                    st25tb_utils_Display_sector_data(Value, ST25TB_IDX_SYSTEM);
                }
            }
        }

        CLI_CARD_leave();
    }
}

void CLI_CARD_dump()
{
    CLI_CARD_load();
    CLI_BASE64_kprint((const uint8_t *) SLOTS_ST25TB_Current, SLOTS_ST25TB_SIZE_INTERNAL);
}

void CLI_CARD_uid()
{
    uint8_t UID[8];
    if(CLI_CARD_Get())
    {
        CLI_CARD_CMD_UID(UID);
        st25tb_utils_Display_UIDChip(UID);
        CLI_CARD_leave();
    }
}

void CLI_CARD_write()
{
    uint8_t ui8UID[8], nbSectors, i;

    printf("Current data ");
    st25tb_utils_Display_UIDChip(SLOTS_ST25TB_Current[SLOTS_ST25TB_INDEX_UID]);

    if(CLI_CARD_Get())
    {
        if(CLI_CARD_CMD_UID(ui8UID))
        {
            printf("Current card ");
            st25tb_utils_Display_UIDChip(ui8UID);
            nbSectors = ST25TB_Initiator_ValidateAndGetNBSectorsFromUID(ui8UID, NULL);
            printf("Sectors: %hu" UART_NEWLINE, nbSectors);
            if(nbSectors && (nbSectors <= SLOTS_ST25TB_SECTORS))
            {
                if(((*(uint64_t*) ui8UID) == (*(uint64_t*) SLOTS_ST25TB_Current[SLOTS_ST25TB_INDEX_UID]))) // implicit check of same size/techno :')
                {
                    for(i = 0; i < nbSectors; i++)
                    {
                        if(((i == ST25TB_IDX_COUNTER1) || (i == ST25TB_IDX_COUNTER2)) && FlashStoredData.bDoNotWriteCounters)
                        {
                            printf("Skipping dangerous/counter #%hu" UART_NEWLINE, i);
                            continue;
                        }
                        st25tb_utils_Display_sector_data(SLOTS_ST25TB_Current[i], i);
                        CLI_CARD_CMD_Write_Block(i, SLOTS_ST25TB_Current[i]);
                    }

                    if(!FlashStoredData.bDoNotWriteSystem)
                    {
                        st25tb_utils_Display_sector_data(SLOTS_ST25TB_Current[SLOTS_ST25TB_INDEX_SYSTEM], ST25TB_IDX_SYSTEM);
                        CLI_CARD_CMD_Write_Block(ST25TB_IDX_SYSTEM, SLOTS_ST25TB_Current[SLOTS_ST25TB_INDEX_SYSTEM]);
                    }
                    else
                    {
                        printf("Skipping dangerous/system #%hu" UART_NEWLINE, ST25TB_IDX_SYSTEM);
                    }
                }
                else
                {
                    printf("Different UID!" UART_NEWLINE);
                }
            }
        }

        CLI_CARD_leave();
    }
}

void CLI_CARD_rdbl()
{
    uint8_t blockNumber, Value[4];

    if(CLI_BlockNumber_Value(NULL, &blockNumber, NULL))
    {
        if(CLI_CARD_Get())
        {
            CLI_CARD_CMD_Read_Block(blockNumber, Value);
            st25tb_utils_Display_sector_data(Value, blockNumber);
            CLI_CARD_leave();
        }
    }
}

void CLI_CARD_wrbl()
{
    uint8_t blockNumber, Value[4];

    if(CLI_BlockNumber_Value(NULL, &blockNumber, Value))
    {
        if(CLI_CARD_Get())
        {
            st25tb_utils_Display_sector_data(Value, blockNumber);
            CLI_CARD_CMD_Write_Block(blockNumber, Value);
            CLI_CARD_leave();
        }
    }
}

void CLI_CARD_tear()
{
    char *strToken;
    uint8_t idx, UID[8], bInRef, retS5, retS6;
    uint32_t c_sector5, c_sector6, t_sector5, t_sector6;

    strToken = CLI_NextArg();
    if(strToken)
    {
        if(CLI_BlockNumber_Value(strToken, &idx, (uint8_t *) &t_sector5))
        {
            if ((idx == ST25TB_IDX_COUNTER1) || (idx == ST25TB_IDX_COUNTER2))
            {
                if(CLI_CARD_Get())
                {
                    if(CLI_CARD_CMD_Read_Block(idx, (uint8_t *) &c_sector5))
                    {
                        printf("Card  : ");
                        st25tb_utils_Display_sector_data((const uint8_t *) &c_sector5, ST25TB_IDX_COUNTER1);
                        printf("Target: ");
                        st25tb_utils_Display_sector_data((const uint8_t *) &t_sector5, ST25TB_IDX_COUNTER1);
                        MODE_tear_Counter(idx, c_sector5 , t_sector5);
                    }
                    CLI_CARD_leave();
                }
            }
            else
            {
                printf("%hu is a not a valid index for tear-off (5-6)" UART_NEWLINE, idx);
            }
        }
    }
    else
    {
        printf("No explicit block / value, using automatic mode from UID..." UART_NEWLINE);
        if(CLI_CARD_Get())
        {
            if(CLI_CARD_CMD_UID(UID))
            {
                st25tb_utils_Display_UIDChip(UID);
                if ((*(uint64_t*) UID) == (*(uint64_t*) SLOTS_ST25TB_Current[SLOTS_ST25TB_INDEX_UID]))
                {
                    bInRef = 1;
                    printf("UID found in current data" UART_NEWLINE);
                }
                else
                {
#if defined(REFERENCES_DATA_READY)
                    bInRef = REFERENCES_FindAndLoadByUID(UID);
                    if (bInRef)
                    {
                        printf("UID found in const references" UART_NEWLINE);
                    }
#else
                    bInRef = 0;
#endif
                }

                if(bInRef)
                {
                    t_sector5 = *(uint32_t *) SLOTS_ST25TB_Current[ST25TB_IDX_COUNTER1];
                    t_sector6 = *(uint32_t *) SLOTS_ST25TB_Current[ST25TB_IDX_COUNTER2];
                    if(CLI_CARD_CMD_Read_Block(ST25TB_IDX_COUNTER1, (uint8_t *) &c_sector5) && CLI_CARD_CMD_Read_Block(ST25TB_IDX_COUNTER2, (uint8_t *) &c_sector6))
                    {
                        printf("Card values:" UART_NEWLINE);
                        st25tb_utils_Display_sector_data((const uint8_t *) &c_sector5, ST25TB_IDX_COUNTER1);
                        st25tb_utils_Display_sector_data((const uint8_t *) &c_sector6, ST25TB_IDX_COUNTER2);
                        printf("Target values:" UART_NEWLINE);
                        st25tb_utils_Display_sector_data((const uint8_t *) &t_sector5, ST25TB_IDX_COUNTER1);
                        st25tb_utils_Display_sector_data((const uint8_t *) &t_sector6, ST25TB_IDX_COUNTER2);

                        retS5 = MODE_tear_Counter(ST25TB_IDX_COUNTER1, c_sector5, t_sector5);
                        retS6 = MODE_tear_Counter(ST25TB_IDX_COUNTER2, c_sector6, t_sector6);
                        if(retS5 && retS6)
                        {
                            printf("Sector5 & Sector6 are OK!" UART_NEWLINE);
                            if(bInRef)
                            {
                                printf("...it was in from data, rewrite" UART_NEWLINE);
                                CLI_CARD_write();
                            }
                        }
                    }
                }
                else
                {
                    printf("No references available for this card, use block mode" UART_NEWLINE);
                }
            }
            CLI_CARD_leave();
        }
    }
}
