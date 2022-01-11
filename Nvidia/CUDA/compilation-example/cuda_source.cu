#include "cuda_header.h"

__global__
void cuda_function(int* var){
	(*var)++;
}

extern "C"
void function(int var){
	int* i;
	int* d_var;
	i = (int*)malloc(sizeof(int));
	cudaMalloc(&d_var, sizeof(int));

	*i = var;

	cudaMemcpy(d_var, i, sizeof(int), cudaMemcpyHostToDevice);
	cuda_function<<<1, 1>>>(d_var);
	cudaMemcpy(i, d_var, sizeof(int), cudaMemcpyDeviceToHost);

	printf("Number from the kernel: %d\n", *i);

	cudaFree(d_var);
	free(i);
}

