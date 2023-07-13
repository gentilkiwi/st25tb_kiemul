#pragma once
#include "led.h"
#include "trf79x0.h"
#include "st25tb.h"

typedef enum _st25tb_kiemul_Mode {
    Read_RealCard_Mode,
    Emulate_VirtualCard_Mode,
    Write_RealCard_Mode,
} st25tb_kiemul_Mode;

void main(void);
void Emulate_VirtualCard(st25tb_kiemul_Mode *pMode);
void Write_RealCard(st25tb_kiemul_Mode *pMode);
void Read_RealCard(st25tb_kiemul_Mode *pMode);
