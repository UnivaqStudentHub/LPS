// nome delle variabili uguale ai registri m68k
// usare registri formato word

int d0 = -35; 
int d1;
int d2 = 6300;
int main(void)
{
    d1 = -9153;

    //d2 = (--d0 - 254) + (1302 - d1);
    int d3;
    d0 = d0 - 1;    //fatto
    d3 = d0 - 254;      //fatto
    int d4;
    d4 = 1302 - d1;     //fatto
    d2 = d3 + d4;       //fatto

    //d0 = (d0 + 27033 - d2) - (740 - d1--) + (d2 - 14);
    d3 = d0 + 27033;    //fatto
    d3 = d3 - d2;       //fatto

    d4 = 740 - d1;      //fatto
    d1 = d1 - 1;        //fatto

    d0 = d3 - d4;       //fatto
    d3 = d2 - 14;       //fatto
    d0 = d0 + d3;    //fatto

    return 0;
}

// d0 = 17090
// d1 = -9154
// d2 = 10165