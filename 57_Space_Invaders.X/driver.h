/*
 * File: driver.h
 * Author: Armstrong Subero
 * PIC: 16F1718/16F1719 w/int OSC @ 32MHz, 5v
 * Program: TinyJoypad Driver Layer for PIC16F
 * Compiler: XC8
 *
 * Description:
 * This driver bridges the Tiny Invaders game code to the PIC16F hardware.
 * Provides the JOY_* interface expected by the game.
 *
 * Hardware Connections:
 *   OLED SDA  -> RC4
 *   OLED SCL  -> RC5
 *   Left btn  -> RA0 (directly to GND when pressed, internal pull-up)
 *   Right btn -> RA1 (directly to GND when pressed, internal pull-up)
 *   Fire btn  -> RA2 (directly to GND when pressed, internal pull-up)
 *   Buzzer    -> RB0 (optional, directly connected piezo)
 *
 * Based on Stefan Wagner's CH32V003 port of TinyJoypad.
 */

#ifndef DRIVER_H
#define DRIVER_H

#include "PIC16F1718_Internal.h"
#include "I2C.h"
#include "oled_min.h"
#include <stdint.h>

/*******************************************************************************
 * Hardware Pin Definitions - Adjust to match your wiring
 ******************************************************************************/
/* Input buttons (directly connected to pins with internal pull-ups) */
#define BTN_LEFT_PORT   PORTAbits.RA0
#define BTN_RIGHT_PORT  PORTAbits.RA1
#define BTN_FIRE_PORT   PORTAbits.RA2

/* Buzzer output */
#define BUZZER_TRIS     TRISBbits.TRISB0
#define BUZZER_LAT      LATBbits.LATB0

/*******************************************************************************
 * SPACE Structure - Game State
 * This must match the original game exactly
 ******************************************************************************/
typedef struct SPACE {
    int8_t   UFOxPos;
    uint8_t  oneFrame;
    uint8_t  MonsterShoot[2];
    int8_t   MonsterGrid[5][6];
    uint8_t  Shield[6];
    uint8_t  ScrBackV;
    int8_t   MyShootBall;
    uint8_t  MyShootBallxpos;
    uint8_t  MyShootBallFrame;
    uint8_t  anim;
    uint8_t  frame;
    uint8_t  PositionDansGrilleMonsterX;
    uint8_t  PositionDansGrilleMonsterY;
    uint8_t  MonsterFloorMax;
    uint8_t  MonsterOffsetGauche;
    uint8_t  MonsterOffsetDroite;
    uint8_t  MonsterGroupeXpos;
    uint8_t  MonsterGroupeYpos;
    uint8_t  DecalageY8;
    uint8_t  frameMax;
    uint8_t  Direction;
} SPACE;

/*******************************************************************************
 * JOY Interface Functions and Macros
 ******************************************************************************/

/* Initialize hardware */
void JOY_init(void);

/* Button reads (active low - pressed = 0) */
#define JOY_left_pressed()   (BTN_LEFT_PORT == 0)
#define JOY_right_pressed()  (BTN_RIGHT_PORT == 0)
#define JOY_act_pressed()    (BTN_FIRE_PORT == 0)

/* Delay */
#define JOY_DLY_ms(x)        __delay_ms(x)

/* Simple random number (uses Timer0 free-running) */
uint8_t JOY_random(void);

/* Sound generation */
void JOY_sound(uint8_t freq, uint8_t duration);

/* Frame rate limiting */
#define JOY_SLOWDOWN()       __delay_ms(2)

/* OLED interface for game rendering */
#define JOY_OLED_data_start(page)   OLED_data_start(page)
#define JOY_OLED_send(data)         OLED_send(data)
#define JOY_OLED_end()              OLED_end()

#endif /* DRIVER_H */