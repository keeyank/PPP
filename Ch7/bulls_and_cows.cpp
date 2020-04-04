#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

constexpr int SIZE = 4; // Must NOT be greater than 10

// Converts a digit char into its corresponding integer
// Returns this integer
int ctoi(char c) {
	if (c < '0' || c > '9') {
		throw runtime_error
			("Invalid input - String must be composed of digits");
	}
	return c - '0';
}


class Answer {
private:
	string answer = "0123";
	vector<bool> answer_set;
public:
	Answer() : answer_set(10) {}
	void reset_answer();
	int get_bull(string guess);
	int get_cow(string guess);
};

// Randomize the 4 unique digits of answer
void Answer::reset_answer() {

	// Reset answer_set, since answer is to be changed
	fill(answer_set.begin(), answer_set.end(), false);

	srand(time(NULL));
	int i = 0;
	while(i < SIZE) {
		int digit = rand()%10;
		answer[i] = '0' + digit;
		if (answer_set[digit] == true) {
			// Digit is not unique; redo this iteration
			--i;
		}
		else { // Digit is unique
			answer_set[digit] = true;
		}
		++i;
	}
}

int Answer::get_bull(string guess) {
	int bull = 0;
	for (int i = 0; i < SIZE; ++i) {
		if (guess[i] == answer[i])
			++bull;
	}
	return bull;
}

int Answer::get_cow(string guess) {
	int cow = 0;
	for (int i = 0; i < SIZE; ++i) {
		int index = ctoi(guess[i]);
		if (answer_set[index] == true && answer[i] != guess[i]) {
			++cow;
		}
	}
	return cow;
}

// Check for repeated chars in string s
// If there are repeats, return true
bool check_repeats(string s) {
	sort(s.begin(), s.end());
	for (int i = 1; i < SIZE; ++i) {
		if (s[i] == s[i-1]) 
			return true;
	}
	return false;
}

Answer a;

void play() {
	cout << "Enter " << SIZE << " unique digits.\n";
	a.reset_answer();
	bool win = false;

	// !win MUST be checked before cin >> guess 
	// (because short circuiting applies!)
	cout << "> ";
	for (string guess; !win && cin >> guess;) 
	try {
		if (guess.size() != SIZE) {
			throw runtime_error
				("Invalid input - string must be of size 4.");
		}
		if (check_repeats(guess)) {
			throw runtime_error
				("Invalid input - each digit must be unique.");
		}
		
		int bull = a.get_bull(guess);
		int cow = a.get_cow(guess);

		if (bull == SIZE) {
			cout << "You win!\n";
			win = true;
		}
		else {
			cout << bull << " bull and " << cow << " cow.\n";
		}
		cout << "> ";
	}
	catch (exception &e) {
		cerr << "Error: " << e.what() << "\n";
		cout << "> ";
		// Once the catch block finishes executing,
		// control is transferred back to condition of for loop
	}
}

int main() 
try {
	string play_again = "y";
	while (play_again == "y") {
		play();
		cout << "Play again? (y/n)\n";
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