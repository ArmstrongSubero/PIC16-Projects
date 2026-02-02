/*
 * File: main.c
 * Author: Armstrong Subero
 * PIC: 16F1719 w/int OSC @ 32MHz, 5v
 * Program: 25_Servo
 * Compiler: XC8 (v2.45, MPLAX X v6.15)
 * Program Version: 1.2
 *                
 * Program Description: This program allows control of a standard servo
 * 
 * Hardware Description: An MG90S servo is connected to PIN B0
 *                       Brown  -> -Ve
 *                       Red    -> +Ve 
 *                       Orange -> PWM
 *                       
 * Created November 4th, 2016, 1:00 PM
 * Updated: December 26th, 2025, 12:24 AM
 */
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include "PIC16F1718_Internal.h"

// ===== Servo timing =====
#define SERVO_FRAME_US      20000u   // 20ms -> 50Hz
#define SERVO_MIN_US         500u
#define SERVO_MAX_US        2500u
#define SERVO_CENTER_US    ((SERVO_MIN_US + SERVO_MAX_US) / 2u)

// Optional safe sweep clamps (like your CH32 code)
#define SERVO_SAFE_MIN_DEG     5u
#define SERVO_SAFE_MAX_DEG   175u

// Q15 helpers for S-curve
#define Q15_ONE 32768u

// Initialize: choose which PORTB bit drives the servo output (RB0..RB7)
void servo_init_rb(uint8_t rb_pin);

// Set pulse width directly (microseconds), clamped
void servo_write_us(uint16_t us);

// Set angle (0..180) mapped to SERVO_MIN_US..SERVO_MAX_US (with safe clamps)
void servo_set_angle_deg(uint16_t deg);

// Smooth S-curve move from current to target
void servo_set_angle_scurve(uint16_t target_deg, uint32_t duration_ms, uint16_t tick_ms);

// Smooth S-curve sweep start->end over duration
void servo_sweep_deg_scurve(uint16_t start_deg, uint16_t end_deg, uint32_t duration_ms, uint16_t tick_ms);

// Call from your global ISR
void servo_isr(void);

// ===== Internal state =====
static volatile uint16_t g_pulse_us = SERVO_CENTER_US;
static volatile uint8_t  g_rb_mask  = 0x01;   // default RB0
static volatile bool     g_pin_high = false;

static inline void delay_ms(uint16_t ms)
{
    while (ms--)
    {
        __delay_ms(1);   // constant ? XC8 is happy
    }
}

// ===== Fixed-point helpers (same as your CH32 approach) =====
static inline uint32_t q15_mul(uint32_t a, uint32_t b)
{
    return (uint32_t)(((uint64_t)a * (uint64_t)b + (1u << 14)) >> 15);
}

// Quintic smoothstep in Q15: 6t^5 - 15t^4 + 10t^3
static inline uint32_t scurve5_q15(uint32_t t)
{
    uint32_t t2 = q15_mul(t, t);
    uint32_t t3 = q15_mul(t2, t);
    uint32_t t4 = q15_mul(t3, t);
    uint32_t t5 = q15_mul(t4, t);

    int64_t s = (int64_t)6  * (int64_t)t5
              - (int64_t)15 * (int64_t)t4
              + (int64_t)10 * (int64_t)t3;

    if (s < 0) s = 0;
    if (s > Q15_ONE) s = Q15_ONE;
    return (uint32_t)s;
}

static inline uint16_t deg_to_us(uint16_t deg)
{
    if (deg < SERVO_SAFE_MIN_DEG) deg = SERVO_SAFE_MIN_DEG;
    if (deg > SERVO_SAFE_MAX_DEG) deg = SERVO_SAFE_MAX_DEG;

    uint32_t span = (uint32_t)(SERVO_MAX_US - SERVO_MIN_US);
    return (uint16_t)(SERVO_MIN_US + (span * deg) / 180u);
}

// Write CCPR1 = TMR1 + delta_us (Timer1 is 1us tick)
static inline void schedule_after_us(uint16_t delta_us)
{
    uint16_t now = ((uint16_t)TMR1H << 8) | TMR1L;
    uint16_t next = (uint16_t)(now + delta_us);   // wraps naturally

    CCPR1H = (uint8_t)(next >> 8);
    CCPR1L = (uint8_t)(next & 0xFF);
}

void servo_init_rb(uint8_t rb_pin)
{
    if (rb_pin > 7) rb_pin = 0;
    g_rb_mask = (uint8_t)(1u << rb_pin);

    // Digital output on that RB pin
    ANSELB = 0x00;
    TRISB &= (uint8_t)~g_rb_mask;
    LATB  &= (uint8_t)~g_rb_mask;

    // ===== Timer1: 1us tick =====
    // FOSC = 32MHz -> FOSC/4 = 8MHz -> 0.125us/tick
    // Prescaler 1:8 -> 1.0us/tick
    T1CONbits.TMR1ON  = 0;
    T1CONbits.TMR1CS  = 0;      // clock = FOSC/4
    T1CONbits.T1CKPS  = 0b11;   // 1:8 prescaler
    T1CONbits.T1OSCEN = 0;      // off
    T1GCONbits.TMR1GE = 0;      // gate off

    TMR1H = 0;
    TMR1L = 0;

    // ===== CCP1 in compare mode (interrupt on match) =====
    // Any compare mode will set CCP1IF on match.
    CCP1CONbits.CCP1M = 0b1010; // Compare, toggle output on match (we don't map output; we do GPIO in ISR)

    PIR1bits.CCP1IF = 0;
    PIE1bits.CCP1IE = 1;

    // Start frame: set pin HIGH and schedule end of pulse
    g_pin_high = true;
    LATB |= g_rb_mask;

    schedule_after_us(g_pulse_us);

    // Enable interrupts
    INTCONbits.PEIE = 1;
    INTCONbits.GIE  = 1;

    // Start Timer1
    T1CONbits.TMR1ON = 1;
}

void servo_write_us(uint16_t us)
{
    if (us < SERVO_MIN_US) us = SERVO_MIN_US;
    if (us > SERVO_MAX_US) us = SERVO_MAX_US;
    g_pulse_us = us;
}

void servo_set_angle_deg(uint16_t deg)
{
    if (deg > 180) deg = 180;
    servo_write_us(deg_to_us(deg));
}

// Reverse map current pulse to degrees (approx)
static uint16_t current_deg_from_pulse(void)
{
    uint16_t us = g_pulse_us;
    if (us < SERVO_MIN_US) us = SERVO_MIN_US;
    if (us > SERVO_MAX_US) us = SERVO_MAX_US;

    uint32_t span = (uint32_t)(SERVO_MAX_US - SERVO_MIN_US);
    return (uint16_t)(((uint32_t)(us - SERVO_MIN_US) * 180u) / span);
}

void servo_sweep_deg_scurve(uint16_t start_deg, uint16_t end_deg, uint32_t duration_ms, uint16_t tick_ms)
{
    if (start_deg > 180) start_deg = 180;
    if (end_deg   > 180) end_deg   = 180;
    if (duration_ms < 5) duration_ms = 5;
    if (tick_ms < 2) tick_ms = 2;

    int32_t diff = (int32_t)end_deg - (int32_t)start_deg;

    uint32_t steps = duration_ms / tick_ms;
    if (steps < 1) steps = 1;

    for (uint32_t k = 0; k <= steps; ++k)
    {
        uint32_t t_q15 = (uint32_t)((uint64_t)Q15_ONE * k / steps);
        uint32_t s_q15 = scurve5_q15(t_q15);

        int32_t delta = (int32_t)(((int64_t)diff * (int64_t)s_q15 + (Q15_ONE >> 1)) >> 15);
        int32_t a = (int32_t)start_deg + delta;

        if (a < 0) a = 0;
        if (a > 180) a = 180;

        servo_set_angle_deg((uint16_t)a);

        // your project likely has a delay helper; otherwise use __delay_ms with _XTAL_FREQ set
        delay_ms(tick_ms);
    }

    servo_set_angle_deg(end_deg);
}

void servo_set_angle_scurve(uint16_t target_deg, uint32_t duration_ms, uint16_t tick_ms)
{
    if (target_deg > 180) target_deg = 180;

    uint16_t start_deg = current_deg_from_pulse();
    if (start_deg == target_deg) return;

    servo_sweep_deg_scurve(start_deg, target_deg, duration_ms, tick_ms);
}

// ===== ISR hook: call this from your main interrupt =====
void servo_isr(void)
{
    if (!PIR1bits.CCP1IF) return;
    PIR1bits.CCP1IF = 0;

    if (g_pin_high)
    {
        // End of pulse -> drive LOW, schedule remainder of frame
        LATB &= (uint8_t)~g_rb_mask;
        g_pin_high = false;

        uint16_t off_us = (uint16_t)(SERVO_FRAME_US - g_pulse_us);
        schedule_after_us(off_us);
    }
    else
    {
        // Start next frame -> drive HIGH, schedule pulse width
        LATB |= g_rb_mask;
        g_pin_high = true;

        schedule_after_us(g_pulse_us);
    }
}

void initMain(void)
{
    internal_32();
    __delay_ms(100);

    // Turn off analog on B
    ANSELB = 0;

    // Servo on RB0 (change to 1..7 if you want RB1..RB7)
    servo_init_rb(0);
}

void __interrupt() isr(void)
{
    // Servo compare interrupt handler
    servo_isr();

    // (If you have other interrupts, handle them here too)
}

void main(void)
{
    initMain();

    while (1)
    {
        servo_sweep_deg_scurve(0,   180, 2000, 10); __delay_ms(300);
        servo_sweep_deg_scurve(180,   0, 2000, 10); __delay_ms(300);

        servo_sweep_deg_scurve(0,   180, 600,  8);  __delay_ms(200);
        servo_sweep_deg_scurve(180,   0, 600,  8);  __delay_ms(200);
    }
}

