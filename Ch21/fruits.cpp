#include <string>
#include <iostream>
#include <set>

using namespace std;

/*
Implementation differences:
set<Fruit*> - doesn't copy the Fruit, but rather just the Fruit pointer.
When we iterate through/retrieve values, we are retrieving pointers.
Have to remember to delete pointers if we allocate on free store.
If we are using primitive type pointers (e.g., int) we can't rely on
default less_than comparison - we have to specify the comparison 
operator to work on the dereference of the pointer. 
*/

struct Fruit {
	string name;
	int count;
};

struct Fruit_cmp {
	bool operator()(const Fruit* a, const Fruit* b) const {
		return a->name < b->name;
	}
};

ostream& operator<<(ostream& os, const Fruit* f) {
	return os << f->name << ' ' << f->count;
}

int main() {
	set<Fruit*, Fruit_cmp> sf;

	Fruit pear {"Pear", 10};
	Fruit apple {"Apple", 8};
	Fruit grape {"Grape", 49};
	Fruit pineapple {"Pineapple", 2};
	Fruit strawberry {"Strawberry", 25};
	Fruit* mango_ptr {new Fruit{"Mango", 6}};

	sf.insert(&pear);
	sf.insert(&apple);
	sf.insert(&grape);
	sf.insert(&pineapple);
	sf.insert(&strawberry);
	sf.insert(mango_ptr);

	ostream_iterator<Fruit*> oi {cout, "\n"};
	copy(sf.begin(), sf.end(), oi);

	for (const Fruit* p : sf) {
		cout << p->name << endl;
	}

	delete mango_ptr;
	return 0;
}