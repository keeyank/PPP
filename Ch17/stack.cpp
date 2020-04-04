#include <iostream>

using namespace std;

int main() {
	int a;
	int b;
	int c;
	cout << &a << ' ' << &b << ' ' << &c << endl;
	// Address of stack variables grows downwards!

	int* pa = new int;
	int* pb = new int;
	int* pc = new int;
	cout << pa << ' ' << pb << ' ' << pc << endl;
	delete pa;
	delete pb;
	delete pc;
	// Address of objects allocated on heap grows upwards!
	return 0;
}