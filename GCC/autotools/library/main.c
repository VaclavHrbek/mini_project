#include <stdio.h>
#include "s_library.h"

int main(void){
	int a = 2;
	int b = 40;
	int c = add_fun(a, b);
	printf("Output is %i. \n", c);
	return 0;
}
