/*
 * File: SPI.h
 * Author: Armstrong Subero
 * PIC: 16F1717 w/X OSC @ 16MHz, 5v
 * Program: Header file for SPI module
 * Compiler: XC8 (v1.38, MPLAX X v3.40)
 *                
 * Program Version 1.0
 *                
 * Program Description: This program header provides function prototypes for 
 *                      SPI module on PIC16F1717
 *                      
 *               
 *
 * Created on November 7th, 2016, 5:45 PM
 */

/*******************************************************************************
 *Includes and defines
 ******************************************************************************/

#include "16F1717_Internal.h"
#define DUMMY_DATA 0x0

void SPI_Initialize(void);
uint8_t SPI_Exchange8bit(uint8_t data);
uint8_t SPI_Exchange8bitBuffer(uint8_t *dataIn, uint8_t bufLen, uint8_t *dataOut);
bool SPI_IsBufferFull(void);
bool SPI_HasWriteCollisionOccured(void);
void SPI_ClearWriteCollisionStatus(void);