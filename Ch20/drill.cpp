#include <vector>
#include <list>
#include <iostream>

using namespace std;

template<typename Iter>
void printout(Iter first, Iter last) {
	cout << "{";
	while (first != last) {
		cout << *first << ",";
		++first;
	}
	cout << "\b}\n";
}

template<typename Iter>
void add2(Iter first, Iter last) {
	while (first != last) {
		*first += 2;
		++first;
	}
}

template<typename Iter1, typename Iter2>	
	// requires Input_iterator<Iter1>() && Output_iterator<Iter2>()
	// Also, Iter1 and Iter2 must refer to compatible types for
	// assignment (e.g., a double and an int)
Iter2 mycopy(Iter1 f1, Iter1 e1, Iter2 f2) { //first1, end1, first2
	while (f1 != e1) {
		*f2 = *f1;
		++f1;
		++f2;
	}
	return f2;
}

int main() {
	int a[] {0,1,2,3,4,5,6,7,8,9};
	vector<int> v {0,1,2,3,4,5,6,7,8,9};
	list<int> l {0,1,2,3,4,5,6,7,8,9};

	int* a2 {a}; // shallow copy!!!
	vector<int> v2 {v};
	list<int> l2 {l};

	add2(a, a+10);
	add2(v.begin(), v.end());
	add2<list<int>::iterator>(l.begin(), l.end());
	add2(l.begin(), l.end());

	// printout(a, a+15) UH OHHHH this gives bad values
	printout<int*>(a, a+10); 
	printout<vector<int>::iterator>(v.begin(), v.end());
	printout(l.begin(), l.end());

	cout << "\nCopies...\n";
	printout<int*>(a2, a2+10);
	printout<vector<int>::iterator>(v2.begin(), v2.end());
	printout(l2.begin(), l2.end());

	//printout(a2+10, a2); // UH OH!!!!! Seggy fault. 

	cout << "\nCopying l into v, and a into l\n\n";
	mycopy(l.begin(), l.end(), v.begin());
	mycopy<int*, list<int>::iterator>(a2, a2+10, l.begin());

	cout << "a: ";
	printout(a, a+10);
	cout << "v: ";
	printout(v.begin(), v.end());
	cout << "l: ";
	printout(l.begin(), l.end());


	// bad coding practice below!!
	cout << "\nFinding stuff\n\n";
	vector<int>::iterator v_itr {find(v.begin(), v.end(), 8)};
	if (v_itr != v.end()) {
		cout << "Found 8 in v! At position: "
			<< v_itr - v.begin() << endl;
	}
	else {
		cout << "3 not in v...\n";
	}

	v_itr = find(v.begin(), v.end(), 99);
	if (v_itr != v.end()) {
		cout << "Found 99 in v! At position: "
			<< v_itr - v.begin() << endl;
	}
	else {
		cout << "99 not in v...\n";
	}

	auto l_itr = find(l.begin(), l.end(), 2);
	if (l_itr != l.end()) {
		cout << "Found 2 in l! At position: "
			<< l_itr - l.begin() << endl;
	}
	else {
		cout << "2 not in l...\n";
	}





	return 0;
}