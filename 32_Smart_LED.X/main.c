/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1719 w/int OSC @ 32MHz, 5v
 * Program: 32_Smart_LED
 * Compiler: XC8 (v2.46, MPLAX X v6.20)
 * Program Version: 1.2
 *                
 * Program Description: This program uses a button and LED to create a "smart" 
 *                      LED with 5 functions, it can:
 *                      1. Fade Arduino Style
 *                      2. Breathe with Ease In/Ease Out ability 
 *                      3. Heartbeat Effect (thump, thump, pause) 
 *                      4. Candle Flicker (flicker like a candle) 
 *                      5. Strobe Effect
 * 
 * Hardware Description: An LED is connected to PIN C4 and an LED to PIN RB0
 *                       
 * Created December 26th 2025, 4:12 AM
 */

/*******************************************************************************
 *Includes and defines
 ******************************************************************************/
#include "PIC16F1718_Internal.h"

#define LED_Set(duty)      (CCPR1L = (uint8_t)(duty))

#define BTN_TRIS           TRISAbits.TRISA4
#define BTN_ANS            ANSELAbits.ANSA4
#define BTN_WPU            WPUAbits.WPUA4
#define BTN_PORT           PORTAbits.RA4   // reads 1 (released), 0 (pressed)

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
    
    ////////////////////
    // Configure Ports
    ///////////////////
    
    // Set PIN B0 as output
    TRISBbits.TRISB0 = 0;
    
    // Set PIN B1 as output
    TRISBbits.TRISB1 = 0;
    
    // Turn off analog
    ANSELB = 0;
    
    /////////////////////
    // Configure Timer6
    /////////////////////
    
    // Select PWM timer as Timer6 for CCP1 and CCP2
    CCPTMRSbits.C1TSEL = 0b10;
    CCPTMRSbits.C2TSEL = 0b10;
    
    // Enable timer Increments every 125 ns (32 MHz clock) 1000/(32/4)
    // Period = 256 x 0.125 us = 31.25 us
    
    //                          Crystal Frequency 
    //    PWM Freq  = ----------------------------------------- 
    //                  (PRX + 1) * (TimerX Prescaler) * 4
    
    //    PWM Frequency = 32 000 000 / 256 * 1 * 4
    //    PWM Frequency = 31.250 kHz
    
    // Prescale = 1
    T6CONbits.T6CKPS = 0b00;
    
    // Enable Timer6
    T6CONbits.TMR6ON = 1;
    
    // Set timer period
    PR6 = 255;
    
    
    //////////////////////////
    // Configure PWM
    /////////////////////////
    
    // Configure CCP1
     
    // LSB's of PWM duty cycle = 00
    CCP1CONbits.DC1B = 00;
    
    // Select PWM mode
    CCP1CONbits.CCP1M = 0b1100;
    
    // Configure CCP2
    
    // LSB's of PWM duty cycle = 00
    CCP2CONbits.DC2B = 00;
    
    // Select PWM mode
    CCP2CONbits.CCP2M = 0b1100;
    
    
    //////////////////////////////
    // Configure PPS
    /////////////////////////////
    
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00; // unlock PPS
    
    // Set RB0 to PWM1
    RB0PPSbits.RB0PPS = 0b01100;
    
    // Set RB1 to PWM2
    RB1PPSbits.RB1PPS = 0b01101;
    
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x01; // lock PPS
}


// Button Pressed Event Function
static uint8_t ButtonPressedEvent(void)
{
    // Returns 1 exactly once per press (debounced)
    static uint8_t stable = 1;      // assume released (pull-up)
    static uint8_t lastStable = 1;
    static uint8_t count = 0;

    uint8_t sample = BTN_PORT;      // 1=released, 0=pressed

    if (sample == stable) {
        count = 0;
    } else {
        if (++count >= 5) {         // 5 * 10ms = 50ms debounce
            stable = sample;
            count = 0;
        }
    }

    // detect falling edge (released -> pressed)
    uint8_t event = (lastStable == 1 && stable == 0) ? 1 : 0;
    lastStable = stable;

    return event;
}

/*****************************************************************
 * Effect 1: Arduino-style fade
 *****************************************************************/
static void Step_Fade(uint8_t reset)
{
    static uint8_t brightness;
    static int8_t fadeAmount;

    if (reset) { brightness = 0; fadeAmount = 5; }

    LED_Set(brightness);
    brightness = (uint8_t)(brightness + fadeAmount);

    if (brightness == 0 || brightness == 255)
        fadeAmount = -fadeAmount;
}

/*****************************************************************
 * Effect 2: Breathing (smoother ?ease in/out? feel)
 *****************************************************************/
static void Step_Breathe(uint8_t reset)
{
    static uint16_t x;
    static int8_t dir;

    if (reset) { x = 0; dir = 1; }

    uint16_t duty = (x * x) / 255;     // 0..255
    LED_Set((uint8_t)duty);

    x = (uint16_t)(x + dir);
    if (x == 255) dir = -1;
    if (x == 0)   dir =  1;
}

/*****************************************************************
 * Effect 3: Heartbeat (thump-thump ... pause)
 *****************************************************************/
static void Step_Heartbeat(uint8_t reset)
{
    static uint8_t state;
    static int16_t duty;

    if (reset) { state = 0; duty = 0; }

    switch (state)
    {
        case 0: duty += 18; if (duty >= 220) { duty = 220; state = 1; } break; // rise 1
        case 1: duty -= 28; if (duty <= 60)  { duty = 60;  state = 2; } break; // fall 1
        case 2:                         { duty = 40; state = 3; }        break; // gap
        case 3: duty += 20; if (duty >= 180) { duty = 180; state = 4; } break; // rise 2
        case 4: duty -= 16; if (duty <= 0)   { duty = 0;   state = 5; } break; // fade out
        case 5:                         { duty = 0;  state = 6; }        break; // pause part A
        case 6:                         { /* hold */ state = 7; }        break; // pause part B
        case 7:                         { /* hold */ state = 0; }        break; // pause part C
    }

    if (duty < 0) duty = 0;
    if (duty > 255) duty = 255;
    LED_Set((uint8_t)duty);
}

/*****************************************************************
 * Effect 4: Candle flicker (random-looking shimmer)
 *****************************************************************/
static void Step_Candle(uint8_t reset)
{
    static uint16_t lfsr;

    if (reset) lfsr = 0xACE1;

    uint16_t bit = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5)) & 1;
    lfsr = (lfsr >> 1) | (bit << 15);

    uint8_t base = 90;
    uint8_t flick = (uint8_t)(lfsr & 0x3F);   // 0..63
    LED_Set((uint8_t)(base + flick));
}

/*****************************************************************
 * Effect 5: Strobe (attention / warning blink)
 *****************************************************************/
static void Step_Strobe(uint8_t reset)
{
    static uint8_t phase = 0;   // 0 = ON phase, 1 = OFF phase
    static uint8_t ticks = 0;

    if (reset) { phase = 0; ticks = 0; }

    if (phase == 0)
    {
        // ON for 40 ms (4 ticks at 10 ms)
        LED_Set(255);
        if (++ticks >= 4) { ticks = 0; phase = 1; }
    }
    else
    {
        // OFF for 120 ms (12 ticks at 10 ms)
        LED_Set(0);
        if (++ticks >= 12) { ticks = 0; phase = 0; }
    }
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

    // Button pin setup: RA4 input, digital, weak pull-up enabled
    BTN_ANS  = 0;
    BTN_TRIS = 1;
    BTN_WPU  = 1;
    OPTION_REGbits.nWPUEN = 0;   // enable global weak pull-ups on many PIC16F1

    uint8_t effect = 0;
    uint8_t resetEffect = 1;

    while (1)
    {
        // Button press -> next effect
        if (ButtonPressedEvent())
        {
            effect = (uint8_t)((effect + 1) % 5);
            resetEffect = 1;
        }

        // Run one "step" of the active effect
        switch (effect)
        {
            case 0: Step_Fade(resetEffect);      break;
            case 1: Step_Breathe(resetEffect);   break;
            case 2: Step_Heartbeat(resetEffect); break;
            case 3: Step_Candle(resetEffect);    break;
            case 4: Step_Strobe(resetEffect);    break;
        }

        resetEffect = 0;

        __delay_ms(10);   // animation tick + debounce tick
    }
}
