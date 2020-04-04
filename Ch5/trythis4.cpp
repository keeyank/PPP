#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int area(int a, int b) {
	throw runtime_error("Oh it is bad.");
	return a*b;
}

int main() 
try {
	area(1,1);
	return 0;
}
catch (exception& e) {
	cerr << "Error: " << e.what() << "\n";
	return 1;
}
catch (...) {
	return 2;
}