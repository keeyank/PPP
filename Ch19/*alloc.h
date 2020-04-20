#include <cstdlib>

// For debug
#include <iostream>
#include <string>

using namespace std;

/*
Here's a good resource on destructors / placement new / etc.
https://isocpp.org/wiki/faq/dtors
*/

template<typename T>
struct Allocator {
	T* allocate(int n);
	void deallocate(T* p);

	void construct(T* p, const T& v);
	void destroy(T* p);
};

/*
Allocate space for T on free store and return ptr to space, does not
initialize (so value is undefined, probably just whatever bytes
that space in memory had before.) Must use construct to initialize.
Return nullptr if n <= 0
*/
template<typename T>
T* Allocator<T>::allocate(int n) {
	if (n <= 0) return nullptr;
	void* p = malloc(sizeof(T) * n);
	return static_cast<T*>(p);
}

/*
This simply deallocates the space from the block that p refers to
It requires that p be the return value of a malloc (see its doc)
Thus, deallocate has the same requirement. 
free(nullptr) does nothing.

You must have allocated p with allocate before calling deallocate
on p. Also, you have to make sure all of the objects in p are
destroyed before calling this, or you may have a memory leak!
*/
template<typename T>
void Allocator<T>::deallocate(T* p) {
	free(p);
}

/*
Placement new is a way to construct an object without allocating
space for it, but rather constructing it onto a pre-allocated part
of memory. That's what construct does. We can throw away the 
return value from new, since we just want to construct.

You have to be very careful when calling this - it assumes that
the portion in memory is large enough to hold something of size
T, so make sure p is a T* pointer returned from allocate, and
be very very careful with pointer arithmetic!
*/
template<typename T>
void Allocator<T>::construct(T* p, const T& v) {
	new (p) T{v}; // Calls copy constructor
}

/*
Explicitly call the destructor of the pointed to object.
*/
template<typename T>
void Allocator<T>::destroy(T* p) {
	p->~T();
}


/* DEBUG */


struct X {
	int a {};
	string b {};

	X()
		: a{0}, b{"default"}
	{
		cout << "Default constructor called for " << *this << "\n";
	}
	X(int aa, string bb)
		: a{aa}, b{bb} 
	{ 
		cout << "Constructor called for " << *this << "\n";
	}
	X(const X& x) {
		a = x.a;
		b = x.b;
		cout << "Copy constructor called for " << *this << "\n";
	}
	~X() {
		cout << "Destructor called for " << *this << "\n";
	}

	friend ostream& operator<<(ostream& os, const X& x);
};

ostream& operator<<(ostream& os, const X& x) {
	return cout << x.a << ' ' << x.b;
}


// int main() {

// 	Allocator<X> alloc;
// 	X* xptr = alloc.allocate(5);
// 	X x0 {32, "x0"};
// 	alloc.construct(xptr, x0);
// 	X x1 {43, "x1"};
// 	alloc.construct(xptr+1, x1);
// 	alloc.construct(&xptr[2], X{531, "x2"});

// 	alloc.destroy(xptr+1);
// 	alloc.destroy(xptr+2);

// 	for (int i = 0; i < 5; ++i) {
// 		cout << xptr[i] << endl;
// 	}

// 	alloc.deallocate(xptr);
// 	// We forgot to destroy xptr[0]! OOPS
// 	cout << "Normal out of scope destructors will now start\n";
	

// 	return 0;
// }

