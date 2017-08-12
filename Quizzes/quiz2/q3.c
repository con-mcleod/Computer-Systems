#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
	unsigned int A = 0x55;
	unsigned int B = 0xAA;

	printf("Result = %u", (A^B)^B);
}