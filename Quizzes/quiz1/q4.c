#include <stdio.h>

int main(void) {
	int a = 5;  
	int *p;
	p = &a;
	printf("Value of p = %d\n", *p);
	*p = *p + 1;
	printf("Value of p = %d\n", *p);
	a++;

	printf("Value of a at end of program = %d\n", a);

	return 0;
}