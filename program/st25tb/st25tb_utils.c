/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "st25tb_utils.h"

uint8_t st25tb_utils_Display_UIDChip(const uint8_t *pui8UID)
{
    uint8_t nbSectors, chipId;
    const char *chipName;

    printf("UID: %016llX", (*(uint64_t*) pui8UID));
    nbSectors = ST25TB_Initiator_ValidateAndGetNBSectorsFromUID(pui8UID, &chipId);
    if(nbSectors)
    {
        switch(chipId)
        {
            case 0x33:
                chipName = "ST25TB512-AT";
                break;
            case 0x1b:
                chipName = "ST25TB512-AC";
                break;
            case 0x3f:
                chipName = "ST25TB02K";
                break;
            case 0x1f:
                chipName = "ST25TB04K";
                break;
            case 0x0c: // 12
                chipName = "SRT512";
                break;
            case 0x06: // 6
                chipName = "SRI512";
                break;
            case 0x04: // 4
                chipName = "SRIX512";
                break;
            case 0x0f: // 15
                chipName = "SRI2K";
                break;
            case 0x07: // 7
                chipName = "SRI4K";
                break;
            case 0x03: // 3
                chipName = "SRIX4K";
                break;
            default:
                chipName = NULL;
        }
        printf(" (%s)", chipName);
    }
    printf(UART_NEWLINE);

    return nbSectors;
}

void st25tb_utils_Display_sector(const uint8_t data[SLOTS_ST25TB_SECTORS_INTERNAL][4], const uint8_t sector)
{
    uint8_t idx = ST25TB_Target_AdjustIdxForSpecialAddr(sector);
    if(idx < SLOTS_ST25TB_SECTORS_INTERNAL)
    {
        st25tb_utils_Display_sector_data(data[idx], sector);
    }
    else
    {
        printf("Invalid sector # %hu" UART_NEWLINE, sector);
    }
}

void st25tb_utils_Write_sector(const uint8_t data[SLOTS_ST25TB_SECTORS_INTERNAL][4], const uint8_t sector, const uint8_t newData[4])
{
    uint8_t idx = ST25TB_Target_AdjustIdxForSpecialAddr(sector);
    if(idx < SLOTS_ST25TB_SECTORS_INTERNAL)
    {
        *(uint32_t *) data[idx] = *(uint32_t *) newData;
    }
    else
    {
        printf("Invalid sector # %hu" UART_NEWLINE, sector);
    }
}

void st25tb_utils_Display_sector_data(const uint8_t data[4], const uint8_t sector)
{
    printf("%3hu/0x%02X | %02hX %02hX %02hX %02hX | %08lX" UART_NEWLINE, sector, sector, data[0], data[1], data[2], data[3], *(uint32_t *)data);
}

void st25tb_utils_Display_dump(const uint8_t data[SLOTS_ST25TB_SECTORS_INTERNAL][4], const uint8_t idxUID)
{
    uint8_t i, nbSectors;

    nbSectors = st25tb_utils_Display_UIDChip(data[idxUID]);
    if(nbSectors)
    {
        printf(UART_NEWLINE " block#  | data        | /data" UART_NEWLINE "---------+-------------+---------" UART_NEWLINE);
        for(i = 0; i < nbSectors; i++)
        {
            st25tb_utils_Display_sector(data, i);
        }
        st25tb_utils_Display_sector(data, 0xff);
        printf("---------+-------------+---------" UART_NEWLINE);
    }
}

