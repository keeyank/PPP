#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
	string name = "???";
	double age = -123;
	cout << "Enter you're name sir\n";
	cin >> name >> age;
	cout << "Name: " << name << " - Age (in months): "
		<< age * 12 << endl;

	return 0;
}