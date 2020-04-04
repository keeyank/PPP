#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

constexpr double absolute_zero = -273.15;
constexpr double ctok_conversion = 273.15

double ctok(double c) {
	if (c < absolute_zero) {
		throw runtime_error("ctok: invalid input (below absolute zero)\n");
	}
	double k = c + ctok_conversion;
	return k;
}

int main() 
try {
	double c = 0;
	cin >> c;
	double k = ctok(c);
	cout << k << '\n';
}
catch (exception &e) {
	cerr << "Error: " << e.what();
	return 1;
}