/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1719 w/int OSC @ 32MHz, 5v
 * Program: 46_Bluetooth_HC05
 * Compiler: XC8 (v2.45, MPLAX X v6.15)
 * Program Version: 1.3
 *                  * Updated to PIC16F1718
 *                  * Updated from PIC16F1717 to PIC16F1719
 *                  * Updated clock speed to 32 MHz 
 *                  * Added PLL stabilization
 * 
 * Program Description: This program allows the PIC16F1718 to communicate 
 *                      via the EUSART to the HC-05 Bluetooth module. A 
 *                      Bluetooth serial device on Android is used to test 
 *                      the device. 
 * 
 * Hardware Description: The HC-05 is connected to the PIC16F1718 as follows:
 *                       RX -> RB2 
 *                       TX -> RB3
 *                       
 * Created November 7th, 2016, 7:05 PM
* Updated on Wednesday 28th, January, 2026, 2:51 PM
 */


/*******************************************************************************
 *Includes and defines
 ******************************************************************************/

#include "PIC16F1718_Internal.h"
#include "EUSART.h"
#include <string.h>

#define LED LATCbits.LATC3

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
    
    // setup pins for UART
    TRISBbits.TRISB2 = 0;
    ANSELBbits.ANSB2 = 0;
    
    TRISBbits.TRISB3 = 1;
    ANSELBbits.ANSB3 = 0;
    
    // Set C3 as output 
    TRISCbits.TRISC3 = 0;
    ANSELCbits.ANSC3 = 0; 
    
    LATCbits.LATC3 = 1; 
    
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
    
    // Initialize EUSART module with 19200 baud
    EUSART_Initialize(9600);
    
    char buf[20];
    char* ON;
    char* OFF;
    
    // Send start so we'll know it's working
    EUSART_Write_Text("Start");
    
    while(1)
    {          
        // Read UART messages
        EUSART_Read_Text(buf, 4);
        buf[4] = '\0';
    
        // Test received string
        ON =  strstr(buf, "ON");
        OFF = strstr(buf, "OFF");
      
        // If ON string, turn LED on
        if (ON)
        {
          EUSART_Write_Text("LED ON");
          LED = 1;
        }
        
        // If OFF string, turn LED off
        else if(OFF)
        {
          EUSART_Write_Text("LED OFF");
          LED = 0;
        }
    }
    
    return;   
}
