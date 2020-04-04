#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {

	cout << "Enter the number of pennies, nickels, dimes, "
		<< "and quarters that you have.\n";
	int pennies;
	int nickels;
	int dimes;
	int quarters;
	cin >> pennies >> nickels >> dimes >> quarters;

	// int total = pennies + 5*nickels + 10*dimes + 25*quarters;
	// int dollars = total / 100;
	// int cents = total % 100;
	// cout << "You have " << dollars << "." << cents << "$.\n";

	float total = pennies*0.01 + nickels*0.05 + dimes*0.1 + quarters*0.25;
	cout << "You have " << ftotal << "$.\n";


	return 0;
}