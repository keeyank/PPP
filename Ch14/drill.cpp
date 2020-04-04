#include <iostream>
#include <string>

using namespace std;

class B1 {
public:
	virtual void pvf() const = 0; // 4.
	virtual void vf() const {
		cout << "B1::vf ";
	}
	void f() const {
		cout << "B1::f ";
	}
};

struct D1 : B1 {
	void vf() const override {
		cout << "D1::vf ";
	}
	// 4.
	void f() const {
		cout << "D1::f ";
	}
};	

struct D2 : D1 {
	void pvf() const override {
		cout << "D2::pvf ";
	}
};

class B2 {
public:
	virtual void pvf() const = 0;
};

struct D21 : B2 {
	void pvf() const override {
		cout << s;
	}
	string s = "D21::pvf ";
};

struct D22 : B2 {
	void pvf() const override {
		cout << i << ' ';
	}
	int i = 22;
};

void f(B2& b) {
	b.pvf();
}

int main() {
	// cout << "1.\n";
	// B1 b;
	// b.vf();
	// b.f();
	// cout << endl;

	// cout << "2.\n";
	// D1 d;
	// d.vf();
	// d.f(); // D1's f called here
	// cout << endl;

	// cout << "3.\n";
	// B1& br = d;
	// br.vf();
	// br.f(); // f not virtual, so B1's f called here
	// cout << endl;

	// 5. Pure virtual never overwritten, so every class is abstract
	// Therefore, program won't compile (can't create instance of
	// abstract class)

	cout << "6.\n";
	D2 d;
	d.pvf();
	d.vf();
	d.f();
	cout << endl;

	B1& br = d;
	br.pvf();
	br.vf();
	br.f();
	cout << endl;

	cout << "7.\n";
	D21 d1;
	D22 d2;
	f(d1);
	f(d2);
	cout << endl;

	return 0;
}
