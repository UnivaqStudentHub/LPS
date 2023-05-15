#include <stdio.h>

int a;
int b = 7;
int c = -9;
int d;

int f(int x, int y)
{
    int t;
    x -= 1;
    t = x + 2;
    int t1;
    t1 = b / 2;
    y -= 1;
    int t2;
    t2 = 15 - y;
    d = t * t1;
    d = d + t2;

    int t3;
    t3 = y - d;
    int t4;
    t4 = 142 & t3;
    t4 = t4 * x;
    b += t4;
    
    int t5;
    t5=d-x;
    int t6;
    t6=4*x;
    t6=t6-t5;
    return t6;
}

int main(void)
{
    scanf("%d", &d);
    int t;
    t = c - 2;
    a = t * d;

    int t1;
    t1 = b % c;
    b = a / t1;
    b = b / d;
    f(5, a);
    printf("%d %d %d %d", a, b, c, d);

    a -= 1;
    t = f(b, 2);
    t1 = c + 7;
    int t2;
    t2 = c - 2;
    int t3;
    t3 = t1 + t2;
    d = t * t3;
    d = a + d;
    printf(" %d %d %d %d\n", a, b, c, d);

    return 0;
}

/*#include <stdio.h>

int a, b = 7, c = -9, d;
int f(int x, int y)
{
    d = (--x + 2) * (b / 2) + (15 - --y);
    b += (142 % (y - d) * x);
    return 4 * x - (d - x);
}
int main(void)
{
    scanf("%d", &d);
    a = (c - 2) * d;
    b = a / (b % c) / d;
    f(5, a);
    printf("%d %d %d %d", a, b, c, d);
    d = --a + f(b, 2) * ((c + 7) / (c - 2));
    printf(" %d %d %d %d\n", a, b, c, d);
    return 0;
}
*/