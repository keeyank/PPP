#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
	int n;
	cout << "number give to me\n";
	cin >> n;
	cout << "n == " << n
		<< "\nn+1 == " << n+1
		<< "\nn/3 == " << n/3
		<< "\nn*3 == " << n*3
		<< "\nn%3 == " << n%3
		<< "\n(n/3)*3+n%3 == " << (n/3)*3+n%3
		<< "\n";

	return 0;
}