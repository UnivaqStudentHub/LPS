* Title      : specifca 1 M68K

    ORG    $2000
START:                  ; first instruction of program

* Put program code here

    SIMHALT             ; halt simulator
    move.l #$12345678,d7
    or.l #$8010001,d7
    

* Put variables and constants here

    END    START        ; last line of source

* GIUSTO!
