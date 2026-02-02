/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1719 w/int OSC @ 32MHz, 5v
 * Program: P54_Inductance_Meter_LCD
 * Compiler: XC8 (v2.46, MPLAX X v6.20)
 * Program Version: 1.2
 *                  * Added Autoranging
 *                  * Added Calibration button
 *                  * Added LCD
 * 
 * Program Description: This program is designed to measure the inductance of a 
 *                      coil in conjunction with a known capacitor to form an LC 
 *                      circuit. Using a PIC16F1719 microcontroller running at 32 MHz, 
 *                      the program measures the frequency of oscillation in the 
 *                      LC circuit using Timer0 and calculates the inductance based 
 *                      on the known capacitance value. It provides the results 
 *                      via UART, displaying the frequency and inductance in either 
 *                      microhenries (µH) or millihenries (mH).Additionally, the program 
 *                      includes a calibration routine triggered by a push button connected 
 *                      to RC6. During calibration, the leads are shorted, and the program
 *                      measures the offset value, which is then subtracted from subsequent 
 *                      measurements to zero out any inherent inductance. 
 * 
 * Hardware Description: A push button on RC6 is used to trigger the calibration routine, 
 *                       The UART pins, RB2 (TX) and RB3 (RX), are connected to a 
 *                       USB-to-UART converter for serial communication with a computer, 
 *                       allowing the user to view measurement results and debug information. 
 *                       The LC circuit includes a fixed 100 nF capacitor, and the microcontroller 
 *                       measures the oscillation frequency via the T0CKI input on RB0 using 
 *                       Timer0 in counter mode. Additional components like resistors 
 *                       ensure proper signal conditioning. This version adds an LCD
 *                       A SC1601K that is connected as follows:
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
 *                       
 * Created December 14th, 2024, 9:33 PM
 * Last Updated: December 15th, 2024, 1:16 AM
 */


/*******************************************************************************
 *Includes and defines
 ******************************************************************************/

#include "PIC16F1719_Internal.h"
#include "SC1601_LCD.h"


#define TEST_CIRCUIT_ONE_OUTPUT_ON LATCbits.LATC4   // button for circuit selection
#define CALIBRATION_BUTTON PORTCbits.RC6            // button for calibration

volatile uint16_t tmr0_overflows = 0;              

// set default calibration value
uint8_t calibration_value = 98;


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
    
    // Allow PLL startup time ~2 ms
    __delay_ms(10);
    
   /////////////////////
    // Setup PPS
    ////////////////////
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00; // unlock PPS
    
    T0CKIPPSbits.T0CKIPPS = 0x08;   //RB0->TMR0:T0CKI;
    
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x01; // lock PPS
    
    // RC4 as I/O for controlling active 
    TRISCbits.TRISC4 = 0;
    ANSELCbits.ANSC4 = 0;
    
    TRISCbits.TRISC6 = 1; // RC6 as input for calibration button
    ANSELCbits.ANSC6 = 0;

    // Set RB0 as input (T0CKI)
    TRISBbits.TRISB0 = 1;
    ANSELBbits.ANSB0 = 0;

    // Configure Timer0 in counter mode with prescaler
    OPTION_REGbits.TMR0CS = 1; // Counter mode (use T0CKI pin)
    OPTION_REGbits.PSA = 0;    // Assign prescaler to Timer0
    OPTION_REGbits.PS = 0b011; // Set prescaler to 1:16
    TMR0 = 0;                  // Clear Timer0

    // Enable Timer0 overflow interrupt
    INTCONbits.TMR0IE = 1;
    INTCONbits.TMR0IF = 0;

    // Configure Timer1 for 100ms interval
    T1CON = 0b00110001; // Timer1 ON, 1:8 prescaler
    TMR1 = 0;           // Clear Timer1
    PIE1bits.TMR1IE = 1; // Enable Timer1 interrupt
    INTCONbits.PEIE = 1; // Enable peripheral interrupts

    // Enable global interrupts
    INTCONbits.GIE = 1;
    

    // Setup LCD Port
    TRISD = 0x00;
    ANSELD = 0x00;
    PORTD = 0x00;

}


/*******************************************************************************
 * Function: void __interrupt() isr()
 *
 * Returns: Nothing
 *
 * Description: Interrupt service routine handling
 *
 ******************************************************************************/
void __interrupt() isr() {
    if (INTCONbits.TMR0IF) {
        // Timer0 overflow occurred
        tmr0_overflows++;
        INTCONbits.TMR0IF = 0; // Clear overflow flag
    }

    if (PIR1bits.TMR1IF) {
        // Timer1 interrupt (100ms interval)
        PIR1bits.TMR1IF = 0; // Clear Timer1 interrupt flag
        TMR1 = 0;            // Reset Timer1
    }
}

/*******************************************************************************
 * Function: uint16_t ReadTimer0WithOverflows() 
 *
 * Returns: Timer0 Overflows
 *
 * Description: combines Timer0 count with overflow counter and returns value
 *
 ******************************************************************************/
uint16_t ReadTimer0WithOverflows() {
    // Combine Timer0 count with overflow counter
    return (tmr0_overflows * 256) + TMR0;
}

/*******************************************************************************
 * Function: void calibrate()
 * 
 * Returns: Nothing
 *
 * Description: Enters calibration mode and measures offset value when leads
 * are shorted together.
 * 
 ******************************************************************************/
void calibrate() {
    Lcd_Clear();
    Lcd_Set_Cursor(1, 1);
    Lcd_Write_String("Calibrating...");
    __delay_ms(1500); // Allow time for user to short the leads
    
    // Measure the offset with leads shorted
    uint16_t count_start = ReadTimer0WithOverflows();
    __delay_ms(1000); // 1-second interval
    uint16_t count_end = ReadTimer0WithOverflows();

    uint16_t total_counts = (count_end >= count_start) 
                            ? (count_end - count_start) 
                            : ((tmr0_overflows - 1) * 256 + (256 - count_start) + count_end);
    tmr0_overflows = 0;

    float frequency = ((float)total_counts * 16) / 1.0; // Frequency in Hz

    if (frequency > 0) {
        float capacitance = 100e-9; // 100 nF
        float precomputed_constant = 4 * 3.14159 * 3.14159 * capacitance;
        float inductance_h = 1.0 / (precomputed_constant * frequency * frequency);
        calibration_value = (uint8_t)(inductance_h * 1e6); // Convert to µH
        Lcd_Clear();
        Lcd_Set_Cursor(1, 1);
        Lcd_Write_String("Offset (uH): ");
       
        Lcd_Set_Cursor(1, 11);
        Lcd_Write_Padded_Integer(calibration_value, 4);
    } else {
        Lcd_Clear();
        Lcd_Set_Cursor(1, 1);
        Lcd_Write_String("Error: Unable to measure frequency");
    }
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
    
    uint16_t count_start, count_end, total_counts;
    float frequency, inductance_h, inductance_uh, inductance_mh; // Inductance in Henries, microhenries, and millihenries
    
    // Set capacitance to 100 nF
    float capacitance = 100e-9; // Capacitance in Farads (100 nF)
    
    // Precompute the constant for inductance calculation
    float precomputed_constant = 4 * 3.14159 * 3.14159 * capacitance; // Precomputed 4?²C
    
    // Initialize LCD
    Lcd_Init();
    
    // Allow time to Stabalize
    __delay_ms(100);
    
    Lcd_Clear();

    while (1) 
    { 
        TEST_CIRCUIT_ONE_OUTPUT_ON = 1;
        
        // Check if calibration button is pressed
        if (CALIBRATION_BUTTON != 1) {
            __delay_ms(50); // Debounce delay
            if (CALIBRATION_BUTTON != 1) {
                calibrate(); // Enter calibration mode
                while (CALIBRATION_BUTTON != 1); // Wait for button release
            }
        }
        
        // Measure frequency
        count_start = ReadTimer0WithOverflows();
        __delay_ms(1000); // 1-second interval for better accuracy at low frequencies
        count_end = ReadTimer0WithOverflows();

        // Handle overflow and calculate total counts
        total_counts = (count_end >= count_start) 
                        ? (count_end - count_start) 
                        : ((tmr0_overflows - 1) * 256 + (256 - count_start) + count_end);
        tmr0_overflows = 0;

        // Calculate frequency in Hz
        frequency = ((float)total_counts * 16) / 1.0; // 2-second interval for frequency calculation

        if (frequency > 0) {
            
            if (frequency < 1000.0) {
                // Frequency below 1000 Hz: Out of range
                Lcd_Clear();
                Lcd_Set_Cursor(1, 1);
                Lcd_Write_String("Err: Too Large");
                __delay_ms(2000);
                continue; // Skip to the next loop iteration
            }
            
            // Calculate inductance in Henries
            inductance_h = 1.0 / (precomputed_constant * frequency * frequency);

            // Convert inductance to microhenries (µH)
            inductance_uh = inductance_h * 1e6; // Convert from H to µH
            inductance_uh = inductance_uh - calibration_value;

            // Check if inductance exceeds 999 µH
            if (inductance_uh > 999.0) {
                // Convert to millihenries (mH)
                inductance_mh = inductance_uh / 1000.0;
                
                Lcd_Clear();
                Lcd_Set_Cursor(1, 1);
                Lcd_Write_String("I (mH): ");
                Lcd_Set_Cursor(1, 9);
                Lcd_Write_Float(inductance_mh);
                
            } else {
                Lcd_Clear();
                Lcd_Set_Cursor(1, 1);
                Lcd_Write_String("I (uH): ");
                Lcd_Set_Cursor(1, 9);
                Lcd_Write_Float(inductance_uh);
                __delay_ms(500);
            }
        } else {
              Lcd_Clear();
              Lcd_Set_Cursor(1, 1);
            // Handle invalid or very low frequencies
            Lcd_Write_String("Err: Range");
        }
    }

    return;   
}
