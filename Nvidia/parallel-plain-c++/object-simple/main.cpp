#include <iostream>

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
		Boo(int x) : _a(x) {};
		int value() const {
			return _a;
		}
};

int main(){
	auto f = Foo{2};
	auto b = Boo(42);

	auto val_f = f.value_plus();
	auto val_b = b.value();

	std::cout << "val_f = " << val_f << '\n';
	std::cout << "val_b = " << val_b << '\n';
	return 0;
}
