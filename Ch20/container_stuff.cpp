/*
Look at vectors input/output stuff definitions
*/

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

/*
Note: without "auto", we would have to use this as the type name
for the iterator "it": 
typename vector<T>::const_iterator
typename because it's unsure if vector<T> has const_iterator as
a type, so we have to let the compiler know that it is a type
(I think the <T> brings the ambiguity, it doesn't actually know
what vector<T>::const_iterator refers to, since it hasn't generated
the vector class for whatever type T happens to be yet.) Also,
we must use const, since v is a const reference to a vector<T>.
*/
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

/*
Puts whitespace seperated input into v, delimited by '.'
The '.' must also be whitespace separated (to handle vector<string>)
TODO: Eat whitespace, then get vals n stuff. Right now, there's a
weirdness thing if you put a space, then another space, then '.'.
So eat whitespace to fix that.
*/
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

int main() 
try {
	vector<int> vi {1,2,3,4,5};
	vector<string> vs {"hello", "ok", "i", "am saying", "welo"};
	cout << vi << endl << vs << endl;

	vector<string> input_v;
	cin >> input_v;
	if (!cin) throw runtime_error("Bad input!!");
	cout << input_v << endl;
	return 0;
}
catch (exception& e) {
	cerr << "Error: " << e.what() << endl;
}
