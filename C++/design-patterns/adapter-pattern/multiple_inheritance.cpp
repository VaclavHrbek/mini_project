#include <iostream>
#include <string>
#include <algorithm>
#include <memory>

class TargetInterface {
	public:
		virtual ~TargetInterface() = default;
		virtual std::string some_method() const {
			return "Target represent the class with client code can work just fine\n";
		}
};

class Adaptee {
	public:
		std::string some_incompatible_method() const {
			return ".eetpadA eht fo roivaheb laicepS\n";
		}
};

class Adapter : public TargetInterface, public Adaptee {
	public:
		// This takes the interface method, override it and return "good" 
		// result from class that need use that interfade.
		// So I can have any name or behavior of some class that need to use interface,
		// and make it work. 
		std::string some_method() const override {
			auto s = some_incompatible_method();
			std::reverse(s.begin(), s.end());
			return "Adapter" + s;
		}
};

template<typename T>
void client_code(T& target){
	std::cout << target->some_method();
}

int main(){
	auto t1 = std::make_unique<TargetInterface>();
	client_code(t1);

	auto t2 = std::make_unique<Adaptee>();
	std::cout << t2->some_incompatible_method();

	auto t3 = std::make_unique<Adapter>();
	client_code(t3);

	return 0;
}
