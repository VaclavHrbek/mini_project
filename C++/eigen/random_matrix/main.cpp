#include <Eigen/Dense>
#include <iostream>

int main(){
	Eigen::MatrixXf m(10,2);
	m.setRandom();
	std::cout << m << std::endl;
	return 0;
}
