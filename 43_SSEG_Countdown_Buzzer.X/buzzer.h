/*
 * File: buzzer.h
 * Author: Armstrong Subero
 * PIC: 16F1719 w/int OSC @ 32MHz, 5v
 * Program: Buzzer Sound Library
 * Compiler: XC8 (v2.45, MPLAX X v6.15)
 * Program Version: 1.0
 *                
 * Program Description: Sound library for piezo buzzer using PWM
 * 
 * Hardware Description: Piezo buzzer connected to RB0 (CCP1/PWM1)
 */

#ifndef BUZZER_H
#define BUZZER_H

#include <xc.h>
#include <stdint.h>

/* Note definitions (A4=440 Hz family) */
#define NOTE_C4   262
#define NOTE_CS4  277
#define NOTE_D4   294
#define NOTE_DS4  311
#define NOTE_E4   330
#define NOTE_F4   349
#define NOTE_FS4  370
#define NOTE_G4   392
#define NOTE_GS4  415
#define NOTE_A4   440
#define NOTE_AS4  466
#define NOTE_B4   494
#define NOTE_C5   523
#define NOTE_CS5  554
#define NOTE_D5   587
#define NOTE_DS5  622
#define NOTE_E5   659
#define NOTE_F5   698
#define NOTE_FS5  740
#define NOTE_G5   784
#define NOTE_GS5  831
#define NOTE_A5   880
#define NOTE_AS5  932
#define NOTE_B5   988
#define NOTE_C6   1047

/* Public API */
void Buzzer_Init(void);
void Buzzer_Set(uint32_t frequency_hz, uint8_t volume_pct);
void Buzzer_Stop(void);
void Buzzer_Beep(uint32_t frequency_hz, uint8_t volume_pct, uint32_t duration_ms);

/* UI tones */
void Buzzer_Success(void);
void Buzzer_Failure(void);
void Buzzer_Warning(void);
void Buzzer_Alert(void);
void Buzzer_KeyPress(void);
void Buzzer_MenuSelect(void);
void Buzzer_MenuBack(void);
void Buzzer_PowerUp(void);
void Buzzer_PowerDown(void);
void Buzzer_CriticalBattery(void);
void Buzzer_Processing(void);
void Buzzer_Error(void);

/* Effects */
void Buzzer_SweepUp(uint32_t start_hz, uint32_t end_hz, uint32_t duration_ms);
void Buzzer_SweepDown(uint32_t start_hz, uint32_t end_hz, uint32_t duration_ms);
void Buzzer_Siren(uint32_t low_hz, uint32_t high_hz, uint32_t duration_ms);

/* Military Applications */
void Buzzer_Countdown(uint32_t duration_ms);
void Buzzer_CountdownIntense(uint32_t duration_ms);
void Buzzer_Ping(void);

/* Consumer Goods */
void Buzzer_Scanner(void);
void Buzzer_Connected(void);
void Buzzer_Disconnected(void);
void Buzzer_ChargingStart(void);
void Buzzer_ChargingComplete(void);
void Buzzer_Reminder(void);
void Buzzer_TimerComplete(void);

#endif