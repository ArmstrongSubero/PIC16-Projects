/*
 * File: EUSART.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Int OSC @ 16MHz, 5v
 * Program: Library file containing functions for the EUSART module
 * Compiler: XC8 (v1.38, MPLAX X v3.40)
 * Program Version: 1.1
 *                *Added additional comments
 *                
 * Program Description: This Library allows you to use the EUSART module of the
 *                      PIC16F1717
 *                      
 * Created on November 7th, 2016, 7:10 PM
 */

/*******************************************************************************
 *Includes and defines
 ******************************************************************************/

#include "16F1717_Internal.h"
#include "EUSART.h"


/*******************************************************************************
 * Function: char EUSART_Initialize (const long int baudrate)
 *
 * Returns: Nothing
 *
 * Description: Initializes the EUSART module
 * 
 * Usage: EUSART_Initialize()
 ******************************************************************************/

char EUSART_Initialize(const long int baudrate)
{
 unsigned int x;
	x = (_XTAL_FREQ - baudrate*64)/(baudrate*64);
	if(x>255)
	{
		x = (_XTAL_FREQ - baudrate*16)/(baudrate*16);
		BRGH = 1;
	}
	if(x<256)
	{
	  SPBRG = x;
	  SYNC = 0;
	  SPEN = 1;
          TRISC7 = 1;
          TRISC6 = 1;
          CREN = 1;
          TXEN = 1;
	  return 1;
	}
	return 0;

}

/*******************************************************************************
 * Function: char EUSART_Read (void)
 *
 * Returns: Nothing
 *
 * Description: Reads the EUSART module
 * 
 * Usage: EUSART_Read()
 ******************************************************************************/

uint8_t EUSART_Read(void)
{

   RC1STAbits.SREN = 1;
    while(!PIR1bits.RCIF)
    {
    }

    
    if(1 == RC1STAbits.OERR)
    {
        // EUSART error - restart

        RC1STAbits.SPEN = 0; 
        RC1STAbits.SPEN = 1; 
    }

    return RC1REG;
}

/*******************************************************************************
 * Function: char EUSART_Write (uint8_t txData)
 *
 * Returns: Nothing
 *
 * Description: Writes to the EUSART module
 * 
 * Usage: EUSART_Write(x)
 ******************************************************************************/

void EUSART_Write(uint8_t txData)
{
    while(0 == PIR1bits.TXIF)
    {
    }

    TX1REG = txData;    // Write the data byte to the USART.
}

void EUSART_Read_Text(char *Output, unsigned int length)
{
	int i;
	for(int i=0;i<length;i++)
		Output[i] = EUSART_Read();
}

char EUSART_Read_Char(char *Output)
{
	Output = EUSART_Read();
    return Output;
}


/*******************************************************************************
 * Function: char EUSART_Write_Text (char *text)
 *
 * Returns: Nothing
 *
 * Description: Writes text the EUSART module
 * 
 * Usage: EUSART_Write_Text("Some String")
 ******************************************************************************/

void EUSART_Write_Text(char *text)
{
  int i;
  for(i=0;text[i]!='\0';i++)
	  EUSART_Write(text[i]);
}