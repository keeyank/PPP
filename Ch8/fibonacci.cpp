#include <vector>
#include <iostream>
#include <string>

using namespace std;

// This include MUST be BELOW using namespace std 
// (because the .h file does not include anything or have a using directive)
// Likewise for the std include statements above
#include "print_vec.h"


// Takes in an empty vector, populates it using a fibonacci sequence
void fibonacci(vector<int>& sequence, int first, int second, int n) {
	sequence.push_back(first);
	sequence.push_back(second);
	for (int i = 2; i < n; ++i) {
		sequence.push_back(sequence[i-2] + sequence[i-1]);
	}
	return;
}

// After testing this function, it appears that ints max out at around
// 1,800,000,000

int main() 
try {
	vector<int> fib;
	int first, second, n;
	cout << "Enter the first 2 elements of the fibonacci sequence "
		<< "followed by the size of the sequence.\n";
	cin >> first >> second >> n;
	if (!cin)
		throw runtime_error("Invalid input.");

	fibonacci(fib, first, second, n);
	print_vec("Fibonacci sequence: ", fib);
	return 0;
}
catch (exception& e) {
	cout << "Error: " << e.what() << "\n";
	return 1;
}
catch (...) {
	cout << "Unkown exception\n";
	return 2;
}