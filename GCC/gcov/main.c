#include "second_fun.c"
#include <stdio.h>

int main(void){
	int a = 10;
	int b = 16;
	for(int i = 0; i != a; ++i){
		b = add(b);
		printf("%d", b);
	}
	return 0;
}
