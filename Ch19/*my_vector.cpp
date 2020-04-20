#include "*alloc.h"

template<typename T, typename A = Allocator<T>>
class Vector {
public:
	explicit Vector(unsigned long n, T def = T{});
	// deallocate is legal with nullptr
	Vector()
		: alloc{}, sz{0}, space{0}, elem{nullptr} { }
	Vector(std::initializer_list<T> lst);
	Vector(const Vector& v);
	Vector(Vector&& v);
	~Vector();

	Vector& operator=(const Vector& v);
	Vector& operator=(Vector&& v);

	void push_back(const T& val);
	void resize(int newsize, T val = T{});

	unsigned long size() const {
		return sz;
	}

	T& operator[] (unsigned long n) {
		return elem[n];
	}
	const T& operator[](unsigned long n) const {
		return elem[n];
	}

private:
	A alloc; // A defaults to Allocator<T>

	void reserve(int newspace);

	/*
	Invariants:
	sz <= space
	[sz, space) is uninitialized (raw memory)
	[0, sz) is initialized (not just raw memory)
	*/
	unsigned long sz;
	unsigned long space;
	T* elem;
};

template<typename T, typename A>
Vector<T,A>::Vector(unsigned long n, T def)
	: alloc{}, sz{n}, space{n}, elem{alloc.allocate(space)}
{
	for (int i = 0; i < sz; ++i) {
		alloc.construct(&elem[i], def);
	}
}

template<typename T, typename A>
Vector<T,A>::Vector(initializer_list<T> lst)
	: sz{lst.size()}, space{sz}, elem{alloc.allocate(space)}
{
	const T* lstptr = lst.begin();
	for (int i = 0; i < sz; ++i) {
		alloc.construct(elem+i, lstptr[i]);
	}
}

/*
We can't just call copy(v.elem, v.elem + sz, elem) anymore.
If we did that, we would be copying the bytes of each element,
and that would be a shallow copy if our element type was another
container. We need to explicitly call the copy constructor for 
each element, and we can do that using construct.
*/
template<typename T, typename A>
Vector<T,A>::Vector(const Vector<T,A>& v) 
	: sz{v.sz}, space{sz}, elem{alloc.allocate(space)}
{
	for (int i = 0; i < sz; ++i) {
		alloc.construct(elem+i, v.elem[i]);
	}
}

/*
"Steal" representation from v.
No reason to copy, since v will be immediately destroyed after
move constructor (e.g., if v is a return value from a function).
*/
template<typename T, typename A>
Vector<T,A>::Vector(Vector<T,A>&& v) 
	: sz{v.sz}, space{v.space}, elem{v.elem}
{
	v.sz = 0;
	v.space = 0;
	v.elem = nullptr;
}

/*
Copy assignment - note the this == &v check. Copy assignment
breaks without this check if you assign a vector to itself.
*/
template<typename T, typename A>
Vector<T,A>& Vector<T,A>::operator=(const Vector<T,A>& v) {
	if (this == &v) {
		return *this;
	}

	reserve(v.sz);
	for (int i = 0; i < sz; ++i) {
		alloc.destroy(elem+i);
	}
	for (int i = 0; i < v.sz; ++i) {
		alloc.construct(elem+i, v.elem[i]);
	}
	sz = v.sz;
	return *this;
}

/* 
Steal representation, but also destroy old representation of
the vector to ensure no memory leaks, since this is assignment
and not construction. 
*/
template<typename T, typename A>
Vector<T,A>& Vector<T,A>::operator=(Vector<T,A>&& v) {
	for (int i = 0; i < sz; ++i) {
		alloc.destroy(&elem[i]);
	}
	alloc.deallocate(elem); // OK if elem == nullptr

	sz = v.sz;
	space = v.space;
	elem = v.elem;

	v.sz = 0;
	v.space = 0;
	v.elem = nullptr;
	return *this;
}

/*
Destroy everything in range [0, sz)
Assumes everything beyond sz is destroyed.              
*/
template<typename T, typename A>
Vector<T,A>::~Vector() {
	for (int i = 0; i < sz; ++i) {
		alloc.destroy(&elem[i]);
	}
	alloc.deallocate(elem);
}

template<typename T, typename A>
void Vector<T,A>::reserve(int newspace) {
	if (newspace <= space) return;
	T* p = alloc.allocate(newspace);
	for (int i = 0; i < sz; ++i) {
		alloc.construct(p+i, elem[i]);
		alloc.destroy(elem+i);
	}
	alloc.deallocate(elem);
	elem = p;
	space = newspace;
}

template<typename T, typename A>
void Vector<T,A>::push_back(const T& val) {
	if (space == 0) reserve(8);
	if (sz == space) reserve(2*space);
	alloc.construct(elem+sz, val);
	++sz;
}

/*
Resize vector such that it can hold newsize elements
If newsize < size, destroy old elements but don't update space
if newsize > size, give make new elements have value val, 
and only allocate the minimal amount of space.
*/
template<typename T, typename A>
void Vector<T,A>::resize(int newsize, T val) {
	reserve(newsize); 
	for (int i = sz; i < newsize; ++i) {
		alloc.construct(elem+i, val);
	}
	for (int i = newsize; i < sz; ++i) {
		alloc.destroy(elem+i);
	}
	sz = newsize;
}

// DEBUG

template<typename A>
ostream& operator<<(ostream& os, const Vector<A>& v) {
	for (int i = 0; i < v.size(); ++i) {
		cout << v[i] << ' ';
	}
	cout << endl;
	return os;
}

Vector<X,Allocator<X>> make_vec() {
	cout << "In make_vec\n";
	Vector<X> v {X{1, "yooo"}, X{3, "a!!!"}};
	cout << "About to exit make_vec\n";
	return v;
}

int main() {
	// Vector v1 {1,2,3};
	// Vector v2 {1,3,5,7,8,9,10,21};
	// v1 = v2;

	// Vector v3 = make_vec();
	// v3[v3.size()-1] = v3[v3.size()-1]/2;
	// v1 = v3;
	// v1 = make_vec();
	// v2[1] = v1[1];

	// cout << v1 << v2 << v3;

	// {
	// 	Vector v1(10);
	// 	Vector v2(10,5);
	// 	cout << v1 << v2;

	// 	Vector v3{1,2,3};
	// 	cout << v3;
	// 	Vector v4{};
	// 	cout << v4;

	// 	Vector v5 = v3;
	// 	cout << v5;
	// 	v5[2] = 2;
	// 	v5[1] = 0;
	// 	cout << v3 << v5;

	// 	const Vector v6 = v2;
	// 	v2[1] = -5;
	// 	cout << v2 << v6;
	// }

	// {
	// 	Vector<X> v1 {X{1,"Tom"}, X{2,"Billbob"}, X{3,"Turtl"}};
	// 	v1.resize(5, X{4,"Santa"});
	// 	cout << v1 << "\n\n";

	// 	Vector<X> v2 = v1;
	// 	cout << v2 << "\n\n";

	// 	Vector<X> v3 {};
	// 	cout << v3 << "\n\n";

	// 	Vector<X> v4 = make_vec();
	// 	cout << v4 << "\n\n";

	// 	v4[1] = X{1, "Hello"};
	// 	v2[0] = X{1, "Hello"};

	// 	cout << v1 << v2 << v3 << v4;


	// }

	{
		Vector<X> v1;
		cout << v1 << "\n\n";
		v1.push_back(X{1, "sire"});
		cout << v1 << "\n\n";
		v1.push_back(X{2, "bingo"});
		cout << v1 << "\n\n";

		for (int i = 0; i < 100; ++i) {
			v1.push_back(X{i,"wee!!"});
		}

		v1.resize(30);

		v1.resize(50);

		Vector<X> v2;
		v2 = v1;

		v1 = v1;
		v2 = v2;

		cout << v1 << v2;

		Vector<X> v3;
		v1 = v2 = v3; // Destructors for all of v2 and v1s elements called

		cout << v1 << v2 << v3; // Just prints a bunch of newlines

		Vector<X> v4 {X{1,"bingey"}, X{2, "Stingy"}, X{3, "slingey"}};
		v1 = v4;
		v4[1] = X{2, "Stunkey"};
		cout << v1 << v4;

		Vector<X> v5;
		for (int i = 0; i < 20; ++i) {
			v5.push_back(X{i, "Henglo"});
		}

		v5 = v4;
		cout << v4 << v5;

		Vector<X> v6;
		for (int i = 0; i < 20; ++i) {
			v6.push_back(X{i, "Henglo"});
		}
		v6 = make_vec();
		cout << v6;
	}

	return 0;
}