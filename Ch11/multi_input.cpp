#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>

using namespace std;

int main() {
	cout << "Enter any amount of integers.\n";

	int n;
	cout << showbase;
	for (char c; cin.get(c);) {
		if (isspace(c)) {continue;}

		// Case: Decimal input
		else if (isdigit(c) && c != '0') {
			cin.unget();
			cin >> dec >> n;
			cout << dec << setw(8) << n 
				<< setw(25) << " decimal converts to "
				<< setw(8) << n << " decimal.\n";
		}
		else if (c == '0') {
			char next; cin.get(next);

			// Case: Hexadecimal input
			if (tolower(next) == 'x') {
				cin >> hex >> n;
				cout << hex << setw(8) << n
					<< setw(25) << " hexadecimal converts to "
					<< setw(8) << dec << n << " decimal.\n";
			}

			// Case: Octal input
			else {
				cin.unget();
				cin >> oct >> n;
				cout << oct << setw(8) << n
					<< setw(25) << " octal converts to "
					<< setw(8) << dec << n << " decimal.\n"; 
			}
		}
		else {break;}
	}
	return 0;
}