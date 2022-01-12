#include <stdio.h>

#include "c/file_1.h"
#include "cuda/cuda_header.h"

int main(void){
	printf("From main source file\n");
	c_function(2);
	cuda_function(4);
	//openacc_function(6);  // openacc_ prefix because the acc_ prefix is reserved by ACC runtime library
	return 0;
}
