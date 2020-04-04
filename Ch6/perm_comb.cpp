#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int rec_p(int a, int last) {
	if (a == last) 
		return 1;
	return a*rec_p(a-1, last);
}

// Permutation
int p(int a, int b) {
	return rec_p(a, a-b);
}

// Factorial
int fact(int a) {
	if (a == 0) 
		return 1;
	return a*fact(a-1);
}

// Combination
int c(int a, int b) {
	return p(a,b)/fact(b);
}

int main() 
try {

	// Prompt
	cout << "Enter P(a,b) for permutations, C(a,b) for combinations, " 
		<< "where a and b are integers.\n";
	char throwaway;
	char option;
	int a;
	int b;
	cin >> option >> throwaway >> a >> throwaway >> b;
	if (!cin) 
		throw runtime_error("Invalid input.");

	int result;
	if (option == 'P') {
		result = p(a, b);
	}
	else if (option == 'C') {
		result = c(a, b);
	}
	else throw runtime_error("Invalid input.");

	cout << "Answer: " << result << "\n";
	return 0;
}

catch (exception& e) {
    cerr << e.what() << endl;
    return 1;
}
catch (...) {
    cerr << "exception \n";
    return 2;
}