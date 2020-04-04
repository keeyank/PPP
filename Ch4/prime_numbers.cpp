#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

void generate_primes(vector<int> &primes, int max) {
	for (int num = 3; num < max; ++num) {
		bool is_prime = true;

		for (int prime : primes) {
			if (num % prime == 0) {
				is_prime = false;
			}
		}

		if (is_prime == true) {
			primes.push_back(num);
		}
	}
}

int main() {
	int max;
	vector<int> primes = {2};
	cin >> max;
	cout << "\n";

	generate_primes(primes, max);
	for (int prime : primes) {
		cout << prime << "\n";
	}
	return 0;
}