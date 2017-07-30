#include <stdio.h>

int f(int n);

int main(void) {

	int a = 4;
	printf("%d", f(a));
	return 0;
}

int f(int n) {
	if (n == 0) return 0;
	else return n + f(n-1);
}