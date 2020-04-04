#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

constexpr char caps_difference = 'a' - 'A';

// Convert string s to all lowercase
void tolower(string &s) {
	for (int i = 0; i < s.size(); ++i) {
		if (s[i] >= 'A' && s[i] <= 'Z') {
			s[i] += caps_difference;
		}
	}
}

// Convert a string representing a day of the week
// to it's corresponding integer.
// Fun fact - This function is onto from the set of viable strings 
// the set {0,1,2,3,4,5,6}, but it is NOT one to one!
// When we define the inverse function, we limit the domain to make
// the set one to one, which allows an inverse function to exist. 
int daytoi(string day) {
	tolower(day);
	if (day == "monday" || day == "mon") return 0;
	else if (day == "tuesday" || day == "tues") return 1;
	else if (day == "wednesday" || day == "wed") return 2;
	else if (day == "thursday" || day == "thurs") return 3;
	else if (day == "friday" || day == "fri") return 4;
	else if (day == "saturday" || day == "sat") return 5;
	else if (day == "sunday" || day == "sun") return 6;
	else throw runtime_error("Invalid input.");
}

int main() 
try {
	return 0;
}
catch (exception &e) {
	cerr << "Error: " << e.what() << "\n";
	return 1;
}
catch (...) {
	cerr << "Error: Unknown exception!\n";
	return 2;
}