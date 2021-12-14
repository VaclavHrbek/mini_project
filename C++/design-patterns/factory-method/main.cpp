#include <iostream>

/*
 * The Product declares the interface, which is common to all objects that can be produced by the creator and its subclasses.
*/
struct ConcreteInterface {
	virtual int value() = 0;
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

};


int main(){
	
}
