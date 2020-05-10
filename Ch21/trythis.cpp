#include <vector>
#include <list>
#include <iostream>

using namespace std;

template<typename In, typename T>
	// Requires Input_iterator<In>()
	//	&& Equality_comparabe<T>()
In find1(In first, In last, const T& val) {
	while (first != last && val != *first) ++first;
	return first;
}


template<typename In, typename T>
	// Requires Input_iterator<In>()
	//	&& Equality_comparabe<T>()
In find2(In first, In last, const T& val) {
	for (In it = first; it != last; ++it) {
		if (*it == val) return it;
	}
	return last;
}

int main() {
	vector<int> v {1,2,3};
	cout << *find2(v.begin(), v.end(), 1) << endl
		<< *find1(v.begin(), v.end(), 2) << endl
		<< *find1(v.begin(), v.end(), 3) << endl
		<< (v.end() == find2(v.begin(), v.end(), 4)) << endl
		<< (v.end() == find1(v.begin(), v.end(), -4)) << endl;
	return 0;
}