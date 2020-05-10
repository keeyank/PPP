#include <iostream>
#include <string>
#include <vector>

using namespace std;

template<typename C>
	// Requires Container<C>
void printout(const C& c, string delim = " ") {
	printout(c.begin(), c.end(), delim);
}

template<typename Iter>
	// Requires bidirectional iterator
	// and value_type<Iter> must have cout overloaded
void printout(Iter first, Iter last, string delim = " ") {
	cout << "{" << delim;
	while (first != last) {
		cout << *first << delim;
		++first;
	}
	cout << "}\n";
}

template<typename C>
	// Requires Container<C> with bidirectional iterator
void reverse_printout(C c) {
	reverse_printout(c.rbegin(), c.rend());
}

template<typename Iter>
void reverse_printout(Iter rfirst, Iter rlast) {
	cout << "{";
	while (rfirst != rlast) {
		cout << *rfirst << " ";
		--rfirst;
	}
	cout << "}\n";
}

template<typename Iter>
	// Requires bidirectional iterator
void print_backwards(Iter rfirst, Iter rlast) {
	cout << "{";
	while (rfirst != rlast) {
		cout << *rfirst << " ";
		--rfirst;
	}
	cout << "}\n"; 
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
		if (val == -1) break;
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