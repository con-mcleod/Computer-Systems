#include <stdlib.h>
#include <stdio.h>

int main (int argc, char *argv[]) {
	
	double *p = 0x00;

	printf("loc of p %p\n", p);
	printf("Size of double: %lu\n", sizeof(p));

	p += 2;

	printf("Location of p: %p\n", p);


}