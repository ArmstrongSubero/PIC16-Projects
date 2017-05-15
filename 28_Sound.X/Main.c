/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Int OSC @ 16MHz, 5v
 * Program: 28_Sound
 * Compiler: XC8 (v1.41, MPLAX X v3.55)
 * Program Version: 1.0
 *                
 *                
 * Program Description: This Program generates a simple alarm on PIN B2
 * 
 * Hardware Description: A Piezo is connected to PIN B2 and a SSD1306 OLED is 
 *                       connected as per header file.
 *
 *                      
 * Created April 15st, 2017, 12:26 PM
 */


/*******************************************************************************
 *Includes and defines
 ******************************************************************************/

#include "16F1717_Internal.h"
#include "I2C.h"
#include "oled.h"
#include "sound.h"
#include <string.h>


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
      
    /////////////////////
    // Setup OLED
    ////////////////////
    
     // Setup pins for I2C
     ANSELCbits.ANSC4 = 0;
     ANSELCbits.ANSC5 = 0;
     
     TRISCbits.TRISC4 = 1;
     TRISCbits.TRISC5 = 1;
     
     PPSLOCK = 0x55;
     PPSLOCK = 0xAA;
     PPSLOCKbits.PPSLOCKED = 0x00; // unlock PPS

     RC4PPSbits.RC4PPS = 0x0011;   //RC4->MSSP:SDA;
     SSPDATPPSbits.SSPDATPPS = 0x0014;   //RC4->MSSP:SDA;
     SSPCLKPPSbits.SSPCLKPPS = 0x0015;   //RC5->MSSP:SCL;
     RC5PPSbits.RC5PPS = 0x0010;   //RC5->MSSP:SCL;
  
     PPSLOCK = 0x55;
     PPSLOCK = 0xAA;
     PPSLOCKbits.PPSLOCKED = 0x01; // lock PPS
     
     ///////////////////////
     // Setup Buzzer Pins
     //////////////////////
     TRISBbits.TRISB2 = 0;
    
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
    
    // Initialize I2C
    I2C_Init();  
    __delay_ms(500);
    
    // Initialize OLED
    OLED_Init();
   
    // clear OLED
    OLED_Clear();
    
    __delay_ms(1000);
  
    while(1){ 
         
        // Play 3 beeps at startup
        
        play_alarm();
        __delay_ms(1000);
        
        play_alarm();
        __delay_ms(1000);
        
        play_alarm();
        __delay_ms(1000);
        
         OLED_YX(0, 0);
         OLED_Write_String("Sounding Alarm");
         __delay_ms(1000);
         
         // Play alarm
         for (int i=0; i<= 60; i++){
             play_alarm();
         }
         
         
         OLED_Clear();
    }
    
    return;   
}



