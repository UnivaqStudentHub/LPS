*-----------------------------------------------------------
* Title      :
* Written by :
* Date       :
* Description:
*-----------------------------------------------------------
    ORG    $2000
START:                  ; first instruction of program

* Put program code here
     move #-325,d0
     move #826,d2
    
    *ADD numero o registro, registro       sintassi
    * add memorizza la somma nel secondo registro
    
    *sub : secondo - primo
    *sub : memorizza nel secondo
    
    * move [sorgente],[destinazione]    move SINTASSI
   
    
    move d0,d6
    add #22,d6
    move d6,d3
    
    move d2,d6
    add #-329,d6
    move d6,d4
    
    move #2048,d6
    sub d3,d6
    move d6,d1
    
    add d4,d1
    
    move d0,d6
    sub #345,d6
    move d6,d3
    
    move d0,d6
    add #9,d6
    move d6,d4
    
    move d1,d6
    sub d4,d6
    move d6,d2
    
    move d3,d6
    sub d2,d6
    move d6,d5
    
    sub d5,d0
    
    
    
    *d0 : 3509
    *d1 : 2848
    *d2 : 3164

    SIMHALT             ; halt simulator

* Put variables and constants here
    
    END    START        ; last line of source
