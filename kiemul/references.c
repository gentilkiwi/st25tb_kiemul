/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "references.h"

#if defined(REFERENCES_DATA_READY)

const uint8_t REFERENCES_ST25TB[][REFERENCES_ST25TB_SECTORS_INTERNAL][4] = {
    #include "references.data"
};

uint8_t REFERENCES_FindByUID(uint8_t pui8Data[8]) // ret == REFERENCES_FIND_INVALID_INDEX -> not found
{
    uint8_t i;

    for (i = 0; i < count_of(REFERENCES_ST25TB); i++)
    {
        if ((*(uint64_t*) pui8Data) == (*(uint64_t*) REFERENCES_ST25TB[i][REFERENCES_ST25TB_INDEX_UID]))
        {
            return i;
        }
    }

    return REFERENCES_FIND_INVALID_INDEX;
}

uint8_t REFERENCES_FindAndLoadByUID(uint8_t pui8Data[8])
{
    uint8_t i = REFERENCES_FindByUID(pui8Data);

    if(i != REFERENCES_FIND_INVALID_INDEX)
    {
#if (REFERENCES_ST25TB_SECTORS_INTERNAL == SLOTS_ST25TB_SECTORS_INTERNAL)
        memcpy(SLOTS_ST25TB_Current, REFERENCES_ST25TB[i], sizeof(REFERENCES_ST25TB[i]));
#elif (REFERENCES_ST25TB_SECTORS_INTERNAL < SLOTS_ST25TB_SECTORS_INTERNAL)
        memcpy(SLOTS_ST25TB_Current, REFERENCES_ST25TB[i], sizeof(REFERENCES_ST25TB[i]) - (3 * 4));
        memcpy(SLOTS_ST25TB_Current + SLOTS_ST25TB_INDEX_SYSTEM, REFERENCES_ST25TB[i] + REFERENCES_ST25TB_INDEX_SYSTEM, 3 * 4);
#else
#error REFERENCE size is > SLOT size
#endif
        return 1;
    }

    return 0;
}

#endif
