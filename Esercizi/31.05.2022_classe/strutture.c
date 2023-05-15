#include <stdio.h>

struct  tipo
{
    long a;
    unsigned char b,c;
    int d;
}s1={128000,'Z',250,-450},s2,*ps1,*ps2=&s2;


int main(void){
    s1.b = 'x';
    s2 = s1;
    s2.a += 96000;
    s2.c += s1.b;

    (*ps2).d *= 3;
    ps1 = ps2;
    ps1 -> a = -8800;
    ps1 = &s1;
    *ps2=*ps1;

    return 0;

}