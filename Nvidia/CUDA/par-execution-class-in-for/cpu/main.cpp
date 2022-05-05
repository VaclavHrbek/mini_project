#include <vector>
#include <execution>
#include <iostream>
#include <algorithm>

class Data {
	int _val;
	public:
	Data(int a) : _val(a) {}
	void plus_one() {
		_val += 1;
	};
	int val(){
		return _val;
	}
};

int main(){
	std::vector<Data> vec;
	for(size_t i = 0; i != 10; i++){
		vec.emplace_back(Data(i));	
	}
	for(auto i : vec){
		std::cout << i.val() << '\n';
	}
	std::for_each(std::execution::par, vec.begin(), vec.end(), [](auto &x){x.plus_one();});
	std::for_each(vec.begin(), vec.end(), [](auto x){std::cout << x.val();});
	return 0;
}
