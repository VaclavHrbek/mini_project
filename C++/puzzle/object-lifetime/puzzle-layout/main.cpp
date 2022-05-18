
#include <iostream>
#include <string>

class S {
	public:
		std::string _a;
		std::string _b;
			S(std::string a, std::string b): _a(a), _b(b) {
				std::cout << _a;
			};
		~S(){
			std::cout << _b;
		}
};

void run(){
}

int main(){
	run();
}
