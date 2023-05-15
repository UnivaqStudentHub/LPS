.text 
.globl main
main:
	
li $s1,-325
li $s3,826

add $t1,$s1,22		
sub $t2,$s3,329	 

li $t5,2048
sub $s2,$t5,$t1  
	
add $s2,$s2,$t2

sub $t1,$s1,345
add $t2,$s1,9
sub $s3,$s2,$t2

sub $t3,$t1,$s3	   
sub $s1,$s1,$t3

#a e t general porpuse 
