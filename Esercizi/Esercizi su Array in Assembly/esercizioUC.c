int main(void)
{
    unsigned int a[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    unsigned int b[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    int i = 0;
    int contatore = 0;
    int j = 0;

inizio_for:
    if (i == 16)
        goto fine_for;
            i = 0;
            j = 0;
            inizio_for_annidato:
                if(j==16) goto fine_for_annidato;
                if(a[i]>a[j]) contatore = contatore + 1;
                j = j + 1;
                goto inizio_for_annidato;
            fine_for_annidato:
        b[i] = contatore;
    i = i + 1;
    contatore = 0;
    goto inizio_for;
fine_for:


    for(int i = 0;i<16;i++){
        printf("%d|",a[16]);
    }

}