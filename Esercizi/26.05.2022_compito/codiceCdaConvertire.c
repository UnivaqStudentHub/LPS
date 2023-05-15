/*
	LPS Exercise

	ASM-Arrays Exercise Statement

	Language: C99
 	Style: plain C
 	Version: Statement-pc
 */

/*
	Tradurre questo programma C99 in ASM MC68000 e in ASM MIPS32
 */

#include <stdio.h>

#define N 10

int main(void) {

	unsigned char array1[ 8 ] = { 9, 3, 0, 5, 1, 12, 19, 7 };
	long int array2[ N ] = { -5, 27, 39, -9, -58, 3, 67, -2, 4, 9 }, id1, id2;

	array1[ 3 ] += 8;

	scanf( "%ld", &id1 );

	array1[ 5 ] = 3 * array1[ id1 ];

	printf( "%hhx %hhx\n", array1[ 3 ], array1[ 5 ] );

	array2[ 4 ] = 100 - array2[ 6 ];

	scanf( "%ld", &id2 );
	
	array2[ id2 ] -= array2[ 3 ];

	printf( "%lx %lx\n", array2[ 4 ], array2[ id2 ] );

	return 0;
}
