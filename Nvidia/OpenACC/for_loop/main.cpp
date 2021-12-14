#include <array>
#include "NVTX/c/include/nvtx3/nvToolsExt.h"
#include <iostream>

#define LENGHT 100000

std::array<double, LENGHT> function(std::array<double, LENGHT>& x, std::array<double, LENGHT>& y){
	std::array<double, LENGHT> out;
#pragma acc data copyout(out)
#pragma acc parallel vector_length(32)
	{
#pragma acc loop gang worker vector
		for(int i = 0; i != LENGHT; i++){
			out.at(i) = x.at(i) + y.at(i);
		}
	}
return out;
}

void print(std::array<double, LENGHT>& x){
	for(int i = 0; i != LENGHT; i++){
		std::cout << x.at(i) << '\n';
	}
}

int main(){
	std::array<double, LENGHT> x;
	std::array<double, LENGHT> y;
#pragma acc data copyin(x, y)
	for(int i = 0; i != LENGHT; i++){
		x.at(i) = i;
		y.at(i) = i;
	}
	nvtxRangePushA("MyFunction");

	auto arr = function(x, y);

	nvtxRangePop();
	return 0;
}
