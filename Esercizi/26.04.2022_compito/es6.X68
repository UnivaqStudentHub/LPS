*-----------------------------------------------------------
* Title      :specifica 3 M68K


    ORG    $2000
START:                  ; first instruction of program

* Put program code here

    SIMHALT             ; halt simulator
    
    move.b #$12,d7
    and.b #$b6,d7

* Put variables and constants here

    END    START        ; last line of source

*  GIUSTO!
