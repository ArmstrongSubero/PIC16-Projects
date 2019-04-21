/*
 * File: onewire.h
 * Author: Armstrong Subero
 * Processor: PIC16F1717 @ 16MHz,5v
 * Program: One Wire Protocol
 * Compiler: XC8 (v2.05, MPLAX X v5.15)
 * Program Version 1.0
 * Program Description: This header file contains onewire library setup
 * 
 * Created on April 20, 2018, 11:40 PM
 */


/*******************************************************************************
* Includes and defines
*******************************************************************************/
#include <xc.h>
#include "16F1717_Internal.h"


// Define OneWire Pin
#define OW_Pin PORTBbits.RB0
#define OW_Dir TRISBbits.TRISB0 
#define OW_Analog ANSELBbits.ANSB0

// Registers
#define SKIP_ROM 0xCC
#define START_CONVERSION 0x44 
#define WRITE_SCRATCHPAD 0x4E
#define RESOLUTION_12BIT 0x7F
#define READ_SCRATCHPAD 0xBE

// function prototypes
void OW_Init(void);
unsigned char OW_Reset(void);
unsigned char OW_ReadBit();
void OW_WriteBit(int b);
unsigned char OW_ReadByte(void);
void OW_WriteByte(char val);