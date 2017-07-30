#include <stdio.h>

int main(void)
{
	int a[10];

	printf("Size of int: %lu\n", sizeof(int));

	int *p;
	p = &a[0];
	
	printf("%p\n", &a[0]);
	printf("%p\n", &a[2]);

	return 0;
}