#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int area(int a, int b) {
	if (!(a>0 && b>0)) {
		throw runtime_error("Precondition violated.");
	}
	int r = a*b;
	if (r < 0) {
		throw runtime_error("Postcondition violated.");
	}
	return a*b;
}

int main() 
try {
	// This input violates the postcondition, but not the precondition
	// Reason is due to overflow! The ints are too big for reasonable compuation
	area(2'111'483'647, 2'111'483'647); 
	return 0;
}
catch (exception& e) {
	cerr << "Error: " << e.what() << "\n";
	return 1;
}
catch (...) {
	return 2;
}