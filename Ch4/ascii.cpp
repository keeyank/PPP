#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {

	int c = 'a';
	while (c <= 'z') {
		cout << c << '\t' << (char)c << '\n';
		++c;
	}

	for (c = 'A'; c <= 'Z'; ++c) {
		cout << c << '\t' << (char)c << '\n';
	}

	for (c = '0'; c <= '9'; ++c) {
		cout << c << '\t' << (char)c << '\n';
	}

	return 0;
}