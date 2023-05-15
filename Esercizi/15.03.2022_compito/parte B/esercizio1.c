#include <stdio.h>
int a;
int b = 10;
int c;
int d;

int main(void)
{
    c = b - 5;
    scanf("%d", &d);
    b *= 3;

    int t;
    t = d - 20;
    a = t / c;
    a -= 2;

    t = b - 13;
    int t1;
    t1 = d % 4;
    c = t - t1;

    printf("%d %d %d %d\n", a, b, c, d);
    return 0;
}



/*
int a, b = 10, c, d;
int main(void)
{
    c = b - 5;
    scanf("%d", &d);
    b *= 3;
    a = (d - 20) / c - 2;
    c = (b - 13) - (d % 4);
    printf("%d %d %d %d\n", a, b, c, d);
    return 0;
}
*/