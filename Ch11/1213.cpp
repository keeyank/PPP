#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main() {
	ifstream ifs {"test.txt"};
	if (!ifs) {return 1;}
	ofstream of12 {"12.txt"};
	ofstream of13 {"13.txt"};

	// Exercise 12
	string s;
	for (char c; ifs.get(c);) {
		s += c;
	}
	for (int i = s.size()-1; i >= 0; --i) {
		of12.put(s[i]);
	}

	// Exercise 13
	ifs.clear();
	ifs.seekg(0);

	vector<string> vs;
	for (string s; ifs >> s;) {
		vs.push_back(s);
	}
	for (int i = vs.size()-1; i >= 0; --i) {
		of13 << vs[i] << ' ';
	}

	return 0;
}