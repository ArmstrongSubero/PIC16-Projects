/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1718 w/int OSC @ 32MHz, 5v
 * Program: 33_HCSR04_Distance
 * Compiler: XC8 (v2.46, MPLAX X v6.20)
 * Program Version: 1.2
 *                
 * Program Description: This program allows us to sense distance using the 
 *                      HCSR04 ultrasonic sensor. 
 * 
 * Hardware Description: An HCSR04 ultrasonic sensor is connected to the MCU 
 *                       as follows: 
 *    
 *                       VCC  -> VCC 
 *                       GND  -> GND 
 *                       TRIG -> RC3 
 *                       ECHO -> RB0 
 *                       
 * Created December 26th 2025, 4:47 AM
 */

/*******************************************************************************
 *Includes and defines
 ******************************************************************************/
#include "PIC16F1718_Internal.h"
#include "I2C.h"
#include "OLED_SSD1306.h"

#define TRIG_TRIS   TRISCbits.TRISC3
#define TRIG_LAT    LATCbits.LATC3

#define ECHO_TRIS   TRISBbits.TRISB0
#define ECHO_PORT   PORTBbits.RB0

static void Trigger_Pulse_10us(void)
{
    TRIG_LAT = 1;
    __delay_us(10);
    TRIG_LAT = 0;
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
static void initMain(void)
{
    internal_32();
    __delay_ms(100);

    // Digital I/O
    ANSELA = 0;
    ANSELB = 0;
    ANSELC = 0;

    // TRIG pin
    TRIG_TRIS = 0;
    TRIG_LAT  = 0;

    // ECHO pin
    ECHO_TRIS = 1;

    // I2C pins for OLED
    ANSELCbits.ANSC4 = 0;
    ANSELCbits.ANSC5 = 0;
    TRISCbits.TRISC4 = 1;
    TRISCbits.TRISC5 = 1;

    // PPS mapping (same as your OLED example)
    PPSLOCK = 0x55; PPSLOCK = 0xAA; PPSLOCKbits.PPSLOCKED = 0;

    RB2PPSbits.RB2PPS = 0x14;
    RXPPSbits.RXPPS   = 0x0B;

    RC4PPSbits.RC4PPS = 0x11;
    SSPDATPPSbits.SSPDATPPS = 0x14;

    SSPCLKPPSbits.SSPCLKPPS = 0x15;
    RC5PPSbits.RC5PPS = 0x10;

    PPSLOCK = 0x55; PPSLOCK = 0xAA; PPSLOCKbits.PPSLOCKED = 1;

    // Timer1: Fosc/4, prescaler 1:1, off until used
    T1CONbits.TMR1CS = 0;      // Fosc/4
    T1CONbits.T1CKPS = 0b00;   // 1:1
    T1CONbits.TMR1ON = 0;
    TMR1 = 0;
    PIR1bits.TMR1IF = 0;
}

// Returns 1 on success, 0 on timeout/out-of-range
static uint8_t HCSR04_Read_cm(uint16_t *cm_out)
{
    Trigger_Pulse_10us();

    // Wait for rising edge with timeout (~30ms)
    uint16_t timeout = 30000;
    while (ECHO_PORT == 0 && timeout--) __delay_us(1);
    if (timeout == 0) return 0;

    // Time high pulse
    TMR1 = 0;
    PIR1bits.TMR1IF = 0;
    T1CONbits.TMR1ON = 1;

    while (ECHO_PORT == 1 && !PIR1bits.TMR1IF) { /* spin */ }

    T1CONbits.TMR1ON = 0;

    if (PIR1bits.TMR1IF) return 0;

    uint16_t counts = TMR1;

    // At 32MHz: Timer1 tick = 0.125us => distance_cm = counts / 464
    *cm_out = (uint16_t)((counts + 232) / 464); // rounded

    return 1;
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

    I2C_Init();
    OLED_Init();
    OLED_SetOrientation(OLED_ORIENT_0);
    OLED_Clear();

    OLED_Printf_Line(0, "PIC16F1718 HC-SR04");

    uint16_t dist_cm;

    while (1)
    {
        if (HCSR04_Read_cm(&dist_cm))
            OLED_Printf_Line(1, "Dist: %u cm", dist_cm);
        else
            OLED_Printf_Line(1, "Dist: --");

        __delay_ms(80);
    }
}
