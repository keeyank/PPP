#include <iostream>

using namespace std;

// This is fine, but you might as well pass by const reference
// Since your not changing the value of m, you are just copying
// it for no good reason. Pass by const reference just passes 
// the reference, so no unneccessary copying is done.
void stuff(const int m) {
	//++m; Doesn't compile - m can't be changed
	cout << m << endl;
}

int main() {
	int m = 0;
	int const mc = 3;
	stuff(1); // Compiles!
	stuff(m); // Compiles
	stuff(mc); // Compiles
	return 0;
}
