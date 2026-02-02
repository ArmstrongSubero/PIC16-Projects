/*
 * File: buzzer.c
 * Implementation file
 */

#include "buzzer.h"
#include "PIC16F1718_Internal.h"
/*******************************************************************************
 * Function: void delay_ms(uint32_t ms)
 *
 * Returns: Nothing
 *
 * Description: Variable delay in milliseconds
 ******************************************************************************/
void delay_ms(uint32_t ms)
{
    while(ms--) {
        __delay_ms(1);  // 1ms is constant
    }
}

/*******************************************************************************
 * Function: void Buzzer_Init(void)
 *
 * Returns: Nothing
 *
 * Description: Initialize PWM for buzzer on RB0 (CCP1)
 ******************************************************************************/
void Buzzer_Init(void)
{
    // Set RB0 as output
    TRISBbits.TRISB0 = 0;
    
    // Turn off analog
    ANSELBbits.ANSB0 = 0;
    
    // Select PWM timer as Timer6 for CCP1
    CCPTMRSbits.C1TSEL = 0b10;
    
    // Timer6 setup (will be reconfigured per frequency)
    T6CONbits.T6CKPS = 0b00;  // Prescale = 1
    T6CONbits.TMR6ON = 1;     // Enable Timer6
    PR6 = 255;                 // Initial period
    
    // Configure CCP1 for PWM
    CCP1CONbits.DC1B = 0b00;   // LSBs of duty cycle
    CCP1CONbits.CCP1M = 0b1100; // PWM mode
    
    // Configure PPS
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00;
    RB0PPSbits.RB0PPS = 0b01100;  // PWM1 to RB0
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x01;
    
    // Start silent
    CCPR1L = 0;
}

/*******************************************************************************
 * Function: void Buzzer_Set(uint32_t frequency_hz, uint8_t volume_pct)
 *
 * Returns: Nothing
 *
 * Description: Set frequency and volume
 *              Volume: 0-100 (maps to 0-50% duty for piezo efficiency)
 *              
 * Usage: Buzzer_Set(2000, 50);
 ******************************************************************************/
void Buzzer_Set(uint32_t frequency_hz, uint8_t volume_pct)
{
    if (frequency_hz == 0 || volume_pct == 0) {
        Buzzer_Stop();
        return;
    }
    
    if (volume_pct > 100) volume_pct = 100;
    
    // Fosc = 32 MHz, Tosc = 31.25 ns
    // PWM Period = [(PR2)+1] * 4 * Tosc * Prescale
    // PWM Freq = Fosc / [(PR2+1) * 4 * Prescale]
    
    uint32_t fosc = 32000000UL;
    uint8_t prescaler = 1;
    uint8_t prescale_bits = 0b00;
    
    // Find appropriate prescaler
    uint32_t pr_value = (fosc / (4UL * frequency_hz * prescaler)) - 1;
    
    if (pr_value > 255) {
        prescaler = 4;
        prescale_bits = 0b01;
        pr_value = (fosc / (4UL * frequency_hz * prescaler)) - 1;
    }
    
    if (pr_value > 255) {
        prescaler = 16;
        prescale_bits = 0b10;
        pr_value = (fosc / (4UL * frequency_hz * prescaler)) - 1;
    }
    
    if (pr_value > 255) {
        prescaler = 64;
        prescale_bits = 0b11;
        pr_value = (fosc / (4UL * frequency_hz * prescaler)) - 1;
    }
    
    if (pr_value > 255) pr_value = 255;
    if (pr_value < 1) pr_value = 1;
    
    // Disable PWM while updating
    CCP1CONbits.CCP1M = 0b0000;
    
    // Update Timer6 settings
    T6CONbits.TMR6ON = 0;
    T6CONbits.T6CKPS = prescale_bits;
    PR6 = (uint8_t)pr_value;
    TMR6 = 0;
    T6CONbits.TMR6ON = 1;
    
    // Calculate duty cycle (max 50% for piezo)
    // Duty Cycle = (CCPR1L:CCP1CON<5:4>) * Tosc * Prescale
    uint16_t duty_10bit = ((pr_value + 1) * 4 * volume_pct) / 200;
    
    // Split into CCPR1L (8 MSBs) and DC1B (2 LSBs)
    CCPR1L = (uint8_t)(duty_10bit >> 2);
    CCP1CONbits.DC1B = (uint8_t)(duty_10bit & 0x03);
    
    // Re-enable PWM
    CCP1CONbits.CCP1M = 0b1100;
}

/*******************************************************************************
 * Function: void Buzzer_Stop(void)
 *
 * Returns: Nothing
 *
 * Description: Stop the buzzer
 ******************************************************************************/
void Buzzer_Stop(void)
{
    CCPR1L = 0;
    CCP1CONbits.DC1B = 0;
}

/*******************************************************************************
 * Function: void Buzzer_Beep(...)
 *
 * Returns: Nothing
 *
 * Description: Simple beep with delay
 ******************************************************************************/
void Buzzer_Beep(uint32_t frequency_hz, uint8_t volume_pct, uint32_t duration_ms)
{
    Buzzer_Set(frequency_hz, volume_pct);
    delay_ms(duration_ms);  // XC8 delay macro
    Buzzer_Stop();
}

// Helper for delays since __delay_ms doesn't take variables
void delay_variable_ms(uint32_t ms)
{
    for(uint32_t i = 0; i < ms; i++) {
        __delay_ms(1);
    }
}

/////////////////////////////
// UI Tones
/////////////////////////////

void Buzzer_Success(void)
{
    Buzzer_Beep(NOTE_C5, 50, 90);
    delay_variable_ms(40);
    Buzzer_Beep(NOTE_E5, 50, 90);
    delay_variable_ms(40);
    Buzzer_Beep(NOTE_G5, 60, 160);
}

void Buzzer_Failure(void)
{
    Buzzer_Beep(NOTE_G5, 60, 160);
    delay_variable_ms(40);
    Buzzer_Beep(NOTE_E5, 60, 220);
}

void Buzzer_Warning(void)
{
    for(uint8_t i = 0; i < 3; i++) {
        Buzzer_Beep(NOTE_A5, 60, 90);
        delay_variable_ms(90);
    }
}

void Buzzer_Alert(void)
{
    for(uint8_t i = 0; i < 5; i++) {
        Buzzer_Beep(NOTE_A5, 75, 50);
        delay_variable_ms(50);
    }
}

void Buzzer_KeyPress(void)    { Buzzer_Beep(NOTE_C5, 35, 40); }
void Buzzer_MenuSelect(void)  { Buzzer_Beep(NOTE_E5, 40, 70); }
void Buzzer_MenuBack(void)    { Buzzer_Beep(NOTE_C5, 40, 70); }

void Buzzer_PowerUp(void)
{
    Buzzer_Beep(NOTE_C5, 55, 80); delay_variable_ms(40);
    Buzzer_Beep(NOTE_E5, 55, 80); delay_variable_ms(40);
    Buzzer_Beep(NOTE_G5, 55, 80); delay_variable_ms(40);
    Buzzer_Beep(NOTE_C6, 60, 150);
}

void Buzzer_PowerDown(void)
{
    Buzzer_Beep(NOTE_C6, 55, 80); delay_variable_ms(40);
    Buzzer_Beep(NOTE_G5, 55, 80); delay_variable_ms(40);
    Buzzer_Beep(NOTE_E5, 55, 80); delay_variable_ms(40);
    Buzzer_Beep(NOTE_C5, 60, 150);
}

void Buzzer_CriticalBattery(void)
{
    for(uint8_t i = 0; i < 2; i++) {
        Buzzer_Beep(NOTE_G4, 75, 280);
        delay_variable_ms(280);
    }
}

void Buzzer_Processing(void)
{
    for(uint8_t i = 0; i < 3; i++) {
        Buzzer_Beep(NOTE_E5, 35, 45);
        delay_variable_ms(90);
    }
}

void Buzzer_Error(void)
{
    for(uint8_t i = 0; i < 2; i++) {
        Buzzer_Beep(NOTE_B5, 75, 180);
        delay_variable_ms(90);
    }
    Buzzer_Beep(NOTE_B5, 75, 360);
}

/////////////////////////////
// Effects
/////////////////////////////

void Buzzer_SweepUp(uint32_t start_hz, uint32_t end_hz, uint32_t duration_ms)
{
    if(end_hz <= start_hz) return;
    
    uint32_t steps = duration_ms / 2;
    if(steps < 1) steps = 1;
    
    for(uint32_t k = 0; k < steps; k++) {
        uint32_t f = start_hz + ((end_hz - start_hz) * k) / steps;
        Buzzer_Set(f, 70);
        __delay_ms(2);
    }
    Buzzer_Stop();
}

void Buzzer_SweepDown(uint32_t start_hz, uint32_t end_hz, uint32_t duration_ms)
{
    if(start_hz <= end_hz) return;
    
    uint32_t steps = duration_ms / 2;
    if(steps < 1) steps = 1;
    
    for(uint32_t k = 0; k < steps; k++) {
        uint32_t f = start_hz - ((start_hz - end_hz) * k) / steps;
        Buzzer_Set(f, 70);
        __delay_ms(2);
    }
    Buzzer_Stop();
}

void Buzzer_Siren(uint32_t low_hz, uint32_t high_hz, uint32_t duration_ms)
{
    if(high_hz <= low_hz) return;
    
    const uint32_t tick = 5;
    uint32_t t = 0;
    int8_t dir = 1;
    uint32_t f = low_hz;
    
    while(t < duration_ms) {
        Buzzer_Set(f, 70);
        delay_variable_ms(tick);
        t += tick;
        
        uint32_t step = (high_hz - low_hz) / (1000 / tick);
        if(step == 0) step = 1;
        
        if(dir > 0) {
            if(f + step >= high_hz) {
                f = high_hz;
                dir = -1;
            } else {
                f += step;
            }
        } else {
            if(f <= low_hz + step) {
                f = low_hz;
                dir = 1;
            } else {
                f -= step;
            }
        }
    }
    Buzzer_Stop();
}

/////////////////////////////
// Military Applications
/////////////////////////////

void Buzzer_Countdown(uint32_t duration_ms)
{
    uint32_t beep_freq = 2200;
    uint32_t initial_delay = 1000;
    uint32_t elapsed = 0;
    
    while(elapsed < duration_ms) {
        Buzzer_Set(beep_freq, 70);
        delay_variable_ms(50);
        Buzzer_Stop();
        
        initial_delay = (initial_delay * 8) / 10;
        if(initial_delay < 50) initial_delay = 50;
        
        delay_variable_ms(initial_delay);
        elapsed += (50 + initial_delay);
    }
    
    Buzzer_Set(3000, 100);
    delay_variable_ms(500);
    Buzzer_Stop();
}

void Buzzer_CountdownIntense(uint32_t duration_ms)
{
    uint32_t start_freq = 2200;
    uint32_t initial_delay = 1000;
    uint32_t elapsed = 0;
    
    while(elapsed < duration_ms) {
        Buzzer_Set(start_freq, 70);
        delay_variable_ms(50);
        Buzzer_Stop();
        
        start_freq += 50;
        initial_delay = (initial_delay * 7) / 10;
        if(initial_delay < 30) initial_delay = 30;
        
        delay_variable_ms(initial_delay);
        elapsed += (50 + initial_delay);
    }
}

void Buzzer_Ping(void)
{
    Buzzer_SweepDown(4000, 1000, 100);
    delay_variable_ms(50);
    Buzzer_SweepUp(1000, 4000, 50);
}

/////////////////////////////
// Consumer Goods
/////////////////////////////

void Buzzer_Scanner(void)
{
    Buzzer_Set(2500, 70);
    delay_variable_ms(80);
    Buzzer_Stop();
    delay_variable_ms(20);
    Buzzer_Set(3000, 50);
    delay_variable_ms(40);
    Buzzer_Stop();
}

void Buzzer_Connected(void)
{
    Buzzer_Set(2000, 50);
    delay_variable_ms(50);
    Buzzer_Stop();
    delay_variable_ms(50);
    Buzzer_Set(2500, 50);
    delay_variable_ms(100);
    Buzzer_Stop();
}

void Buzzer_Disconnected(void)
{
    Buzzer_Set(2500, 50);
    delay_variable_ms(50);
    Buzzer_Stop();
    delay_variable_ms(50);
    Buzzer_Set(2000, 50);
    delay_variable_ms(100);
    Buzzer_Stop();
}

void Buzzer_ChargingStart(void)
{
    Buzzer_SweepUp(1500, 3000, 200);
}

void Buzzer_ChargingComplete(void)
{
    for(uint8_t i = 0; i < 3; i++) {
        Buzzer_Set(3000, 60);
        delay_variable_ms(100);
        Buzzer_Stop();
        delay_variable_ms(100);
    }
}

void Buzzer_Reminder(void)
{
    for(uint8_t i = 0; i < 2; i++) {
        Buzzer_Set(2000, 40);
        delay_variable_ms(100);
        Buzzer_Stop();
        delay_variable_ms(300);
    }
}

void Buzzer_TimerComplete(void)
{
    for(uint8_t i = 0; i < 3; i++) {
        Buzzer_Set(4000, 70);
        delay_variable_ms(100);
        Buzzer_Stop();
        delay_variable_ms(100);
        Buzzer_Set(3000, 70);
        delay_variable_ms(100);
        Buzzer_Stop();
        delay_variable_ms(300);
    }
}