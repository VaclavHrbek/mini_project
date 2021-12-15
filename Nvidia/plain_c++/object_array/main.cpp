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
		Boo() = default;
		Boo(int x) : _a(x) {};
		int value() const {
			return _a;
		}
		void print() const {
			std::cout << _a << '\n';
		}
		void add_thousand(){
			_a = _a + 1000;
		}
};

class BooArray {
	private:
		std::size_t _size;
		Boo* _arr;
	public:
		BooArray(std::size_t s) : _size(s) {
			_arr = new Boo[_size];
		};
		~BooArray(){
			delete[] _arr;
		}
		Boo& at(std::size_t indx) const {
			return _arr[indx];
		}
		std::size_t size(){
			return _size;
		}
		void fill_array(){
			for(std::size_t i = 0; i != _size; i++){
				_arr[i] = i;
			}
		}
		void add_thousand(){
			for(std::size_t i = 0; i != _size; i++){
				_arr[i].add_thousand();
			}
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
	auto arr_obj = BooArray(10000);
	arr_obj.fill_array();
	nvtxRangePop();
	nvtxRangePushA("Call function on every object in wrapper");
	arr_obj.add_thousand();
	nvtxRangePop();

	return 0;
}
