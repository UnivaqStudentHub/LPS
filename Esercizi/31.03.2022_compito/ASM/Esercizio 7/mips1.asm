.text 
.globl main
main:

li $t0,-35
li $t2,6300
li $t1,-9153

sub $t0,$t0,1

sub $t3,$t0,254

li $t5,1302
sub $t4,$t5,$t1

add $t2,$t3,$t4

add $t3,$t0,27033

sub $t3,$t3,$t2

li $t5,740
sub $t4,$t5,$t1

sub $t1,$t1,1

sub $t0,$t3,$t4

sub $t3,$t2,14

add $t0,$t0,$t3