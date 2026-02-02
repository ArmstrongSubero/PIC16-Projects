/*
 * File: EEPROM_24AA512.c
 * Author: Armstrong Subero
 * Device: 24AA512
 *
 * Program Description:
 * 24AA512 EEPROM driver
 *
 * Requirements:
 *  - 7-bit I2C address: 0x50 (A2/A1/A0 = 0)
 *  - Control byte: (ADDR << 1) | R/W
 *  - 16-bit memory address (MSB first)
 *  - ACK polling after writes
 */

#include "EEPROM_24AA512.h"

/*******************************************************************************
 * Configuration
 ******************************************************************************/
#define EEPROM24AA512_ADDR7   0x50    // Arduino-compatible 7-bit address
#define EEPROM24AA512_PAGE_SZ 128

/*******************************************************************************
 * Local helper: build control byte
 ******************************************************************************/
static uint8_t EEPROM24AA512_Ctrl(bool read)
{
    return (uint8_t)((EEPROM24AA512_ADDR7 << 1) | (read ? 1 : 0));
}

/*******************************************************************************
 * Function: EEPROM24AA512_AckPoll
 *
 * Description:
 * EEPROM NAKs while busy after write. Poll until ACK.
 ******************************************************************************/
I2C_Status_t EEPROM24AA512_AckPoll(void)
{
    for (uint16_t t = 0; t < 200; t++)
    {
        I2C_Start();
        I2C_Status_t st = I2C_WriteByte(EEPROM24AA512_Ctrl(false));
        I2C_Stop();

        if (st == I2C_OK)
            return I2C_OK;

        __delay_ms(1);
    }
    return I2C_TIMEOUT;
}

/*******************************************************************************
 * Function: EEPROM24AA512_WriteByte
 *
 * START ? CTRL(W) ? ADDR_H ? ADDR_L ? DATA ? STOP ? ACK poll
 ******************************************************************************/
I2C_Status_t EEPROM24AA512_WriteByte(uint16_t addr, uint8_t data)
{
    I2C_Status_t st;

    if ((st = I2C_Start()) != I2C_OK) return st;
    if ((st = I2C_WriteByte(EEPROM24AA512_Ctrl(false))) != I2C_OK) goto stop;
    if ((st = I2C_WriteByte(addr >> 8)) != I2C_OK) goto stop;
    if ((st = I2C_WriteByte(addr & 0xFF)) != I2C_OK) goto stop;
    if ((st = I2C_WriteByte(data)) != I2C_OK) goto stop;

stop:
    I2C_Stop();
    if (st != I2C_OK) return st;

    return EEPROM24AA512_AckPoll();
}

/*******************************************************************************
 * Function: EEPROM24AA512_ReadByte
 *
 * START ? CTRL(W) ? ADDR_H ? ADDR_L ? RSTART ? CTRL(R) ? READ ? NAK ? STOP
 ******************************************************************************/
I2C_Status_t EEPROM24AA512_ReadByte(uint16_t addr, uint8_t *data)
{
    I2C_Status_t st;

    if (data == NULL) return I2C_TIMEOUT;

    if ((st = I2C_Start()) != I2C_OK) return st;
    if ((st = I2C_WriteByte(EEPROM24AA512_Ctrl(false))) != I2C_OK) goto stop;
    if ((st = I2C_WriteByte(addr >> 8)) != I2C_OK) goto stop;
    if ((st = I2C_WriteByte(addr & 0xFF)) != I2C_OK) goto stop;

    if ((st = I2C_RepeatedStart()) != I2C_OK) goto stop;
    if ((st = I2C_WriteByte(EEPROM24AA512_Ctrl(true))) != I2C_OK) goto stop;

    st = I2C_ReadByte(data, false);

stop:
    I2C_Stop();
    return st;
}

/*******************************************************************************
 * Function: EEPROM24AA512_WritePage
 *
 * Writes up to 128 bytes without crossing page boundary
 ******************************************************************************/
I2C_Status_t EEPROM24AA512_WritePage(uint16_t addr, const uint8_t *data, uint8_t len)
{
    if (!data || len == 0) return I2C_OK;
    if (len > EEPROM24AA512_PAGE_SZ) len = EEPROM24AA512_PAGE_SZ;

    uint8_t offset = addr & (EEPROM24AA512_PAGE_SZ - 1);
    uint8_t room   = EEPROM24AA512_PAGE_SZ - offset;
    if (len > room) len = room;

    I2C_Status_t st;

    if ((st = I2C_Start()) != I2C_OK) return st;
    if ((st = I2C_WriteByte(EEPROM24AA512_Ctrl(false))) != I2C_OK) goto stop;
    if ((st = I2C_WriteByte(addr >> 8)) != I2C_OK) goto stop;
    if ((st = I2C_WriteByte(addr & 0xFF)) != I2C_OK) goto stop;

    for (uint8_t i = 0; i < len; i++)
    {
        if ((st = I2C_WriteByte(data[i])) != I2C_OK) goto stop;
    }

stop:
    I2C_Stop();
    if (st != I2C_OK) return st;

    return EEPROM24AA512_AckPoll();
}

/*******************************************************************************
 * Function: EEPROM24AA512_ReadSequential
 ******************************************************************************/
I2C_Status_t EEPROM24AA512_ReadSequential(uint16_t addr, uint8_t *data, uint16_t len)
{
    if (!data || len == 0) return I2C_OK;

    I2C_Status_t st;

    if ((st = I2C_Start()) != I2C_OK) return st;
    if ((st = I2C_WriteByte(EEPROM24AA512_Ctrl(false))) != I2C_OK) goto stop;
    if ((st = I2C_WriteByte(addr >> 8)) != I2C_OK) goto stop;
    if ((st = I2C_WriteByte(addr & 0xFF)) != I2C_OK) goto stop;

    if ((st = I2C_RepeatedStart()) != I2C_OK) goto stop;
    if ((st = I2C_WriteByte(EEPROM24AA512_Ctrl(true))) != I2C_OK) goto stop;

    for (uint16_t i = 0; i < len; i++)
    {
        bool ack = (i < (len - 1));
        if ((st = I2C_ReadByte(&data[i], ack)) != I2C_OK) goto stop;
    }

stop:
    I2C_Stop();
    return st;
}
