int d0 = 23; 
int d1 = 9;
int d2 = -11;

int main(void)
{
    //d1 = d0 + d1 + 4;
    d1 = d0 + d1;
    d1 = d1 + 4;
   
    //d2 = d1 - (14 - d0);
    d2 = 14 - d0;
    d2 = d1 - d2;

    //d0 = d1 - d2 - 15;
    d0 = d1 - d2;
    d0 = d0 - 15;
    return 0;
}

//d0 = -24
//d1 = 36
//d2 = 45