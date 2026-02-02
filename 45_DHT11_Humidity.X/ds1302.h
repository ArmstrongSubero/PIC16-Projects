/*
 * File: ds1302.h
 * Author: Armstrong Subero
 * MCU: PIC16F1718
 * Notes: DS1302 uses 3-wire (CE, SCLK, IO) bit-banged
 */

#ifndef DS1302_H
#define DS1302_H

#include "PIC16F1718_Internal.h"   // <-- change to your 1718 internal header

// Use LAT for outputs (recommended)
#define CE           LATBbits.LATB0
#define SCLK         LATBbits.LATB1
#define IO           PORTBbits.RB2

// IO direction control (1=input, 0=output)
#define Data_Tris    TRISBbits.TRISB2

typedef unsigned char byte;

void DS1302_Reset(void);
void DS1302_WriteByte(unsigned char W_Byte);
unsigned char DS1302_ReadByte(void);
void DS1302_Initialize(byte sec, byte min, byte hr, byte day, byte date, byte mth, byte year);
unsigned char get_bcd(unsigned char data);
unsigned char get_dec(byte var);

#endif
