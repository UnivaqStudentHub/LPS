.data 
a: 	.word 7
b: 	.word -5
p_si: 	.word 0
g:	.half 0
h:	.half 0
k:	.half 43
p1_ss:	.half 0
p2_ss:	.half g
x:	.byte 0
y:	.byte 31
z:	.byte 99
pi_uc:	.byte 0
p2_uc:	.byte 0

.text

#    p_si=&b;
	la $t0,b
	sw $t0,p_si
#    *p_si+=1;	==> *p_si = *p_si + 1
	la $s0,p_si
	lw $t0,($s0)
	add $t0,$t0,1
	sw $t0,($s0)
#    a = a - (*p_si);.
	lw $s0,a
	lw $s1,p_si
	
	
	
	sub $t1,$t1,$t2
	sw $t1,($s0)
#    p1_ss = &k;
	la $s0,k
	sw $s0,p1_ss
#    *p2_ss=*p1_ss;
	
#    p1_ss = &h;
#    *p1_ss = k - 3;
#    p1_uc = &x;
#    p2_uc = &y;
#    *p2_uc = *p2_uc + 4;
#    *p1_uc = z + 1;
#    p2_uc = p1_uc;
#    *p1_uc = *p1_uc - y;
#    *p2_uc = *p2_uc + 5;
