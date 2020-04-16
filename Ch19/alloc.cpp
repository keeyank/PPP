#include <vector>
#include <iostream>
#include "*numbers.cpp"

using namespace std;

template<typename T>
void f(vector<T>& v1, const vector<T>& v2) {
	if (v2.size() < v1.size()) throw runtime_error("BAD!");

	for (int i = 0; i < v1.size(); ++i) {
		v1[i] += v2[i];
	}
}

// Won't compile with a lot of types (it's good we get compile errors)
// E.g., char, string, any struct without * overloaded
// Only works if * and + are defined / overloaded
// It also requires that U be castable to T, but the two 
// vectors can be different types as long as they both have + and *
// defined. 

// We could have replaced static_cast<T> with (T)
// (like in (double)1 or (int)double_variable)
// BUT you should prefer static_cast<int> to c-style casting
// C++ casting makes clear what casts are safe(ish) (like static_cast)
// and which arent (like reinterpret_cast and const_cast)

// Note - min(v1.size(), v2.size()) is deduced to be
// min<int>(v1.size(), v2.size()) by compiler!!! COOL
template<class T, class U>
T bigsum(const vector<T>& vt, const vector<U>& vu) {
	T sum = 0;
	for (int i = 0; i < min(vt.size(), vu.size()); ++i) {
		sum += vt[i] * static_cast<T>(vu[i]);
	}
	return sum;
}

template<typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
	os << "{";
	for (int i = 0; i < v.size(); ++i) {
		os << v[i];
		if (i != v.size()-1) os << ", ";
	}
	return os << "}";
}

int main() {
/*
	vector<string> v1 {"wecomebob", "blocko", "HARRY STYLES"};
	// vector<char> v2 {1,-3,5,1,1,4}; Compiler error - conflicting type
	vector<string> v2 {"blockman", "funkybob", "bregorski"};
	cout << v1 << endl << v2 << endl; 
	f(v1, v2);
	cout << v1 << endl;

	vector<int> v3 {1,2,3,4,5};
	vector<int> v4 {1,2,1,1,2};
	vector<double> d1 {1., 2.1, 1.1, 1.1, 2.999};
	cout << bigsum(v3, v4) << endl;
	cout << bigsum(v3, d1) << endl; // Same output as above! 
									// since double casted to int
	cout << bigsum<int, double>(v3, d1) << endl; // Equivelant to above
	cout << bigsum(d1, v3) << endl; // Now it outputs a double
						// (it casts the ints to doubles this time)
*/
	vector<Number<int>> vn1 {1,3,0,-1,2};
	vector<Number<int>> vn2 {1,1,2,3,-4};
	cout << bigsum(vn1, vn2) << endl;

	return 0;
}