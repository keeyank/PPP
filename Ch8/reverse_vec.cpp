#include <vector>
#include <iostream>
#include <string>

using namespace std;

#include "print_vec.h"

void reverse_vec1(vector<int>& v) {
	for (int i = 0; i < v.size()/2; ++i) {
		swap(v[i], v[v.size()-i-1]);
	}
}

vector<int> reverse_vec2(const vector<int>& v) {
	vector<int> reversed;
	for (int i = v.size()-1; i >= 0; --i) {
		reversed.push_back(v[i]);
	}
	return reversed;
}

int main() 
try {
	vector<int> sequence;
	cout << "Start typing!\n";
	for (int tmp; cin >> tmp;) {
		sequence.push_back(tmp);
	}

	print_vec("Normal: ", sequence);
	reverse_vec1(sequence);
	print_vec("Reversed: ", sequence);

	vector<int> og = reverse_vec2(sequence);
	print_vec("Reversed: ", sequence);
	print_vec("Original: ", og);

	return 0;
}
catch (exception& e) {
	cerr << "Error: " << e.what() << endl;
	return 1;
}