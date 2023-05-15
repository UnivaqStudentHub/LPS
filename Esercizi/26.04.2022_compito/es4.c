//specifica 3 C99
/*
1.Dichiarare una variabile v di tipo unsigned char
(assumendo che le variabili di tale tipo abbiano 8 bit) e inizializzarla con una costante esadecimale
2.Scrivere un'istruzione che modifica v, ponendo a 0 il contenuto dei bit di posizione 0, 4, 7
*/
#include <stdio.h>

int main(void){

    unsigned char v = 0x12;
    // binary: 0001 0010

    v = v & 0xB6;
    // binary: 1011 0110
    // hex: 0xB6

    printf("%lx\n", v);
    // binary result: 0001 0010
    // hex result: 0x12

    system("pause");
}

// GIUSTO!!