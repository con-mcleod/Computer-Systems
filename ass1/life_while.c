#include <stdio.h>
#include <stdlib.h>

#include "board1.h"

int neighbours(int, int);
void copyBackAndShow();

int main(void) {
		int maxiters;
		printf("# Iterations: ");
		scanf("%d", &maxiters);
		int n = 1;
		while (n <= maxiters) {
				int i = 0;
				while (i < N) {
						int j = 0;
						while (j < N) {
								int nn = neighbours(i,j);
								if (board[i][j] == 1) {
										if (nn < 2) newboard[i][j] = 0;
										else if (nn == 2 || nn == 3) newboard[i][j] = 1;
										else newboard[i][j] = 0;
								}
								else if (nn == 3) newboard[i][j] = 1;
								else newboard[i][j] = 0;
								j++;
						}
						i++;
				}
				printf("=== After iteration %d ===\n", n);
				n++;
				copyBackAndShow();
				
		}
		return 0;
}

int neighbours(int i, int j) {
		int nn = 0;
		int x = -1;
		while (x <= 1) {
				int y = -1;
				while(y <= 1) {
						if (i+x < 0 || i+x > N-1) {
							y++;
							continue;
						}
						if (j+y < 0 || j+y > N-1) {
							y++;
							continue;
						}
						if (x == 0 && y == 0) {
							y++;
							continue;
						}
						if (board[i+x][j+y] == 1) {
							nn++;
							y++;
						}
				}
				x++;
		}
		return nn;
}

void copyBackAndShow() {
		int i = 0;
		while (i < N) {
				int j = 0;
				while (j < N) {
						board[i][j] = newboard[i][j];
						if (board[i][j] == 0)
								putchar('.');
						else
								putchar('#');
						j++;
				}
				putchar('\n');
				i++;
		}
}