// specifica 1 c99
/*Dichiarare una variabile v di tipo unsigned long
(assumendo che le variabili di tale tipo abbiano 32 bit)e inizializzarla con una costante esadecimale
Scrivere un'istruzione che modifica v, ponendo a 1 il contenuto dei bit di posizione 0, 17 e 28
*/

#include <stdio.h>

int main(void){
    unsigned long v = 0x12345678;
    // binary: 0001 0010 0011 0100 0101 0110 0111 1000

    v = v | 0x8010001;
    // binary: 0000 1000 0000 0001 0000 0000 0000 0001
    //hex 08010001

    printf("%lx\n", v);
    //binary with or: 0001 1010 0011 0101 0101 0110 0111 1001
    //hex: 0x1a355679
    system("pause");
}

//GIUSTO!!
