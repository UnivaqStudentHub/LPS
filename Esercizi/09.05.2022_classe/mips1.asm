
#long 32 bit
.eqv var_v, 0x10011000
.eqv var_w, 0x10011004

#short signed - unsigned
.eqv var_x, 0x10011008
.eqv var_y, 0x1001100a
.eqv var_z, 0x1001100c
.eqv var_h, 0x1001100e
.eqv var_k, 0x10011010
.eqv var_m, 0x10011012

#signed char 
.eqv var_a, 0x10011014
.eqv var_b, 0x10011015
.eqv var_c, 0x10011016


.text 
inizio_codice:

	li $t0, 'A'
	sb $t0, var_b	#store byte

	li &t0, -43
	sb $t0, var_c
	
	li $t0, 450
	sh $t0, var_x

	li $t0, 98
	sh $t0, var_z
	
	li $t0, 22020
	sw $t0, var_w
	
	li $t0, 600
	sh $t0, var_k
	
	li $t0, 12
	sh $t0, var_m
	
	lb $t0, var_b
	lb $t1, var_c
	
	add $t0, $t0, $t1
	sb $t0, var_a
	
	lhu $t0, var_x
	lhu $t1, var_z
	
	multu $t0,$t1
	mflo $t0
	addu $t0,$t0,2300
	sh $t0,var_y
	
	lb $t0, var_a
	lh $t1, var_k
	mult $t0,$t1
	mflo $t1
	lh $t0, var_m
	add $t0,$t0,$t1
	sh $t0, var_h
	
	lw $t1, var_w
	sub $t1, $t1, 160900
	sub $t1, $t1, $t0
	sw $t1, var_v
	
	li $t0, 780
	sh $t0, var_h
	
	li $t1, -24078
	lh $t2, var_m
	div $t1, $t2
	mfhi $t1
	sll $t0, $t0, 2
	add $t1,$t1,$t0
	sh $t1,var_k
	
	fine_codice:







