#include "iostream"

using namespace std;

#include <iostream>
#include <string>
#include <vector>

using namespace std;

template<typename Iter>
void printout(Iter first, Iter last) {
	while (first != last) {
		cout << *first << ' ';
		++first;
	}
	cout << "\b\n";
}

template<typename T> 
	// Requires T to be an element, and has << defined
ostream& operator<<(ostream& os, const vector<T>& v) {
	os << "{";
	for (auto it = v.begin(); it != v.end(); ++it) {
		os << *it;
		if (it + 1 != v.end()) os << ", ";
	}
	return os << "}";
}

template<class T>
	// Requires T to be an element that has >> defined
istream& operator>>(istream& is, vector<T>& v) {
	vector<T> v_tmp;
	char test;
	T val;

	while (true) {
		is >> val;
		if (!is) return is;
		v_tmp.push_back(val);

		is.get(test);
		if (!is) return is;
		if (!isspace(test)) {
			is.clear(ios_base::failbit);
			return is;
		}

		is.get(test);
		if (!is) return is;
		if (test == '.') break;
		is.putback(test);
	} 

	v = v_tmp;
	return is;
}