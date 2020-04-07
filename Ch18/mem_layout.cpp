#include <iostream>

using namespace std;

int i = 0;
int* static_ptr = &i;

int main() {
	int stack_ptr[2] {1, 2};
	if (stack_ptr < stack_ptr+1) {
		cout << "Stack grows towards high memory.\n";
	}
	else {
		cout << "Stack grows towards low memory.\n";
	}

	int* heap_ptr = new int[2] {1, 2};
	if (heap_ptr < heap_ptr+1) {
		cout << "Heap grows towards high memory.\n";
	}
	else {
		cout << "Heap grows towards low memory.\n";
	}

	if (heap_ptr > stack_ptr) {
		cout << "Heap above stack.\n";
	}
	else {
		cout << "Stack above heap.\n";
	}

	if (static_ptr > heap_ptr) {
		cout << "Static storage above heap.\n";
	}
	else {
		cout << "Heap above static storage.\n";
	}
	delete[] heap_ptr;
	return 0;
}
