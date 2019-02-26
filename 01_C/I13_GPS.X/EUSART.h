/*
 * File: EUSART.h
 * Author: Armstrong Subero
 * PIC: 16F1717 w/X OSC @ 16MHz, 5v
 * Program: Header file to setup PIC16F1717
 * Compiler: XC8 (v1.35, MPLAX X v3.10)
 * Program Version 1.0
 *                  
 * Program Description: This header sets up the EUSART module
 * Created on November 7th, 2016, 7:00 PM
 */

/*******************************************************************************
 * Function Prototype
 ******************************************************************************/
#define EUSART_DataReady  (eusartRxCount)

/**
  Section: Data Type Definitions
*/

/**
 Section: Global variables
 */
extern volatile uint8_t eusartTxBufferRemaining;
extern volatile uint8_t eusartRxCount;

char EUSART_Initialize(const long int baudrate);
uint8_t EUSART_Read(void);
char EUSART_Read_Char(char *Output);
void EUSART_Write(uint8_t txData);
void EUSART_Write_Text(char *text);
void EUSART_Read_Text(char *Output, unsigned int length);