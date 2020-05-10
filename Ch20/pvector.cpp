#include "test_class.h"
#include "container_stuff.h"

/*
This is analogous to a unique_ptr, but now its a vector of
pointers.
Data structures like this are useful for object oriented programming
(like when we had a vector of Shape*'s. We couldn't use normal Shape
objects in the vector, since the Shapes were actually derived classes
that may have more member variables, and we don't want slicing to occur)
*/

template<typename T>
	// requires Element<T>
struct pvector {
	struct iterator {
		iterator(typename vector<T*>::iterator it)
			:curr{it} { }

		iterator operator++() {return ++curr;}
		iterator operator--() {return --curr;}

		T& operator*() {return *(*curr);}

		bool operator==(iterator it) {return curr == it.curr;}
		bool operator!=(iterator it) {return !(*this == it);}
	private:
		typename vector<T*>::iterator curr;
	};

	pvector()
		: pv{} {}
	pvector(initializer_list<T*> l);
	~pvector();

	pvector(const pvector& p) = delete;
	pvector& operator=(const pvector& p) = delete;

	iterator begin() {return iterator{pv.begin()};}
	iterator end() {return iterator{pv.end()};}

	T& operator[](int i) {return *pv[i];}
	void push_back(T* p) {
		pv.push_back(p);
	}

	T* release(int i);

	friend ostream& operator<<(ostream& os, const pvector& p) {
		for (T* e : p.pv) {
			if (!e) {cout << "(nullptr) "; continue;}
			os << "(" << e << ", " << *e << ") ";
		}
		os << endl;
		return os;
	}
private:
	vector<T*> pv;
};

template<typename T>
pvector<T>::pvector(initializer_list<T*> l) 
	: pv(l.size())
{
	copy(l.begin(), l.end(), pv.begin());
}

template<typename T>
pvector<T>::~pvector() {
	for (T* p : pv) {
		delete p;
	}
}

/*
This will invalidate any current iterators, so be careful
when using erase in conjunction with iterators!
(use an integer index reference instead, like the technique
used in 20.8 in the insert code)
*/
template<typename T>
T* pvector<T>::release(int i) {
	T* p = pv[i];
	pv.erase(pv.begin() + i);
	return p;
}

int main() {
	//{
	// 	pvector<X> pv {new X{"a",1}, new X{"b",2}, new X{"c",3}, nullptr};
	// 	delete pv[2]; // Make sure to set pv[2] to nullptr after (else 
	// 		// destructor shall delete AGAIN!!)
	// 	pv[2] = nullptr; // Make sure we destroy pv[2] first
	// 	pv[3] = new X{"d", 4};
	// 	cout << pv;

	// 	//pvector<X> pv2 = pv; // Uh oh - Objects will be deleted twice by each
	// 		// destructor! So delete copy assignment/construction

	// }

	{
		pvector<X> pv {new X{"a",1}, new X{"b",2}};
		pv.push_back(new X{"A",1});
		printout(pv.begin(), pv.end());
		cout << pv;
		pv[2] = X{"c",3};
		cout << pv[1] << endl;
		cout << pv;
		pv[0].f();

		//delete &pv[1]; // Uh oh, bad news for destructor!
		X* x = pv.release(1); // We are now responsible for deleting
		delete pv.release(1); // refers to final element (since elements
			// got moved downwards)
		delete x;
		printout(pv.begin(), pv.end());
	}

	/*
	For ownership_vector, we should update the iterator so that it
	skips over nullptrs. We should also have a function that returns
	a ptr, and sets the ptr at its index to nullptr, so when the destructor
	destroys it, it won't lead to a double deletion situation.
	*/
	return 0;
}