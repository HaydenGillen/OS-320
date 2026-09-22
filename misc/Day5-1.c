#include <stdio.h>
int addTwo(int x, int y);

int main(void) {
	printf("x + y = %d\n", addTwo(5, 10));
	return 0;
}

int addTwo(int x, int y){
	return x + y;
}