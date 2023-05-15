*-----------------------------------------------------------
* Title      :
* Written by :
* Date       :
* Description:
*-----------------------------------------------------------
N: equ 10
    ORG $4000
*   #define N 10
*	unsigned char array1[ 8 ] = { 9, 3, 0, 5, 1, 12, 19, 7 };
*	long int array2[ N ] = { -5, 27, 39, -9, -58, 3, 67, -2, 4, 9 }, id1, id2;
array1: dc.b  9, 3, 0, 5, 1, 12, 19, 7 
array2: dc.l -5, 27, 39, -9, -58, 3, 67, -2, 4, 9

* definizione variabili
* id1 ==> d0
* id2 ==> d1
    ORG $1000
    
    move #1,d0
    move #1,d1

*	array1[ 3 ] += 8;
*   array1[ 3 ] = array1[ 3 ] + 8
    move.l #array1,a0
    move.b 3(a0),d2
    add.b #8,d2
    move.b d2,3(a0)

*	array1[ 5 ] = 3 * array1[ id1 ];
 
    move.b (a0,d0),d2
    mulu #3,d2
    move.b d2,5(a0)

*	array2[ 4 ] = 100 - array2[ 6 ];
    
    move.l #array2,a1
    move.l 24(a1),d2
    move.l #100,d3
    sub.l  d2,d3
    move.l d3,24(a1)
	
*	array2[ id2 ] -= array2[ 3 ];
*   array2[id2] = array2[id2] - array2[ 3 ];

    muls #4,d1
    move.l (a1,d1),d2
    move.l 12(a1),d3
    sub.l d3,d2
    move.l d2,(a1,d1)
    
*Array1:
*|9|3|0|13|1|9|19|7|0
*array2:
*|-5|36|39|-9|33|3|67|-2|4 | 9

    END
