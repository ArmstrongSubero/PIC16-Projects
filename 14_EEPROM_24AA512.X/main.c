/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1718 w/int OSC @ 32MHz, 5v
 * Program: I2C EEPROM Demo (24AA512)
 * Compiler: XC8 (v2.46, MPLAB X v6.20)
 *
 * Program Description:
 * Demonstrates explicit WRITE and READ cycles to a 24AA512 EEPROM
 * using a driver-grade I2C bus layer.
 *
 * Hardware:
 *  - RC4 : SDA (4.7k pull-up)
 *  - RC5 : SCL (4.7k pull-up)
 *  - RB2 : UART TX ? USB-UART
 *  - 24AA512 A2/A1/A0 tied LOW, WP tied LOW
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "PIC16F1718_Internal.h"
#include "EUSART.h"
#include "I2C.h"
#include "EEPROM_24AA512.h"

// Scan the I2C Bus 
static void I2C_ScanBus(void)
{
    EUSART_Write_Text("\nI2C SCAN (0x08..0x77)\n");

    for (uint8_t addr7 = 0x08; addr7 <= 0x77; addr7++)
    {
        uint8_t ctrlW = (uint8_t)((addr7 << 1) | 0);

        I2C_Status_t st = I2C_Start();
        if (st != I2C_OK)
        {
            EUSART_Write_Text("Start failed\n");
            return;
        }

        st = I2C_WriteByte(ctrlW);
        I2C_Stop();

        if (st == I2C_OK)
        {
            EUSART_Write_Text("ACK @ 7-bit addr: ");
            EUSART_Write_Integer(addr7);
            EUSART_Write_Text("\n");
        }
    }
}


/*******************************************************************************
 * Function: void initMain(void)
 *
 * Description:
 * MCU clock, PPS, UART, and I2C pin initialization
 ******************************************************************************/
void initMain(void)
{
    // Internal oscillator @ 32 MHz
    internal_32();
    __delay_ms(10);     // PLL settle

    // UART TX pin
    TRISBbits.TRISB2 = 0;
    ANSELBbits.ANSB2 = 0;

    // I2C pins (open-drain handled by MSSP + pull-ups)
    ANSELCbits.ANSC4 = 0;
    ANSELCbits.ANSC5 = 0;
    TRISCbits.TRISC4 = 1;   // SDA
    TRISCbits.TRISC5 = 1;   // SCL

    // PPS mapping
    PPSLOCK = 0x55; PPSLOCK = 0xAA; PPSLOCKbits.PPSLOCKED = 0;

    RB2PPSbits.RB2PPS = 0x14;      // RB2 ? EUSART TX
    RXPPSbits.RXPPS   = 0x0B;      // RB3 ? EUSART RX

    RC4PPSbits.RC4PPS = 0x11;      // RC4 ? MSSP SDA out
    SSPDATPPSbits.SSPDATPPS = 0x14;// RC4 ? MSSP SDA in

    SSPCLKPPSbits.SSPCLKPPS = 0x15;// RC5 ? MSSP SCL in
    RC5PPSbits.RC5PPS = 0x10;      // RC5 ? MSSP SCL out

    PPSLOCK = 0x55; PPSLOCK = 0xAA; PPSLOCKbits.PPSLOCKED = 1;
}

/*******************************************************************************
 * Main
 ******************************************************************************/
void main(void)
{
    initMain();

    EUSART_Initialize(19200);
    I2C_Init();
    
    I2C_ScanBus();

    EUSART_Write_Text("\n====================================\n");
    EUSART_Write_Text("  24AA512 EEPROM I2C DEMO\n");
    EUSART_Write_Text("====================================\n");

    uint16_t address  = 0x0000;
    uint8_t  writeVal = 10;
    uint8_t  readVal  = 0;

    while (1)
    {
        I2C_Status_t st;

        /* ================= WRITE ================= */
        EUSART_Write_Text("\nWRITE CYCLE\n");
        EUSART_Write_Text("Addr: ");
        EUSART_Write_Integer(address);
        EUSART_Write_Text("  Data: ");
        EUSART_Write_Integer(writeVal);
        EUSART_Write_Text("\n");

        st = EEPROM24AA512_WriteByte(address, writeVal);

        EUSART_Write_Text("Write Status: ");
        EUSART_Write_Integer(st);
        EUSART_Write_Text(st == I2C_OK ? " (OK)\n" : " (FAIL)\n");

        /* ================= READ ================= */
        EUSART_Write_Text("\nREAD CYCLE\n");
        EUSART_Write_Text("Addr: ");
        EUSART_Write_Integer(address);
        EUSART_Write_Text("\n");

        st = EEPROM24AA512_ReadByte(address, &readVal);

        EUSART_Write_Text("Read Status: ");
        EUSART_Write_Integer(st);
        EUSART_Write_Text(st == I2C_OK ? " (OK)\n" : " (FAIL)\n");

        if (st == I2C_OK)
        {
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

        // Next test
        writeVal += 3;
        address++;

        __delay_ms(3000);
    }
}
