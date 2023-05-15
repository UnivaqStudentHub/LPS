/*
⁃LEGGERE da input un intero senza segno x
⁃SE x è minore di 256 
ALLORA
    ⁃CONTARE quante cifre binarie di x hanno valore 1
    ⁃STAMPARE in output il numero trovato⁃
    TERMINARE
 Scrivere un programma che soddisfa la specifica riportata sotto, 
 nei seguenti linguaggi:
 a)C99 (realizzare input/output mediante le funzioni di C Standard Library)
 b)assembly MIPS32-MARS (realizzare input/output mediante ASM-API di MARS)
 c)assemblyMC68000-ASM1
 (simulare input/output con copie da/a registro A0 verso/da altri registri)

*/

#include <stdio.h>

int main(void){
    unsigned input;
    int contatore=0;
    scanf("%i", &input);
    if(input>=256) goto fine;
inizio_loop:
    int temp;
    temp=input&1;
    contatore = contatore + temp;

    input = input>>1;

    if(input!=0) goto inizio_loop;

    printf("%i", contatore);

fine:
}