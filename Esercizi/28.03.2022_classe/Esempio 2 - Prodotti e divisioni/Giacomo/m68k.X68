*-----------------------------------------------------------
* Title      :
* Written by :
* Date       :
* Description:
*-----------------------------------------------------------
    ORG    $1000
    START:                  ; first instruction of program

* Put program code here

    move.l #4095,d0
    move.l #41,d1
    move.l #33,d2

    move.l #29041,d5
    divs d0,d5
    move.w d5,d4


    move.l d4,d5
    muls d2,d5
    move.l d5,d3


    move.l d2,d5
    add #113,d5
    move d5,d2

    move.l d2,d5
    divs #3,d5
    move.w d5,d4

    move.l d4,d5
    divs #5,d5
    swap d5
    move.w d5,d2


    move.l d1,d5
    muls #52,d5
    move.l d5,d1


    move.l d1,d5
    divs d2,d5
    move d5,d0


    move.l d1,d5
    divs d2,d5
    swap d5
    move.w d5,d1

    SIMHALT             ; halt simulator

* Put variables and constants here

    END    START        ; last line of source