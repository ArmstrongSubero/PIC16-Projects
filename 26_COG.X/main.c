/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1718 w/int OSC @ 32MHz, 5v
 * Program: 26_COG
 * Compiler: XC8 (v2.46, MPLAX X v6.20)
 * Program Version: 1.2
 *                
 * Program Description: This Program Allows PIC16F1718 to used the complementary
 *                      output generator (COG) module
 * 
 * Hardware Description: Oscilloscope probes are connected to RB0 and RB1
 *                     
 * Updated December 26th, 2025, 12:44 AM
 */

/*******************************************************************************
 Change History:
 Revision     Description
 v1.2         Updated and recompiled with MPLABX v6.15 using XC8 v2.45
 v1.1         Changed from PIC16F1717 to PIC16F1719 and recompiled with
              MPLABX v5.15 using v2.05 of the XC8 compiler
*******************************************************************************/

/*******************************************************************************
 *Includes and defines
 ******************************************************************************/

#include "PIC16F1718_Internal.h"

// Control the Duty of PWM3
 void PWM3_LoadDutyValue(uint16_t dutyValue)
 {
     // Writing to 8 MSBs of PWM duty cycle in PWMDCH register
     PWM3DCH = (dutyValue & 0x03FC)>>2;
     
     // Writing to 2 LSBs of PWM duty cycle in PWMDCL register
     PWM3DCL = (dutyValue & 0x0003)<<6;
 }


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
    
    // PLL Stabilization delay
    __delay_ms(100);
    
    ///////////////////////////
    // Setup Pins 
    ///////////////////////////

    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB1 = 0;
    
    ANSELBbits.ANSB0 = 0;
    ANSELBbits.ANSB1 = 0;
    
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00; // unlock PPS
    
    RB1PPS = 0x09;   //RB1->COG1:COG1B;    
    RB0PPS = 0x08;   //RB0->COG1:COG1A; 

    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x01; // lock PPS
    
    ///////////////////////////
    // Setup Timer  2
    ///////////////////////////
    // PR2 255; 
    PR2 = 0xFF;

    // TMR2 0; 
    TMR2 = 0x00;

    // Clearing IF flag.
    PIR1bits.TMR2IF = 0;

    // T2CKPS 1:1; T2OUTPS 1:1; TMR2ON on; 
    T2CON = 0x04;
    
    // Start the Timer by writing to TMRxON bit
    T2CONbits.TMR2ON = 1;
    
    
    ///////////////////////////
    // Setup PWM
    //////////////////////////
   
    // PWM3POL active_hi; PWM3OUT disabled; PWM3EN enabled; 
    PWM3CON = 0x80;   

    // PWM3DCH 127; 
    PWM3DCH = 0x7F;   

    // PWM3DCL 3; 
    PWM3DCL = 0xC0;   

    // Select timer
    CCPTMRSbits.P3TSEL = 0;
    
    
    //////////////////////////
    // Setup the COG 
    /////////////////////////
    
    // Reset double buffered register COG1CON0
    COG1CON0 = 0x00;

    // Set the COG to the options selected in PIC10 / PIC12 / PIC16 / PIC18 MCUs
    // G1POLA Active high; G1POLB Active high; G1POLC Active high; G1POLD Active high; G1FDBS COGx_clock and COGxDBF; G1RDBS COGx_clock and COGxDBR; 
    COG1CON1 = 0x00;

    // G1RIS0 disabled; G1RIS1 disabled; G1RIS2 disabled; G1RIS3 disabled; G1RIS4 disabled; G1RIS5 disabled; G1RIS6 enabled; G1RIS7 disabled; 
    COG1RIS = 0x40;

    // G1RSIM0 Level Trigger; G1RSIM1 Level Trigger; G1RSIM2 Level Trigger; G1RSIM3 Level Trigger; G1RSIM4 Level Trigger; G1RSIM5 Level Trigger; G1RSIM6 Level Trigger; G1RSIM7 Level Trigger; 
    COG1RSIM = 0x40;

    // G1FIS0 disabled; G1FIS1 disabled; G1FIS2 disabled; G1FIS3 disabled; G1FIS4 disabled; G1FIS5 disabled; G1FIS6 enabled; G1FIS7 disabled; 
    COG1FIS = 0x40;

    // G1FSIM0 Level Trigger; G1FSIM1 Level Trigger; G1FSIM2 Level Trigger; G1FSIM3 Level Trigger; G1FSIM4 Level Trigger; G1FSIM5 Level Trigger; G1FSIM6 Edge Trigger; G1FSIM7 Level Trigger; 
    COG1FSIM = 0x40;

    // G1ASDAC tri-stated; G1ASDBD tri-stated; G1ARSEN disabled; G1ASE not shutdown; 
    COG1ASD0 = 0x2C;

    // G1AS0E disabled; G1AS1E disabled; G1AS2E disabled; G1AS3E disabled; 
    COG1ASD1 = 0x00;

    // G1STRA waveform; G1STRB waveform; G1STRC static level; G1STRD static level; G1SDATA static data low; G1SDATB static data low; G1SDATC static data low; G1SDATD static data low; 
    COG1STR = 0x0F;

    // G1DBR 20; 
    COG1DBR = 0x00;

    // G1DBF 0; 
    COG1DBF = 0x00;

    // G1BLKR 20; 
    COG1BLKR = 0x00;

    // G1BLKF 0; 
    COG1BLKF = 0x00;

    // G1PHR 20; 
    COG1PHR = 0x00;

    // G1PHF 0; 
    COG1PHF = 0x00;

    // G1MD Push-Pull mode; G1CS HFINTOSC; G1LD transfer complete; G1EN enabled; 
    COG1CON0 = 0x94;
    
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
        // Do nothing
    }
    
    return;
}
