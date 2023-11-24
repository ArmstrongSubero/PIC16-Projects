/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1719 w/int OSC @ 32MHz, 5v
 * Program: 19_I2C
 * Compiler: XC8 (v2.45, MPLAX X v6.15)
 * Program Version: 1.2
 *                  * Updated from PIC16F1717 to PIC16F1719
 *                  * Updated clock speed to 32 MHz 
 *                  * Added PLL stabilization
 * 
 * Program Description: This program allows the PIC16F1719 to demonstrate use 
 *                      of the I2C bus 
 * 
 * Hardware Description: PIN RB2 of a the PIC16F1719 MCU is connected to 
 *                       a PL2303XX USB to UART converter cable and a 
 *                       24LC16B EEPROM is connected to the I2C bus 
 *                       -- RC4 SDA 
 *                       -- RC5 SCL
 *                       10k pull up resistors are used on the I2C lines
 *                       
 * Created November 7th, 2016, 7:05 PM
 * Last Updated: November 24th, 2023, 3:36 AM
 */


/*******************************************************************************
 *Includes and defines
 ******************************************************************************/

#include "PIC16F1719_Internal.h"
#include "EUSART.h"
#include "I2C.h"


////////////////////////////////////
// Function to Write EEPROM 
////////////////////////////////////
void EEPROM_Write(unsigned char block_address, unsigned char word_address, unsigned char eeprom_data) {
    EUSART_Write_Text("Writing EEPROM\n");

    Send_I2C_StartBit();
    Send_I2C_ControlByte(block_address, 0);
    Send_I2C_Data(word_address);
    Send_I2C_Data(eeprom_data);
    Send_I2C_StopBit();

    // Add a delay after write (adjust the delay time as per EEPROM specifications)
    __delay_ms(200); // Increase the delay time to 20 milliseconds or more

    EUSART_Write_Text("Write completed\n");
}

//////////////////////////////////////////
// Function to Read EEPROM
/////////////////////////////////////////
unsigned char EEPROM_Read(unsigned char block_address, unsigned char word_address) {
    EUSART_Write_Text("Reading EEPROM\n");

    Send_I2C_StartBit();
    Send_I2C_ControlByte(block_address, 0);
    Send_I2C_Data(word_address);

    Send_I2C_StartBit();
    Send_I2C_ControlByte(block_address, 1);
    unsigned char incoming_data = Read_I2C_Data();
    Send_I2C_NAK();
    Send_I2C_StopBit();
    
    __delay_ms(1000);

    return incoming_data;
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
    
    // Setup pins for I2C
    ANSELCbits.ANSC4 = 0;
    ANSELCbits.ANSC5 = 0;
     
    TRISCbits.TRISC4 = 1;
    TRISCbits.TRISC5 = 1;
    
    /////////////////////
    // Setup EUSART
    ////////////////////
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00; // unlock PPS
    
    RB2PPSbits.RB2PPS = 0x14;   //RB2->EUSART:TX;
    RXPPSbits.RXPPS = 0x0B;   //RB3->EUSART:RX;
    
    RC4PPSbits.RC4PPS = 0x0011;   //RC4->MSSP:SDA;
    SSPDATPPSbits.SSPDATPPS = 0x0014;   //RC4->MSSP:SDA;
    SSPCLKPPSbits.SSPCLKPPS = 0x0015;   //RC5->MSSP:SCL;
    RC5PPSbits.RC5PPS = 0x0010;   //RC5->MSSP:SCL;
    
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x01; // lock PPS
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
    
    // Initialize the I2C Module
    I2C_Init();
    
    __delay_ms(100);
    
    unsigned char block_address = 0x55; // Replace with your EEPROM's address
    unsigned char word_address = 0;     // Replace with the word address to read/write
    unsigned char eeprom_data = 8;      // Replace with the data to be written
    
    int x = 0;
    
    while (1) {
        EEPROM_Write(block_address, word_address, eeprom_data);
        unsigned char read_data = EEPROM_Read(block_address, word_address);
        
        EUSART_Write_Text("Word Address: ");
        EUSART_Write_Integer(word_address);
        
        EUSART_Write_Text(", Written Data: ");
        EUSART_Write_Integer(eeprom_data);
        
        EUSART_Write_Text(", Read Data: ");
        EUSART_Write_Integer(read_data);
        EUSART_Write_Text("\n");

        eeprom_data+=2; // Increment the data for the next write
        word_address++; // Increment the word address

        // Delay between write-read cycles
        __delay_ms(5000);
    }
    return;   
}
