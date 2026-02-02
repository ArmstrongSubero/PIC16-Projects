/*
 * File: SEUSART.h
 * Author: Armstrong Subero
 * PIC: 16F1718 w/X OSC @ 32MHz, 5v
 * Program: Header file to setup PIC16F1718 software UART
 * Compiler: XC8 (v2.45, MPLAX X v6.20)
 * Program Version 1.0
 *           
 * Program Description: This program header allows PIC to use a software UART
 *
 * Created on April 15th, 2017, 12:57 PM
 * Updated on January 29th 2026, 6:16 PM 
 * 
 */

#include "PIC16F1718_Internal.h"

#define Baudrate 2400
#define OneBitDelay (1000000UL/Baudrate)
#define DataBitCount 8

#define UART_RX     PORTBbits.RB0
#define UART_TX     LATBbits.LATB1
#define UART_RX_DIR TRISBbits.TRISB0
#define UART_TX_DIR TRISBbits.TRISB1


//Function Declarations
void SUART_Init(void);
unsigned char SUART_Receive(void);
void SUART_Transmit(const char);
void SUART_Write_Text(char *text);
void SUART_Write_Char(char a);
void SUART_Read_Text(char *Output, unsigned int length);
