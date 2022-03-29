#include <stdio.h>
#include <time.h>

#include <cuda.h>
#include <curand.h>

__global__
void foo_kernel(int* a, int* b, size_t* size){
	int id = blockDim.x * blockIdx.x + threadIdx.x;
	if(id < *size){
		//a[id] = b[id];
	}
}

int main(void){
	size_t size = 10;
	size_t* ptr_size;
	int* a = (int*)(malloc(sizeof(int)*size));
	int* b = (int*)(malloc(sizeof(int)*size));
	int* d_a;
	int* d_b;
	cudaMalloc(&d_a, (sizeof(int)*size));
	cudaMalloc(&d_b, (sizeof(int)*size));
	cudaMalloc(&ptr_size, (sizeof(size_t)));
	for(size_t i = 0; i != size; ++i){
		b[i] = i;
	}
	cudaMemcpy(d_b, b, sizeof(int)*size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_a, a, sizeof(int)*size, cudaMemcpyHostToDevice);
	cudaMemcpy(ptr_size, &size, sizeof(size_t), cudaMemcpyHostToDevice);

	// create generation type
	curandGenerator_t gen;
	// create generator
	curandCreateGenerator(&gen, CURAND_RNG_PSEUDO_DEFAULT);
	// seed the generator
	curandSetPseudoRandomGeneratorSeed(gen, time(NULL));
	// generate numbers (Generate 32-bit pseudo or quasirandom numbers)
	// generate numbers on device
	curandGenerate(gen, (uint*)d_a, size);

	foo_kernel<<<1,1024>>>(d_a, d_b, ptr_size);
	cudaMemcpy(a, d_a, sizeof(int)*size, cudaMemcpyDeviceToHost);
	
	// error checking
	int err;
	for(size_t i = 0; i != size; ++i){
		err += a[i] - i;
		printf("%i\n", a[i]);
	}
	if(err != 0){
		printf("The computation is wrong\n");
	}
	else{
		printf("The computation is success\n");
	}
	cudaFree(d_a);
	cudaFree(d_b);
	free(a);
	free(b);
	cudaFree(ptr_size);
}

