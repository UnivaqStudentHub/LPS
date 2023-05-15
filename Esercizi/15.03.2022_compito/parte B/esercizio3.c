#include <stdio.h>
int a = 21;
int b = -3;
int c;
int d;
int main(void)
{
    scanf("%d", &d);
    c = a;
    d-=1;
    int t;
    t = 3 * d;
    t = t + 4;
    t = b - t;
    c += t;
    int t1;
    t1 = c + d;
    t1 = t1 / 2;
    printf("%d ", t1);

    t = d + a;
    a = b + t;
    b+=1;

    a /= d;
    c-=1;
    t1 = c * a;
    b -= t1;

    a-=1;
    d=c-a;
    c-=1;
    printf("%d %d %d %d\n", a, b, c, d);
    return 0;
}

/*
#include <stdio.h>
int a = 21, b = -3, c, d;
int main(void)
{
    scanf("%d", &d);
    c = a;
    d--;
    c += b - (3 * d + 4);
    printf("%d ", (c + d) / 2);
    a = b++ * (d + a);
    b -= --c * (a /= d);
    d = c-- -- -a;
    printf("%d %d %d %d\n", a, b, c, d);
    return 0;
}
*/