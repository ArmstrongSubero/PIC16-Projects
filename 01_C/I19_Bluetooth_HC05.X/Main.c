/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Int OSC @ 16MHz, 5v
 * Program: I19_Bluetooth_HC05
 * Compiler: XC8 (v1.41, MPLAX X v3.61)
 * Program Version: 1.0
 *                
 *                
 * Program Description: This Program Allows PIC16F1717 to communicate via 
 *                      Bluetooth
 *                      
 *           
 * Hardware Description: A HC-05 is connected to the PIC16F1717 as follows:
 *                        
 *                       RX -> RB3
 *                       TX -> RB2
 *                      
 * Created May 15th, 2017, 5:00 PM
 */


/*******************************************************************************
 *Includes and defines
 ******************************************************************************/

#include "16F1717_Internal.h"
#include "EUSART.h"
#include <string.h>

#define LED LATDbits.LATD1


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
    
    // Set PIN D1 as output
    TRISDbits.TRISD1 = 0;
    
    // Turn off LED
    LATDbits.LATD1 = 0;
    
    // Setup PORTD
    TRISD = 0;
    ANSELD = 0;
    
    // Setup pins for EUSART
    TRISBbits.TRISB2 = 0;
    ANSELBbits.ANSB2 = 0;
    
    TRISBbits.TRISB3 = 1;
    ANSELBbits.ANSB3 = 0;
    
    
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
    
    // Initialize EUSART module with 9600 baud
    EUSART_Initialize(9600);
    
    char buf[20];
    char* ON;
    char* OFF;
    
    while(1){
        
        // Send start so we'll know it's working
        EUSART_Write_Text("Start");
        
        // Read UART messages
        EUSART_Read_Text(buf, 4);
    
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
