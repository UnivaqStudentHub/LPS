.text 

li $t0,24
bge $t0,256,fine
inizio_loop:
and $t7,$t0,1
add $t6,$t6,$t7

srl $t0,$t0,1

bnez $t0,inizio_loop


fine: