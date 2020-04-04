#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

void print_array(ostream& os, int* a, int n) {
	for (int i = 0; i < n; ++i) {
		cout << a[i] << endl;
	}
}

void print_vector(ostream& os, const vector<int>& v) {
	for (int i = 0; i < v.size(); ++i) {
		cout << v[i] << endl;
	}
}

int main() {

	// // p2rt 1
	// int* a = new int[10];
	// print_array(cout, a, 10);
	// delete[] a;

	// int* b = new int[10] {10,11,12,13,14,15,16,17,18,19};
	// print_array(cout, b, 10);
	// delete[] b;

	// int* c = new int[11] {10,11,12,13,14,15,16,17,18,19,20};
	// print_array(cout, c, 11);
	// delete[] c;

	// int* d = new int[20];
	// for (int i = 0; i < 20; ++i) {
	// 	d[i] = rand();
	// }
	// print_array(cout, d, 20);
	// delete[] d;

	// vector<int> bv {10,11,12,13,14,15,16,17,18,19};
	// print_vector(cout, bv);

	// vector<int> cv {10,11,12,13,14,15,16,17,18,19,20};
	// print_vector(cout, cv);

	// vector<int> dv(20);
	// for (int i = 0; i < 20; ++i) {
	// 	dv[i] = rand();
	// }
	// print_vector(cout, dv);

	// p2rt 2
	int* p1 = new int {7};
	cout << "Address: " << p1 << "\nContents of: " << *p1 << endl;
	int* p2 = new int[7] {1,2,4,8,16,32,64};
	cout << "Address: " << p2 << "\nContents of: {";
	for (int i = 0; i < 6; ++i) {
		cout << p2[i] << ", ";
	}
	cout << p2[6] << "}\n";
	int* p3 = p2;
	delete p1;
	p1 = p2;
	p2 = p3;
	cout << "p1: {";
	for (int i = 0; i < 6; ++i) {
		cout << p1[i] << ", ";
	}
	cout << p2[6] << "}\n";
	cout << "p2: {";
	for (int i = 0; i < 6; ++i) {
		cout << p2[i] << ", ";
	}
	cout << p2[6] << "}\n";

	delete[] p2;
	// delete[] p1; // Error: Contents already freed by delete[] p2!

	p1 = new int[10] {1,2,4,8,16,32,64,128,256,512};
	p2 = new int[10];
	for (int i = 0; i < 10; ++i) {
		p2[i] = p1[i];
	}
	delete[] p1;
	cout << "\n\n\n\n\n\n\n\n\n\np1: " << p1 << '\n';

	cout << "p2: {";
	for (int i = 0; i < 10; ++i) {
		cout << p2[i] << ", ";
	}
	cout << p2[9] << "}\n";

	vector<int> v1 {1,2,4,8,16,32,64,128,256,512};
	vector<int> v2 {v1};
	print_vector(cout, v1);

	return 0;
}