.text 
.globl main
main:

li $s1,4095
li $s2,41
li $s3,33

li $s6,29041
div $s5,$s6,$s1
mul $s4,$s5,$s3
add $s3,$s3,113
div $s5,$s3,3

li $s6,5
div $s5,$s6
mfhi $s3

mul $s2,$s2,52
div $s1,$s2,$s3
div $s2,$s3
mfhi $s2

