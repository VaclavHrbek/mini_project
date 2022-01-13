#include "cuda/cuda_header.cuh"

__global__
void device_function(int* var){
	(*var)++;
}

// Wrapper around cuda kernel
void cuda_function(int var){
	int* i;
	int* d_var;
	i = (int*)malloc(sizeof(int));
	cudaMalloc(&d_var, sizeof(int));

	*i = var;

	cudaMemcpy(d_var, i, sizeof(int), cudaMemcpyHostToDevice);
	device_function<<<2, 3>>>(d_var);
	cudaMemcpy(i, d_var, sizeof(int), cudaMemcpyDeviceToHost);

	printf("From .cu file. Kernel returned: %d\n", *i);

	cudaFree(d_var);
	free(i);
}


void cuda_function_call_c_function(){
	c_function(3);
}

