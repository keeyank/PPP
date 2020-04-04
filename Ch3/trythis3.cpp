#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
	string current;
	string previous = " ";
	cout << "Type.\n";
	while (cin >> current) {
		if (current == previous) 
			cout << "Repeated word!\n";
		previous = current;
	}
	return 0;
}