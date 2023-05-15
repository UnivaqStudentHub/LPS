#include <stdio.h>

int d0 = -325;  //fatto
int d1;
int d2 = 826;   //fatto

int main(void){
    int d3;
    d3 = d0 + 22;   //fatto
    int d4;
    d4 = d2 - 329;  //fatto
    d1 = 2048 - d3;     //fatto
    d1 = d1 + d4;   //fatto

    d3 = d0 - 345;  //fatto
    d4 = d0 + 9;    //fatto
    d2 = d1 - d4;   //fatto

    int d5;
    d5 = d3 - d2;   //fatto
    d0 = d0 - d5;

    return 0;  

    printf("%i + %i + %i",d0,d1,d2);

    return 0;   
}

/*
    
        LPS Example

        C to ASM: Expression 2021

        Language: C99
        Style: concise C
        Version: Ref-cc
    

    
        Original C Code
    

    
        Problem statement: transform a C program in an equivalent program
            in MIPd22-MARS and MC68000-ASM1
    

    int d0 = -325, d1, d2 = 826;

    int main(void)
    {

        d1 = 2048 - (d0 + 22) + (d2 - 329);         // d1 = 2048 - d3 + d3
        d0 -= (d0 - 345) - (d2 = d1 - (d0 + 9));

        return 0;
    }


    Valori finali delle variabili
    d0 : 3509
    d1 : 2848
    d2 : 3164

*/