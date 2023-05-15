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
    move.l #88010,d0
    
    move.l d0,d4
    muls #-1,d4     ;a causa di questo fottuto -1 non funziona nulla
    move.l d4,d1
    
    
    
    
* Put variables and constants here

    END    START        ; last line of source

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
