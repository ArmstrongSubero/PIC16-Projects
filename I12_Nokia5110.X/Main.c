/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Int OSC @ 16MHz, 5v
 * Program: I12_Nokia5110
 * Compiler: XC8 (v1.38, MPLAX X v5.05)
 * Program Version: 1.0     
 *                
 * Program Description: This Program Allows PIC16F1717 to interface to a Nokia
 *                      5110 LCD module
 *                      
 *           
 * Hardware Description: A Nokia 5110 LCD is connected via a logic level Conveter
 *                       as follows:
 *                        
 *                       Vcc  --> Vdd
 *                       Gnd  --> Vss
 *                       SCE  --> D0
 *                       RST  --> D1
 *                       DC   --> D2  (Via 10 k resistor)
 *                       SCK  --> RC3
 *                       MOSI --> RC5
 *                       LED  --> Vdd (Via 1k resistor)
 *                     
 *                      
 * Created September 11th, 2018, 12:04 PM
 */


/*******************************************************************************
 *Includes and defines
 ******************************************************************************/

#include "16F1717_Internal.h"
#include "SPI.h"
#include "Bitmap.h"
#include "Nokia5110.h"


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
    
    // Setup PORTC for SPI
    ANSELCbits.ANSC3 = 0;
    ANSELCbits.ANSC4 = 0;
    ANSELCbits.ANSC5 = 0;
    
    TRISCbits.TRISC3 = 0;
    TRISCbits.TRISC4 = 1;
    TRISCbits.TRISC5 = 0;
     
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00; // unlock PPS
    
    SSPDATPPSbits.SSPDATPPS = 0x14;   //RC4->MSSP:SDI;
    RC3PPSbits.RC3PPS = 0x10;         //RC3->MSSP:SCK;
    RC5PPSbits.RC5PPS = 0x11;         //RC5->MSSP:SDO;

    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x01; // lock PPS
    
    
    // Initialize SPI
    SPI_Initialize();

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
    
    //Initialize LCD and clear screen
    LCD5110_init();
    LCD5110_clearScreen();
    
    
    while(1){
        
    //Draw bitmap "Microchip Logo"
    LCD5110_send(0x40 + 0, 0); //Y address
    LCD5110_send(0x80 + 0, 0); //X address
    LCD5110_drawBitmap(microchip);
    __delay_ms(5000);
    LCD5110_clearScreen();
    
      //Write text routines
    LCD5110_send(0x40 + 0, 0); //Y address
    LCD5110_send(0x80 + 0, 0); //X address
    LCD5110_sendString("Text");
    __delay_ms(1000);
    LCD5110_clearScreen();
    
    
    //Begin write integer routines
    int u;

    for (u = 0; u<= 10; u++){
        LCD5110_send(0x40 + 0, 0); //Y address
        LCD5110_send(0x80 + 0, 0); //X address

        LCD5110_writeInteger(u);
        __delay_ms(500);
        LCD5110_clearScreen();
    }

    //Start braw border routines
    LCD5110_drawBorder();
    LCD5110_send(0x40 + 10, 0); //Y address
    LCD5110_send(0x80 + 10, 0); //X address
    LCD5110_sendString("Text in Box");
    __delay_ms(5000);

    LCD5110_clearScreen();
    
    }
    
    return;
    
}