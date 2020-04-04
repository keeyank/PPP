#include <iostream>

using namespace std;


int main() {
	char c = 'a';
	int i = 1;
	double d = 0.1;
	bool b = true;
	int* pi = &i;
	char* pc = &c;

	cout << "Size of char " << sizeof(char) << ' ' << sizeof(c) << '\n';
	cout << "Size of int " << sizeof(int) << ' ' << sizeof(i) << '\n';
	cout << "Size of double " << sizeof(double) << ' ' << sizeof(d) << '\n';
	cout << "Size of bool " << sizeof(bool) << ' ' << sizeof(b) << '\n';
	cout << "Size of int* " << sizeof(int*) << ' ' << sizeof(pi) << '\n';
	cout << "Size of char* " << sizeof(char*) << ' ' << sizeof(pc) << '\n';

	return 0;
}