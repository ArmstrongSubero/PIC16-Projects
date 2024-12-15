/*
 * File: I2C.h
 * Author: Armstrong Subero
 * PIC: 16F1717 w/X OSC @ 16MHz, 5v
 * Program: Header file to setup PIC16F1717 I2C
 * Compiler: XC8 (v1.35, MPLAX X v3.10)
 * Program Version 1.2
 *                *Separated file into Header and C source file
 *                *Used non-mcc code
 *           
 *                  
 * Program Description: This program header will allows setup of I2C
 *
 * Created on September 12th, 2016, 7:00 PM
 */

/*******************************************************************************
 *Includes and defines
 ******************************************************************************/

#include "16F1717_Internal.h"


void I2C_Init(void);
void Send_I2C_Data(unsigned int databyte);
unsigned int Read_I2C_Data(void);
void Send_I2C_ControlByte(unsigned int BlockAddress,unsigned int RW_bit);
void Send_I2C_StartBit(void);
void Send_I2C_StopBit(void);
void Send_I2C_ACK(void);
void Send_I2C_NAK(void);