#include <Eigen/Dense>
#include <iostream>

int main(){
	Eigen::MatrixXf m(2,2);
	m(0,0) = 2;
	m(0,1) = 3;
	m(1,0) = 4;
	m(1,1) = 5;
	std::cout << m << std::endl;
	return 0;
}
