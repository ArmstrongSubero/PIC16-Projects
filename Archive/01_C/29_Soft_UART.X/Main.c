/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Int OSC @ 16MHz, 5v
 * Program: 28_Sound
 * Compiler: XC8 (v1.41, MPLAX X v3.55)
 * Program Version: 1.0
 *                
 *                
 * Program Description: This Program allows the PIC16F1717 to use a software 
 *                      UART
 * 
 * Hardware Description: A Parallax 2x16 LCD is connected to PIN RE 2
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
#include "sw_uart.h"
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
     // Setup SW UART 
     //////////////////////
      
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
    
    // Initialize I2C
    I2C_Init();  
    __delay_ms(500);
    
    // Initialize OLED
    OLED_Init();
   
    // clear OLED
    OLED_Clear();
    
    __delay_ms(1000);
     
     // Initialize SW UART
     SUART_Init(); 
     __delay_ms(1000);
  
    while(1){ 
         
         OLED_YX(0, 0);
         OLED_Write_String("Sending Message");
         __delay_ms(1000);
         
         OLED_Clear();
         
        SUART_Write_Text("Hello");
        __delay_ms(1000);
           
        __delay_ms(2000);
       
    }
    
    return;   
}



