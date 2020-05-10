#include <vector>
#include <fstream>

#include "container_stuff.h"
#include "list.h"

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

/*
Note - the first >= last check does not work for bidirectional
iterators (like List's iterator). <= does not make sense as an 
operation for List iterators - the underlying Link* may be located
in arbitrary locations in the free store!
*/
template<typename Iter> // Requires Input_iterator
Iter high(Iter first, Iter last) {
	//if (first >= last) return last;
	Iter high = first;
	for (Iter curr = first; curr != last; ++curr) {
		if (*curr > *high) high = curr;
	}
	return high;
}

/*---------------------------------------------*/

/*
Remember f1++ returns the iterator f1 before the increment
Unlike ++f1, which returns the iterator f1 after the increment
We could have equivelantly done
*f2 = *f1;
++f1;
++f2;
*/
template<typename Itr1, typename Itr2>
	// requires Itr1 be input iterator, Itr2 be output iterator
void mycopy(Itr1 f1, const Itr1& e1, Itr2 f2) {
	while (f1 != e1) {
		*f2++ = *f1++;
	}
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

	/* Exercise 5 */

	vector<string> jombo_data {"aeh","wer","or","asf","awe","otr",
			"wer", "wer","as","gsds","gdw","ger","sti","stu","moh",
			"xyo", "zzz"};
	auto jombo_max = high(jombo_data.begin(), jombo_data.end());
	cout << "How could we forget Jombo! Jombo's max: "
		<< *jombo_max << endl;

	/* Exercise 10 */
	copy(jack_data, jack_data+jack_count, jill_data.begin());
	sort(jill_data.begin(), jill_data.end());
	printout(jack_data, jack_data+jack_count);
	printout(jill_data.begin(), jill_data.end());
	printout(jombo_data.begin(), jombo_data.end());

	/* Exercise 12 */
	List<int> bugy_data {4,4,1,4,5,2,4,1,0,5,2,6,8,29,3
			,690,30,683,91,06,94,02,8};
	List<int>::Iterator bugy_max = high(bugy_data.begin(),
		 bugy_data.end());
	cout << "Bugy in da house !! Bugy's max: " << *bugy_max << endl;
	printout(bugy_data.begin(), bugy_data.end());

	delete[] jack_data;
	return 0;
}