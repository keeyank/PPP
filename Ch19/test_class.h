#include <string>
#include <iostream>

using namespace std;

struct X {
	string a {};
	int b {};

	X()
		: a{"default"}, b{0}
	{
		cout << "Default constructor called for " << *this 
			<< " (loc " << this << ")\n";
	}

	X(string aa, int bb)
		: a{aa}, b{bb} 
	{ 
		cout << "Constructor called for " << *this
			<< " (loc " << this << ")\n";
	}

	X(const X& x) {
		a = x.a;
		b = x.b;
		cout << "Copy constructor called for " << *this
			<< " (loc " << this << ")\n";
		cout << "Copied from " << x << " (loc " << &x << ")\n";
	}

	X& operator=(const X& x) {
		cout << "Copy assignment called for " << *this
			<< " (loc " << this << ")\n";

		a = x.a;
		b = x.b;

		cout << "Copied from " << x << " (loc " << &x << ")\n";

		return *this;
	}
	
	~X() {
		cout << "Destructor called for " << *this
			<< " (loc " << this << ")\n";
	}

	void f() {
		cout << "f called for " << *this
			<< " (loc " << this << ")\n";
	}

	friend ostream& operator<<(ostream& os, const X& x);
};

ostream& operator<<(ostream& os, const X& x) {
	return os << x.a << ' ' << x.b;
}
