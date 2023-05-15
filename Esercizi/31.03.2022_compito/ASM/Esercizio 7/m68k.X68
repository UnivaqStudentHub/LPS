*-----------------------------------------------------------
* Title      :
* Written by :
* Date       :
* Description:
*-----------------------------------------------------------
    ORG    $1000
START:                  ; first instruction of program

* Put program code here
    move.w #-35,d0
    move.w #6300,d2
    move.w #-9153,d1
    
    *d0 = d0 - 1;
    sub #1,d0
    
    *d3 = d0 - 254;
    move.w d0,d5
    sub #254,d5
    move.w d5,d3
    
    *d4 = 1302 - d1;
    move.w #1302,d5
    sub d1,d5
    move.w d5,d4
    
    *d2 = d3 + d4;
    move.w d3,d5
    add d4,d5
    move.w d5,d2
    
    *d3 = d0 + 27033;
    move.w d0,d5
    add #27033,d5
    move.w d5,d3
    
    *d3 = d3 - d2;
    sub d2,d3
    
    *d4 = 740 - d1;
    move.w #740,d5
    sub d1,d5
    move.w d5,d4
    
    *d1 = d1 - 1;
    sub #1,d1
    
    *d0 = d3 - d4; 
    move.w d3,d5
    sub d4,d5
    move.w d5,d0
    
    *d3 = d2 - 14;
    move.w d2,d5
    sub #14,d5
    move.w d5,d3
    
    *d0 = d0 + d3;
    add d3,d0
    
    
    
    
    SIMHALT             ; halt simulator

* Put variables and constants here

    END    START        ; last line of source


* d0 = 17090
* d1 = -9154
* d2 = 10165
*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
