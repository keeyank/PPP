#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

bool elem_of(char elem, string s) {
	for (char c : s) {
		if (elem == c) return true;
	}
	return false;
}

int main() {
	ifstream ifs {"test.txt"};
	if (!ifs) {return 1;}
	ofstream of12 {"12.txt"};
	ofstream of13 {"13.txt"};

	// Exercise 12
	string s;
	for (char c; ifs.get(c)) {
		s += c;
	}
	for (int i = s.size()-1; i >= 0; --i) {
		of12.put(s[i]);
	}

	return 0;
}