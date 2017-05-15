/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Int OSC @ 16MHz, 5v
 * Program: 19_Timer2
 * Compiler: XC8 (v1.38, MPLAX X v3.40)
 * Program Version: 1.0
 *                
 *                
 * Program Description: This Program uses Timer2 to blink an LED at precisely
 *                      1 Hz
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
 * A LED is connected to PIND1                  
 *                      
 * Created November 7th, 2016, 5:00 PM
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
    
    /////////////////////
    // Configure Timer2
    /////////////////////
    
    /*                                     fclk
     *  count =       -------------------------------------------------
     *                4 * prescaler * (PR2-TMR2) * postscaler * freqout
     * 
     * 
     * count = 16 000 000 / 4 * 16  * (256) * 15 * 1
     * 
     * count = ~65
     *
     */
    
    
    // prescale = 16 
    T2CONbits.T2CKPS = 0b10;
    
    // Set period to 255
    PR2 = 255;
    
    // Set TMR2 to 0
    TMR2 = 0;
    
    // postscale = 15 
    T2CONbits.T2OUTPS = 0b1110;
    
    // enable timer2
    T2CONbits.TMR2ON = 1;
    
    // enable timer2 interrupt
    PIE1bits.TMR2IE = 1;
    
    // enable peripheral interrupt
    INTCONbits.PEIE = 1;
    
    // enable global interrupts
    ei();
    
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
        
        Lcd_Set_Cursor(1,1);
        __delay_ms(5);
        Lcd_Write_String("Ready");
        
        __delay_ms(2000);
        Lcd_Clear();
    }
    
    return;   
}

/*******************************************************************************
 * Function: void interrupt isr(void)
 *
 * Returns: Nothing
 *
 * Description: Timer2 interrupt at a rate of 1 second
 ******************************************************************************/

void interrupt isr(void){
    static uint8_t count = 0;
    
    PIR1bits.TMR2IF = 0;
    
    count++;
    
    // Blink every second
    if (count == 65){
        count = 0;
        LATDbits.LATD1 = 1;
    }
    
    else {
        LATDbits.LATD1 = 0;
    }
}
