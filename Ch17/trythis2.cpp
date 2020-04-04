#include <iostream>

using namespace std;

class Base {
public:
	Base() {
		cout << "Base constructed!\n";
	}
	~Base() {
		cout << "Base destroyed!\n";
	}
};

struct Derived : Base {
	Derived() {
		cout << "Derived constructed!\n";
	}
	~Derived() { // This is executed whenever object leaves scope
				// Then, base destructor is executed
		cout << "Derived destroyed!\n";
	}
};

int main() {
	Base b;
	{
		Derived d;
	}
	cout << "Deleted d\n";
	return 0;
}