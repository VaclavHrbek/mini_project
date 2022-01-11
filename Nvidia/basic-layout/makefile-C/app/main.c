#include <stdio.h>

#include "c/file_1.h"
#include "c/file_2.h"
#include "openacc/file_1.h"

int main(void){
	printf("Z main source file\n");
	fun_c_1(2);
	fun_2();

	openacc_fun_1(3);
	return 0;
}
