/*
 * File: EEPROM_24AA512.h
 * Author: Armstrong Subero
 * Device: 24AA512
 * Program Description:
 * High-level driver for 24AA512 using I2C v2.0 bus routines.
 */

#ifndef EEPROM_24AA512_H
#define EEPROM_24AA512_H

#include <stdint.h>
#include <stdbool.h>
#include "I2C.h"

#define EEPROM24AA512_ADDR7  0x50   // 7-bit address (A2/A1/A0 all low)


/*******************************************************************************
 * Hardware Address Select (A2..A0)
 * If A2/A1/A0 are tied to GND => 0
 * If you strap A0 high => 1, etc.
 ******************************************************************************/
#define EEPROM24AA512_A2A1A0   0   // 0..7

I2C_Status_t EEPROM24AA512_AckPoll(void);

I2C_Status_t EEPROM24AA512_WriteByte(uint16_t addr, uint8_t data);
I2C_Status_t EEPROM24AA512_ReadByte(uint16_t addr, uint8_t *data);

/* Optional (recommended) */
I2C_Status_t EEPROM24AA512_WritePage(uint16_t addr, const uint8_t *data, uint8_t len);
I2C_Status_t EEPROM24AA512_ReadSequential(uint16_t addr, uint8_t *data, uint16_t len);

#endif
