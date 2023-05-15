#include <stdio.h>

// variabili cambiate per m68k

int d0 = 4095;
int d1 = 41;
int d2 = 33;
int d3;
int d4;

int main(void){

// part 1: computes two quotients and a product

	d4 = 29041 / d0;	//fatto
	d3 = d4 * d2;		//fatto
	d2 = d2 + 113;		//fatto
	d4 = d2 / 3;	//fatto

// part 2: computes reminder

	d2 = d4 % 5;
	
// part 3: computes both quotient and reminder of a product
	d1 = d1 * 52;
	d0 = d1 / d2;
	d1 = d1 % d2;

}


/*

	LPS Example

	C to ASM: Expression 2022

	Language: C99
 	Style: unstructured C
 	Version: Ref-uc
 


    Original C Code

	Problem statement: transform a C program in an equivalent program
		in MIPd22-MARS and MC68000-ASM1



	Important point: in this example, all variables should have non-negative values


int d0 = 4095, d1 = 41, d2 = 33, d3, d4;

int main( void ) {

// part 1: computes two quotients and a product
	d4 = 29041 / d0;
	d3 = d4 * d2;
	d2 += 113;
	d4 = d2 / 3;

// part 2: computes reminder
	d2 = d4 % 5;

// part 3: computes both quotient and reminder of a product
	d1 *= 52;
	d0 = d1 / d2;
	d1 = d1 % d2;

	return 0;
}

Final values of the variables
d0 : 710
d1 : 2
d2 : 3
d3 : 231
d4 : 48

*/
