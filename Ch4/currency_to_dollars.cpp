#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {

	constexpr double yen_factor = 0.012;
	constexpr double kroner_factor = 0.14;
	constexpr double pound_factor = 1.71;

	cout << "Enter your amount of money, followed by 'y' for yen, " 
		<< "'k' for kroner, or 'p' for pounds.\n";
	double money;
	char currency;
	cin >> money >> currency;

	switch (currency) {
	case 'y':
		cout << "You have " << money * yen_factor << " dollars.\n";
		break;
	case 'k':
		cout << "You have " << money * kroner_factor << " dollars.\n";
		break;
	case 'p':
		cout << "You have " << money * pound_factor << " dollars.\n";
		break;
	default:
		cout << "I don't understand the input!\n";
	}

	// // Alternate solution:
	// if (currency == 'y') {
	// 	cout << "You have " << money * yen_factor << " dollars.\n";
	// }
	// else if (currency == 'k') {
	// 	cout << "You have " << money * kroner_factor << " dollars.\n";
	// }
	// else if (currency == 'p') {
	// 	cout << "You have " << money * pound_factor << " dollars.\n";
	// }
	// else {
	// 	cout << "I don't understand the input!\n";
	// }

	return 0;
}