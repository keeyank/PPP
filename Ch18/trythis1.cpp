#include <iostream>
#include <vector>

using namespace std;

struct X {
	int val;

	void out(const string& s, int nv) {
		cerr << this << ": " << s << ": Changed from " << val
			<< " to " << nv << "\n\n";
	}

	X() {
		out("Default constructor", 0); 
		val = 0;
	}
	X(int v) {
		out("Normal 1-param constructor", v);
		val = v;
	}
	X(const X& x){
		out("Copy constructor", x.val);
		val = x.val;
	}
	X& operator=(const X& x) {
		out("Copy assignment", x.val);
		val = x.val;
		return *this;
	}
	~X() {
		cout << this << ": Destructor called\n\n";
	}
};

//X glob(2);

X copy(X a) {
	cout << "In copy call\n\n";
	// Note the redundancy of the copy constructor
	// for the return value!
	return a;
}

X copy2(X a) {
	// I think the compiler compiles away the redundant
	// extra copy here, so the result is the same as for copy
	X aa = a;
	return aa;
}

X& ref_to(X& a) {return a;}

X* make(int i) {
	X a(i);
	return new X(a);
}

struct XX {
	X a; 
	X b;
};

int main() {
	//X loc {5};
	// X loc2 {loc};

	// loc2 = copy(loc);
	// cout << "Out of Copy call\n\n";

	// X loc3 = 6;
	// cout << "loc: " << &loc << "\nloc2: " << &loc2 
	// 	<< "\nloc3: " << &loc3 << "\n\n";

	// X& r = ref_to(loc); // No constructors called due to reference!
	// 					// No new objects are created here (params
	// 					// also are pass by reference)
	// X* loc4ptr = make(8);
	// cout << "Out of make call\n\n";
	// delete loc4ptr; // Without this delete, the object pointed to by loc4ptr
	// 				// is never destroyed.
	// delete make(7); // Order - First calls destructor for local var, then
	// 				// destructor for the object pointed by the pointer that
	// 				// make returns
	// vector<X>(4); // Vector is destroyed immediately after since not 
	// 				// initialized to nothing

	XX loc5;
	X* p = new X{9};
	delete p;
	// X* pp = new X[5]; // Interesting fact - X objects are precisely 4 bytes!
	// delete[] pp;

	// XX* ppp = new XX[3];
	// delete[] ppp;


	return 0;
}



