/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Int OSC @ 16MHz, 5v
 * Program: 27_NCO
 * Compiler: XC8 (v1.38, MPLAX X v3.40)
 * Program Version: 1.0
 *                
 *                
 * Program Description: This Program Allows PIC16F1717 to use the NCO
 * 
 * Hardware Description: An oscilloscope probe is connected to PIN C0
 *                      
 * Created November 4th, 2016, 1:00 PM
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
    
    /////////////////
    // Set UP NCO
    ////////////////
    TRISCbits.TRISC0 = 0x00; // Port C as digital output port
    ANSELC = 0;
   
    bool state = GIE;
    GIE = 0;
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00; // unlock PPS

    RA4PPSbits.RA4PPS = 0x03;   //RC0->NCO1:NCO1OUT;

    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x01; // lock PPS

    TRISCbits.TRISC0 = 0;
    LATCbits.LATC0 = 0;
    
    // Enable NCO
    NCO1CONbits.N1EN = 1;
    
    // Operate in Fixed Duty cycle mode
    NCO1CONbits.N1PFM = 0;
    
    // Output signal active high
    NCO1CONbits.N1POL = 0;
    
    // Clock is 16 MHz
    NCO1CLKbits.N1CKS = 0b01;
    
    // NCO increment 
    NCO1INC =0x3334;
  
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
    
    NCO1INC = 0x4CCD;
    
    while(1){
       
     
    }
    
    return;
    
}
