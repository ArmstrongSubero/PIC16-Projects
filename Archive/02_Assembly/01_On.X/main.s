;
; File:     main.S
; Target:   PIC16F1718
; Author:   Armstrong Subero
; Compiler: pic-as (v2.30), MPLABX V5.45
;                
; Program Description: This Program Allows PIC16F1718 to Turn on an LED
; 
; Hardware Description: An LED is connected via a 1K resistor to PIN C3
;                       
; Created November 10th, 2020, 1:46 PM
; Last Updated: November 10th, 2020, 1:46 PM
 

PROCESSOR 16F1718
#include <xc.inc>
    
;configuration word 1
 CONFIG FOSC=INTOSC         // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
 CONFIG WDTE=OFF,PWRTE=OFF  // WDT & PWRT disabled
 CONFIG MCLRE=ON            // MCLR/VPP pin function is MCLR
 CONFIG CP=OFF              // Program & data memory unprotected
 CONFIG BOREN=ON            // Brown-out Reset enabled
 CONFIG CLKOUTEN=OFF        // CLKOUT function is disabled
 CONFIG IESO=ON             // Internal/External Switchover mode enabled
 CONFIG FCMEN=ON            // Fail-Safe Clock Monitor enabled

;configuration word 2
CONFIG WRT=OFF             // Write protection off
CONFIG PLLEN=ON            // 4x PLL enabled
CONFIG STVREN=ON           // Stack Over/underflow will cause a Reset
CONFIG BORV=LO             // Brown-out Reset Voltage low trip point
CONFIG LPBOR = OFF         // Low power BOR disabled
CONFIG LVP=OFF             // Low-voltage programming enabled
 
PSECT resetVec, class=CODE, delta=2
resetVec:
    PAGESEL main
    goto main
    
PSECT code 
main:
    movlw 0b11110111  ; make RC3 an output pin
    banksel TRISC     
    movwf TRISC
    
  
ledon:
    banksel LATC      ; turn RC3 on
    bsf LATC3
    
    goto ledon        ; loop forever
    
    END resetVec