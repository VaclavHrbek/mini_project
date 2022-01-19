#include <iostream>

int main(){

	int b = 42;
#pragma acc enter data create(b)
#pragma acc data present(b)
#pragma acc parallel
	{
		b = 82;
	}
#pragma acc update self(b)

	std::cout << "Value is: " << b << '\n';

	b = 42;
	std::cout << "Value is: " << b << '\n';
#pragma acc update self(b)

	std::cout << "Value is: " << b << '\n';

	return 0;
}
