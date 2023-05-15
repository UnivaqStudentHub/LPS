*-----------------------------------------------------------
* Title      :
* Written by :
* Date       :
* Description:
*-----------------------------------------------------------
    ORG    $4000
;    unsigned int A[16] = {0,1,2,3,4,5,6,7,8,7,6,5,4,3,2,1};
;    unsigned int B[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

A: dc.l 0,1,2,3,4,5,6,7,8,7,6,5,4,3,2,1
B: dc.l 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

    ORG    $1000
START:

;    int i,cont,j;
;    i=0;
    
; i ==> d0
; cont ==> d1
; j ==> d2

    move.l #1,d0



for1_begin:
    cmp.l #16,d0
;    if(i>=16) goto for1_end;
    bge for1_end
;    cont = 0;
    move.l #0,d1
;    j = 0;
    move.l #0,d2

for2_begin:
    cmp.l #16,d2
;    if(j>=16) goto for2_end;
    bge for2_end
    
;    if(A[j]<A[i]) cont += 1;

    
;    j += 1;
;    goto for2_begin;
    bra for2_begin

for2_end:
;    B[i]=cont;
;    i += 1;
;    goto for1_begin;

for1_end:

    END
*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
