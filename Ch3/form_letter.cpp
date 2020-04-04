#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
	cout << "Enter your name\n";
	string first_name;
	cin >> first_name;
	cout << "Dear " << first_name << ",\n\n" 
		<< "\tHow is it going, sir. Ah yes, good to hear.\n";

	cout << "Enter the name of your friend\n";
	string friend_name;
	cin >> friend_name;
	cout << "Have you seen " << friend_name << " lately?\n";

	cout << "Enter the gender of your friend (m or f)\n";
	char friend_gender;
	cin >> friend_gender;
	if (friend_gender == 'm') {
		cout << "If you see " << friend_name
			<< " please ask him to call me.\n";
	}
	if (friend_gender == 'f') {
		cout << "If you see " << friend_name
			<< " please ask her to call me.\n";
	}

	cout << "Enter your age\n";
	int age;
	cin >> age;
	if (age < 0 or age > 110) {
		cout << "You're being silly my good sire.\n";
	}
	else {
		cout << "I heard you just turned " << age << "!\n";
	}

	if (age < 12) {
		cout << "Next year you will be " << age+1 << "!\n";
	}
	if (age == 17) {
		cout << "Next you will be able to vote!\n";
	}
	if (age > 70) {
		cout << "You are so fat and old.";
	}

	cout << "Yours sincerely,\n\nGunkther\n";

	return 0;
}