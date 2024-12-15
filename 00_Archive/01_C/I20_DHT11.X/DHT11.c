/*
 * File: DHT11.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Int OSC @ 16MHz, 5v
 * Program: Library file to configure PIC16F1717
 * Compiler: XC8 (v1.38, MPLAX X v5.05)
 * Program Version: 1.0
 *                
 * Program Description: This Library allows you to use a DHT11 temp/hum sensor
 *                      
 * Created on September 11th, 2018, 01:39 PM
 */

/*******************************************************************************
 * Includes and defines
 ******************************************************************************/
#include "DHT11.h"

/*******************************************************************************
* Function: void DHT11_Init()
*
* Returns: Nothing
*
* Description: Initializes the DHT11 module
*
*******************************************************************************/
void DHT11_Init()
{    
    // set as output
    Dat_Direction = 0;  
    
    // send 18 ms pulse
    Dat_Output = 0; 
    __delay_ms(18);
    
    // pull high
    Dat_Output = 1; 
    __delay_us(20);
    
    // set as input
    Dat_Direction = 1;   
}

/*******************************************************************************
* Function: void DHT11_Check()
* 
* Returns: Nothing
*
* Description: Check the DHT11 module
*
*******************************************************************************/
void DHT11_Check()
{
    // wait for bus high
    while(Dat_Input & 1); 

    // wait for bus low    
    while(!(Dat_Input & 1)); 
    
    // wait for bus high
    while(Dat_Input & 1); 
}


/*******************************************************************************
* Function: char DHT11_Read()
* 
* Returns: Nothing
*
* Description: Read the DHT11 module
*
*******************************************************************************/
char DHT11_Read()
{
    char i,dat = 0;  
    
    for(i = 0; i<8; i++)
    {
        // wait till 0 pulse, start
        while(!(Dat_Input & 1));  // wait till 0 pulse
        __delay_us(30); 

        // check if data is 0 or 1        
        if(Dat_Input & 1)
        {
          dat = ((dat<<1) | 1); 
        }
        else
        {
          dat = (dat<<1); 
        }
        
        while(Dat_Input & 1);
    }
  return dat;
}