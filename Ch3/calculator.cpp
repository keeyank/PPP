#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {

	cout << "Enter an operation followed by 2 operands.\n";
	string op;
	double val1;
	double val2;
	cin >> op >> val1 >> val2;

	if (op == "+") {
		cout << val1 + val2 << endl;
	}
	if (op == "-") {
		cout << val1 - val2 << endl;
	}
	if (op == "*") {
		cout << val1 * val2 << endl;
	}
	if (op == "/") {
		cout << val1 / val2 << endl;
	}

	return 0;
}