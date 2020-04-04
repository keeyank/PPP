#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

vector<string> illegal_words = {"stupid", "Stupid", "poo", 
								"Poo", "pee", "Pee"};

bool is_illegal(string s) {
	for (string illegal : illegal_words) {
		if (s == illegal) {
			return true;
		}
	}
	return false;
}

int main() {

	vector<string> words;
	for (string word; cin >> word;) {
		words.push_back(word);
	}

	for (string s : words) {
		if (is_illegal(s)) {
			cout << "BLEEP ";
		}
		else {
			cout << s << ' ';
		}
	}
	cout << '\n';

	return 0;
}