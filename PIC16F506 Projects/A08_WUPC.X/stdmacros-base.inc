;************************************************************************
;                                                                       *
;   Filename:      stdmacros-base.inc                                   *
;   Date:          16/2/12                                              *
;   File Version:  1.1                                                  *
;                                                                       *
;   Author:        David Meiklejohn                                     *
;   Company:       Gooligum Electronics                                 *
;                                                                       *
;************************************************************************
;                                                                       *
;   Architecture:  Baseline PIC                                         *
;   Processor:     any                                                  *
;                                                                       *
;************************************************************************
;                                                                       *
;   Files required: none                                                *
;                                                                       *
;************************************************************************
;                                                                       *
;   Description:    Library of useful macros                            *
;                                                                       *
;   DelayMS - delay in milliseconds (wrapper for delay10 subroutine)    *
;   DbnceHi - debounce switch, wait for high input                      *
;   DbnceLo - debounce switch, wait for low input                       *
;                                                                       *
;************************************************************************


;***** DelayMS
; Delay in milliseconds
;
; Calls: 'delay10' subroutine, providing a Wx10ms delay
;
DelayMS MACRO   ms                  ; delay time in ms
    IF ms>.2550
        ERROR "Maximum delay time is 2550ms"
    ENDIF
        movlw   ms/.10              ; divide by 10 to pass to delay10 routine
        pagesel delay10
        call    delay10
        pagesel $
        ENDM


;***** DbnceHi
; Debounce switch on given input port,pin
; Waits for switch to be 'high' continuously for 10 ms
;
; Uses:	TMR0		Assumes: TMR0 running at 256 us/tick
;
DbnceHi MACRO   port,pin
    local       start,wait,DEBOUNCE
    variable    DEBOUNCE=.10*.1000/.256 ; switch debounce count = 10ms/(256us/tick)

        pagesel $               ; select current page for gotos
start   clrf    TMR0            ; button down so reset timer (counts "up" time)
wait    btfss   port,pin        ; wait for switch to go high (=1)
        goto    start 
        movf    TMR0,w          ; has switch has been up continuously for debounce time?
        xorlw   DEBOUNCE
        btfss   STATUS,Z        ; if not, keep checking that it is still up
        goto    wait
        ENDM


;***** DbnceLo
; Debounce switch on given input port,pin
; Waits for switch to be 'low' continuously for 10 ms
;
; Uses:	TMR0		Assumes: TMR0 running at 256 us/tick
;
DbnceLo MACRO   port,pin
    local       start,wait,DEBOUNCE
    variable    DEBOUNCE=.10*.1000/.256 ; switch debounce count = 10ms/(256us/tick)

        pagesel $               ; select current page for gotos
start   clrf    TMR0            ; button down so reset timer (counts "down" time)
wait    btfsc   port,pin        ; wait for switch to go low (=0)
        goto    start 
        movf    TMR0,w          ; has switch has been down continuously for debounce time?
        xorlw   DEBOUNCE
        btfss   STATUS,Z        ; if not, keep checking that it is still up
        goto    wait
        ENDM