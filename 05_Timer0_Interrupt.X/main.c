/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1718 w/int OSC @ 32MHz, 5v
 * Program: 05_Timer0_Interrupt
 * Compiler: XC8 (v2.46, MPLAX X v6.20)
 * Program Version: 1.2
 *                
 * Program Description: This Program Allows PIC16F1718 to turn on an LED 
 *                      using Timer0 internal interrupt while another LED 
 *                      is under pushbutton control 
 * 
 * Hardware Description: An LED is connected via a 1K resistor to PIN C3 and 
 *                       a switch is connected to PIN B0 and another LED is 
 *                       connected to PIN C4 via a 1K resistor. 
 *                       
 * Created November 4th, 2016, 1:00 PM
 * Updated on Thursday 25th, December, 2025, 1:25 AM
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
    
    // Run at 32 MHz
    internal_32();
    
    // Stabilize PLL
    __delay_ms(100);
    
    // Set PIN C3, C4 as output
    TRISCbits.TRISC3 = 0;
    TRISCbits.TRISC4 = 0;
    
    // Turn off LED
    LATCbits.LATC3 = 0;
    LATCbits.LATC4 = 0;
    
    // Set PIN B0 as input
    TRISBbits.TRISB0 = 1;
    
    // Configure ANSELB0 
    ANSELBbits.ANSB0 = 0;
    
    
    ///////////////////////
    // Configure Timer0
    //////////////////////
    
    // Select timer mode
    OPTION_REGbits.TMR0CS = 0;
    
    // Assign Prescaler to TIMER0
    OPTION_REGbits.PSA = 0;
    
    // Set Prescaler to 256
    OPTION_REGbits.PS = 0b111;
    
    // Clear pending overflow flag 
    // before enabling interrupt
    INTCONbits.TMR0IF = 0;
    
    // enable Timer0 interrupt
    INTCONbits.TMR0IE = 1;

    // enable global interrupts
    ei();  
}

/*******************************************************************************
 * Function: void interrupt isr(void)
 *
 * Returns: Nothing
 *
 * Description: Timer0 interrupt at a rate of 1 second
 ******************************************************************************/
volatile uint8_t tick = 0;   // set every Timer0 overflow

void __interrupt() isr(void)
{
    if (INTCONbits.TMR0IE && INTCONbits.TMR0IF) {
        INTCONbits.TMR0IF = 0;
        // Optional: TMR0 = 0;  // keep tick consistent; either way is OK
        tick = 1;
    }
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

    // --- LED1 timing ---
    // Timer0 overflow tick ~8.192ms -> 1 second ~ 122 ticks
    uint8_t sec_count = 0;

    // --- Button debounce state ---
    // Debounce requires N consecutive identical samples
    const uint8_t DEBOUNCE_TICKS = 4;  // 4 * 8.192ms ? 33ms
    uint8_t stable_btn = 1;           // assume released (pull-up makes it 1)
    uint8_t last_sample = 1;
    uint8_t same_count = 0;

    while (1) {

        if (tick) {
            tick = 0;

            // ---------- LED1: 1 Hz toggle ----------
            if (++sec_count >= 122) {
                sec_count = 0;
                LATCbits.LATC3 ^= 1;
            }

            // ---------- Button debounce + press event ----------
            uint8_t sample = PORTBbits.RB0; // 1=released, 0=pressed

            if (sample == last_sample) {
                if (same_count < DEBOUNCE_TICKS) same_count++;
            } else {
                same_count = 0;
                last_sample = sample;
            }

            if (same_count == DEBOUNCE_TICKS) {
                // We consider it stable now
                if (stable_btn != sample) {
                    stable_btn = sample;

                    // Detect press edge (released -> pressed)
                    if (stable_btn == 0) {
                        LATCbits.LATC4 ^= 1;   // LED2 toggles on each press
                    }
                }
            }
        }

        // main loop can do other work here;
    }
}