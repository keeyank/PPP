#include "test_class.h"

// T must have copy defined, and be able to be allocated
// on free store / be dereferenced.
template<typename T>
struct Counted_ptr {

	Counted_ptr(const T& val)
		: ptr{new T{val}}, use_count{new int{1}} { }

	Counted_ptr(const Counted_ptr&);
	Counted_ptr& operator=(const Counted_ptr&);

	// Counted_ptr(Counted_ptr&& up);
	// Counted_ptr& operator=(Counted_ptr&& up);

	T& operator*() {
		return *ptr;
	}

	T* operator->() {
		return ptr;
	}

	~Counted_ptr() {
		--*use_count;
		if (*use_count == 0) {
			delete ptr;	
			delete use_count;
		}
	}


private:
	T* ptr;
	int* use_count;
};

template<typename T>
Counted_ptr<T>::Counted_ptr(const Counted_ptr<T>& cp)  
		: ptr{cp.ptr}, use_count{cp.use_count}
{
	++*use_count;
}

template<typename T>
Counted_ptr<T>& Counted_ptr<T>::operator=(const Counted_ptr<T>& cp) {
	if (cp.ptr == ptr) return *this;

	--*use_count;
	if (*use_count == 0) {
		delete ptr;
		delete use_count;
	}

	ptr = cp.ptr;
	use_count = cp.use_count;
	++*use_count;

	return *this;
}

template<typename T>
Counted_ptr<T> get_cp(Counted_ptr<T> cp1) {
	cp1->a = "get_cp was here";
	return Counted_ptr<T>{T{}};
}

int main() 
try {
	Counted_ptr<X> cp1 {X{"Mr. Rogo.", 1}};

	// /* 1 */
	// {
	// 	(*cp1).a = "Mr Bogologo";
	// 	cp1->f();
	// 	cout << *cp1 << endl;
	// }

	// /* 2 */
	// {
	// 	Counted_ptr<X> cp2 {cp1};
	// 	cp1->a = "Wogor";
	// 	cp2->b = 41;
	// 	cp1->f();

	// 	Counted_ptr<X> cp3 {cp1};
	// 	Counted_ptr<X> cp4 {X{}};
	// 	cp1 = cp2; // Nothing should change;
	// }

	// /* 3 */
	// {
	// 	Counted_ptr<X> cp2 {X{"Monkeyman", 18}};
	// 	cout << "cp1 and cp2 constructed\n\n";

	// 	cp2 = cp1;
	// 	cp2->a = "Monkeyman Dynasty";
	// 	cp1->f();
	// }

	// /* 4 */
	// {
	// 	Counted_ptr<X> cp2 {X{"Monkeyman", 18}};
	// 	Counted_ptr<X> cp3 {cp2};
	// 	{ // scope to call cp4's destructor early
	// 		Counted_ptr<X> cp4 {cp2};
	// 	}
	// 	cout << "cp1, cp2, cp3 constructed.\n\n";

	// 	*cp2 = X{"Chunko", 12};
	// 	cp2 = cp1;
	// 	cp2->a = "Monkeyman Dynasty";
	// 	cp1->f();
	// }

	// /* 5 */
	// {
	// 	Counted_ptr<X> cp2 = get_cp(cp1);
	// 	cp1->f();
	// 	cp2->f();

	// 	cp2 = get_cp(cp2);
	// }

	// /* 6 */
	// {
	// 	Counted_ptr<X> cp2 = cp1;
	// 	Counted_ptr<X> cp3 = cp2;
	// 	Counted_ptr<X> cp4 = get_cp(cp3);
	// 	cp3 = get_cp(cp4);
	// }

	return 0;
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
	return 1;
}

