#include <vector>
#include <iostream>

using namespace std;

template<typename T> 
struct S { 
	S(T v)
		: val{v} { }

	T get() const {return val;}
	T& get() {return val;}
	void set(T v) {val = v;}

	S& operator=(const T& v);

	// friend - not a true member function (the class object is
	// an explicit argument rather than implicit) but basically
	// a member function - has access to that objects private members
	// Avoid friend's as much as you possibly can, only use them when 
	// they are absolutely required (input/output operators are an example
	// where they are required). Why?
	// Because it's probably not good to have a non-member function have
	// access to the object's private members (this defeats the purpose of
	// encapsulation)

	// We always need to pass by reference for the class S,
	// since we haven't defined a copy constructor

	// Weird issue with templates - function definition has to be here,
	// or we get a linker error - https://stackoverflow.com/questions/456713/why-do-i-get-unresolved-external-symbol-errors-when-using-templates
	friend ostream& operator<<(ostream& os, const S& s) {
		return os << s.val;
	}
	friend istream& operator>>(istream& is, S& s) {
		return is >> s.val;
	}
private:
	T val;
};


template<typename T>
S<T>& S<T>::operator=(const T& v) {
	val = v;
	return *this;
}

// We always need to pass by reference for the class S,
// since we haven't defined a copy constructor
// template<typename T>
// ostream& operator<<(ostream& os, const S<T>& s) {
// 	return os << s.val;
// }

// Doesn't work for const T& objects - it modifies the object
// Also, this only works if >> is overloaded for objects of type T
// (So it won't work for vectors)
template<typename T>
istream& read_val(istream& is, T& v) {
	is >> v;
	return is;
}

int main() {
	S<int> si{1};
	S<char> sc{'a'};
	S<double> sd{0.5};
	S<string> ss{"Hello"};
	S<vector<int>> sv{vector<int>{1, 3, 6}};

	si.set(2);
	sc.set(sc.get()+1);
	ss.set("Bye");
	vector<int> mr_cool {-1, 32, 19};
	sv.set(mr_cool);

	si = 3;
	ss = "Yo!";
	sv = mr_cool;

	si.set(2);

	cout << si.get() << '\t'
		<< sc.get() << '\t'
		<< sd.get() << '\t'
		<< ss.get() << '\t'
		<< sv.get()[1] << '\n';

	const S<int> si2{9};
	const S<vector<int>> sv2{vector<int>{3,3}};

	cout << si.get() << endl;
	si.get() = 3; // This changes si's val to 3 (kinda weird, but get
					// returns a reference if non-const!)
	cout << si.get() << endl;

	cout << si2.get() << '\t' << sv2.get()[1] << endl;
	sv2.get() = vector<int>{1,2,4,5}; // Doesn't change sv2's v
									// Because sv2.get() returns a value,
									// not an object 
	vector<int>{2,3,1} = vector<int>{1}; // Equivelant to above 
										// (nothing happents)
	//si2.get() = 2; // Error: expression not assignable
					// (equivelant to something like "1 = 4;")
	cout << sv2.get()[0] << endl;

	int val_int;
	read_val(cin, val_int); // Implicit call to read_val<int>(val_int)
	char val_char;
	read_val<char>(cin, val_char);
	double val_double;
	read_val(cin, val_double);
	string val_string;
	read_val<string>(cin, val_string);
	if (!cin) {throw runtime_error("Badness occured, yo!");}

	cout << val_int << '\t'
		<< val_char << '\t'
		<< val_double << '\t'
		<< val_string << '\n';

	S<char> yongus {val_char};
	cout << yongus;

	S<string> yongus_polo {""};
	cin >> yongus_polo;
	cout << yongus_polo << endl;

	return 0;
}