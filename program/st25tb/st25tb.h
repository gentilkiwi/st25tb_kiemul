/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#include "../board.h"

#include "st25tb_target.h"
#include "st25tb_initiator.h"
#include "st25tb_utils.h"

void ST25TB_TRF7970A_Mode(uint8_t bIsInitiator);
uint8_t ST25TB_Recv(uint8_t bIsinitiator, uint8_t irqProvided);
uint8_t ST25TB_Send(const uint8_t *pcbData, const uint8_t cbData);

#define ST25TB_IDX_COUNTER1             0x05
#define ST25TB_IDX_COUNTER2             0x06
#define ST25TB_IDX_SYSTEM               0xff

#define ST25TB_CMD_INITIATE             0x06 // 0x00
#define ST25TB_CMD_PCALL16              0x06 // 0x04
#define ST25TB_CMD_SLOT_MARKER_MASK     0x06
#define ST25TB_CMD_READ_BLOCK           0x08
#define ST25TB_CMD_WRITE_BLOCK          0x09
#define ST25TB_CMD_AUTHENTICATE         0x0a // SRIX4K - France Telecom proprietary anti-clone function - Authenticate(RND)
#define ST25TB_CMD_GET_UID              0x0b
#define ST25TB_CMD_RESET_TO_INVENTORY   0x0c
#define ST25TB_CMD_SELECT               0x0e
#define ST25TB_CMD_COMPLETION           0x0f

extern uint8_t g_ui8_ST25TB_Buffer[0x10];
extern uint8_t g_ui8_cbST25TB_Buffer;
