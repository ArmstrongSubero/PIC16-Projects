/*
 * File: oled.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Int OSC @ 16MHz, 5v
 * Program: Library file for Software UART
 * Compiler: XC8 (v1.41, MPLAX X v3.55)
 * Program Version: 1.0
 *
 * Program Description: This Library allows you to use a software UART with 
 *                      the PIC microcontroller
 *                      
 * Created on March 15th, 2017, 12:50 PM
 */

#include "sw_uart.h"


/*******************************************************************************
 * Function: SUART_Init(void)
 *
 * Returns: Nothing
 *
 * Description: Initializes UART pins
 * 
 ******************************************************************************/

void SUART_Init(void)
{
 UART_TX = 1; // TX pin is high in idle state
 
 UART_RX_DIR = 1; // Input
 UART_TX_DIR = 0; // Output
}


/*******************************************************************************
 * Function: unsigned char SUART_Receive(void)
 *
 * Returns: Nothing
 *
 * Description: recieves via soft UART
 * 
 ******************************************************************************/

unsigned char SUART_Receive(void)
{
 // Initial at 0
 unsigned char DataValue = 0;

 //wait for start bit
 while(UART_RX==1);

 __delay_us(OneBitDelay);
 __delay_us(OneBitDelay/2); // Take sample value in the mid of bit duration

 for ( unsigned char i = 0; i < DataBitCount; i++ )
 {
  if ( UART_RX == 1 ) //if received bit is high
  {
   DataValue += (1<<i);
  }

  __delay_us(OneBitDelay);
 }

 // Check for stop bit
 if ( UART_RX == 1 ) //Stop bit should be high
 {
  __delay_us(OneBitDelay/2);
  return DataValue;
 }
 else //some error occurred !
 {
  __delay_us(OneBitDelay/2);
  return 0x000;
 }
}


/*******************************************************************************
 * Function: void SUART_Transmit(const char DataValue)
 *
 * Returns: Nothing
 *
 * Description: transmits via soft UART
 * 
 ******************************************************************************/

void SUART_Transmit(const char DataValue)
{
 /* Basic Logic
    
    TX pin is usually high. A high to low bit is the starting bit and 
    a low to high bit is the ending bit. No parity bit. No flow control.
    BitCount is the number of bits to transmit. Data is transmitted LSB first.

 */

 // Send Start Bit
 UART_TX = 0;
 __delay_us(OneBitDelay);

 for ( unsigned char i = 0; i < DataBitCount; i++ )
 {
  //Set Data pin according to the DataValue
  if(((DataValue>>i)&0x1) == 0x1 ) //if Bit is high
  {
   UART_TX = 1;
  }
  else //if Bit is low
  {
   UART_TX = 0;
  }

     __delay_us(OneBitDelay);
 }

 //Send Stop Bit
 UART_TX = 1;
 __delay_us(OneBitDelay);
}

/*******************************************************************************
 * Function: void SUART_Write_Text(char *text)
 *
 * Returns: Nothing
 *
 * Description: writes text via soft UART
 * 
 ******************************************************************************/

void SUART_Write_Text(char *text)
{
  int i;
  
  for(i=0;text[i]!='\0';i++)
      SUART_Transmit(text[i]);
}


/*******************************************************************************
 * Function: void SUART_Read_Text(char *Output, unsigned int length)
 *
 * Returns: Nothing
 *
 * Description: reads text via soft UART
 * 
 ******************************************************************************/

void SUART_Read_Text(char *Output, unsigned int length)
{
	int i;
	for(int i=0;i<length;i++)
		Output[i] = SUART_Receive();
}


/*******************************************************************************
 * Function: void SUART_Write_Char(char a)
 *
 * Returns: Nothing
 *
 * Description: writes a character to SOFT UART
 * 
 ******************************************************************************/

void SUART_Write_Char(char a)
{
    SUART_Transmit(a - 0x128);
}