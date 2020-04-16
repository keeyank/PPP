#include <iostream>
#include <string>
#include <vector>

using namespace std;
/*
T and U must be elements - support copy and default vals.
Default memberwise copy for pair will call copy constructer for both
T and U. We use T and U's default vals in the default constructor.
Default memberwise copy works similarly for copy assignment
Compile-generated destructor will call destructor for a and b
*/
template<class T, class U>
struct Pair {
	Pair() : a{}, b{} { }
	Pair(T aa, U bb) : a{aa}, b{bb} { }

	T a;
	U b;
};

template<typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
	os << "{";
	for (int i = 0; i < v.size(); ++i) {
		os << v[i];
		if (i != v.size()-1) os << ", ";
	}
	return os << "}";
}

template<class T, class U>
ostream& operator<<(ostream& os, const Pair<T, U>& p) {
	os << "(" << p.a << "," << p.b << ")";
	return os;
}


template<typename T>
struct Symbol_table {
	Symbol_table() { }
	void add(string name, T val);
	void update(string name, T val);

	T& operator[](string name);
	const T& operator[](string name) const;

	friend ostream& operator<<(ostream& os, 
			const Symbol_table<T>& st) 
	{
		cout << "{";
		for (int i = 0; i < st.tbl.size(); ++i) {
			cout << st.tbl[i];
			if (i != st.tbl.size()-1) cout << ", ";
		}
		return cout << "}\n";
	}

private:
	bool has_name(string name);
	vector<Pair<string, T>> tbl; // No two names are the same
};

template<typename T>
bool Symbol_table<T>::has_name(string name) {
	for (int i = 0; i < tbl.size(); ++i) {
		if (tbl[i].a == name) return true;
	}
	return false;
}

template<typename T>
void Symbol_table<T>::add(string name, T val) {
	if (has_name(name)) {
		throw runtime_error("Symbol_table::add:" 
			" Name already defined");
	}
	tbl.push_back(Pair{name, val});
}

template<typename T>
void Symbol_table<T>::update(string name, T val) {
	for (int i = 0; i < tbl.size(); ++i) {
		if (tbl[i].a == name) {
			tbl[i].b = val; // Copy assignment
			return;
		}
	}
	throw runtime_error("Symbol_table::update: Name not found");
}

template<typename T>
T& Symbol_table<T>::operator[](string name) {
	for (int i = 0; i < tbl.size(); ++i) {
		if (tbl[i].a == name) return tbl[i].b;
	}
	throw runtime_error("Symbol_table::operator[]: Name not found");
}

template<typename T>
const T& Symbol_table<T>::operator[](string name) const {
	for (int i = 0; i < tbl.size(); ++i) {
		if (tbl[i].a == name) return tbl[i].b;
	}
	throw runtime_error("Symbol_table::operator[]: Name not found");
}

int main() {
// // Pair tests
// Pair<string, int> p1 {"Hello Bingo", 2};
// Pair<string, int> p2;
// Pair<int, string> p3 {3, "Weehaw!!!"};
// Pair<Pair<int, int>, string> p4 {Pair{1,1}, "Ok!"}; //Uses default copy 
// 	// constructor for inner Pair in constructor for outer Pair
// Pair<Pair<string, double>, vector<int>> p5;
// Pair<vector<int>, vector<Pair<int, double>>> p6 {vector<int>{1,2,12}, 
// 		vector<Pair<int,double>>
// 		{Pair<int, double>{3,2.1}, Pair<int, double>{1,.1}}}; // lol
// cout << p1 << ' ' << p2 << ' ' << p3 << ' ' << p4 << ' ' << p5 << endl;
// cout << p6 << endl;

// Pair<string, int> p7 {p1};
// p7.a += "!!!!!";
// cout << p7 << endl;
// cout << p1 << endl; // p1 not affected - string member 'a' does deep copy
// p7 = p2;
// p7.a = "YAY!";
// //p7 = p4; // Error:not the same type. p4 is a Pair<Pair<int,int>,string>
// cout << p7 << ' ' << p2 << endl; // Again, p2 not affected

// // Moral of the story - copy constructors, copy assignment, default
// // constructors, and destructors work really well with templates 
// // due to the recursive nature of structs with other structs as members
// // (the constructors / destructor / assignment 
// // will call each member's constructors / destructor / assignment)
// // Of course, these have to be defined and
// // work as expected for the types/classes of each member

	// Symbol_table tests
	Symbol_table<int> symtbl;
	cout << symtbl << endl;
	symtbl.add("x", 1);
	symtbl.update("x", 12);
	symtbl.add("y", 20);
	symtbl.add("xvar", 2);
	//symtbl.add("y", 30); // Runtime error
	symtbl.update("y", 2); // OK 
	//symtbl.update("xvary", 1); // Runtime error

	symtbl.update("y", 2 + symtbl["y"]);
	symtbl.update("x", symtbl["y"]);
	symtbl["x"] = 2*symtbl["x"];
	//symtbl["polo aka yoooooo"]; // runtime error
	symtbl["x"]; // OK!

	const Symbol_table st2 = symtbl; // Default copy constructor is fine
			// Will call copy constructor or assignment for vector
			// Vector's copy will call Pair's copy
	//st2["x"] = 3; // Error - [] non-const. Good!
	symtbl["xvar"] = st2["xvar"] - 1; // Error - [] non-const. Bad!
									// Lets fix that.
	int guy = (-1)*st2["x"];
	symtbl["x"] = guy;

	cout << symtbl << endl;
	cout << st2 << endl;

	return 0;
}