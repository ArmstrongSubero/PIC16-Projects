/*
 * File: ds1302.h
 * Author: Armstrong Subero
 * PIC: 16F1717 w/X OSC @ 16MHz, 5v
 * Program: Header file to setup PIC16F1717 I2C
 * Compiler: XC8 (v1.41, MPLAX X v3.55)
 * Program Version 1.0
 *                      
 * Program Description: This program header allows the control of a DS1302 
 *                      time keeper chip
 *
 * Created on April 18th, 2017, 11:40 PM
 */


#include "16F1717_Internal.h"

#define CE             RD0
#define SCLK           RD1
#define IO             RD2
#define Data_Tris      TRISD2

typedef unsigned char byte;

void DS1302_Reset();
void DS1302_WriteByte(unsigned char W_Byte);
unsigned char DS1302_ReadByte();
void DS1302_Initialize(byte sec, byte min, byte hr, byte day, byte date, byte mth, byte year);	
unsigned char get_bcd(unsigned char data);
unsigned char get_dec(byte var);
