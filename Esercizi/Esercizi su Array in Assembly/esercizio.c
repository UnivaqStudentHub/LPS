#include <stdio.h>

int main(void)
{

    unsigned int a[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 7, 6, 5, 4, 3, 2, 1};
    unsigned int b[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    int i = 0, contatore = 0;
    for (i = 0; i < 16; i++)
    {

        int j = 0;

        for (j = 0; j < 16; j++)
        {
            if (a[i] > a[j])
            {
                contatore++;
            }
        }

        b[i] = contatore;
        contatore = 0;
    }

    for(int i = 0;i<16;i++){
        printf("%d|",a[16]);
    }

}