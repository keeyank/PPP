#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

const int w = 8;

int main() {


	string s;
	for (char c; cin.get(c);) {
		s += c;
	}

	cout << setw(w) << "char  " 
		<< setw(w) << "isalnum"
		<< setw(w) << "isalpha"
		<< setw(w) << "iscntrl"
		<< setw(w) << "isgraph"
		<< setw(w) << "islower"
		<< setw(w) << "isprint"
		<< setw(w) << "ispunct"
		<< setw(w) << "isspace"
		<< setw(w) << "isupper" << '\n';

	for (const char& c : s) {
		cout << setw(w/2) << c
			<< setw(w) << isalnum(c)
			<< setw(w) << isalpha(c)
			<< setw(w) << iscntrl(c)
			<< setw(w) << isgraph(c)
			<< setw(w) << islower(c)
			<< setw(w) << isprint(c)
			<< setw(w) << ispunct(c)
			<< setw(w) << isspace(c)
			<< setw(w) << isupper(c) << endl;
	}

	return 0;
}