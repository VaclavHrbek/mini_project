#include <stdio.h>

#include "c/file_1.h"
#include "c/file_2.h"

int main(void){
	printf("Z main source file\n");
	fun_c_1(2);
	fun_2();
	return 0;
}
