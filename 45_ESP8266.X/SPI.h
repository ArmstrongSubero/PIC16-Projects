/*
 * File: SPI.h
 * Author: Armstrong Subero
 * PIC: 16F1719 w/X OSC @ 32MHz, 5v
 * Program: Header file for SPI module
 * Compiler: XC8 (v2.45, MPLAX X v6.15)
 *                
 * Program Version 1.1
 *                 *Updated Comments
 *                
 * Program Description: This program header provides function prototypes for 
 *                      SPI module on PIC16F1719
 *                      
 *               
 *
 * Created on November 7th,  2016, 5:45 PM
 * Updated on November 24th, 2023, 4:13 AM
 */

/*******************************************************************************
 *Includes and defines
 ******************************************************************************/

#include "PIC16F1719_Internal.h"
#define DUMMY_DATA 0x0

void SPI_Initialize(void);
uint8_t SPI_Exchange8bit(uint8_t data);
uint8_t SPI_Exchange8bitBuffer(uint8_t *dataIn, uint8_t bufLen, uint8_t *dataOut);
bool SPI_IsBufferFull(void);
bool SPI_HasWriteCollisionOccured(void);
void SPI_ClearWriteCollisionStatus(void);