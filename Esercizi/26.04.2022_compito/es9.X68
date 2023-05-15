
*LEGGERE da input 4 interi senza segno x, a, b, c?
*SE x è minore di 256 e a, b e c sono ciascuno minore di 8 
*ALLORA PORRE a 1 le cifre binarie di x che hanno posizioni uguali ai valori a, b, 

    ORG    $2000
START:                  ; first instruction of program

* Put program code here

    SIMHALT             ; halt simulator
    move.l 5,d0
    move.l 4,d1
    move.l 3,d2
    move.l 2,d3
    
    cmp.l #256,d0
    bge fine
    cmp.l #8,d1
    bge fine
    cmp.l #8,d2
    bge fine
    cmp.l #8,d3
    bge fine
    
    move.l #1,d4
    lsl d1,d4
    or.l d4,d0
    
    move.l #1,d4
    lsl d2,d4
    or.l d4,d0
    
    move.l #1,d4
    lsl d3,d4
    or.l d4,d0
    
fine:

* Put variables and constants here

    END    START        ; last line of source

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
