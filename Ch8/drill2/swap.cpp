#include <iostream>

using namespace std;

// This compiles, but it's useless - swaps 2 copies of a and b
// The copies are destroyed once program exits function scope
void swap_v(int a, int b) {
	int temp = a;
	a = b;
	b = temp;
	// implicit return here
}

void swap_r(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

// This won't compile - setting the value of a const reference
// is illegal
// void swap_v(const int& a, const int& b) {
// 	int temp = a;
// 	a = b;
// 	b = temp;
// }

int main() {
	int x = 7;
	int y = 9;
	swap_v(x, y); // Compiles, x and y in this scope not swapped
	swap_v(7, 9); // Compiles, doesn't do anything
	swap_r(x, y); // Compiles, x and y are swapped.
	//swap_r(7, 9); // Doesn't compile - expects lvalues (variable names)
				  // so it can operate on the object named by the variable

	const int cx = 7;
	const int cy = 9;
	swap_v(cx, cy); // Compiles - copies constants cx and cy to non-const ints
					// Then operates on those ints. Doesn't do anything.
	//swap_r(cx, cy); // Doesn't compile - const qualifiers not preserved when
					// cx and cy passed by reference, the function may write
					// to cx and cy (and it does in this case)

	double dx = 7.7;
	double dy = 9.9;
	swap_v(x, y);	// Compiles, doesn't generate warnings, Doesn't do anything
	swap_v(7.7, 9.9); // Compiles, generates implicit conversion warnings,
					  // Doesn't do anything
	//swap_r(dx, dy); // Doesn't compile - can't convert a double to an int reference
					// Makes sense, dx and dy are doubles, so a reference to an int
					// can't refer to the same object that dx or dy refers to.
	swap_r(7.7, 9.9) // Same problem as in line 34
	
	

	cout << cx << " " << cy << '\n';

	return 0;
}