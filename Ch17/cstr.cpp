#include <iostream>

using namespace std;

// Length of c string s
// Length includes null terminator
int str_len(const char* s) {
	int i;
	for (i = 0; s[i] != 0; ++i);
	return i+1;
}

// Convert a cstring to all lowercase
void to_lower(char* s) {
	for (int i = 0; s[i] != 0; ++i) {
		if (s[i] >= 65 && s[i] <= 90) {
			s[i] += 32;
		}
	}
}

// Returns a new char pointer, allocated on the heap
// This pointer must be deleted or a memory leak will occur
char* strdup(const char* s) {
	int len = str_len(s);
	char* dup = new char[len];
	for (int i = 0; i < len; ++i) {
		dup[i] = s[i];
	}
	return dup;
}

// Find instance of x in s, index of location of x in s
// if x is in s, else return -1
int find(const char* s, const char* x) {

	for (int i = 0; s[i] != 0; ++i) {

		int j = 0;
		while (s[i+j] != 0) {
			if (x[j] == 0) return i;

			if (s[i+j] == x[j]) ++j;
			else break;
		}

		// Handles special case 
		if (x[j] == 0) return i;
	}

	return -1;
}

int main() 
try {
	// Exercise 4,5
	// char* s = new char[41]{"Hello,Sir! OOOhhhHH!!#*20832...BLAH\tya\\\n"};
	// char* s2 = strdup(s);
	// to_lower(s);

	// cout << s;
	// cout << s2;

	// delete[] s2;
	// delete[] s;

	// Exercise 6
	cout << ">";
	char* big = new char[256];
	cin.getline(big, 256);
	if (cin.fail() && !cin.eof()) 
		{throw runtime_error("Input too long!");}

	cout << '>';
	char* small = new char[256];

	// Successive getlines will write new null terminators,
	// so their won't be conflicts with successive c strings
	while (cin.getline(small, 256)) {
		int i = find(big, small);
		cout << "Index: " << i << endl;
		cout << '>';
	}

	if (cin.fail() && !cin.eof()) 
		{throw runtime_error("Input too long!");}

	delete[] big;
	delete[] small;

	return 0;
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}