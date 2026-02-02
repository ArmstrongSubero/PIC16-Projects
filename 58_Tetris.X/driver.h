/*
 * File: driver.h
 * Author: Armstrong Subero
 * PIC: 16F1718/16F1719 w/int OSC @ 32MHz, 5v
 * Program: TinyJoypad Driver Layer for Tiny Tris
 * Compiler: XC8
 *
 * Hardware Connections:
 *   OLED SDA  -> RC4
 *   OLED SCL  -> RC5
 *   Left btn  -> RA0 (to GND, internal pull-up)
 *   Right btn -> RA1 (to GND, internal pull-up)
 *   Rotate    -> RA2 (to GND, internal pull-up)
 *   Down/Drop -> RA3 (to GND, internal pull-up)
 *   Buzzer    -> RB0 (optional piezo)
 */

#ifndef DRIVER_H
#define DRIVER_H

#include "PIC16F1718_Internal.h"
#include "oled_min.h"
#include <stdint.h>
#include <xc.h>

/* Hardware Pins */
#define BTN_LEFT_PORT   PORTAbits.RA0
#define BTN_RIGHT_PORT  PORTAbits.RA1
#define BTN_FIRE_PORT   PORTAbits.RA2
#define BTN_DOWN_PORT   PORTAbits.RA4

#define BUZZER_TRIS     TRISBbits.TRISB0
#define BUZZER_LAT      LATBbits.LATB0

/* JOY Interface */
void JOY_init(void);

/* Buttons (active low) */
#define JOY_left_pressed()    (BTN_LEFT_PORT == 0)
#define JOY_right_pressed()   (BTN_RIGHT_PORT == 0)
#define JOY_act_pressed()     (BTN_FIRE_PORT == 0)
#define JOY_down_pressed()    (BTN_DOWN_PORT == 0)
#define JOY_act_released()    (BTN_FIRE_PORT == 1)

/* Delay */
#define JOY_DLY_ms(x)         __delay_ms(x)

/* Random */
uint8_t JOY_random(void);

/* Sound */
void JOY_sound(uint8_t freq, uint8_t duration);

/* Frame rate */
#define JOY_SLOWDOWN()        __delay_ms(5)

/* OLED interface */
#define JOY_OLED_data_start(page)   OLED_data_start(page)
#define JOY_OLED_send(data)         OLED_send(data)
#define JOY_OLED_end()              OLED_end()

/* Arduino-style map function (used by game) */
#define map(x, in_min, in_max, out_min, out_max) \
    (((long)(x) - (long)(in_min)) * ((long)(out_max) - (long)(out_min)) / ((long)(in_max) - (long)(in_min)) + (long)(out_min))

#endif /* DRIVER_H */
