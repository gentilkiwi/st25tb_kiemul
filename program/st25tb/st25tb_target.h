/*  Benjamin DELPY `gentilkiwi`
    https://blog.gentilkiwi.com
    benjamin@gentilkiwi.com
    Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#include "st25tb.h"

uint8_t ST25TB_Target_ResponseTo();
uint8_t ST25TB_Target_AdjustIdxForSpecialAddr(uint8_t original);

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
 *  -> focus on t0 <= 160 탎 ?
 */

/*
 * Values here were tested with:
 * --opt_level=4 (Whole Program Optimizations)
 * --opt_for_speed=5 (Enables optimizations geared towards improving the code performance/speed with a high risk of worsening or impacting code size)
 */
/*
#define ST25TB_TARGET_DELAY_US_GLOBAL  96
#define ST25TB_TARGET_DELAY_US_MEDIUM  11
#define ST25TB_TARGET_DELAY_US_SMALL   3
*/

/*
 * Values here were tested with:
 * --opt_level=4 (Whole Program Optimizations)
 * --opt_for_speed=3 (Enables optimizations geared towards improving the code performance/speed with a low risk of worsening or impacting code size)
 */
#define ST25TB_TARGET_DELAY_US_GLOBAL  91
#define ST25TB_TARGET_DELAY_US_MEDIUM  11
#define ST25TB_TARGET_DELAY_US_SMALL   3
