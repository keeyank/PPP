#include "test_class.h"

template<typename T>
struct Unique_ptr {
	Unique_ptr(T* p)
		: ptr{p} { }

	// Prevent copying
	Unique_ptr(const Unique_ptr&) = delete;
	Unique_ptr& operator=(const Unique_ptr&) = delete; 

	Unique_ptr(Unique_ptr&& up)
		: ptr{up.ptr}
	{
		up.ptr = nullptr;
	}
	Unique_ptr& operator=(Unique_ptr&& up) {
		delete ptr;
		ptr = up.ptr;
		up.ptr = nullptr;
		return *this;
	}

	T& operator*() {
		return *ptr;
	}

	/* 
	Returns the unique_ptr's underlying pointer, then gets access
	to whatever is after the ->. So
	p->x is equivelant to p.operator->()->x
	and p->f() is equivelant to p.operator->()->f()
	(see (3))
	*/
	T* operator->() {
		return ptr;
	}

	/*
	Note how release makes ptr = nullptr
	This is because it is transfering ownership - we expect them to
	delete, and if we delete the object as well, that's bad news!
	So we set our ptr to nullptr so nothing bad happens.
	*/
	T* release() {
		T* p = ptr;
		ptr = nullptr; 
		return p;
	}

	~Unique_ptr() {
		delete ptr;
	}


private:
	T* ptr;
};

template<typename T>
Unique_ptr<T> get_unique_ptr() {
	return Unique_ptr<T>{new T{}};
}

int main() 
try {
	Unique_ptr<X> p1 {new X{"hey", 1}};

	// /* (1) */
	// {
	// X* x {new X{"Helo!", 2}};
	// Unique_ptr<X> p2 {x};
	// // delete x; // Uh oh!!! 
	// 	// Unique_ptr has ownership, it will also delete in destructor

	// (*p1).f();
	// (*p1).a = "Hey!!!";
	// (*p1).b += 2*((*p1).b);
	// X x2 = *p1;
	// x2.f();
	// }

	// /* (2) */
	// {
	// X& p2 = *p1; // Bad name (too lazy to change)
	// p2.b = 3;
	// p2.f();

	// X p3 {};
	// p3 = *p1;
	// p3.a = "Wooo!";
	// p3.f();

	// Unique_ptr<X> up3 {p1}; // Error!!! Copy constructor deleted. GOOD!
	// }

	// /* (3) */
	// {
	// 	// Implicit calls to operator->
	// 	p1->a = "GUNKY"; 
	// 	p1->f();
	// 	// Explicit calls to operator->
	// 	p1.operator->()->b = 10;
	// 	p1.operator->()->f();

	// 	// Note how this doesn't work!
	// 	// X* raw_ptr = p1->f(); 
	// 	// X* raw_ptr2 = p1.operator->()->f(); // Expression returns void*
	// 	// This does work though (kinda bad, but whatever!)
	// 	// We don't want people to do this, we would rather they use
	// 	// release instead
	// 	X* raw_ptr3 = p1.operator->();
	// 	raw_ptr3->b = 100;
	// }

	// /* (4) */
	// {
	// 	//p1.release();
	// 	// Uh oh, we forgot to set it to anything - memory leak!
	// 	//delete p1.release(); // Pretty pointless (it would have deleted
	// 		// anyways)
	// 	X* ptr = p1.release();
	// 	ptr->a = "I am cool";
	// 	delete ptr;
	// }

	// /* (5) */
	// {
	// 	Unique_ptr<X> p2 = get_unique_ptr<X>();
	// 	p2->a = "Mr Kark";
	// 	p2->f();
	// 	p1 = get_unique_ptr<X>();
	// 	p1->f();
	// 	// Destroys p2 here, then destroys p1 at return statement below
	// }

	return 0;
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
	return 1;
}

