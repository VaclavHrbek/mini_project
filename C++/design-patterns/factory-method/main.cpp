#include <iostream>
#include <memory>

/*
 * The Product declares the interface, which is common to all objects that can be produced by the creator and its subclasses.
*/
struct ConcreteInterface {
	virtual int value() = 0;
	virtual ~ConcreteInterface(){};
};
/*
 * Concrete Products are different implementations of the product interface.
*/
struct ConcreteClassA : ConcreteInterface {
	int a;
	int value(){return a;}
};

struct ConcreteClassB : ConcreteInterface {
	int a;
	int value(){return a;}
};

/*
 *

The Creator class declares the factory method that returns new product objects. It’s important that the return type of this method matches the product interface.

You can declare the factory method as abstract to force all subclasses to implement their own versions of the method. As an alternative, the base factory method can return some default product type.

Note, despite its name, product creation is not the primary responsibility of the creator. Usually, the creator class already has some core business logic related to products. The factory method helps to decouple this logic from the concrete product classes. Here is an analogy: a large software development company can have a training department for programmers. However, the primary function of the company as a whole is still writing code, not producing programmers.

*/

struct Creator {
	virtual std::unique_ptr<ConcreteInterface> factory_method() const = 0;
	virtual ~Creator(){};
/**
   * Also note that, despite its name, the Creator's primary responsibility is
   * not creating products. Usually, it contains some core business logic that
   * relies on Product objects, returned by the factory method. Subclasses can
   * indirectly change that business logic by overriding the factory method and
   * returning a different type of product from it.
   */

	void some_operation() const {
		std::unique_ptr<ConcreteInterface> product = factory_method();
		std::cout << "Creation of concrete product\n";

	}

};

struct ConcreteCreator1 : public Creator {
	std::unique_ptr<ConcreteInterface> factory_method() const override {
		return  std::make_unique<ConcreteClassA>();
	}
};

struct ConcreteCreator2 : public Creator {
	std::unique_ptr<ConcreteInterface> factory_method() const override {
		return  std::make_unique<ConcreteClassB>();
	}
};



int main(){
	auto cr1 = std::make_unique<ConcreteCreator1>();
	auto cr2 = std::make_unique<ConcreteCreator2>();
	cr1->some_operation();
	cr2->some_operation();
	
}
