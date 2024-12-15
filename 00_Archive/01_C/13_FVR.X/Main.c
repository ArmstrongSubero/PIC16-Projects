/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Int OSC @ 16MHz, 5v
 * Program: 13_FVR
 * Compiler: XC8 (v1.38, MPLAX X v3.40)
 * Program Version: 1.0
 *                
 *                
 * Program Description: This Program utilizes the FVR to provide a reference for
 *                      the positive input of the comparator.
 *                      
 * Hardware Description: An LED is connected via a 10k resistor to PIN RA3 and
 *                       the output of a 10k pot is fed into the - input 
 *                       (PIN RA0) of the comparator.
 *                      
 * Created March 24th, 2017, 1:30 PM
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
    // RA1 = C1IN1-
    //_____________
    
    // Set as input
    TRISAbits.TRISA0 = 1;
    
    // Set analog mode on
    ANSELAbits.ANSA0 = 1;
    
    
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
    CM1CON0bits.C1POL = 1;
    
    // normal power mode
    CM1CON0bits.C1SP = 1;
    
    // hysteresis disabled
    CM1CON0bits.C1HYS =0;
    
    // asynchronous output
    CM1CON0bits.C1SYNC = 0;
    
    // turn on zero latency filter
    CM1CON0bits.C1ZLF = 1;
    
    // Set IN+ to fixed voltage reference
    CM1CON1bits.C1PCH = 0b110;
    
    // - in = C1IN- PIN (C1OUT = 1 if < 2.048v)
    CM1CON1bits.C1NCH = 0b00;
    

    
    ///////////////////////////
    // Configure FVR
    //////////////////////////
    
    // Enable the FVR 
    FVRCONbits.FVREN = 1;
    
    // Output 2.048v to comparators
    FVRCONbits.CDAFVR = 0b10;
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
        // Put the CPU to sleep!
        SLEEP();
    }
    
    return;
    
}
