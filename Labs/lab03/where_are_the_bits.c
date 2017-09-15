// where_are_the_bits.c ... determine bit-field order
// COMP1521 Lab 03 Exercise
// Written by ...

#include <stdio.h>
#include <stdlib.h>

struct _bit_fields {
   unsigned int a : 4,
                b : 8,
                c : 20;
};

int main(void)
{
	struct _bit_fields x;

	printf("%lu\n",sizeof(x));

	printf("Memory address of x = %p\n", &x);

	x.a = 12;
	x.b = 0;
	x.c = 0;
	printf("Value of a = %u\n", x.a);
	printf("Value of b = %u\n", x.b);
	printf("Value of c = %u\n", x.c);



	unsigned int mask;
	for (int bitCount = 0; bitCount <= 32; bitCount++) {
		mask = 1u << bitCount;
		if (mask & x.a) printf("1");
		else printf("0");
	}





	return 0;
}