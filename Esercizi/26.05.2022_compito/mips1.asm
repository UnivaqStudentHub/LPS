.data
array1: .byte 9, 3, 0, 5, 1, 12, 19, 7
array2: .word -5, 27, 39, -9, -58, 3, 67, -2, 4, 9
#corrispondenza variabili:
# id1 ==> t0
# id2 ==> t1

.text

li $t0,1
li $t1,1

#	array1[ 3 ] += 8;
#	array1[ 3 ] = array1[ 3 ] + 8

la $t7, array1
lb $t2,3($t7)
addu $t2,$t2,8
sb $t2,3($t7)

#	array1[ 5 ] = 3 * array1[ id1 ];
lb $t2,array1($t0)
mulu $t2,$t2,3
sb $t2,5($t7)

#	array2[ 4 ] = 100 - array2[ 6 ];
la $t7,array2
lw $t2,24($t7)
sub $t2,$t2,100
sw $t2,16($t7)
#	array2[ id2 ] -= array2[ 3 ];
#	array2[id2] = array2[id2] - array2 [ 3 ]

lw $t2,12($t7)
mul $t1,$t1,4
lw $t3,array2($t1)
sub $t2,$t3,$t2
sw $t2,array2($t1)

#Array1:
#|9|3|0|13|1|9|19|7|0
#array2:
#|-5|36|39|-9|33|3|67|-2|4 | 9
