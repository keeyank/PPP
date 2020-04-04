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
	ofstream of1 {"1.txt"};
	ofstream of2 {"2.txt"};
	ofstream of3 {"3.txt"};

	// Exercise 1
	for (char tmp; ifs.get(tmp);) {
		char c = tolower(tmp);
		of1 << c;
	}

	// Exercise 2
	ifs.clear(); // Put ifs in a good state
	ifs.seekg(0); // Reset reading position to 0'th char
	string word = "kayanne";
	int i = 0;
	for (string line; getline(ifs, line);) {
		istringstream iss {line};
		for (string tmp; iss >> tmp;) {
			if (tmp == word) {
				++i;
				of2 << line << '\n';
				break;
			}
		}
	}
	of2 << i;

	// Exercise 3
	ifs.clear();
	ifs.seekg(0); 
	string remove = "aeiouAEIOU";
	for (char c; ifs.get(c);) {
		if (!elem_of(c, remove)) {
			of3 << c;
		}
	}




	return 0;
}