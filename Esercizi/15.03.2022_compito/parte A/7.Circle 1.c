#include <stdio.h>

#define PI 3.14159f
float raggio;

int main(void){
    printf("Inserisci il raggio del cerchio:\n>>");
    scanf("%f",&raggio);
    printf("\tCirconferenza: %.2f",2*PI*raggio);
    printf("\n\tArea: %.2f",PI*raggio*raggio);

    return 0;
}