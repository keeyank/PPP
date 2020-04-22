#include <vector>
#include <fstream>

#include "container_stuff.h"

using namespace std;

/*---------------------------------------------*/

int* read_jack(int* count) {
	ifstream ifs {"jack.txt"};
	
	int* a = new int[100];
	*count = 0;
	while (ifs >> a[*count]) {
		++*count;
	}

	return a;
}

vector<int> read_jill() {
	ifstream ifs {"jill.txt"};
	vector<int> v;
	for (int tmp; ifs >> tmp;) {
		v.push_back(tmp);
	}
	return v;
}

/*---------------------------------------------*/

int* high(int arr[], int count) {
	if (count <= 0) return nullptr;

	int* max = arr;
	for (int i = 1; i < count; ++i) {
		if (arr[i] > *max) max = &arr[i];
	}
	return max;
}

template<typename Iter> // Requires Input_iterator
Iter high(Iter first, Iter last) {
	if (first >= last) return last;
	Iter high = first;
	for (Iter curr = first; curr != last; ++curr) {
		if (*curr > *high) high = curr;
	}
	return high;
}

/*---------------------------------------------*/

int main() {
	int jack_count;
	int* jack_data = read_jack(&jack_count);
	vector<int> jill_data = read_jill();

	// printout(jack_data, jack_data+jack_count);
	// printout(jill_data.begin(), jill_data.end());

	int* jack_high = high(jack_data, jack_data+jack_count);
	// int* jill_high = high(&jill_data[0], 
	// 		&jill_data[0] + jill_data.size());
	auto jill_high = high(jill_data.begin(), jill_data.end());

	cout << "Jill's max: " << *jill_high
		<< "; Jack's max: " << *jack_high << endl;

	delete[] jack_data;
	return 0;
}