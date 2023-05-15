#include <stdio.h>

    int a = 7, b = -5, *p_si;
    short g, h, k = 43, *p1_ss, *p2_ss = &g;
    unsigned char x, y = 31, z = 99, *p1_uc, *p2_uc;

int main(void)
{
    p_si=&b; 
    *p_si+=1;   
    a = a - (*p_si);
    p1_ss = &k;
    *p2_ss=*p1_ss;
    p1_ss = &h;
    *p1_ss = k - 3;
    p1_uc = &x;
    p2_uc = &y;
    *p2_uc = *p2_uc + 4;
    *p1_uc = z + 1;
    p2_uc = p1_uc;
    *p1_uc = *p1_uc - y;
    *p2_uc = *p2_uc + 5;

}