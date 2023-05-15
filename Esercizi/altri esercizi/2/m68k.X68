    *-----------------------------------------------------------
* Title      :
* Written by :
* Date       :
* Description:
*-----------------------------------------------------------
    ORG    $1000
START:                  ; first instruction of program

* Put program code here

    SIMHALT             ; halt simulator
    move #24,d0
    cmp #256,d0
    bge fine
inizio_loop:
    move d0,d1
    
    and #1,d1
    
    add d1,d2
    
    lsr #1,d0
    
    tst d0
    bne inizio_loop
fine:

* Put variables and constants here

    END    START        ; last line of source

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
