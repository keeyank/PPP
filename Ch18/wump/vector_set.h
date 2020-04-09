#include <iostream>
#include <vector>

using namespace std;

/*
Set that supports accessing random elements
Only supports types that support copying (for pass-by-value), 
equality comparisons (for checking if an element is in set),
and the << operator (for debugging)
Also, must be able to be a template parameter for vector
*/
template <typename T> 
struct Vector_set {
	Vector_set() { }

	// Return true if elem in set, else return false
	bool in(T elem) const;
	// Insert elem into set, ensure elem is not a duplicate
	// If elem is a duplicate, do nothing
	void insert(T elem);
	// Remove elem from the set
	// If elem is not in the set, do nothing
	void remove(T elem);
	// Get a random element from Vector_set
	T get_rand() const;

	// For debugging
	friend ostream& operator<<(ostream& os, const Vector_set& vs) {
		os << "{";
		for (int i = 0; i < vs.set.size(); ++i) {
			os << vs.set.at(i);
			if (i != vs.set.size()-1) os << ", ";
		}
		return os << "}";
	}
private:
	// Invariant - no duplicate elements in set
	vector<T> set;
};

template<typename T>
void Vector_set<T>::insert(T elem) {
	if (!in(elem)) set.push_back(elem);
}

template<typename T>
bool Vector_set<T>::in(T elem) const {
	for (int i = 0; i < set.size(); ++i) {
		if (elem == set.at(i)) return true;
	}
	return false;
}

template<typename T>
void Vector_set<T>::remove(T elem) {
	for (auto it = set.begin(); it < set.end(); ++it) {
		if (*it == elem) {
			set.erase(it); 
			return; 
		}
	}
}

template<typename T>
T Vector_set<T>::get_rand() const {
	if (set.size() <= 0) {
		throw runtime_error("Vector_set<T>::get_rand(): Attempted to"
				" get element from empty set");
	}
	return set.at(rand() % set.size());
}
