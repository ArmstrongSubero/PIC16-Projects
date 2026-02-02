/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1719 w/int OSC @ 32MHz, 5v
 * Program: 52_EMIC2_TTS
 * Compiler: XC8 (v2.45, MPLAX X v6.15)
 * Program Version: 1.3
 *                  * Updated to PIC16F1718
 *                  * Updated from PIC16F1717 to PIC16F1719
 *                  * Updated clock speed to 32 MHz 
 *                  * Added PLL stabilization
 * 
 * Program Description: This Program Allows PIC16F1717 to communicate via the
 *                      EUSART module to a EMIC 2 TTS module.
 *                      
 *           
 * Hardware Description: A EMIC 2 TTS module is connected to the PIC16F1717 as
 *                       follows:
 * 
 *                       RB2-> SIN;
 *                       RB3-> SOUT;
 *                       
 *                       The other pins on the EMIC2 TTS are connected as per 
 *                       datasheet.
 *                       
 * Created February 25th, 2017, 9:55 PM
 * Updated on Friday 30th, January, 2026, 10:54 AM
 */


/*******************************************************************************
 *Includes and defines
 ******************************************************************************/

#include "PIC16F1718_Internal.h"
#include "EUSART.h"


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
    
    // Run at 32 MHz
    internal_32();
    
    // Allow PLL startup time ~100 ms
    __delay_ms(100);
    
    TRISBbits.TRISB2 = 0;
    ANSELBbits.ANSB2 = 0;
    
    /////////////////////
    // Setup EUSART
    ////////////////////
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00; // unlock PPS
    
    RB2PPSbits.RB2PPS = 0x14;   //RB2->EUSART:TX;
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
    
    char readEmic;
    
    // Initialize EUSART module with 9600 baud
    EUSART_Initialize(9600);
    
    // give the module time to stabilize
    __delay_ms(3000);
    
    // Send CR in case system is up
    EUSART_Write(13);
    
    while(1)
    {  
      // Say something
      EUSART_Write(83);
      EUSART_Write_Text("I am EMIC 2 Text to Speech Module");
      EUSART_Write(13);
      __delay_ms(500);      
    }
    
    return;   
}
