#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int str_len(const char* s) {
	if (s == nullptr) return 0;
	int count = 0;
	while (s[count]) ++count;
	return count;
}

string cat(string s1, string s2, string delim = "") {
	ostringstream c;
	c << s1 << delim << s2;
	return c.str();
}

char* cat(const char* s1, const char* s2, const char* delim = nullptr) {
	int n = str_len(s1) + str_len(delim) + str_len(s2) + 1;
	char* c = new char[n];

	char* curr = c;
	while (*s1 != 0) {
		*curr = *s1;
		++curr;
		++s1;
	}
	if (delim) {
		while (*delim != 0) {
			*curr = *delim;
			++curr;
			++delim;
		}
	}
	while (*s2 != 0) {
		*curr = *s2;
		++curr;
		++s2;
	}
	*curr = 0;

	return c;
}

istream& read_cstr(istream& is, char* buffer, int max) {
	is.width(max);
	return is >> buffer;
}

int main() {
	constexpr int max = 128;
	char s1[max];
	char s2[max];
	while (true) {
		cin.getline(s1, max);
		cin.getline(s2, max);
		if (!cin) break;

		char* c = cat(s1, s2, "---");
		cout << c << endl;
		delete[] c;
	}

	return 0;
}



