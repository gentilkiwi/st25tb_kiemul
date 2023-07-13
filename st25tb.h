#pragma once
#include <flashctl.h>
#include "trf79x0.h"

//#define ST25TB_TEST_CARD

typedef enum _tSt25TbState {
    Invalid,
    PowerOff,
    Ready,
    Inventory,
    Selected,
    Deselected,
    Deactivated,
} tSt25TbState;

#define ST25TB_INITIATE             0x06 // 0x00
#define ST25TB_PCALL16              0x06 // 0x04
#define ST25TB_SLOT_MARKER_MASK     0x06
#define ST25TB_READ_BLOCK           0x08
#define ST25TB_WRITE_BLOCK          0x09
#define ST25TB_GET_UID              0x0b
#define ST25TB_RESET_TO_INVENTORY   0x0c
#define ST25TB_SELECT               0x0e
#define ST25TB_COMPLETION           0x0f

extern void ST25TB_Write_Reference_to_Flash();

extern void ST25TB_Target_Init();
extern void ST25TB_Target_ResetState();
extern tSt25TbState ST25TB_Target_StateMachine(uint8_t * pui8Payload, uint8_t ui8Length);

extern bool ST25TB_Initiator_Initiate(uint8_t *pui8ChipId);
extern bool ST25TB_Initiator_Compare_UID_with_Ref(bool *pbIsEqual);
extern bool ST25TB_Initiator_Write_Then_Compare();
extern bool ST25TB_Initiator_Read_Reference(bool *pbIsEqual);
