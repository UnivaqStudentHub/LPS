#include <stdio.h>

int a;
int b = 10;
int c;
int d;
int main(void)
{
    scanf("%d%d", &a, &d);
    c = 5;

    int t;
    t = a + 7;
    int t1;
    t1 = 13 - d;
    a = t / t1;

    int r;
    int r1;
    r = a + 2;
    r1 = c % 3;
    printf("%d %d", r, r1);

    t = b * 4;
    t1 = d - 4;
    t1 = t1 - a; // b = t - c * t1; prima le moltiplicazioni
    c = d;
    b = c * t1;
    b = t - b;
    d = -c;
    printf(" %d %d %d %d\n", a, b, c, d);
    return 0;
}

/*
int a, b = 10, c, d;
int main(void)
{
    scanf("%d%d", &a, &d);
    c = 5;
    a = (a + 7) / (13 - d);
    printf("%d %d", a + 2, c % 3);
    b = (b * 4) - (c = d) * (d - 4 + -a);
    d = -c;
    printf(" %d %d %d %d¥n", a, b, c, d);
    return 0;
}
*/