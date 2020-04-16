#include <iostream>

using namespace std;

/*
Review the very bottom of main, and the actual Number struct itself
*/

// T must have +,-,*,/,%,<,==,<<,>> defined 
// Also, 1 must be a valid value for T's constructor 
// (for incr / decr)
template<class T>
struct Number {
	Number() 
		: val{T{}} { } // T{} is T's default value
	Number(T v)
		: val{v} { }

	Number operator+(Number o) const {
		return Number{val + o.val};
	}
	Number operator-(Number o) const {
		return Number{val - o.val};
	}
	Number operator*(Number o) const {
		return Number{val * o.val};
	}
	Number operator/(Number o) const {
		return Number{val / o.val};
	}
	Number operator%(Number o) const {
		return Number{val % o.val};
	}

	Number operator-() const { // unary negative
		return Number{-val};
	}

	/*
	Normally you would return a reference for the current object
	for these overloaded functions. However, I think it's better
	to just return a new Number object.
	(Returning references may lead to undefined behaviour, 
	see PPP 8.6.1).
	Note that none of these are const - they modify the object.
	*/
	Number operator+=(Number o) {
		*this = *this + o; // Uses copy assignment on THIS object
			// Think about why this works! Remember, 'this' is an
			// implicit pointer argument to Number<T> operator+=(Number o)
			// So there's nothing stopping us from doing copy assignment
			// on this object. We also call operator+ to get a
			// Number<T> to use for the copy assignment (the result of
			// the addition)
		return *this; // Returns as value, not reference
	}
	Number operator-=(Number o) {
		*this = *this - o;
		return *this;
	}
	Number operator*=(Number o) {
		*this = *this * o;
		return *this;
	}
	Number operator/=(Number o) {
		*this = *this / o;
		return *this;
	}
	Number operator%=(Number o) {
		*this = *this % o;
		return *this;
	}

	// Pre-increment/decrement
	Number operator++() {
		return *this += Number{T{1}};
	}
	Number operator--() {
		return *this -= Number{T{1}};
	}
	// Post-increment/decrement
	Number operator++(int) { 
		Number ret = *this;
		++*this;
		return ret;
	}
	Number operator--(int) {
		Number ret = *this;
		--*this;
		return ret;
	}

	// Comparison
	bool operator==(Number o) const {
		return val == o.val;
	}
	bool operator<(Number o) const {
		return val < o.val;
	}
	bool operator<=(Number o) const {
		return *this < o || *this == o;
	}
	bool operator>(Number o) const {
		return !(*this <= o);
	}
	bool operator>=(Number o) const {
		return !(*this < o);
	}

	friend istream& operator>>(istream& is, Number& o) {
		return is >> o.val;
	}
	friend ostream& operator<<(ostream& os, const Number& o) {
		return os << o.val << endl;
	}
private:
	T val;
};

template<class T>
Number<T> square(Number<T> n) {
	return n*n;
}
/* 
int main() {
	// {
	// Int i1 {2};
	// Int i2 = 3; // constructor not explicit! We can do this
	// Int i3 {};
	// Int i4;
	// cout << Int{1} << i1 << i2 << i3 << i4 << Int{};
	// }

	// {
	// Int i1 = {4};
	// Int i2 {i1};
	// Int i3 {i2};
	// i2 = 3; // Compiler implicitly assumes this is Int{3}
	// i3 = i1;
	// i1 = Int{i1};
	// Int i4 {Int{Int{}}};
	// cout << i1 << i2 << i3 << i4;
	// }

	// {
	// Int i1 = 2;
	// Int i2 {3};
	// Int i3 = i1 + i2; // Uses copy constructor and operator+
	// i3 = i3 + i3; // Uses copy assignment and operator+
	// Int i4 = 1 + 2; // Same as Int i4 = Int{1} + Int{2}; 
	// 	// Compiler implicitly converts 1 and 2 using Int constructor
	// Int i5 {Int{1}.operator+(Int{2})}; // Logically the same as above
	// i3.operator=(i5.operator+(i3));
	// i3 = i5 + i3; // Exact same operation as above!
	// Int i6 = i1 + i1 + i1 + i1; 
	// i6 = i6 + i1 + Int{-2} + Int{} + Int{i6};
	// cout << i1 << i2 << i3 << i4 << i5 << i6;
	// }

	// {
	// 	Int i1 = 30;
	// 	Int i2 = i1 / 4;
	// 	Int i3 = i1 % 4;
	// 	Int i4 = i2 * 4 + i3; 
	// 	Int i5 = 4 + 5 * 30 - 4 * 30; // Order of operation for the
	// 		// operator member functions follows bedmas. 
	// 		// This is determined in the compilation step. Cool stuff!
	// 	Int i6 = (1+2) * 30 - (1*30);
	// 	Int i7 {2};
	// 	i7 = square(i7);
	// 	Int i8 = square(4); // Implicitly known to be Int{4}

	// 	cout << i1 << i2 << i3 << i4 << i5 << i6 << i7 << i8;
	// }

	// {
	// Int i;
	// cin >> i;
	// cout << square(i);
	// }

	// {
	// 	// You should never do this, this is the confusingest 
	// 	// thing ever.
	// 	// But it's interesting how it works - it just follows from
	// 	// the definition of operator+=
	// 	Int i1 {1};
	// 	Int i2 {i1 += Int{1}};
	// 	i2 = Int{1} += Int{1};
	// 	Int i3 = i2 += i1 - 1;
	// 	cout << i1 << i2 << i3;

	// 	Int i4{};
	// 	i4 -= i3;
	// 	i4 *= 2;
	// 	Int i5 = (i4)*-1 % 3; // Weird - If you swap i4 and -1, 
	// 		// it doesn't compile
	// 	i5 = -Int{1}*i4 % 3 + -(-10); // We added unary minus!
	// 	i5 += 1; 
	// 	cout << i4 << i4 / 5 << i5;
	// }

	// {
	// Int i1{1};
	// ++i1;
	// ++i1;
	// cout << ++i1 << --i1 << i1;
	// const Int i2{i1++}; // Return old value of i1
	// //++i2; // Error - operator++() not const!
	// cout << i1 << i2 << i2 + i1; // + ok for i2 - it's const!
	// }

	// {
	// 	Int i1;
	// 	Int i2;
	// 	cout << (i1 < i2) << (i1 <= i2) << (i1 == i2) << endl;
	// 	++i1;
	// 	cout << (i2++ == i1) << (i2 == i1) << (++i2 == i1) << endl;
	// 	cout << (Int{3} >= i1) << endl;
	// }

	// {
	// Number<double> d1 = 1.0;
	// Number<double> d2 {d1};
	// Number<double> d3 {d1 * (d2+1)}; // 2
	// Number<double> d4 = Number<double>{9}/d3; // 4.5
	// cout << d1 << d2 << d3 << d4;
	// cout << ++d4 << d4++ << d4;
	// Number<int> i1 = 4;
	// cout << i1 / 3 % 2;
	// }

	{
		Number<double> d1 {3.1};
		Number<double> d2 {d1 % 4.3}; 
		
		This line allows the compiler to generate a member function 
		for the generated class Number<double>. It generates 
		Number<double>::operator%, and the compiler detects that
		it is using the % operator on a double, which is illegal.
		So we get a compiler error.
		
	}

	return 0;
}
*/