/*
 * File: ds1302.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Int OSC @ 16MHz, 5v
 * Program: Library file for ds1302 RTCC
 * Compiler: XC8 (v1.38, MPLAX X v3.40)
 * Program Version: 1.1
 *                *Added additional comments
 *                
 * Program Description: This Library allows you to control the ds1302
 *                      
 * Created on April 18th, 2017, 11:40 PM
 */

#include "ds1302.h"

/*******************************************************************************
 * Function:void DS1302_Reset() 
 *
 * Returns: Nothing
 *
 * Description: Resets the DS1302
 * 
 ******************************************************************************/

void DS1302_Reset()
{
    SCLK = 0;
    CE = 0;
    CE = 1;
}


/*******************************************************************************
 * Function: unsigned char DS1302_WriteByte(unsigned char W_Byte)
 *
 * Returns: Nothing
 *
 * Description: Writes a byte of data into the DS1302
 * 
 ******************************************************************************/

void DS1302_WriteByte(unsigned char W_Byte) 
{
    unsigned char i;
    
    for(i = 0; i < 8; ++i)
    {
        IO = 0;
        
        if(W_Byte & 0x01)
        {
            IO = 1; /* set port pin high to read data */
        }
        
        SCLK = 0;
        SCLK = 1;
        W_Byte >>= 1;
    }
}

/*******************************************************************************
 * Function: unsigned char DS1302_ReadByte()
 *
 * Returns: Nothing
 *
 * Description: Reads a byte of data from the DS1302
 * 
 ******************************************************************************/

unsigned char DS1302_ReadByte()	
{
    unsigned char i;
    unsigned char R_Byte;
    unsigned char TmpByte;
    
    R_Byte = 0x00;
    
    Data_Tris = 1;
    IO = 1;
    
    for(i=0; i<8; ++i)
    {
        SCLK = 1;
        SCLK = 0;
        TmpByte = (unsigned char)IO;
        TmpByte <<= 7;
        R_Byte >>= 1;
        R_Byte |= TmpByte; 
    }
    Data_Tris = 0;
    return R_Byte;
}

/*******************************************************************************
 * Function: void DS1302_Initialize(byte sec, byte min, byte hr, byte day, byte date, 
                       byte mth, byte year)	
 *
 * Returns: Nothing
 *
 * Description: Initializes the DS1302 with time/date specified by user
 * 
 ******************************************************************************/

void DS1302_Initialize(byte sec, byte min, byte hr, byte day, byte date, 
                       byte mth, byte year)	
{

    byte sec1 = get_bcd(sec);
    byte min1 = get_bcd(min);
    byte hr1  = get_bcd(hr);
    byte day1 = get_bcd(day);
    byte date1 = get_bcd(date);
    byte mth1 = get_bcd(mth);
    byte year1 = get_bcd(year);
    
    
    DS1302_Reset();
    DS1302_WriteByte(0x8e);	/* control register */
    DS1302_WriteByte(0);	/* disable write protect */
    DS1302_Reset();
    DS1302_WriteByte(0x90);	/* trickle charger register */
    DS1302_WriteByte(0xab);	/* enable, 2 diodes, 8K resistor */
    DS1302_Reset();
    DS1302_WriteByte(0xbe);	/* clock burst write (eight registers) */
    DS1302_WriteByte(sec1);
    DS1302_WriteByte(min1);
    DS1302_WriteByte(hr1);
    DS1302_WriteByte(date1);
    DS1302_WriteByte(mth1);
    DS1302_WriteByte(day1);
    DS1302_WriteByte(year1);
    DS1302_WriteByte(0); /* must write control register in burst mode */
    DS1302_Reset();
}


/*******************************************************************************
 * Function: unsigned char get_bcd(unsigned char data)
 *
 * Returns: number in BCD format for RTCC
 *
 * Description: Converts decimal time into BCD format
 * 
 ******************************************************************************/

unsigned char get_bcd(unsigned char data)
{
   unsigned char nibh;
   unsigned char nibl;

   nibh=data/10;
   nibl=data-(nibh*10);

   return((nibh<<4)|nibl);
}


unsigned char get_dec(byte var)
{
    unsigned char var2;. 
    
    var2 =  (var >> 4) * 10;
    var2 += (var & 15);
    
    return var2;        
}

