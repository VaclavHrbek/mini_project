#include <vector>
#include "NVTX/c/include/nvtx3/nvToolsExt.h"
#include <iostream>

const unsigned long long int LENGHT = 100000;

std::vector<double> function(std::vector<double>& x, std::vector<double>& y){
	std::vector<double> out;
	for(unsigned long long i = 0; i != LENGHT; i++){
		out.push_back(x.at(i) + y.at(i));
	}
	return out;
}

void print(std::vector<double>& x){
	for(unsigned long long int i = 0; i != LENGHT; i++){
		std::cout << x.at(i) << '\n';
	}
}

int main(){
	std::vector<double> x;
	std::vector<double> y;
	for(unsigned long long i = 0; i != LENGHT; i++){
		x.push_back(i);
		y.push_back(i);
	}
	nvtxRangePushA("MyFunction");
	auto arr = function(x, y);
	nvtxRangePop();
	return 0;
}
