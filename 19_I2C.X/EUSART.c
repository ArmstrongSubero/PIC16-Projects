/*
 * File: EUSART.c
 * Author: Armstrong Subero
 * PIC: 16F1719 w/Int OSC @ 16MHz, 5v
 * Program: Library file containing functions for the EUSART module
 * Compiler: XC8 (v2.45, MPLAX X v6.15)
 * Program Version: 1.2
 *                *Added additional comments
 *                *Simplified UART calculations
 *                
 * Program Description: This Library allows you to use the EUSART module of the
 *                      PIC16F1719 in Asynchronous Mode
 *                      
 * Created on November 7th, 2016, 7:10 PM
 * Updated on November 24th 2023, 1:00 AM
 */

/*******************************************************************************
 *Includes and defines
 ******************************************************************************/

#include "PIC16F1719_Internal.h"
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

	SPBRGL = x;
    BRGH = 0;
    BRG16 = 0;
    SYNC = 0;
    SPEN = 1;
    CREN = 1;
    TXEN = 1;
    
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
 * Function: void EUSART_Read_Text(char *Output, unsigned int length)
 *
 * Returns: Nothing
 *
 * Description: Writes to the EUSART module
 * 
 * Usage: 
 ******************************************************************************/
void EUSART_Read_Text(char *Output, unsigned int length)
{
	int i;
	for(int i=0;i<length;i++)
		Output[i] = EUSART_Read();
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




/*******************************************************************************
 * Function: void itoa(char **buf, int d)
 *
 * Returns: Nothing
 *
 * Description: Converts integer to ASCII values
 * 
 * Usage:     char buffer[20]; // Buffer to hold the ASCII representation of the integer
 *            char *ptr = buffer; // Pointer to buffer
 *
 *            itoa(&ptr, value_to_send); // Convert integer to ASCII
 ******************************************************************************/
void itoa(char **buf, int d)
{
    int div = 1;
    if (d < 0) 
    {
        *((*buf)++) = '-';
        d = -d;
    }

    int temp = d;
    while (temp / 10) 
    {
        temp /= 10;
        div *= 10;
    }

    while (div != 0)
    {
        int num = d / div;
        d %= div;
        div /= 10;
        *((*buf)++) = num + '0';
    }
    *(*buf) = '\0'; // Terminate the string
}


/*******************************************************************************
 * Function: char EUSART_Write_Integer (int value_to_send)
 *
 * Returns: Nothing
 *
 * Description: Writes text the EUSART module
 * 
 * Usage: EUSART_Write_Text(integer)
 ******************************************************************************/
void EUSART_Write_Integer(int value_to_send) 
{
    char buffer[20]; // Buffer to hold the ASCII representation of the integer
    char *ptr = buffer; // Pointer to buffer

    itoa(&ptr, value_to_send); // Convert integer to ASCII

    // Send each character (digit) of the ASCII representation over EUSART
    char *temp_ptr = buffer; // Temporary pointer to iterate through the buffer
    while (*temp_ptr != '\0') {
        EUSART_Write(*temp_ptr++);
    }
}
