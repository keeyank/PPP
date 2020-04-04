#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

double convert_to_cm(double val, string unit) {
	if (unit == "m") val *= 100.;
	else if (unit == "cm") ; // Do nothing
	else if (unit == "in") val *= 2.54;
	else if (unit == "ft") val *= 2.54*12.;
	else ; // Default unit is cm
	return val;
}

bool is_valid_unit(string unit) {
	if (unit == "cm" || unit == "m" || unit == "in" 
   			|| unit == "ft") {
		return true;
	}
	return false;
}

int main() {

	double min = 0;
	double max = 0;
	double curr = 0;
	string unit = "";
	bool first_loop = true;

	double sum = 0;
	int count = 0;
	vector<double> vals;

	// Handle further input
	while(cin >> curr >> unit) {

		if (!is_valid_unit(unit)) {
			cout << "Invalid unit, try again!\n";
			continue;
		}

		curr = convert_to_cm(curr, unit);

		if (first_loop) {
			first_loop = false;
			max = curr;
			min = curr;
		}

		// Statistics
		vals.push_back(curr);
		if (curr > max) max = curr;
		if (curr < min) min = curr;
		sum += curr;
		++count;
	}

	// Final output
	cout << "\nAll values recorded in cm.\n";
	cout << "Largest value: " << max << "\nSmallest value: " 
		<< min << "\nSum: " << sum << "\nNumber of values entered: " 
		<< count << '\n';

	sort(vals.begin(), vals.end());
	cout << "Inputted data:\n\n";
	for (double v : vals) {
		cout << v << "\n";
	}

	return 0;
}