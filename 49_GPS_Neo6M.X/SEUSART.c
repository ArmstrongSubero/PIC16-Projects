/*
 * File: SEUSART.c   (software UART library)
 * Author: Armstrong Subero
 * PIC: 16F1718 w/Int OSC @ 16MHz, 5v
 * Compiler: XC8 (v2.45, MPLAX X v6.20)
 *
 * Robustness upgrades (no delay calibration changes):
 *  - Start-bit validation (reject glitches)
 *  - Stop-bit framing check
 *  - Optional timeout so RX won?t hang forever
 *  - Interrupt protection during bit timing (optional but recommended)
 *  - Read_Text null-termination and safe length handling
 * 
 * Updated on January, 29th 2026, 6:17 PM 
 */

#include "SEUSART.h"

/* ------------------ Robustness controls ------------------ */

// Enable/disable interrupt locking around TX/RX bit timing.
// Recommended if you have interrupts enabled elsewhere.
#ifndef SUART_USE_GIE_LOCK
#define SUART_USE_GIE_LOCK 1
#endif

// RX timeout in microseconds for waiting on start bit.
// Set to 0 to wait forever (original behavior).
#ifndef SUART_RX_TIMEOUT_US
#define SUART_RX_TIMEOUT_US 20000UL   // 20 ms default
#endif

// Lock and unlock to diable interrupts while bit-banging
static inline unsigned char SUART_Lock(void)
{
#if SUART_USE_GIE_LOCK
    unsigned char gie = INTCONbits.GIE;
    INTCONbits.GIE = 0;
    return gie;
#else
    return 0;
#endif
}

static inline void SUART_Unlock(unsigned char gie)
{
#if SUART_USE_GIE_LOCK
    INTCONbits.GIE = gie;
#else
    (void)gie;
#endif
}

// Wait for start bit (RX goes low). Returns 1 if detected, 0 if timeout.
static unsigned char SUART_WaitStartBit(void)
{
#if (SUART_RX_TIMEOUT_US == 0)
    while (UART_RX == 1) { ; }
    return 1;
#else
    unsigned long t = SUART_RX_TIMEOUT_US;
    while (UART_RX == 1)
    {
        if (t-- == 0) return 0;
        __delay_us(1);
    }
    return 1;
#endif
}

/* --------------------------- Public API --------------------------- */


/*******************************************************************************
 * Function: SUART_Init(void)
 *
 * Returns: Nothing
 *
 * Description: Initializes UART pins
 * 
 ******************************************************************************/
void SUART_Init(void)
{
    // Ensure idle state is high before enabling output
    UART_TX = 1;

    UART_RX_DIR = 1; // Input
    UART_TX_DIR = 0; // Output
}

/*******************************************************************************
 * Function: unsigned char SUART_Receive(void)
 *
 * Returns: Nothing
 *
 * Description: recieves via soft UART
 * 
 ******************************************************************************/
unsigned char SUART_Receive(void)
{
    unsigned char DataValue = 0;

    // Wait for start bit (idle high -> start low)
    if (!SUART_WaitStartBit())
    {
        // Timeout: return 0 (you can change to 0xFF or similar if preferred)
        return 0x00;
    }

    // From the falling edge, move to the middle of the start bit and validate it.
    __delay_us(OneBitDelay / 2);

    // Start-bit validation (reject noise/glitches)
    if (UART_RX == 1)
    {
        // False start
        __delay_us(OneBitDelay / 2);
        return 0x00;
    }

    // Move to the middle of bit0 (one full bit after mid-start)
    __delay_us(OneBitDelay);

    // Sample 8 data bits, LSB first
    {
        unsigned char gie = SUART_Lock();
        for (unsigned char i = 0; i < DataBitCount; i++)
        {
            if (UART_RX == 1)
            {
                DataValue |= (1u << i);
            }
            __delay_us(OneBitDelay);
        }
        SUART_Unlock(gie);
    }

    // Stop bit should be high (framing check)
    if (UART_RX == 0)
    {
        // Framing error
        __delay_us(OneBitDelay / 2);
        return 0x00;
    }

    // Optional: small settle to center stop bit
    __delay_us(OneBitDelay / 2);
    return DataValue;
}

/*******************************************************************************
 * Function: void SUART_Transmit(const char DataValue)
 *
 * Returns: Nothing
 *
 * Description: transmits via soft UART
 * 
 ******************************************************************************/
void SUART_Transmit(const char DataValue)
{
    unsigned char gie = SUART_Lock();

    // Start bit (low)
    UART_TX = 0;
    __delay_us(OneBitDelay);

    // Data bits (LSB first)
    for (unsigned char i = 0; i < DataBitCount; i++)
    {
        UART_TX = ((DataValue >> i) & 0x1) ? 1 : 0;
        __delay_us(OneBitDelay);
    }

    // Stop bit (high)
    UART_TX = 1;
    __delay_us(OneBitDelay);

    SUART_Unlock(gie);
}

/*******************************************************************************
 * Function: void SUART_Write_Text(char *text)
 *
 * Returns: Nothing
 *
 * Description: writes text via soft UART
 * 
 ******************************************************************************/
void SUART_Write_Text(char *text)
{
    int i;
    for (i = 0; text[i] != '\0'; i++)
    {
        SUART_Transmit(text[i]);
    }
}

/*******************************************************************************
 * Function: void SUART_Read_Text(char *Output, unsigned int length)
 *
 * Returns: Nothing
 *
 * Description: reads text via soft UART
 * 
 ******************************************************************************/
void SUART_Read_Text(char *Output, unsigned int length)
{
    // Make it safe: if caller says length N, reserve last byte for '\0'
    if (length == 0) return;

    for (unsigned int i = 0; i < (length - 1); i++)
    {
        Output[i] = (char)SUART_Receive();
    }

    Output[length - 1] = '\0';
}

/*******************************************************************************
 * Function: void SUART_Write_Char(char a)
 *
 * Returns: Nothing
 *
 * Description: writes a character to SOFT UART
 * 
 ******************************************************************************/
void SUART_Write_Char(char a)
{
    SUART_Transmit(a);
}
