#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
	int max = 100;
	int min = 0;
	bool i_win = false;

	cout << "Think of a number between 1 and 100.\n";

	int i = 0;
	while (!i_win && i <= 10) {
		int guess = (max+min)/2;
		cout << "Is your number " << guess << "?\n";
		char answer;
		cin >> answer;

		if (answer == '<') {
			max = guess;
		}
		else if (answer == '>') {
			min = guess;
		}
		else { // answer == '='
			i_win = true;
		}
		++i;
	}

	if (i_win) {
		cout << "HAHAHAHAHA YOU ARE INFERIOR\n";
	}
	else {
		cout << "Wow you cheated didn't you? Congratulations on cheating.\n";
	}


	return 0;
}