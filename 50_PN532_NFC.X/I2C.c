/*
 * File: I2C.c
 * Author: Armstrong Subero
 * PIC: 16F1718 w/Int OSC @ 32MHz, 5v
 * Program: Driver-grade I2C (MSSP) source
 * Compiler: XC8
 *
 * Program Version 2.0
 * Program Description:
 * Robust I2C master-mode driver built on MSSP.
 * Adds:
 *  - ACK checking
 *  - idle-state waits
 *  - error clearing
 *  - timeouts to avoid infinite hangs
 */

#include "I2C.h"

/*******************************************************************************
 * Local helper: Wait for SSP1IF with a timeout
 ******************************************************************************/
static I2C_Status_t I2C_WaitIF(uint16_t timeout_ms)
{
    while (timeout_ms--)
    {
        if (PIR1bits.SSP1IF)
            return I2C_OK;

        __delay_ms(1);
    }
    return I2C_TIMEOUT;
}

/*******************************************************************************
 * Function: void I2C_Init(void)
 *
 * Description:
 * Setup MSSP as I2C Master mode @ 100 kHz with Fosc=32 MHz.
 ******************************************************************************/
void I2C_Init(void)
{
    // I2C Master mode, clock = Fosc/(4 * (SSPADD+1))
    SSPCONbits.SSPM  = 0x08;

    // Enable MSSP port
    SSPCONbits.SSPEN = 1;

    // 100 kHz @ 32 MHz => SSPADD = 79
    SSPADD = 79;

    I2C_ClearErrors();
    __delay_ms(10);
}

/*******************************************************************************
 * Function: void I2C_ClearErrors(void)
 *
 * Description:
 * Clears overflow/collision conditions. Safe to call anytime.
 ******************************************************************************/
void I2C_ClearErrors(void)
{
    // Clear buffer overflow and write collision
    SSPCON1bits.SSPOV = 0;
    SSPCON1bits.WCOL  = 0;

    // Clear bus collision flag if used
    PIR2bits.BCL1IF = 0;

    // Clear interrupt flag
    PIR1bits.SSP1IF = 0;
}

/*******************************************************************************
 * Function: I2C_Status_t I2C_WaitIdle(uint16_t timeout_ms)
 *
 * Description:
 * Waits until MSSP is idle (no Start/Stop/Ack/Receive in progress).
 ******************************************************************************/
I2C_Status_t I2C_WaitIdle(uint16_t timeout_ms)
{
    while (timeout_ms--)
    {
        // SSPCON2 lower bits indicate I2C activity:
        // SEN, RSEN, PEN, RCEN, ACKEN
        if ((SSPCON2 & 0x1F) == 0 && SSPSTATbits.R_nW == 0)
            return I2C_OK;

        __delay_ms(1);
    }
    return I2C_TIMEOUT;
}

/*******************************************************************************
 * Function: I2C_Status_t I2C_Start(void)
 ******************************************************************************/
I2C_Status_t I2C_Start(void)
{
    I2C_Status_t st;

    st = I2C_WaitIdle(50);
    if (st != I2C_OK) return st;

    PIR1bits.SSP1IF = 0;
    SSPCON2bits.SEN = 1;

    st = I2C_WaitIF(50);
    if (st != I2C_OK) return st;

    PIR1bits.SSP1IF = 0;
    return I2C_OK;
}

/*******************************************************************************
 * Function: I2C_Status_t I2C_RepeatedStart(void)
 ******************************************************************************/
I2C_Status_t I2C_RepeatedStart(void)
{
    I2C_Status_t st;

    st = I2C_WaitIdle(50);
    if (st != I2C_OK) return st;

    PIR1bits.SSP1IF  = 0;
    SSPCON2bits.RSEN = 1;

    st = I2C_WaitIF(50);
    if (st != I2C_OK) return st;

    PIR1bits.SSP1IF = 0;
    return I2C_OK;
}

/*******************************************************************************
 * Function: I2C_Status_t I2C_Stop(void)
 ******************************************************************************/
I2C_Status_t I2C_Stop(void)
{
    I2C_Status_t st;

    st = I2C_WaitIdle(50);
    if (st != I2C_OK) return st;

    PIR1bits.SSP1IF = 0;
    SSPCON2bits.PEN = 1;

    st = I2C_WaitIF(50);
    if (st != I2C_OK) return st;

    PIR1bits.SSP1IF = 0;
    return I2C_OK;
}

/*******************************************************************************
 * Function: I2C_Status_t I2C_WriteByte(uint8_t data)
 *
 * Description:
 * Sends one byte and checks if slave ACK'd.
 ******************************************************************************/
I2C_Status_t I2C_WriteByte(uint8_t data)
{
    I2C_Status_t st;

    st = I2C_WaitIdle(50);
    if (st != I2C_OK) return st;

    PIR1bits.SSP1IF = 0;
    SSPBUF = data;

    st = I2C_WaitIF(50);
    if (st != I2C_OK) return st;

    // Check bus collision
    if (PIR2bits.BCL1IF)
    {
        PIR2bits.BCL1IF = 0;
        return I2C_BUS_COLLISION;
    }

    // ACKSTAT = 0 means ACK received; 1 means NAK received
    PIR1bits.SSP1IF = 0;
    return (SSPCON2bits.ACKSTAT == 0) ? I2C_OK : I2C_NAK;
}

/*******************************************************************************
 * Function: I2C_Status_t I2C_ReadByte(uint8_t *data, bool ack)
 *
 * Description:
 * Reads one byte and then sends ACK (ack=true) or NAK (ack=false).
 ******************************************************************************/
I2C_Status_t I2C_ReadByte(uint8_t *data, bool ack)
{
    I2C_Status_t st;

    if (data == NULL) return I2C_TIMEOUT;

    st = I2C_WaitIdle(50);
    if (st != I2C_OK) return st;

    // Enable receive
    PIR1bits.SSP1IF = 0;
    SSPCON2bits.RCEN = 1;

    st = I2C_WaitIF(50);
    if (st != I2C_OK) return st;

    *data = SSPBUF;

    // Send ACK/NAK
    PIR1bits.SSP1IF = 0;
    SSPCON2bits.ACKDT = (ack ? 0 : 1);
    SSPCON2bits.ACKEN = 1;

    st = I2C_WaitIF(50);
    if (st != I2C_OK) return st;

    PIR1bits.SSP1IF = 0;
    return I2C_OK;
}

void I2C_ResetModule(void)
{
    // Disable MSSP
    SSPCONbits.SSPEN = 0;

    // Clear errors/flags
    SSPCON1bits.SSPOV = 0;
    SSPCON1bits.WCOL  = 0;
    PIR1bits.SSP1IF   = 0;
    PIR2bits.BCL1IF   = 0;

    // Re-enable MSSP
    SSPCONbits.SSPEN = 1;
}

// GPIO-level bus recovery: 9 clocks + STOP
void I2C_RecoverBus(void)
{
    // Disable MSSP so we can bit-bang SCL
    SSPCONbits.SSPEN = 0;

    // Ensure pins are digital
    ANSELCbits.ANSC4 = 0;
    ANSELCbits.ANSC5 = 0;

    // SDA input (release), SCL output (we will toggle)
    TRISCbits.TRISC4 = 1;
    TRISCbits.TRISC5 = 0;

    // Drive SCL high first (release bus)
    LATCbits.LATC5 = 1;
    __delay_us(10);

    // If SDA is stuck low, clock SCL 9 times to make slave release
    for (uint8_t i = 0; i < 9; i++)
    {
        LATCbits.LATC5 = 0;
        __delay_us(10);
        LATCbits.LATC5 = 1;
        __delay_us(10);
    }

    // Generate a STOP condition manually:
    // SDA low -> SCL high -> SDA high
    // (We can only pull SDA low if we make it output briefly)
    TRISCbits.TRISC4 = 0;
    LATCbits.LATC4 = 0;
    __delay_us(10);

    LATCbits.LATC5 = 1;
    __delay_us(10);

    LATCbits.LATC4 = 1;
    __delay_us(10);

    // Release SDA, put SCL back to input (MSSP controls)
    TRISCbits.TRISC4 = 1;
    TRISCbits.TRISC5 = 1;

    // Re-enable MSSP and clear flags
    SSPCONbits.SSPEN = 1;
    I2C_ClearErrors();
}
