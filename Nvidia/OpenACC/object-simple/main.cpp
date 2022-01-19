#include <iostream>

#include "NVTX/c/include/nvtx3/nvToolsExt.h"

struct Foo {
	int a;
	int value_plus(){
		return a + 10;
	}
};

class Boo {
	private:
		int _a;
	public:
		Boo(int x) : _a(x) {
	#pragma acc enter data copyin(this)
	#pragma acc enter data create(_a)
		};
#pragma acc routine
		int value() const {
			return _a;
		}
//#pragma acc routine vector
#pragma acc routine
		int for_value() const {
			int a = 0;
#pragma acc loop 
			for(int i = 0; i != 1000; i++){
				a += i;
			}
			return a + _a;
		}
};

int main(){
	auto f = Foo{2};

	nvtxRangePushA("Initialization of class");
	auto b = Boo(42);
	nvtxRangePop();

	auto val_f = f.value_plus();
	double val_b;
	nvtxRangePushA("Call member of class");
#pragma acc parallel async
	{
		val_b = b.for_value();
	}
	nvtxRangePop();

	std::cout << "val_f = " << val_f << '\n';
	std::cout << "val_b = " << val_b << '\n';
	return 0;
}
