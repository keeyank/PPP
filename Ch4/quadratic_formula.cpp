#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
	double a, b, c;
	cin >> a >> b >> c;
	double root1 = (-b + sqrt(b*b - 4*a*c)) / (2*a);
	double root2 = (-b - sqrt(b*b - 4*a*c)) / (2*a);
	cout << root1 << ", " << root2 << '\n';
	return 0;
}