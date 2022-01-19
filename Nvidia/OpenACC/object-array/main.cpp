#include <iostream>
#include <array>

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
		Boo() {
		};
#pragma acc routine seq
		Boo(int x) : _a(x) {
		};
		~Boo(){
		}
		int value() const {
			return _a;
		}
		void print() const {
			std::cout << _a << '\n';
		}
#pragma acc routine seq
		void add_thousand(){
			_a = _a + 1000;
		}
};

class BooArray {
	private:
		std::size_t _size;
		Boo* _arr; public: BooArray(std::size_t s) : _size(s) { _arr = new Boo[_size]; #pragma acc enter data copyin (this) #pragma acc enter data create(_arr[0:_size])
		};

		BooArray(const BooArray& obj) :  _size(obj._size) {
			std::cout << "Copy constructor called" << '\n';
			_arr = new Boo[_size];
			for(std::size_t i = 0; i != 0; i++){
				_arr[i] = obj._arr[i];
			}
#pragma acc enter data copyin (this)
#pragma acc enter data create(_arr[0:_size])
		}

		Boo& at(std::size_t indx) const {
			return _arr[indx];
		}

		std::size_t size(){
			return _size;
		}

		void fill_array(){
#pragma acc parallel loop
			for(std::size_t i = 0; i != _size; i++){
				_arr[i] = Boo(i);
			}
#pragma acc update self(_arr[0:_size])
		}

		void add_thousand(){
#pragma acc parallel loop gang, vector_length(32) 
				for(std::size_t i = 0; i != _size; i++){
					_arr[i].add_thousand();
				}
#pragma acc update self(_arr[0:_size])
		}

};

Boo* create_Boo_array(std::size_t size){
	auto arr = new Boo[size];
	for(std::size_t i = 0; i != size; i++){
		arr[i] = Boo(i);
	}
	return arr;
}

template<typename T>
void print_Boo_array(const T& arr, std::size_t size){
	for(std::size_t i = 0; i != size; i++){
		arr[i].print();
	}
}

int main(){
	nvtxRangePushA("Create array of object from a function");
	auto arr = create_Boo_array(10000);
	nvtxRangePop();
	nvtxRangePushA("Create array of object from a wrapper");
	auto arr_obj = BooArray(10000000);
	arr_obj.fill_array();
	nvtxRangePop();
	nvtxRangePushA("Call function on every object in wrapper");
	arr_obj.add_thousand();
	nvtxRangePop();
	auto arr_obj_2 = arr_obj;
	arr_obj_2.fill_array();
	nvtxRangePushA("Call function on every object in copy of wrapper");
	arr_obj_2.add_thousand();
	std::cout << "VAlue : " << arr_obj_2.at(90).value() << '\n';
	nvtxRangePop();


	return 0;
}
