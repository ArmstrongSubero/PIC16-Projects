/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1718 w/int OSC @ 32MHz, 5v
 * Program: 27_CLC
 * Compiler: XC8 (v2.46, MPLAX X v6.20)
 * Program Version: 1.2
 *                
 * Program Description: This Program Allows PIC16F1718 to use the CLC module. 
 *                      The CLC program is generated using the CLC GUI designer
 *                      tool.  
 * 
 * Hardware Description: Two pushbuttons are connected to RA0 and RA1 and an 
 *                       LED is connected to RA2
 *                     
 * Updated December 26th, 2025, 1:49 AM
 */

/*******************************************************************************
 *Includes and defines
 ******************************************************************************/
#include "PIC16F1718_Internal.h"

/*******************************************************************************
 *Initialize the CLC module
 ******************************************************************************/
void CLC1_Initialize(void)
{
    CLC1GLS0  = 0x02;
	CLC1GLS1  = 0x08;
	CLC1GLS2  = 0x08;
	CLC1GLS3  = 0x02;
	CLC1SEL0  = 0x00;
	CLC1SEL1  = 0x01;
	CLC1SEL2  = 0x00;
	CLC1SEL3  = 0x00;
	CLC1POL   = 0x00;
	CLC1CON   = 0x80;
	CLCIN0PPS = 0x00;
	CLCIN1PPS = 0x01;
	CLCIN2PPS = 0x00;
	CLCIN3PPS = 0x00;
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
void initMain(void)
{
    internal_32();
    __delay_ms(100);
    
    LATA = 0x00;
    ANSELA = 0;
    
    TRISAbits.TRISA0 = 1;
    TRISAbits.TRISA1 = 1;
    TRISAbits.TRISA2 = 0; 
        
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00; // unlock PPS
    
    CLCIN0PPS = 0x00;   //RA0->CLC1:CLCIN0;    
    CLCIN1PPS = 0x01;   //RA1->CLC1:CLCIN1;    
    RA2PPS = 0x04;      //RA2->CLC1:CLC1OUT;  
    
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x01; // lock PPS

    CLC1_Initialize();
}


/*******************************************************************************
 * Function: Main
 *
 * Returns: Nothing
 *
 * Description: Program entry point
 ******************************************************************************/
void main(void)
{
    initMain();

    while (1)
    {
        // nothing
    }
}
