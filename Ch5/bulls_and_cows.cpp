#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

string answer = "2780";
vector<bool> answer_set(10); // Initialized to all false

int ctoi(char c) {
	if (c < '0' || c > '9')
		throw runtime_error("Invalid input.");
	return c - '0';
}

// Randomize the 4 unique digits of answer
void set_answer() {

	// Reset answer_set, since answer is to be changed
	fill(answer_set.begin(), answer_set.end(), false);

	srand(time(NULL));
	int i = 0;
	while(i < 4) {
		int digit = rand()%10;
		answer[i] = '0' + digit;
		if (answer_set[digit] == true) {
			// Digit is not unique; reset this iteration
			--i;
		}
		else { // Digit is unique
			answer_set[digit] = true;
		}
		++i;
	}
}

// Check for repeated chars in string s
// If there are repeats, return true
bool check_repeats(string s) {
	sort(s.begin(), s.end());
	for (int i = 1; i < 4; ++i) {
		if (s[i] == s[i-1]) 
			return true;
	}
	return false;
}

int main() 
try {
	int bull = 0;
	int cow = 0;
	bool win = false;
	string play_again = "Yes";

	while (play_again == "Yes") {
		cout << "Enter 4 unique digits.\n";
		set_answer();
		win = false;

		// !win MUST be checked before cin >> guess 
		// (because short circuiting applies!)
		for (string guess; !win && cin >> guess;) {
			if (guess.size() != answer.size())
				throw runtime_error("Invalid input.");
			if (check_repeats(guess)) {
				throw runtime_error("Invalid input.");
			}
			
			bull = 0;
			cow = 0;
			for (int i = 0; i < 4; ++i) {

				int index = ctoi(guess[i]);
				if (answer_set[index] == true) {
					++cow;
				}

				if (guess[i] == answer[i]) {
					++bull;
					--cow; // Cancel out increment above
				}
			}

			if (bull == 4) {
				cout << "You win!\n";
				win = true;
			}
			else {
				cout << bull << " bull and " << cow << " cow.\n";
			}
		}

		cout << "Play again?\n";
		cin >> play_again;
	}

	return 0;
}
catch (exception &e) {
	cerr << "Error: " << e.what() << "\n";
	return 1;
}
catch (...) {
	cerr << "Error: Unknown exception!\n";
	return 2;
}