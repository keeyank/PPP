#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

bool isdelim(char c, const string& delims) {
	for (char d : delims) {
		if (c == d) {return true;}
	}
	return false;
}

string delims_to_space(const string& s, const string& delims) {
	string result;
	for (char c : s) {
		if (isdelim(c, delims)) {
			c = ' ';
		}
		result += c;
	}
	return result;
}

vector<string> split(const string& s, const string& d) {
	string stripped = delims_to_space(s, d);

	istringstream iss {stripped};
	vector<string> words;
	for (string word; iss >> word;) {
		words.push_back(word);
	}	
	return words;
}

int main() {
	string delims = "1234567890-=!@#$%^&*()_+{}|:\"<>?,./\\;'[]\'`~";
	for (string line; getline(cin, line);) {
		vector<string> words = split(line, delims);
		for (string word : words) {
			cout << word << endl;
		}
	}
	return 0;
}