#include <vector>
#include <iostream>

using namespace std;

void suspicious(vector<int> v, int s) {
	int* p = new int[s];
	vector<int> v1;

	try {
		//v1.at(0);
	}
	catch (exception& e) {
		cout << "Caught exception: " << e.what() << ", freeing p\n";
		delete[] p;
		throw;
	}

	int* q = new int[s];
	vector<double> v2;

	try {
		v2.at(s);
	}
	catch (exception& e) {
		cout << "Caught exception: " << e.what() << ", freeing p and q\n";
		delete[] p;
		delete[] q;
		throw;
	}

	delete[] p;
	delete[] q;
}

int main() {
	suspicious(vector<int>{1,2,3}, 3);
	return 0;
}