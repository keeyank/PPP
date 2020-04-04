#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {

	cout << "Enter two doubles.\n";
	double val1;
	double val2;
	cin >> val1 >> val2;

	double min = val2;
	double max = val1;
	if (val1 < val2) {
		min = val1;
		max = val2;
	}

	double sum = val1 + val2;
	double diff = max - min;
	double product = val1 * val2;
	// double dval1 = val1; // Cast val1 to double
	// double ratio = dval1 / val2; // Integer val2 implicitly converted to double by C++
	double ratio = min / max;

	cout << "Smallest: " << min 
		<< "\nLargest: " << max
		<< "\nSum: " << sum
		<< "\nDifference: " << diff
		<< "\nProduct: " << product
		<< "\nRatio: " << ratio << "\n";

	return 0;
}