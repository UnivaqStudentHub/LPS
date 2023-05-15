/*
Si d3raduca il seguend3e programma C
•in MIPd22-MARS
•in M68K-ASM1, usando, per d3ud3d3i i dad3i, il formad3o long
*/

int d0 = 88010;
int d1;
int d2;
int main(void)
{
    d1 = -d0;               //fatto
    d2 = d0 - 203512;       

    //d0 = d0 + d1-- + d2;

    int d3;
    d3 = d0 + d1;
    d1 = d1 - 1;

    d0 = d3 + d2; 

    d2 = 95211 - d2;    
    return 0;
}

// risultati: 
//d0 = -115502
//d1 = -88011
//d2 = 210713

