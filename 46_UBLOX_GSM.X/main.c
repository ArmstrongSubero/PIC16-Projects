/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1719 w/Int OSC @ 16MHz, 5v
 * Program: 46_UBLOX_GSM
 * Compiler: XC8 (v1.38, MPLAX X v3.40)
 * Program Version: 1.0
 *                
 *                
 * Program Description: This Program Allows PIC16F1719 to communicate with a
 *                      SIM800L GSM module and send a SMS message using a 
 *                      software UART. 
 *                      
 *           
 * Hardware Description: A SIM800L GSM module is connected as follows:
 *                      
 *                      5v      -> 5V 
 *                      GND     -> GND
 *                      VDD     -> NC
 *                      SIM_TXD -> RX
 *                      SIM_RXD -> TX
 *                      GND     -> GND
 *                     
 *                      
 * Created April 18th, 2017, 1:11 PM
 * Updated March 25th, 2024, 11:26 AM
 */


/*******************************************************************************
 *Includes and defines
 ******************************************************************************/
#include "PIC16F1719_Internal.h"

// Setup for soft UART
#define Baudrate 2400 //bps
#define OneBitDelay (1000000/Baudrate)
#define DataBitCount 8 // no parity, no flow control
#define UART_RX LATEbits.LATE0// UART RX pin
#define UART_TX LATEbits.LATE1 // UART TX pin
#define UART_RX_DIR TRISE0// UART RX pin direction register
#define UART_TX_DIR TRISE1 // UART TX pin direction register

//Function Declarations
void InitSoftUART(void);
unsigned char UART_Receive(void);
void UART_Transmit(const char);
void SUART_Write_Text(char *text);
void SUART_Write_Char(char a);
void SUART_Read_Text(char *Output, unsigned int length);

/*******************************************************************************
 * Function: void initMain()
 *
 * Returns: Nothing
 *
 * Description: Contains initializations for main
 * 
 * Usage: initMain()
 ******************************************************************************/

void initMain(){
    // Run at 16 MHz
    internal_16();
    
    // Setup pins
    TRISD = 0x00;
    ANSELD = 0x00;
    PORTD = 0x00;
  
    TRISE = 0;
    ANSELE = 0;
}


/*******************************************************************************
 * Function: Main
 *
 * Returns: Nothing
 *
 * Description: Program entry point
 ******************************************************************************/

void main(void) {
    initMain();
    
    __delay_ms(1000);
    
    
     InitSoftUART(); // Initialize Soft UART
     __delay_ms(1000);
    
    while(1){  
       
        // Send commands to module
        SUART_Write_Text("AT+CMGF=1\r\n");
        __delay_ms(1000);
         
        SUART_Write_Text("AT+CMGS=\"1113951\"\r\n");
        __delay_ms(1000);
        
        // Message to send
        SUART_Write_Text("Test");
        __delay_ms(1000);
        
        UART_Transmit((char)26);
        __delay_ms(1000);
}
    
    return;
}


/*******************************************************************************
 * Function: void InitSoftUART(void)
 *
 * Returns: Nothing
 *
 * Description: Initialize the software UART module
 ******************************************************************************/
void InitSoftUART(void)
{
 UART_TX = 1; // TX pin is high in idle state
 
 UART_RX_DIR = 1; // Input
 UART_TX_DIR = 0; // Output
}


/*******************************************************************************
 * Function: unsigned char UART_Receive(void)
 *
 * Returns: Status
 *
 * Description: Recieve a character via software USART 
 ******************************************************************************/
unsigned char UART_Receive(void)
{
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
 * Function: void UART_Transmit(const char DataValue)
 *
 * Returns: Status
 *
 * Description: Transmit a character via software USART 
 ******************************************************************************/
void UART_Transmit(const char DataValue)
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
 * Description: Writes Text via the Software UART module
 ******************************************************************************/
void SUART_Write_Text(char *text)
{
  int i;
  
  for(i=0;text[i]!='\0';i++)
      UART_Transmit(text[i]);
}


/*******************************************************************************
 * Function: void SUART_Read_Text(char *Output, unsigned int length)
 *
 * Returns: Nothing
 *
 * Description: Reads Text via the Software UART module
 ******************************************************************************/
void SUART_Read_Text(char *Output, unsigned int length)
{
	int i;
	for(int i=0;i<length;i++)
		Output[i] = UART_Receive();
}


/*******************************************************************************
 * Function: void SUART_Write_Char(char a)
 *
 * Returns: Nothing
 *
 * Description: Writes Text via the Software UART module
 ******************************************************************************/
void SUART_Write_Char(char a)
{
    UART_Transmit(a - 0x128);
}
