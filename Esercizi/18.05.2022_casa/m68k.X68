*-----------------------------------------------------------
* Title      :
* Written by :
* Date       :
* Description:
*-----------------------------------------------------------
    ORG $4000    
    
a: dc.l 7
b: dc.l -5
p_si: dc.l 0
g: dc.w 0
h: dc.w 0
k: dc.w 43
p1_ss: dc.l 0
p2_ss: dc.l g
x: dc.b 0
y: dc.b 31
z: dc.b 99
p1_uc dc.l 0
p2_uc dc.l 0


    ORG    $1000
START:
    
    ; p_si=&b; 
    move.l #b,p_si
    ; *p_si+=1;  *p_s1 = *p_si + 1
    
    move.l p_si,a0
    add.l #1,(a0)
    
    ; a = a - (*p_si);
    
    move.l (a0),d0
    sub.l d0,a
    
    ; p1_ss = &k;
    move.l #k,p1_ss
    
    ; *p2_ss=*p1_ss;
    move.l p2_ss,a0
    move.l p1_ss,a1
    move.l (a1),(a0)
    
    ; p1_ss = &h;
    
    move.l #h,p1_ss
    
    ; *p1_ss = k - 3;
    
    move.w k,d0
    sub.w #3,d0
    move.l d0,(a1)
    
    ; p1_uc = &x;
    
    move.l #x,p1_uc
    
    ; p2_uc = &y;
    
    move.l #y,p2_uc
    
    ; *p2_uc = *p2_uc + 4;
    
    move.l p2_uc,a2
    add.b #4,(a2)
    
    ; *p1_uc = z + 1;
    
    move.l p1_uc,a3
    move.b z,d0
    add.b #1,d0
    move.b d0,(a3)
    
    ; p2_uc = p1_uc;
    
    move.l p1_uc,p2_uc
    
    ; *p1_uc = *p1_uc - y;
    
    move.b y,d0
    sub.b d0,(a3) 
    
    ; *p2_uc = *p2_uc + 5;
    
    add.b #5,(a3)

    END