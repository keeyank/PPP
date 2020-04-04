#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

void print_vector(vector<int> v) {
	cout << "{";
	for (double val : v) {
		cout << val << ",";
	}
	cout << "\b}\n";
}

int main() {
	vector<int> v;
	for (int temp; cin >> temp;) {
		v.push_back(temp);
	}
	sort(v.begin(), v.end());

	print_vector(v);

	// Count consecutive elements to determine mode
	int mode = v[0];
	int elem_count = 1;
	int max_elem_count = 1;
	for (int i = 1; i < v.size(); i++) {

		// Increment or reset elem_count
		if (v[i] == v[i-1]) {
			++elem_count;
		}
		else {
			elem_count = 1;
		}

		// Update mode
		if (elem_count > max_elem_count) {
			mode = v[i];
			max_elem_count = elem_count;
		}
	}

	cout << mode << '\n';
	return 0;
}