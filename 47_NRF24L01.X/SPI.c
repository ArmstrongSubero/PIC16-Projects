/*******************************************************************************
 * File: SPI.c
 * Author: Armstrong Subero
 * PIC: 16F1718 w/X OSC @ 32MHz, 5V
 * Program: SPI (MSSP) Driver Source File
 * Compiler: XC8 (v2.46, MPLAB X v6.20)
 *
 * Program Version 1.2
 * Updated: Comments refactored to match documentation style
 *
 * Program Description:
 * This module provides simple blocking SPI routines using the MSSP peripheral.
 * It supports:
 *  - SPI initialization (master mode)
 *  - Single-byte exchange
 *  - Buffer exchange (byte-wise)
 *  - Write collision status helpers
 *
 * NOTE:
 * This file intentionally preserves the original function bodies and behavior.
 ******************************************************************************/

/*******************************************************************************
 * Includes and defines
 ******************************************************************************/
#include <xc.h>
#include "SPI.h"

/*******************************************************************************
 * Macro Declarations
 ******************************************************************************/
#define SPI_RX_IN_PROGRESS 0x0
#define DUMMY_DATA         0x0

/*******************************************************************************
 * Function: void SPI_Initialize(void)
 *
 * Returns: Nothing
 *
 * Description:
 * Initializes the MSSP peripheral for SPI operation using the configuration
 * selected in the original implementation (master mode).
 *
 * Usage:
 * SPI_Initialize();
 *
 * Notes:
 * - This routine should be called once at startup before any SPI transfers.
 * - The SPI pins (PPS mapping, TRIS, ANSEL) must be configured elsewhere
 *   before transfers begin.
 ******************************************************************************/
void SPI_Initialize(void)
{
    // Set the SPI module to the options selected in the User Interface

    // BF RCinprocess_TXcomplete; UA dontupdate; SMP Sample At Middle;
    // P stopbit_notdetected; S startbit_notdetected; R_nW write_noTX;
    // CKE Active to Idle; D_nA lastbyte_address;
    SSP1STAT = 0x40;

    // SSPEN enabled; WCOL no_collision; SSPOV no_overflow;
    // CKP Idle:Low, Active:High; SSPM FOSC/64;
    SSP1CON1 = 0x22;

    // SSP1ADD 0;
    SSP1ADD = 0x00;
}

/*******************************************************************************
 * Function: uint8_t SPI_Exchange8bit(uint8_t data)
 *
 * Returns:
 * Byte received on the SPI bus
 *
 * Description:
 * Exchanges (writes and reads) a single byte over SPI.
 * This is a blocking function that waits until the receive buffer is full.
 *
 * Usage:
 * uint8_t rx = SPI_Exchange8bit(tx);
 *
 * Notes:
 * - Clears any write collision status before writing.
 * - Reading SSPBUF returns the received byte and clears BF.
 ******************************************************************************/
uint8_t SPI_Exchange8bit(uint8_t data)
{
    volatile uint8_t dummy;

    // If BF is still set from a previous operation, clear it
    if (SSP1STATbits.BF)
        dummy = SSPBUF;

    SSP1CON1bits.WCOL = 0;     // Clear collision
    SSPBUF = data;             // Start transfer

    while (!SSP1STATbits.BF)   // Wait complete
        ;

    return SSPBUF;             // Read received byte (clears BF)
}


/*******************************************************************************
 * Function: uint8_t SPI_Exchange8bitBuffer(uint8_t *dataIn, uint8_t bufLen, uint8_t *dataOut)
 *
 * Returns:
 * Number of bytes exchanged over SPI
 *
 * Description:
 * Exchanges a buffer of bytes over SPI.
 *
 * Usage:
 * SPI_Exchange8bitBuffer(txBuf, len, rxBuf);
 *
 * Parameters:
 * dataIn  - Pointer to transmit buffer (can be NULL to transmit DUMMY_DATA)
 * bufLen  - Number of bytes to exchange
 * dataOut - Pointer to receive buffer (can be NULL to discard received bytes)
 *
 * Notes:
 * - If dataIn is NULL and dataOut is not NULL, the function performs reads
 *   by transmitting DUMMY_DATA for each byte.
 * - If dataOut is NULL, received bytes are discarded.
 ******************************************************************************/
uint8_t SPI_Exchange8bitBuffer(uint8_t *dataIn, uint8_t bufLen, uint8_t *dataOut)
{
    uint8_t bytesWritten = 0;

    if (bufLen != 0)
    {
        if (dataIn != NULL)
        {
            while (bytesWritten < bufLen)
            {
                if (dataOut == NULL)
                {
                    SPI_Exchange8bit(dataIn[bytesWritten]);
                }
                else
                {
                    dataOut[bytesWritten] = SPI_Exchange8bit(dataIn[bytesWritten]);
                }

                bytesWritten++;
            }
        }
        else
        {
            if (dataOut != NULL)
            {
                while (bytesWritten < bufLen)
                {
                    dataOut[bytesWritten] = SPI_Exchange8bit(DUMMY_DATA);
                    bytesWritten++;
                }
            }
        }
    }

    return bytesWritten;
}

/*******************************************************************************
 * Function: bool SPI_IsBufferFull(void)
 *
 * Returns:
 * True if the SPI receive buffer is full (BF = 1), otherwise False.
 *
 * Description:
 * Checks the MSSP Buffer Full (BF) status bit.
 *
 * Usage:
 * if (SPI_IsBufferFull()) { ... }
 ******************************************************************************/
bool SPI_IsBufferFull(void)
{
    return (SSP1STATbits.BF);
}

/*******************************************************************************
 * Function: bool SPI_HasWriteCollisionOccured(void)
 *
 * Returns:
 * True if a write collision occurred (WCOL = 1), otherwise False.
 *
 * Description:
 * Checks the MSSP Write Collision status bit.
 *
 * Usage:
 * if (SPI_HasWriteCollisionOccured()) { SPI_ClearWriteCollisionStatus(); }
 ******************************************************************************/
bool SPI_HasWriteCollisionOccured(void)
{
    return (SSP1CON1bits.WCOL);
}

/*******************************************************************************
 * Function: void SPI_ClearWriteCollisionStatus(void)
 *
 * Returns: Nothing
 *
 * Description:
 * Clears the MSSP Write Collision status bit.
 *
 * Usage:
 * SPI_ClearWriteCollisionStatus();
 ******************************************************************************/
void SPI_ClearWriteCollisionStatus(void)
{
    SSP1CON1bits.WCOL = 0;
}

/*******************************************************************************
 * End of File
 ******************************************************************************/