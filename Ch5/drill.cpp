#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() 
try {
	// cout << "Success!1\n";
	// cout << "Success!2\n";
	// cout << "Success" << "!3\n";
	// cout << "Success" << "!4\n";
	//int res = 7; vector<int> v(10); v[5] = res; cout << "Success!5\n";
	//vector<int> v(10); v[5] = 7; if (v[5]==7) cout << "Success!\n";
	//if (true) cout << "Success!\n"; else cout << "Fail!\n";

	return 0;
}
catch (exception& e) {
	cerr << "Error: " << e.what() << "\n";
	return 1;
}
catch (...) {
	cerr << "Oops: Unknown exception!\n";
	return 2;
}