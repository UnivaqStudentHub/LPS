#include <stdio.h>
#include <math.h>

float ipotenusa;
float cateto;
float risultato;

int main(void){
    printf("Inserisci l'ipotenusa\n>>");
    scanf("%f",&ipotenusa);
    printf("Inserisci il cateto\n>>");
    scanf("%f",&cateto);
    risultato=sqrtf((ipotenusa*ipotenusa)-(cateto*cateto));
    printf("\nIl cateto misura %.2f",risultato);

    return 0;
}