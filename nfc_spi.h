#pragma once
#include <mcu.h>
#include <usci_b_spi.h>
#include <gpio.h>
#include <ucs.h>
#include "trf79x0.h"

#define SPI_CLK_FREQ				(4*MHZ)

void SPI_setup();
void SPI_directCommand(uint8_t command);
void SPI_readSingle(uint8_t *pbuf, uint8_t reg);
void SPI_readCont(uint8_t *pbuf, uint8_t reg, uint8_t length);
void SPI_writeSingle(uint8_t data, uint8_t reg);
void SPI_writeCont(uint8_t *pbuf, uint8_t reg, uint8_t length);
void SPI_writePacket(const uint8_t *pbuf, uint8_t total_length, uint8_t payload_length);
