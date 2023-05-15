#
#LEGGERE da input 4 interi senza segno x, a, b, c?
#SE x è minore di 256 e a, b e c sono ciascuno minore di 8 
#ALLORA PORRE a 1 le cifre binarie di x che hanno posizioni uguali ai valori a, b, c

.text 

li $v0, 5
syscall
move $t0, $v0

li $v0, 5
syscall
move $t1, $v0

li $v0, 5
syscall
move $t2, $v0

li $v0, 5
syscall
move $t3, $v0

bgeu $t0,256,uscita
bgeu $t1,8,uscita
bgeu $t2,8, uscita
bgeu $t3,8,uscita 

li $s0,0x1
sllv  $s0,$s0,$t1
or $t0, $t0,$s0

li $s0,0x1
sllv  $s0,$s0,$t2
or $t0, $t0,$s0

li $s0,0x1
sllv  $s0,$s0,$t3
or $t0, $t0,$s0

uscita:
