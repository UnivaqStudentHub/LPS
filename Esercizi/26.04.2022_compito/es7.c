/*
LEGGERE da input 4 interi senza segno x, a, b, c⁃
SE x è minore di 256 e a, b e c sono ciascuno minore di 8 
ALLORA PORRE a 1 le cifre binarie di x che hanno posizioni uguali ai valori a, b, c
*/

#include <stdio.h>

int main(void){
    unsigned int x, a, b, c;
    scanf("%i %i %i %i", &x, &a, &b, &c);
    if(x<256&&a<8&&b<8&&c<8){
        int maschera=1;
        maschera=maschera<<a;
        x = x|maschera;

        maschera=1;
        maschera=maschera<<b;
        x = x|maschera;

        maschera=1;
        maschera=maschera<<c;
        x = x|maschera;
    }
}