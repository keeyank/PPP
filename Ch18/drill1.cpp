#include <iostream>
#include <vector>

using namespace std;

int ga[] = {1,2,4,8,16};

void f(int a[], int n) {
	int la[10] {}; // {} to zero-initialize
	for (int i = 0; i < n; ++i) {
		la[i] = a[i];
	}
	for (int i = 0; i < 10; ++i) {
		cout << la[i] << ' ';
	}
	cout << endl;

	int* p = new int[n];
	for (int i = 0; i < n; ++i) {
		p[i] = a[i];
	}
	for (int i = 0; i < n; ++i) {
		cout << p[i] << ' ';
	}
	cout << endl;
	delete[] p;
}

int main() {
	f(ga, 5);
	int a[10] {1,2*1,3*2,4*3*2,5*4*3*2,36*4,7,8,9,10};
	f(a,10);
	return 0;
}



