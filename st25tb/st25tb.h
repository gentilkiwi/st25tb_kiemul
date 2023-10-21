#pragma once
#include "../boards/bp-trf7970a/trf7970a.h"

/*
 * SRT512
 *  t0 Antenna reversal delay 128/fS  151 탎
 *  t1 Synchronization delay          151 탎
 *  t2 Answer to new request delay >= 132 탎
 *
 * ST25TB512-AT
 *  t0 Antenna reversal delay 128/fS  159 탎
 *  t1 Synchronization delay          151 탎
 *  t2 Answer to new request delay >= 132 탎
 *
 *  -> focus on t0 = 155 탎 ?
 */

#if defined(__MSP430F5529__)
#define ST25TB_TARGET_GLOBAL_DELAY_US  70 // (+~12 of the function call)
#define ST25TB_TARGET_MEDIUM_DELAY_US  14
#define ST25TB_TARGET_SMALL_DELAY_US   5
#elif defined(__MSP430FR2476__)
#define ST25TB_TARGET_GLOBAL_DELAY_US  13
#define ST25TB_TARGET_MEDIUM_DELAY_US  21
#define ST25TB_TARGET_SMALL_DELAY_US   7
#else
#error Target is not supported !
#endif

typedef enum _tSt25TbState {
    Invalid,
    PowerOff,
    Ready,
    Inventory,
    Selected,
    Deselected,
    Deactivated,
} tSt25TbState;

#define ST25TB_CMD_INITIATE              0x06 // 0x00
#define ST25TB_CMD_PCALL16               0x06 // 0x04
#define ST25TB_CMD_SLOT_MARKER_MASK      0x06
#define ST25TB_CMD_READ_BLOCK            0x08
#define ST25TB_CMD_WRITE_BLOCK           0x09
#define ST25TB_CMD_AUTHENTICATE          0x0a // SRIX4K - France Telecom proprietary anti-clone function - Authenticate(RND)
#define ST25TB_CMD_GET_UID               0x0b
#define ST25TB_CMD_RESET_TO_INVENTORY    0x0c
#define ST25TB_CMD_SELECT                0x0e
#define ST25TB_CMD_COMPLETION            0x0f

#define ST25TB_DELAY_WRITE_TIME_OTP      3
#define ST25TB_DELAY_WRITE_TIME_EEPROM   5
#define ST25TB_DELAY_WRITE_TIME_COUNTER  7

extern uint8_t g_ui8FifoBuffer[0x20];
extern uint8_t g_ui8cbFifoBuffer;

bool ST25TB_Recv(bool bIsinitiator, uint8_t irqProvided);
bool ST25TB_Send(const uint8_t *pui8Payload, const uint8_t ui8Length);
void ST25TB_TRF7970A_Mode(bool bIsInitiator);
