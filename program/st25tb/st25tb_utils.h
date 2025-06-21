/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#include "st25tb.h"

uint8_t st25tb_utils_Display_UIDChip(const uint8_t *pui8UID);
void st25tb_utils_Display_sector(const uint8_t data[SLOTS_ST25TB_SECTORS_INTERNAL][4], const uint8_t sector);
void st25tb_utils_Display_sector_data(const uint8_t data[4], const uint8_t sector);
void st25tb_utils_Write_sector(const uint8_t data[SLOTS_ST25TB_SECTORS_INTERNAL][4], const uint8_t sector, const uint8_t newData[4]);
void st25tb_utils_Display_dump(const uint8_t data[SLOTS_ST25TB_SECTORS_INTERNAL][4], const uint8_t idxUID);
