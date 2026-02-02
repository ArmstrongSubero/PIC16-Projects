/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1718 w/int OSC @ 32MHz, 5v
 * Program: 17_Comparator
 * Compiler: XC8 (v2.46, MPLAX X v6.20)
 * Program Version: 1.3
 *                
 * Program Description: This Program uses the on board comparator module of
 *                      the PIC microcontroller. When the voltage at Vin+ is
 *                      more than the voltage at Vin- the comparator outputs a
 *                      logic level high and vice versa.
 * 
 * Hardware Description: An LED is connected via a 1k resistor to PIN RA3 and
 *                       the output of a 10k voltage divider is fed into the 
 *                       - input (PIN RA0) of the comparator with the + input
 *                       (PIN RA2) being the output of a 10k pot is fed into 
 *                        the positive end.
 *                       
 * Created November 4th, 2016, 1:00 PM
 * Updated on Thursday 25th, December, 2025, 7:24 PM
 */


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
    // Run at 32 MHz
    internal_32();
    
    //////////////////////
    // Setup Comparator1
    /////////////////////
    
    //_____________
    // RA0 = C1IN0-
    //_____________
    
    // Set as input
    TRISAbits.TRISA0 = 1;
    
    // Set analog mode on
    ANSELAbits.ANSA0 = 1;
    
    
    //______________
    // RA2 = C1IN0+
    //______________
    
    // Set as input
    TRISAbits.TRISA2 = 1;
    
    // Set analog mode on
    ANSELAbits.ANSA2 = 1;
    
    
    TRISAbits.TRISA3 = 0;
    
    //___________________
    // RA3 = C1OUT
    //___________________
    
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00; // unlock PPS

    RA3PPSbits.RA3PPS = 0x16;   //RA3->CMP1:C1OUT;

    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x01; // lock PPS
    
    TRISAbits.TRISA3 = 0;
    
    /////////////////////////
    // configure comparator1
    /////////////////////////
    
    // enable comparator
    CM1CON0bits.C1ON = 1;
    
    // output not inverted
    CM1CON0bits.C1POL = 0;
    
    // normal power mode
    CM1CON0bits.C1SP = 1;
    
    // asynchronous output
    CM1CON0bits.C1SYNC = 0;
    
    // turn on zero latency filter
    CM1CON0bits.C1ZLF = 1;
    
    //Enable comparator hysteresis (45 mV)
    CM1CON0bits.C1HYS = 1;
    
    // + in = C1IN+ pin
    CM1CON1bits.C1PCH = 0b00;
    
    // - in = C1IN- PIN
    CM1CON1bits.C1NCH = 0b00;
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
        // Have the CPU sleep!
        SLEEP();
    }
    
    return;
}
