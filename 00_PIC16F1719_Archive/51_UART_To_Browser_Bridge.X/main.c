/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1719 w/int OSC @ 32MHz, 5v
 * Program: 51_UART_To_Browser_Bridge
 * Compiler: XC8 (v2.45, MPLAX X v6.15)
 * Program Version: 1.2
 *                  * Updated from PIC16F1717 to PIC16F1719
 *                  * Updated clock speed to 32 MHz 
 *                  * Added PLL stabilization
 * 
 * Program Description: This program allows the PIC16F1719 to communicate with 
 *                      a server to send data via the serial port and turn on
 *                      an LED based on data received from the server
 * 
 * Hardware Description: PIN RB2 of a the PIC16F1719 MCU is connected to 
 *                       a PL2303XX USB to UART converter cable and a 
 *                       10k potentiometer is connected to pin RA0. An LED 
 *                       is connected to PORTD1
 *                       
 * Created November 7th, 2016, 7:05 PM
 * Last Updated: March 24th, 2024, 4:58 AM
 */


/*******************************************************************************
 *Includes and defines
 ******************************************************************************/

#include "PIC16F1719_Internal.h"
#include "EUSART.h"


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
    
    // Set PIN D1 as output
    TRISDbits.TRISD1 = 0;
    
    // Turn off LED
    LATDbits.LATD1 = 0;
    
    // Setup PORTD
    TRISD = 0;
    ANSELD = 0;
    
    TRISBbits.TRISB2 = 0;
    ANSELBbits.ANSB2 = 0;
    
    /////////////////////
    // Setup EUSART
    ////////////////////
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00; // unlock PPS
    
    RB2PPSbits.RB2PPS = 0x14;   //RB2->EUSART:TX;
    RXPPSbits.RXPPS = 0x0B;   //RB3->EUSART:RX;
    
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x01; // lock PPS
    
    
    ////////////////////
    // Configure ADC
    ///////////////////
     
    // Set A0 as input
    TRISAbits.TRISA0 = 1;
    
    // Set A0 as analog
    ANSELAbits.ANSA0 = 1;
    
    // Fosc/32 ADC conversion time is 1.0 us
    ADCON1bits.ADCS = 0b010;
    
    // Right justified 
    ADCON1bits.ADFM = 1;
    
    // Vref- is Vss
    ADCON1bits.ADNREF = 0;
    
    // Vref+ is Vdd
    ADCON1bits.ADPREF = 0b00;
    
    // Set input channel to AN0
    ADCON0bits.CHS = 0b00000;
    
    // Zero ADRESL and ADRESH
    ADRESL = 0;
    ADRESH = 0;  
    
    //////////////////////
    // Configure Timer1
    /////////////////////
    // prescale = 1
    T1CONbits.T1CKPS = 0b00;
    
    // Set TMR1 to 0
    TMR1 = 0;
    
    // enable timer1
    T1CONbits.TMR1ON = 1;
    
    // enable timer1 interrupt
    PIE1bits.TMR1IE = 1;
    
    // enable peripheral interrupt
    INTCONbits.PEIE = 1;
    
    // enable global interrupts
    ei();
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
    
    // Initialize EUSART module with 19200 baud
    EUSART_Initialize(19200);
    
    while(1)
    {    
      
      if (PIR1bits.RCIF) 
        {   // Check if data received via USART
         char command = EUSART_Read();  // Read incoming command from serial port using EUSART
         if (command == '1') {
            LATDbits.LATD1 = 1; // Turn on the LED if '1' is received
            EUSART_Write_Text("LED turned on\n");
         } else if (command == '0') {
            LATDbits.LATD1 = 0; // Turn off the LED if '0' is received
            EUSART_Write_Text("LED turned off\n");
        }
      }
    }
    
    return;   
}


/*******************************************************************************
 * Function: void interrupt isr(void)
 *
 * Returns: Nothing
 *
 * Description: Timer1 interrupt
 ******************************************************************************/

void __interrupt() isr(void){
    static uint8_t count = 0;
    
    PIR1bits.TMR1IF = 0;
    
    count++;
    
    // Send sensor data every second
    if (count == 122){
        count = 0;
        
        // Turn ADC on
        ADCON0bits.ADON = 1;

        // Sample CH0
        __delay_us(10);
        ADCON0bits.GO = 1;
        while (ADCON0bits.GO_nDONE);

        // Store ADC result
        int result = ((ADRESH<<8)+ADRESL);

        EUSART_Write_Integer(result);
        EUSART_Write_Text("\n");
     
    }
    
}
