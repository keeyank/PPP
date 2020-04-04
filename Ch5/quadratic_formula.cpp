#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

double find_roots(double a, double b, double c, char sign) {

	// Preconditions
	if (!(sign == '+' || sign == '-')) 
		throw runtime_error("find_roots: Invalid sign");
	if ((b*b - 4*a*c) < 0) 
		throw runtime_error("find_roots: Negative determinant");
	

	if (sign == '+') 
		return (-b + sqrt(b*b - 4*a*c)) / (2*a);
	else // sign == '-'
		return (-b - sqrt(b*b - 4*a*c)) / (2*a);
	
}

int main() 
try {
	double a, b, c;
	cin >> a >> b >> c;
	double root1 = find_roots(a, b, c, '+');
	double root2 = find_roots(a, b, c, '-');
	cout << root1 << ", " << root2 << '\n';
	return 0;
}
catch (exception &e) {
	cerr << "Error: " << e.what() << "\n";
	return 1;
}