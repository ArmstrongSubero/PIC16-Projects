/*
 * File: I2C.h
 * Author: Armstrong Subero
 * PIC: 16F1719 w/Int OSC @ 32MHz, 5v
 * Program: Driver-grade I2C (MSSP) header
 * Compiler: XC8
 *
 * Program Version 2.0
 * Program Description:
 * This driver provides robust I2C master-mode routines using MSSP.
 */

#ifndef I2C_H
#define I2C_H

#include "PIC16F1718_Internal.h"
#include <stdint.h>
#include <stdbool.h>

/*******************************************************************************
 * Types
 ******************************************************************************/
typedef enum {
    I2C_OK = 0,
    I2C_NAK,
    I2C_TIMEOUT,
    I2C_BUS_COLLISION
} I2C_Status_t;

/*******************************************************************************
 * Public API
 ******************************************************************************/
void I2C_Init(void);

/* Core bus primitives */
I2C_Status_t I2C_Start(void);
I2C_Status_t I2C_RepeatedStart(void);
I2C_Status_t I2C_Stop(void);

I2C_Status_t I2C_WriteByte(uint8_t data);
I2C_Status_t I2C_ReadByte(uint8_t *data, bool ack);

/* Helpers */
I2C_Status_t I2C_WaitIdle(uint16_t timeout_ms);
void I2C_ClearErrors(void);

void I2C_RecoverBus(void);
void I2C_ResetModule(void);


#endif
