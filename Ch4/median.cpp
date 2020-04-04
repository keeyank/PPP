#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {

	vector<double> vals;
	for(double temp; cin >> temp;) {
		vals.push_back(temp);
	}

	sort(vals.begin(), vals.end());
	cout << "{";
	for (double v : vals) {
		cout << v << ",";
	}
	cout << "\b}\n";

	if (vals.size() < 2) return 0;

	double median = 0;
	if (vals.size()%2 == 0) {
		int half_size = vals.size()/2;
		median = (vals[half_size-1] + vals[half_size])/2.;
	}
	else {
		median = vals[vals.size()/2];
	}

	cout << "Median = " << median << '\n';

	return 0;
}