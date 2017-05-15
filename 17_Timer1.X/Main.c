/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Int OSC @ 16MHz, 5v
 * Program: 15_HD44780_LCD
 * Compiler: XC8 (v1.38, MPLAX X v3.40)
 * Program Version: 1.0
 *                
 *                
 * Program Description: This Program Allows PIC16F1717 to interface to HD44780
 *                      and compatible LCD's
 *                      
 *           
 * Hardware Description: An HD44780 compatible LCD is connected to PORTD of the
 *                       microcontroller as follows:
 * 
 *                       RS ---> RD2
 *                       R/W ---> GND
 *                       EN ---> RD3
 *                       D4 ---> RD4
 *                       D5 ---> RD5
 *                       D6 ---> RD6
 *                       D7 ---> RD7
 *                     
 *                      
 * Created November 7th, 2016, 11:05 AM
 */


/*******************************************************************************
 *Includes and defines
 ******************************************************************************/

#include "16F1717_Internal.h"
#include "LCD.h"


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
    
    // B5 = T1G
    
    // Set PIN B5 as input
    TRISBbits.TRISB5 = 1;
    
    // Configure ANSELB5
    ANSELBbits.ANSB5 = 0;
    
    ///////////////////////
    // Configure Timer1
    //////////////////////
    // Use processor clock
    T1CONbits.TMR1CS = 0b01;
    
    // No prescaler
    T1CONbits.T1CKPS = 0b00;
    
    // Enable timer1
    T1CONbits.TMR1ON = 1;
    
    // Gate enabled
    T1GCONbits.TMR1GE = 1;
    
    // Gate source is T1G pin
    T1GCONbits.T1GSS = 00;
    
    // Gate is active high
    T1GCONbits.T1GPOL = 1;
    
    // Toggle mode disabled
    T1GCONbits.T1GTM = 0;
    
    // Single-pulse mode enabled
    T1GCONbits.T1GSPM = 1;
    
    // Single pulse acquisition disabled
    T1GCONbits.T1GGO_nDONE = 0;
    
    // Initialize LCD
    Lcd_Init();
    __delay_ms(100);
    Lcd_Clear();
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
        
        // Measure width of pulses on T1G
        // Clear Timer1
        TMR1 = 0;
        
        // Acquire a single pulse
        T1GCONbits.T1GGO_nDONE = 1;
        
        // Wait for end of pulse
        while (T1GCONbits.T1GGO_nDONE);
        
        // Display count
        Lcd_Set_Cursor(1,1);
        __delay_ms(5);
        Lcd_Write_Integer(TMR1);
      
      __delay_ms(2000);
      Lcd_Clear();
    }
    
    return;
    
}
