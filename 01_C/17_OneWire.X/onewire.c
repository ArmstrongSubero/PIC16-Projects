/*
 * File: onewire.c
 * Author: Armstrong Subero
 * Processor: PIC16F1717 w/int OSC @ 16MHz, 5v
 * Program: Library file for DS1820 
 * Compiler:  XC8 (v2.05, MPLAX X v5.15)
 * Program Version: 1.0
 *              
 * Program Description: This Library allows you to setup the PIC16F1719 with
 *                      a DS1820 temperature sensor
 *                      
 * Created on April 20th, 2019, 11:44 PM
 */

/*******************************************************************************
 * Includes and defines
 ******************************************************************************/
#include "onewire.h"


/*******************************************************************************
* Function: void OW_Init(void)
*
* Returns: Nothing
*
* Description: Initializes pin with the one wire protocol
*
*******************************************************************************/
void OW_Init(void)
{
    OW_Analog = 0;
}

/*******************************************************************************
* Function: unsigned char OW_Reset(void)
*
* Returns: Nothing
*
* Description: Issues one wire reset signal for the DS1820
*
*******************************************************************************/
unsigned char OW_Reset(void)
{
    OW_Dir = 0;   // set as output  
    OW_Pin = 0;             //pull line low
    __delay_us(480);          // leave it low for 480us

    OW_Dir = 1;   // set as input
    
    __delay_us(60);           // wait for presence
    
    if (OW_Pin == 0)        // 0 is detected
    {
        __delay_us(480);
        return 0;
    }
    
    else                    // 1 is not detected  
    {
        __delay_us(480);
        return 1;
    }
} 

/*******************************************************************************
* Function: unsigned char OW_ReadBit() 
*
* Returns: Nothing
*
* Description: reads one bit of data via the OneWire bus
*
*******************************************************************************/
unsigned char OW_ReadBit() 
{
  unsigned char result;

  OW_Dir = 0;       // set as output
  OW_Pin = 0;       // set high
  __delay_us(1);      // 1 us delay
  
  OW_Dir = 1;       // set as input
  __delay_us(5);      // 5 us delay
  
  result = OW_Pin;  // read pin
  __delay_us(55);     // 55 us delay
  
  return result;    // return result
}


/*******************************************************************************
* Function: void OW_WriteBit(int b)
*
* Returns: Nothing
*
* Description: writes one bit of data via the OneWire bus
*
*******************************************************************************/
void OW_WriteBit(int b) 
{
    b = b & 0x01;    // AND 0x01
    
    if (b) 
    {
        OW_Dir = 0;   // set as output
        OW_Pin = 0;   // set high
        __delay_us(5);  // 5 us delay
        
        OW_Dir = 1;   // set as input
        __delay_us(60); // 60 us delay
    } 
    else 
    {
        OW_Dir = 0;   // set as output
        OW_Pin = 0;   // set high
        __delay_us(70); // 70 us delay
        
        OW_Dir = 1;   // set as input
        __delay_us(2);  // 2 us delay
  }
}

/*******************************************************************************
* Function: unsigned char OW_ReadByte() 
*
* Returns: Nothing
*
* Description: reads one byte of data via the OneWire bus
*
*******************************************************************************/
unsigned char OW_ReadByte(void)
{
    unsigned char i;
    unsigned char value = 0;
    
    for (i=0;i<8;i++)
    {
        // read byte in and shift left
        if(OW_ReadBit()) 
        {
            value|=0x01<<i;
        }
    } 
    
    __delay_ms(6);  // delay 6 ms
    
    return(value);
}

/*******************************************************************************
* Function: void OW_WriteBbyte (char val)
*
* Returns: Nothing
*
* Description: writes one byte of data via the OneWire bus
*
*******************************************************************************/
void OW_WriteByte(char val)
{
    unsigned char i;
    unsigned char temp;
    
    // write byte and shift val right inc spaces, then write bit
    for (i=0; i<8; i++) 
    {
        temp = val>>i;
        temp &= 0x01;
        OW_WriteBit(temp); 
    }
    __delay_ms(5);
}