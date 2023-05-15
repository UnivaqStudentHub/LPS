.text 
.globl main
main:

li $t0,23
li $t1,9
li $t2, -11

add $t1,$t0,$t1
add $t1,$t1,4

li $t3,14
sub $t2,$t3,$t0
sub $t2,$t1,$t2

sub $t0,$t1,$t2
sub $t0,$t0,15


