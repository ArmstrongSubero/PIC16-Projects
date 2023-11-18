/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Int OSC @ 16MHz, 5v
 * Program: 12_Comparator
 * Compiler: XC8 (v1.41, MPLAX X v3.55)
 * Program Version: 1.0
 *                
 *                
 * Program Description: This Program uses the on board comparator module of
 *                      the PIC microcontroller. When the voltage at Vin+ is
 *                      more than the voltage at Vin- the comparator outputs a
 *                      logic level high and vice versa.
 *                     
 * Hardware Description: An LED is connected via a 10k resistor to PIN RA3 and
 *                       the output of a 1k voltage divider is fed into the 
 *                       - input (PIN RA0) of the comparator with the + input
 *                       (PIN RA2) being the output of a 10k pot is fed into 
 *                        the positive end.
 *                      
 * Created March 24th, 2017, 12:48 PM
 */


/*******************************************************************************
 *Includes and defines
 ******************************************************************************/

#include "16F1717_Internal.h"


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
