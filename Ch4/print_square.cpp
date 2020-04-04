#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int square(int base) {
	int sqr = 0;
	for (int i = 0; i < base; ++i) {
		sqr += base;
	}
	return sqr;
}

int main() {

	for (int i = 0; i < 10; ++i) {
		cout << i << '\t' << square(i) << '\n';
	}

	return 0;
}