/*
 * File: sw_uart.h
 * Author: Armstrong Subero
 * PIC: 16F1717 w/X OSC @ 16MHz, 5v
 * Program: Header file to setup PIC16F1717 software UART
 * Compiler: XC8 (v1.41, MPLAX X v3.55)
 * Program Version 1.0
 *           
 * Program Description: This program header allows PIC to use a software UART
 *
 * Created on April 15th, 2017, 12:57 PM
 */


#include "16F1717_Internal.h"

// bits per second
#define Baudrate 2400 

// delay for UART
#define OneBitDelay (1000000/Baudrate)

// no parity no flow control
#define DataBitCount 8 

// SW UART RX
#define UART_RX LATEbits.LATE0

// SW WART TX
#define UART_TX LATEbits.LATE1

// RX pin direction register
#define UART_RX_DIR TRISE0

// TX pin direction register
#define UART_TX_DIR TRISE1

//Function Declarations
void SUART_Init(void);
unsigned char SUART_Receive(void);
void SUART_Transmit(const char);
void SUART_Write_Text(char *text);
void SUART_Write_Char(char a);
void SUART_Read_Text(char *Output, unsigned int length);

