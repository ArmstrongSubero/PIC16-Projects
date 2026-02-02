/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1719 w/int OSC @ 32MHz, 5v
 * Program: 13_I2C
 * Compiler: XC8 (v2.46, MPLAX X v6.20)
 * Program Version: 1.3
 *                  * Focused on PIC16F1718
 *                  * Updated from PIC16F1717 to PIC16F1719
 *                  * Updated clock speed to 32 MHz 
 *                  * Added PLL stabilization
 * 
 * Program Description: This program allows the PIC16F1718 to demonstrate use 
 *                      of the I2C bus 
 * 
 * Hardware Description: PIN RB2 of a the PIC16F1719 MCU is connected to 
 *                       a PL2303XX USB to UART converter cable and a 
 *                       24LC16B EEPROM is connected to the I2C bus 
 *                       -- RC4 SDA 
 *                       -- RC5 SCL
 *                       4.7k pull up resistors are used on the I2C lines
 *                       
 * Created November 7th, 2016, 7:05 PM
 * Updated on Thursday 25th, December, 2025, 4:18 PM
 */


/*******************************************************************************
 *Includes and defines
 ******************************************************************************/

#include "PIC16F1718_Internal.h"
#include "EUSART.h"
#include "I2C.h"

static uint8_t EEPROM_ControlByte(uint16_t memAddr, bool read)
{
    uint8_t block = (memAddr >> 8) & 0x07;        // A10..A8
    uint8_t ctrl  = (0b1010 << 4) | (block << 1); // 1010 BBB 0
    return ctrl | (read ? 1 : 0);
}

/*******************************************************************************
 * Function: I2C_Status_t EEPROM_AckPoll(uint16_t memAddr)
 *
 * Description:
 * After a write, EEPROM will NAK until internal write cycle completes.
 ******************************************************************************/
I2C_Status_t EEPROM_AckPoll(uint16_t memAddr)
{
    for (uint16_t t = 0; t < 200; t++)
    {
        I2C_Status_t st = I2C_Start();
        if (st != I2C_OK) return st;

        st = I2C_WriteByte(EEPROM_ControlByte(memAddr, false));
        I2C_Stop();

        if (st == I2C_OK)
            return I2C_OK;

        __delay_ms(1);
    }
    return I2C_TIMEOUT;
}

I2C_Status_t EEPROM_WriteByte(uint16_t memAddr, uint8_t data)
{
    I2C_Status_t st;

    st = I2C_Start();
    if (st != I2C_OK) return st;

    st = I2C_WriteByte(EEPROM_ControlByte(memAddr, false));
    if (st != I2C_OK) { I2C_Stop(); return st; }

    st = I2C_WriteByte((uint8_t)(memAddr & 0xFF));
    if (st != I2C_OK) { I2C_Stop(); return st; }

    st = I2C_WriteByte(data);
    I2C_Stop();
    if (st != I2C_OK) return st;

    return EEPROM_AckPoll(memAddr);
}

I2C_Status_t EEPROM_ReadByte(uint16_t memAddr, uint8_t *data)
{
    I2C_Status_t st;

    st = I2C_Start();
    if (st != I2C_OK) return st;

    st = I2C_WriteByte(EEPROM_ControlByte(memAddr, false));
    if (st != I2C_OK) { I2C_Stop(); return st; }

    st = I2C_WriteByte((uint8_t)(memAddr & 0xFF));
    if (st != I2C_OK) { I2C_Stop(); return st; }

    st = I2C_RepeatedStart();
    if (st != I2C_OK) { I2C_Stop(); return st; }

    st = I2C_WriteByte(EEPROM_ControlByte(memAddr, true));
    if (st != I2C_OK) { I2C_Stop(); return st; }

    st = I2C_ReadByte(data, false); // read 1 byte, then NAK
    I2C_Stop();

    return st;
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

void main(void)
{
    initMain();

    EUSART_Initialize(19200);
    I2C_Init();

    EUSART_Write_Text("\n=== I2C EEPROM READ/WRITE DEMO ===\n");

    uint16_t address = 0;
    uint8_t  writeVal = 10;
    uint8_t  readVal  = 0;

    while (1)
    {
        I2C_Status_t status;

        /* ================= WRITE ================= */
        EUSART_Write_Text("\nWRITE CYCLE\n");
        EUSART_Write_Text("Address: ");
        EUSART_Write_Integer(address);
        EUSART_Write_Text("  Data: ");
        EUSART_Write_Integer(writeVal);
        EUSART_Write_Text("\n");

        status = EEPROM_WriteByte(address, writeVal);

        if (status != I2C_OK)
        {
            EUSART_Write_Text("WRITE FAILED, STATUS = ");
            EUSART_Write_Integer(status);
            EUSART_Write_Text("\n");
        }
        else
        {
            EUSART_Write_Text("WRITE OK\n");
        }

        /* ================= READ ================= */
        EUSART_Write_Text("\nREAD CYCLE\n");
        EUSART_Write_Text("Address: ");
        EUSART_Write_Integer(address);
        EUSART_Write_Text("\n");

        status = EEPROM_ReadByte(address, &readVal);

        if (status != I2C_OK)
        {
            EUSART_Write_Text("READ FAILED, STATUS = ");
            EUSART_Write_Integer(status);
            EUSART_Write_Text("\n");
        }
        else
        {
            EUSART_Write_Text("READ OK\n");
            EUSART_Write_Text("Read Data: ");
            EUSART_Write_Integer(readVal);
            EUSART_Write_Text("\n");
        }

        /* ================= RESULT ================= */
        EUSART_Write_Text("\nRESULT\n");
        EUSART_Write_Text("Written: ");
        EUSART_Write_Integer(writeVal);
        EUSART_Write_Text("  Read: ");
        EUSART_Write_Integer(readVal);
        EUSART_Write_Text("\n");

        /* Prepare next cycle */
        writeVal += 3;
        address++;

        __delay_ms(3000);
    }
}