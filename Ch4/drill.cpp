#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {

	double min;
	double max;
	while(cin >> min >> max) {

		// Correctly assign min and max
		if (min > max) {
			double temp = max;
			max = min;
			min = temp;
		}

		if (min == max) {
			cout << "The numbers are equal.\n";
		}
		else {
			cout << "The larger value is " << max << '\n';
			cout << "The smaller value is " << min << '\n';

			if (max-min < 1./100.) { // . to indicate float division
				cout << "The numbers are almost equal.\n";
			}
		}
	}

	return 0;
}