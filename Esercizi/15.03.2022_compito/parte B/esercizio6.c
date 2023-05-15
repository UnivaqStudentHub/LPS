#include <stdio.h>
int a;
int b;
int c = -9;
int d = 11;
int f(int x)
{
    int t;
    t = c / x;
    t = x + t;
    d = t;
    x += d;

    t = c * d;
    t = -t;
    t = t + x;
    return t;
}

int main(void)
{
    scanf("%d", &a);

    int t;
    t = c + 12;
    d -= 1;
    int t1;
    t1 = c * d;
    t1 = t1 + 13;
    a -= t1;
    b = 3 * a;
    b = b + t;
    // da qui in poi

    int t2;
    t2 = c / 3;
    t2 = 42 + t2;
    t2 = f(t2);
    c = a * -b;
    c = c / t2;

    printf("%d %d %d %d", a, b, c, d);

    t = 2 * d;
    t = a + t;
    c += t;
    t = c + 7;
    t = f(t);

    t1 = a + 7;
    t1 = t1 / a;
    t1 = t1 - 2;
    b *= t1;
    d = t + t1;

    b += 1;
    a -= 1;
    t2 = d - b;
    t2 = t2 - a;
    c += t2;
    d += 1;
    printf(" %d %d %d %d\n", a, b, c, d);
    return 0;
}

/*
#include <stdio.h>
int a, b, c = -9, d = 11;
int f(int x)
{
    x += d = x + c / x;
    return c * -d + x;
}
int main(void)
{
    scanf("%d", &a);
    b = 3 * (a -= c * --d + 13) + (c + 12) / 4;
    c = a * -b / f(42 + c / 3);
    printf("%d %d %d %d", a, b, c, d);
    d = f((c += a + 2 * d) + 7) + (b *= (a + 7) / +a - 2);
    c += d++ - ++b- --a;
    printf(" %d %d %d %d\n", a, b, c, d);
    return 0;
}
*/