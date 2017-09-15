#include <stdlib.h>
#include <stdio.h>

int function1(char *y);

int main (void) {


	int x = function1("hello 2222");

	printf("%d\n", x);


}

int function1(char *y)
{
   int z = 0;
   while (*y++ != '\0') z++;
   return z;
}