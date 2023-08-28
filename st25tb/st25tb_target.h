#pragma once
#include "st25tb.h"
#include "st25tb_cards.h"

void ST25TB_Target_Init();
void ST25TB_Target_ResetState();
tSt25TbState ST25TB_Target_StateMachine();
