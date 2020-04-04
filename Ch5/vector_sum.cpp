#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() 
try {

	int n;
	cout << "Enter the amount to sum\n";
	cin >> n;
	if (!cin)
		throw runtime_error("Invalid user input");
	if (n <= 0)
		throw runtime_error("n must be greater than 0");

	cout << "Enter data\n";
	vector<double> v;
	for (double tmp; cin >> tmp;) {
		v.push_back(tmp);
	}

	if (n > v.size()) 
		throw runtime_error("n is greater than the amount of inputs");
	double sum = 0;
	cout << "The sum of the first " << n << " numbers (";
	for (int i = 0; i < n; ++i) {
		sum += v[i];
		cout << v[i] << " ";
	}
	cout << "\b) " << sum << "\n";

	vector<double> d(n-1);
	for (int i = 0; i < n-1; ++i) {
		d[i] = v[i+1] - v[i];
	}

	for (double dingle : d) {
		cout << dingle << "\n";
	}

}

catch (exception &e) {
	cerr << "Error: " << e.what() << "\n";
	return 1;
}