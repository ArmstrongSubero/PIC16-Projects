/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1718 w/int OSC @ 32MHz, 5v
 * Program: 06_Timer0_Ext_Interrupt
 * Compiler: XC8 (v2.45, MPLAX X v6.15)
 * Program Version: 1.2
 *                
 * Program Description: This Program Allows PIC16F1718 to demonstrate use 
 *                      of an external interrupt
 * 
 * Hardware Description: An LED is connected via a 1K resistor to PIN C3 and 
 *                       a switch is connected to PIN B0
 *                       
 * Created November 4th, 2016, 1:00 PM
 * Updated on Thursday 25th, December, 2025, 1:45 AM
 */

/*******************************************************************************
 Change History:
 Revision     Description
 v1.3         Updated for MPLABX v6.20 and XC8 v2.46 target PIC16F1718
 v1.2         Updated and recompiled with MPLABX v6.15 using XC8 v2.45
 v1.1         Changed from PIC16F1717 to PIC16F1719 and recompiled with
              MPLABX v5.15 using v2.05 of the XC8 compiler
*******************************************************************************/

/*******************************************************************************
 *Includes and defines
 ******************************************************************************/

#include "PIC16F1718_Internal.h"

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
    //////////////////////
    // Configure Ports
    /////////////////////
    
    // Run at 16 MHz
    internal_32();
    
    // Set PIN D1 as output
    TRISCbits.TRISC3 = 0;
    
    // Turn off LED
    LATCbits.LATC3 = 0;
    
    // Set PIN B0 as input
    TRISBbits.TRISB0 = 1;
    
    // Configure ANSELB0 
    ANSELBbits.ANSB0 = 0;
    
    /////////////////////////
    /// Configure Interrupts
    ////////////////////////
    
    // Set Interrupt pin to pin B0
    INTPPSbits.INTPPS = 0b01000;
    
    // lock   PPS 
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCK = 0x01; 
    
    // Trigger on falling edge
    OPTION_REGbits.INTEDG = 0;
    
    // Clear external interrupt flag
    INTCONbits.INTF = 0;
    
    //  Enable external interrupt
    INTCONbits.INTE = 1;
    
    // Enable global interrupt
    ei();  
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
    
    while(1){
        // Toggle LED Free running
        LATCbits.LATC3 = ~LATCbits.LATC3;
        __delay_ms(150);
    }
    
    return;
}

/*******************************************************************************
 * Function: void interrupt isr(void)
 *
 * Returns: Nothing
 *
 * Description: Use Timer0 External Interrupt
 ******************************************************************************/
void __interrupt() isr(void)
{                               
    // Clear interrupt flag
    INTCONbits.INTF = 0;
    
    // Toggle led
    LATCbits.LATC3 = 1;
    __delay_ms(1000);
}