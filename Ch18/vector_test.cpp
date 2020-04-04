#include <iostream>
#include "my_vector.h"

using namespace std;

ostream& operator<<(ostream& os, const Vector& v) {
	os << '{';
	for (int i = 0; i < v.size(); ++i) {
		os << v[i] << ", ";
	}
	return os << "\b\b}";
}

int main() {
	Vector v{3,1,4,3,1,9,10};
	Vector v2 {v};

	cout << v << endl;
	v2[3] = 2;
	cout << v2 << endl;

	return 0;
}



