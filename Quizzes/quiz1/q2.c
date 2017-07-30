#include <stdio.h>

int main(void) {

	int i;
	int loopCount = 0;

	char *str = "Hello";

	for (i = 0; str[i] != '\0'; i++) {
		loopCount += 1;
		putchar(str[i]);
		printf("\nLoop Count: %d\n", loopCount);
	}

	printf("\nOne more check is made to see if we are at the null "
				"terminator so Loop Count = 6");

}