/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#include "board.h"

/* ST25TB Private references
 * Again I push my private includes here, as I don't know how to make #include based on file presence (like in CMakeLists.txt) for _piko
 * If REFERENCES_DATA_READY is set, it will try to include 'references.data' file. It MUST NOT be empty.
 * You can ignore them, or adapt to your(s)
 */
//#define REFERENCES_DATA_READY

#if defined(REFERENCES_DATA_READY)

#define REFERENCES_ST25TB_SECTORS_INTERNAL   (( 512 / 8 / 4) + 3)

#define REFERENCES_ST25TB_INDEX_SYSTEM   (REFERENCES_ST25TB_SECTORS_INTERNAL - 3)
#define REFERENCES_ST25TB_INDEX_UID      (REFERENCES_ST25TB_SECTORS_INTERNAL - 2)
#define REFERENCES_ST25TB_INDEX_UID_2    (REFERENCES_ST25TB_SECTORS_INTERNAL - 1)

extern const uint8_t REFERENCES_ST25TB[][REFERENCES_ST25TB_SECTORS_INTERNAL][4];
extern const uint8_t REFERENCES_ST25TB_COUNT;

#define REFERENCES_FIND_INVALID_INDEX    0xff

uint8_t REFERENCES_FindByUID(uint8_t pui8Data[8]); // ret == REFERENCES_FIND_INVALID_INDEX -> not found
uint8_t REFERENCES_Load(uint8_t index);
uint8_t REFERENCES_FindAndLoadByUID(uint8_t pui8Data[8]);

#endif
