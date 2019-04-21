/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1719 w/int OSC @ 16MHz, 5v
 * Program: 17_OneWire
 * Compiler: XC8 (v2.05, MPLAX X v5.15)
 * Program Version: 1.0
 *                
 *                
 * Program Description: This Program Allows PIC16F1719 to use the one wire 
 *                      protocol by interfacing with a DS18B20 temperature
 *                      sensor. 
 * Hardware Description: A DS18B20 is connected to PINB0 with 4.7k resistor
 *                       and a CP2104 USB-UART converter is connected to PINB2
 *                      
 * Created April 20th, 2019, 11:39 PM
 */


/*******************************************************************************
 *Includes and defines
 ******************************************************************************/

#include "16F1717_Internal.h"
#include <xc.h>
#include "EUSART.h"
#include <stdlib.h>
#include "onewire.h"


// program variables
char getDat[10];
char TEMP_LSB;
char TEMP_MSB;
int  loop_var;
char far_temp;
char cel_temp;


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
   

    TRISBbits.TRISB2 = 0;
    ANSELBbits.ANSB2 = 0;
    
    TRISBbits.TRISB0 = 0;
    ANSELBbits.ANSB0 = 0;
    
    /////////////////////
    // Setup EUSART
    ////////////////////
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00; // unlock PPS
    
    RB2PPSbits.RB2PPS = 0x14; //RB2->EUSART:TX;
    RXPPSbits.RXPPS = 0x0B;   //RB3->EUSART:RX;
    
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x01; // lock PPS
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
  
    int present;  //var to check for device presence

    
    // Initialize EUSART module with 19200 baud
    EUSART_Initialize(19200);
    
    
    // buffer to hold temperature
    unsigned char buf[8]; 
    OW_Init();    // initialize OW

    present = OW_Reset();  // see if device is present
        
    if (present == 0)
    {
        EUSART_Write_Text("Device is Present");
    }
    
    else
    {
        EUSART_Write_Text("Device not present");
        return;
    }
    
    
    while(1){
        OW_Reset();                     // reset device
        OW_WriteByte(SKIP_ROM);         //Skip ROM
        OW_WriteByte(START_CONVERSION); // Start Conversion
        __delay_ms(5);
        
        OW_Reset();                    // reset device
        OW_WriteByte(SKIP_ROM);        // Skip ROM
        OW_WriteByte(READ_SCRATCHPAD); // Read Scratch Pad
        
        // read scratchpad data
        for(loop_var=0;loop_var<9;loop_var++)
        {
            getDat[loop_var] = OW_ReadByte();
        }

        // get temperature data
        TEMP_MSB = getDat[1]; // Sign byte + lsbit
        TEMP_LSB = getDat[0]; // Temp data plus lsb
        
         EUSART_Write_Text(itoa(buf, (int)TEMP_MSB, 10));
        if (TEMP_MSB <= 0x80)
        {
            TEMP_LSB = (TEMP_LSB/2); // shift to get whole degree
        } 
        
        TEMP_MSB = TEMP_MSB & 0x80;   // mask all but the sign bit
        
        if (TEMP_MSB >= 0x80)
        {
            TEMP_LSB = (~TEMP_LSB)+1;  // two's complement
        } 
        
       if (TEMP_MSB >= 0x80) 
       {
           TEMP_LSB = (TEMP_LSB/2);    // shift to get whole degree
       }

       if (TEMP_MSB >= 0x80) 
       {
           TEMP_LSB = ((-1)*TEMP_LSB);  // add sign bit
       } 
       
       // print temp in Celsius
       EUSART_Write_Text( "\nTempC degrees C\t:"); 
       EUSART_Write_Text(itoa(buf, (int)TEMP_LSB, 10));
       
    
        // convert to Fahrenheit
       cel_temp = TEMP_LSB;         
       far_temp = (((int)cel_temp)* 9)/5 + 32;
       
       // print temp in Farenheit
       EUSART_Write_Text( "\nTempF degrees F\t:"); // print temp. 
       EUSART_Write_Text(itoa(buf, (int)far_temp, 10));
       __delay_ms(1000);
    }
    
    return;
    
}
