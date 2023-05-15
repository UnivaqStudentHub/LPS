#include <stdio.h>

int main(void){
    
    unsigned int A[16] = {0,1,2,3,4,5,6,7,8,7,6,5,4,3,2,1};
    unsigned int B[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    
    int i,cont,j;
    i=0;

for1_begin:
    if(i>=16) goto for1_end;
    cont = 0;
    j = 0;

for2_begin:
    if(j>=16) goto for2_end;
    if(A[j]<A[i]) cont += 1;
    j += 1;
    goto for2_begin;

for2_end:
    B[i]=cont;
    i += 1;
    goto for1_begin;

for1_end:

    return 0;
}