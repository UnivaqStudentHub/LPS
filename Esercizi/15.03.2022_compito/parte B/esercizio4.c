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
    int t2;
    t2 = 15 - -y;
    d = t * t1;
    d = d + t2;

    int t3;
    t3 = 142 % y;
    int t4;
    t4 = d * x;
    t3 = t3 - t4;
    b += t3;

    int t4;
    t4 = 4 * x;
    t4 = t4 - d;
    t4 = t4 - x;
    return t4;
}
int main(void)
{
    scanf("%d", &d);
    a = 2 * d;
    a = c - a;

    b = a / b;
    b = b % c;
    b = b / d;

    f(5, a);
    printf("%d %d %d %d", a, b, c, d);

    int t;
    t = 7 / c;
    t = c + t;
    t = t - 2;
    int t1;
    t1 = f(b, 2);
    d = t1 * t;
    d = -a + d;

    printf(" %d %d %d %d\n", a, b, c, d);
    return 0;
}

/*
#include <stdio.h>
int a, b = 7, c = -9, d;
int f(int x, int y)
{
    d = (--x + 2) * (b / 2) + (15 - -y);
    b += (142 % y - d * x);
    return 4 * x - d - x;
}
int main(void)
{
    scanf("%d", &d);
    a = c - 2 * d;
    b = a / b % c / d;
    f(5, a);
    printf("%d %d %d %d", a, b, c, d);
    d = -a + f(b, 2) * (c + 7 / c - 2);
    printf(" %d %d %d %d¥n", a, b, c, d);
    return 0;
}
*/