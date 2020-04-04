#include <iostream>
#include <string>

using namespace std;

int main() 
try {
	// Exercise 7
	constexpr int len = 100;
	char* s = new char[len];
	for (int i = 0; i < len; ++i) {
		int c = cin.get();
		if (!cin || c == '!') {
			s[i] = 0;
			break;
		}
		s[i] = c;
	}
	cout << endl << s << endl;
	delete[] s;
	// Exercise 10
	/* 
	The for loop stops looping after len loops, so it prevents 
	users from adding extra characters to s.
	I could have added an extra check after the loop to see if there
	is anything still in the buffer, and if so, get mad at the user for
	writing extra stuff and trying to break the program!
	*/

	// Exercise 8 - Way easier!
	// string s;
	// for (char c; cin.get(c);) {
	// 	if (!cin || c == '!') {
	// 		break;
	// 	}
	// 	s += c;
	// }
	// cout << s;
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}