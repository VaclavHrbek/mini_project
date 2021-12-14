#include <array>
#include "NVTX/c/include/nvtx3/nvToolsExt.h"
#include <iostream>

const unsigned long long int LENGHT = 100000;

std::array<double, LENGHT> function(std::array<double, LENGHT>& x, std::array<double, LENGHT>& y){
	std::array<double, LENGHT> out;
	for(unsigned long long i = 0; i != LENGHT; i++){
		out.at(i) = x.at(i) + y.at(i);
	}
	return out;
}

void print(std::array<double, LENGHT>& x){
	for(unsigned long long int i = 0; i != LENGHT; i++){
		std::cout << x.at(i) << '\n';
	}
}

int main(){
	std::array<double, LENGHT> x;
	std::array<double, LENGHT> y;
	for(unsigned long long i = 0; i != LENGHT; i++){
		x.at(i) = i;
		y.at(i) = i;
	}
	nvtxRangePushA("MyFunction");
	auto arr = function(x, y);
	nvtxRangePop();
	return 0;
}
