/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1718 w/Int OSC @ 32MHz, 5v
 * Program: Countdown_Timer_4Digit_Timer2_HoldAccel
 * Compiler: XC8 (v2.46, MPLAB X v6.20)
 *
 * Display:
 *   Segments on PORTC (LATC)
 *   Digit enables on PORTB:
 *     RB0 = DIG0 (ones)
 *     RB1 = DIG1 (tens)
 *     RB2 = DIG2 (hundreds)
 *     RB3 = DIG3 (thousands)
 *
 * Buttons (PORTA, active-low with pull-ups):
 *   RA0 = START/STOP toggle
 *   RA1 = INC (tap + hold-to-speedup)
 *   RA2 = DEC (tap + hold-to-speedup)
 */

#include "PIC16F1718_Internal.h"

/*******************************************************************************
 * Digit enable macros (PORTB)
 ******************************************************************************/
#define DIG0 LATBbits.LATB0
#define DIG1 LATBbits.LATB1
#define DIG2 LATBbits.LATB2
#define DIG3 LATBbits.LATB3

/*******************************************************************************
 * Button inputs (PORTA) - active-low
 ******************************************************************************/
#define BTN_START PORTAbits.RA0
#define BTN_INC   PORTAbits.RA1
#define BTN_DEC   PORTAbits.RA2

/*******************************************************************************
 * Globals used by ISR
 ******************************************************************************/
volatile uint16_t displayValue = 0;
volatile uint8_t  digits[4]     = {0,0,0,0};
volatile uint8_t  currentDigit  = 0;

/*******************************************************************************
 * 7-seg decode (0..9)
 ******************************************************************************/
uint8_t seg(uint8_t num)
{
    switch(num)
    {
        case 0: return 0x3F;
        case 1: return 0x06;
        case 2: return 0x5B;
        case 3: return 0x4F;
        case 4: return 0x66;
        case 5: return 0x6D;
        case 6: return 0x7D;
        case 7: return 0x07;
        case 8: return 0x7F;
        case 9: return 0x6F;
        default: return 0x00;
    }
}

void updateDigits(uint16_t value)
{
    digits[0] = (uint8_t)(value % 10);
    digits[1] = (uint8_t)((value / 10) % 10);
    digits[2] = (uint8_t)((value / 100) % 10);
    digits[3] = (uint8_t)((value / 1000) % 10);
}

/*******************************************************************************
 * Hold-to-speedup state for a button
 ******************************************************************************/
typedef struct
{
    uint8_t  prev;         // previous raw pin state
    uint16_t hold_ms;      // how long held (ms)
    uint16_t repeat_ms;    // accumulator for repeat timing (ms)
    uint8_t  fired_hold;   // whether we've started repeating
} hold_btn_t;

static uint8_t pressed_edge_active_low(uint8_t now, uint8_t *prev)
{
    // detect released->pressed transition (1 -> 0)
    uint8_t hit = ((*prev == 1) && (now == 0)) ? 1 : 0;
    *prev = now;
    return hit;
}

// Compute repeat interval based on hold duration (acceleration curve)
static uint16_t accel_interval_ms(uint16_t hold_ms)
{
    // After repeating starts, speed up as you keep holding
    // Tune these as you like:
    if(hold_ms < 800)   return 200;  // slow
    if(hold_ms < 1600)  return 120;  // faster
    if(hold_ms < 3000)  return 70;   // fast
    return 40;                      // very fast
}

// Handle a hold button each tick. Returns 1 when an "action" should occur.
static uint8_t hold_button_action(uint8_t pin_now, hold_btn_t *b, uint16_t tick_ms)
{
    // Tap detection (edge)
    if(pressed_edge_active_low(pin_now, &b->prev))
    {
        b->hold_ms = 0;
        b->repeat_ms = 0;
        b->fired_hold = 0;
        return 1; // single tap action
    }

    // If held down (active-low)
    if(pin_now == 0)
    {
        b->hold_ms += tick_ms;

        // start repeating after initial delay
        if(b->hold_ms >= 450)
        {
            b->repeat_ms += tick_ms;

            // Once repeating starts, use an accelerating interval
            uint16_t interval = accel_interval_ms(b->hold_ms);

            if(b->repeat_ms >= interval)
            {
                b->repeat_ms = 0;
                b->fired_hold = 1;
                return 1; // repeat action
            }
        }
    }
    else
    {
        // released
        b->hold_ms = 0;
        b->repeat_ms = 0;
        b->fired_hold = 0;
    }

    return 0;
}

/*******************************************************************************
 * init
 ******************************************************************************/
void initMain(void)
{
    internal_32();
    __delay_ms(100);

    // Ensure digital I/O
    ANSELA = 0x00;
    ANSELB = 0x00;
    ANSELC = 0x00;

    // Segments on PORTC
    TRISC = 0x00;
    LATC  = 0x00;

    // Digit enables on RB0..RB3
    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB1 = 0;
    TRISBbits.TRISB2 = 0;
    TRISBbits.TRISB3 = 0;

    DIG0 = 0; DIG1 = 0; DIG2 = 0; DIG3 = 0;

    // Buttons on RA0..RA2
    TRISAbits.TRISA0 = 1;
    TRISAbits.TRISA1 = 1;
    TRISAbits.TRISA2 = 1;

    /////////////////////
    // Timer2 for display scan (~8kHz ISR)
    /////////////////////
    T2CONbits.T2CKPS  = 0b10;   // prescaler 16
    T2CONbits.T2OUTPS = 0b0000; // postscaler 1
    PR2 = 62;                   // ~7.9 kHz
    TMR2 = 0;

    PIR1bits.TMR2IF = 0;
    PIE1bits.TMR2IE = 1;
    INTCONbits.PEIE = 1;

    T2CONbits.TMR2ON = 1;
    ei();
}

/*******************************************************************************
 * Timer2 ISR: multiplex scan (ACTIVE-HIGH digit enables)
 ******************************************************************************/
void __interrupt() isr(void)
{
    if(PIR1bits.TMR2IF)
    {
        PIR1bits.TMR2IF = 0;

        // all digits off
        DIG0 = 0; DIG1 = 0; DIG2 = 0; DIG3 = 0;

        // segments
        LATC = seg(digits[currentDigit]);

        // enable one digit
        switch(currentDigit)
        {
            case 0: DIG0 = 1; break;
            case 1: DIG1 = 1; break;
            case 2: DIG2 = 1; break;
            case 3: DIG3 = 1; break;
            default: break;
        }

        currentDigit++;
        if(currentDigit >= 4) currentDigit = 0;
    }
}

/*******************************************************************************
 * Main
 ******************************************************************************/
void main(void)
{
    initMain();

    // Button states
    uint8_t running = 0;
    uint8_t prev_start = 1;

    hold_btn_t incBtn = { .prev = 1, .hold_ms = 0, .repeat_ms = 0, .fired_hold = 0 };
    hold_btn_t decBtn = { .prev = 1, .hold_ms = 0, .repeat_ms = 0, .fired_hold = 0 };

    // Countdown tick accumulator (non-blocking)
    const uint16_t TICK_MS = 10;
    uint16_t sec_accum_ms = 0;

    displayValue = 0;
    updateDigits(displayValue);

    while(1)
    {
        __delay_ms(TICK_MS);

        // START/STOP toggle on press edge
        if(pressed_edge_active_low(BTN_START, &prev_start))
        {
            running = !running;
        }

        // INC tap/hold accel
        if(hold_button_action(BTN_INC, &incBtn, TICK_MS))
        {
            if(displayValue < 9999) displayValue++;
            else displayValue = 0;
        }

        // DEC tap/hold accel
        if(hold_button_action(BTN_DEC, &decBtn, TICK_MS))
        {
            if(displayValue > 0) displayValue--;
        }

        // Countdown when running (about 1 second)
        if(running)
        {
            sec_accum_ms += TICK_MS;
            if(sec_accum_ms >= 1000)
            {
                sec_accum_ms = 0;

                if(displayValue > 0) displayValue--;
                else running = 0; // stop at zero
            }
        }
        else
        {
            sec_accum_ms = 0; // optional: reset timing when stopped
        }

        // Update digits atomically (prevents tearing)
        di();
        updateDigits(displayValue);
        ei();
    }
}
