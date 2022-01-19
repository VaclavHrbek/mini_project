#include <iostream>

void function(int* b){
#pragma acc parallel copy(b)
	{
	*b = 123;
	}
}

int main(){

	int* a;
	int b = 42;
	a = &b;
#pragma acc enter data create(b)
#pragma acc data present(a)
#pragma acc parallel
	{
		*a = 82;
	}
#pragma acc update self(a)

	std::cout << "Value is: " << *a << '\n';

	*a = 42;
	std::cout << "Value is: " << *a << '\n';
function(a);
#pragma acc update host(a)

	std::cout << "Value is: " << *a << '\n';

	return 0;
}
