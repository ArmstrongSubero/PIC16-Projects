/*
 * File: EUSART.h
 * Author: Armstrong Subero
 * PIC: 16F1719 w/Int OSC @ 32MHz, 5v
 * Program: Header file to setup PIC16F1717
 * Compiler: XC8 (v2.45, MPLAX X v6.15)
 * Program Version 1.1
 *                  
 * Program Description: This header sets up the EUSART module
 * Created on November 7th, 2016, 7:00 PM
 * Updated on November 24th 2023, 1:02 AM
 */

/*******************************************************************************
 * Function Prototype
 ******************************************************************************/

char EUSART_Initialize(const long int baudrate);
uint8_t EUSART_Read(void);
void EUSART_Write(uint8_t txData);
void EUSART_Write_Text(char *text);
void EUSART_Read_Text(char *Output, unsigned int length);