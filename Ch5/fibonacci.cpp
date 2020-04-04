#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

constexpr int max_fib_index = 47;

void print_vector(vector<int> &vec) {
	cout << "{";
	for (int v : vec) {
		cout << v << ", ";
	}
	cout << "\b\b}\n";
	return;
}

void fibonacci(vector<int> &v) {
	if (v.size() >= max_fib_index)
		throw runtime_error("Sequence size is too large.");

	v[0] = 1; v[1] = 1;
	for (int i = 2; i < v.size(); ++i) {
		v[i] = v[i-1] + v[i-2];
	}
}

int main() 
try {
	int n;
	cin >> n;
	if (!cin)
		throw runtime_error("Bad input.");

	vector<int> v(n);
	fibonacci(v);
	print_vector(v);
}

catch (exception &e) {
	cerr << "Error: " << e.what() << "\n";
	return 1;
}