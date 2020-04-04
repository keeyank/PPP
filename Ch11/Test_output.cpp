#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main() {
	int birth_year = 1998;
	int age = 22;
	cout << showbase << birth_year << "\t(decimal)\n"
		<< hex << birth_year << "\t(hex)\n" 
		<< oct << birth_year << "\t(oct)\n";
	cout << dec << age << endl;

	// int a, b, c, d;
	// cin >> a >> oct >> b >> hex >> c >> d;
	// cout << a << '\t' << b << '\t' << c << '\t' << d << '\n';
	// Interprets 1234 as decimal, octal, and hexadecimal, respectively
	// depending on the input options specified

	double f = 1234567.89;
	// Interesting - double gives perfect representation,
	// float doesnt! (makes the value 1234567.87500) cuz floats store less information
	cout << f << "\t(defaultfloat)\n"
		<< fixed << f << "\t(fixed)\n"
		<< scientific << f << "\t(scientific)\n";

	cout << endl << endl << endl;

	int w = 24;
	cout << setw(w) << "Jeffeths Barksons" 
		<< setw(w) << "jw@gmail.com" 
		<< setw(w) << "6040460444\n"
		<< setw(w) << "Elon Marksk" 
		<< setw(w) << "em@drmsemprtium.com" 
		<< setw(w) << "6123612612\n"
		<< setw(w) << "Babylonian Dr." 
		<< setw(w) << "Dr.B@drbfart.com" 
		<< setw(w) << "6123614612\n";
	return 0;
}