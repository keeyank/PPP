#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <numeric>

#include "container_stuff.h"

using namespace std;

struct X {
	int a = 1;
	double b = 0.1;

	bool operator==(const X& other) const {
		return (a == other.a && b == other.b);
	}
	bool operator!=(const X& other) const {
		return !(*this == other);
	}
};

template<class InputIt, class T>
int mycount(InputIt first, InputIt last, const T& val) {
	int c = 0;
	for (; first != last; ++first) {
		if (*first == val) ++c;
	}
	return c;
}

template<class InputIt, class UnaryPredicate>
int mycount_if(InputIt first, InputIt last, UnaryPredicate p) {
	int c = 0;
	for (; first != last; ++first) {
		if (p(*first)) ++c;
	}
	return c;
}

/*
Order of boolean expression evaluation is important here!!
If first == last, we DON'T want to evaluate *first != val,
since dereferencing last is undefined. 
*/
template<class InputIt, class T>
InputIt find(InputIt first, InputIt last, const T& val) {
	while (first != last && *first != val) ++first;
	return first;
}

/*
See notebook for a justification as to why the base cases work
(trace the base cases along with the algorithm)
The algorithm is conceptually clear in terms of containers with
N > 3, but for smaller containers (like 1 and 2), we need to 
fully trace out the algorithm with pictures to understand why it works
*/
template<class RandIt, class T>
bool mybinary_search(RandIt first, RandIt last, const T& val) {
	if (first == last) return false;

	int mid_index = (last - first)/2;
	if (first[mid_index] < val) {
		return binary_search(first+mid_index+1, last, val);
	}
	else if (val < first[mid_index]) {
		return binary_search(first, first+mid_index, val);
	}
	else return true;
}

int main() {
	vector<int> v{1,4,1,2,4,1,1,4,2};
	// list<int> l {1,1,1};
	// vector<X> vx = {X{4,.1}, X{4,.1}, X{4,53.1}, X{4,4.1}};
	// map<string,int> m;
	// m["1"] = 1;
	// m["2"] = 2;
	// cout << mycount(v.begin(), v.end(), 1) << endl
	// 	<< mycount(v.begin(), v.end(), 4) << endl
	// 	<< mycount(l.begin(), l.end(), 2) << endl
	// 	<< mycount_if(v.begin(), v.end(), 
	// 			[](int a){return a > 1;}) << endl
	// 	<< mycount(vx.begin(),vx.end(), X{4,.1}) << endl;

	// sort(v.begin(), v.end());
	// cout << endl << mybinary_search(v.begin(), v.end(), 1) << endl;

	cin >> v;
	sort(v.begin(), v.end());
	cin.clear();
	for (int i; cin >> i;) {
		cout << mybinary_search(v.begin(), v.end(), i) << endl;
	}
	


	return 0;
}