; TODO INSERT CONFIG CODE HERE USING CONFIG BITS GENERATOR
	#include <p16f506.inc>
	
	GLOBAL delay10_R

;**** variable definitions
    UDATA
dc1 res 1
dc2 res 1
dc3 res 1

;**** subroutines
    CODE

;**********
; Delay W * 10 ms
;
delay10_R
    ; delay 10 ms
    banksel  dc3
    movwf    dc3
dly2
    movlw    .13
    movwf    dc2
    clrf     dc1
dly1
    decfsz   dc1, f
    goto     dly1
    decfsz   dc2, f
    goto     dly1
    decfsz   dc3, f
    goto     dly2
    
    retlw   0			    ; return

    END
 