*-----------------------------------------------------------
* Title      :
* Written by :
* Date       :
* Description:
*-----------------------------------------------------------
v   equ $00002800
w   equ $00002804
    
x   equ $00002810
y   equ $00002812
z   equ $00002814
h   equ $00002816
k   equ $00002818
m   equ $0000281a
   
a   equ $0000281c
b   equ $0000281d
c   equ $0000281e
        
    ORG    $2000
    
inizio_codice:
    
    move.b	#'A',b
	move.b	#-43,c
	move.w	#450,x
	move.w	#98,z

	move.l	#220200,w

	move.w	#600,k
	move.w	#12,m

	move.b	b,d0
	add.b	c,d0
	move.b	d0,a

	move.w	z,d0
	mulu	x,d0
	add.w	#2300,d0
	move.w	d0,y

	move.b	a,d0
	ext.w	d0
	muls	k,d0
	add.w	m,d0
	move.w	d0,h
    
    move.l w,v
    sub.l #160900, v 
    ext.l d0
    sub.l d0,v
    
    move.w #780,h
    
    move.l #-24078, d0
    divs m,d0
    swap d0
    move.w h,d1
    asl.w #2,d1
    add.w d1,d0
    move.w d0,k
    


*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
