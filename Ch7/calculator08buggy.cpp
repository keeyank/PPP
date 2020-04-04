
/*
	calculator08buggy.cpp

	Helpful comments removed.

	We have inserted 3 bugs that the compiler will catch and 3 that it won't.
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// A token acts as a unit of user input
struct Token {
	char kind;
	double value;
	string name;
	Token(char ch) :kind(ch), value(0) { }
	Token(char ch, double val) :kind(ch), value(val) { }
	Token(char ch, string s) :kind(ch), name(s) { }
};

// Token_stream constructs tokens from cin
// Access tokens from cin using Token_stream
class Token_stream {
	bool full;
	Token buffer;
public:
	Token_stream() :full(0), buffer(0) { }

	Token get();
	void unget(Token t);

	void ignore(char);
};

const char let = 'L';
const char set = 'S';
const char quit = 'Q';
const char print = '\n';
const char number = '8';
const char name = 'a';
const char sqroot = 's';
const char power = 'p';

const string declkey = "let";
const string asnkey = "set";

// Constructs and returns token from cin (or buffer)
Token Token_stream::get()
{
	if (full) { full=false; return buffer; }
	char ch;
	cin.get(ch);
	while (isspace(ch) && ch != print) {
		cin.get(ch);
	}
	switch (ch) {
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case '=':
	case ',':
	case print:
	case quit:
		return Token(ch);
	case '.':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	{	cin.unget();
		double val;
		cin >> val;
		return Token(number,val);
	}
	default:
		if (isalpha(ch)) {
			string s;
			s += ch;
			while(cin.get(ch) && (isalpha(ch) || isdigit(ch))) s+=ch;
			cin.unget();
			if (s == declkey) return Token(let);
			if (s == asnkey) return Token(set);	
			if (s == "sqrt") return Token(sqroot);
			if (s == "pow") return Token(power);
			return Token(name,s);
		}
		throw runtime_error("Bad token");
	}
}

// Put back a token into Token_stream
void Token_stream::unget(Token t) {
	if (full) 
		throw runtime_error("Attempted to unget while buffer full");
	buffer = t;
	full = true;
}

// Ignore all chars in cin and buffer up to and including c
void Token_stream::ignore(char c)
{
	if (full && c==buffer.kind) {
		full = false;
		return;
	}
	full = false;

	char ch;
	while (cin.get(ch))
		if (ch==c) return;
}

struct Variable {
	string name;
	double value;
	bool is_const;
	Variable(string n, double v) :name(n), value(v) { }
	Variable(string n, double v, bool c) :name(n), value(v), is_const(c) { }
};

class Var_list {
public:
	double get_value(string s);
	void set_value(string s, double d);
	bool is_declared(string s);
	void define_value(string s, double d, bool is_c);
private:
	vector<Variable> vars;
};	

// Return value of s
// s must have been previously defined
double Var_list::get_value(string s)
{
	for (int i = 0; i<vars.size(); ++i)
		if (vars[i].name == s) return vars[i].value;
	throw runtime_error("get: undefined name " + s);
}

// Set value of s to d
// s must have been previously defined
void Var_list::set_value(string s, double d)
{
	for (int i = 0; i<vars.size(); ++i)
		if (vars[i].name == s) {
			if (vars[i].is_const)
				throw runtime_error(vars[i].name + " is constant");
			vars[i].value = d;
			return;
		}
	throw runtime_error("set: undefined name " + s);
}

// Check if s defined
bool Var_list::is_declared(string s)
{
	for (int i = 0; i<vars.size(); ++i)
		if (vars[i].name == s) return true;
	return false;
}

void Var_list::define_value(string s, double d, bool is_c = false) {
	if (is_declared(s)) 
		throw runtime_error(s + " declared twice");
	vars.push_back(Variable(s, d, is_c));
}

Token_stream ts;
Var_list vl;

// Cast double to int, if the cast is unsafe (loses information),
// throw an exception
int safe_cast(double d) {
	int cast = (int)d;
	if ((double)cast != d) 
		throw runtime_error("Unsafe conversion from double to int");
	return cast;
	
}

double expression();

double primary()
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':
	{	double d = expression();
		t = ts.get();
		if (t.kind != ')') throw runtime_error("')' expected");
		break;
	}
	case '-':
		return - primary();
	case '+':
		return primary();
	case number:
		return t.value;
	case name:
		return vl.get_value(t.name);
	case sqroot: {
		Token b = ts.get();
		if (b.kind != '(')
			throw runtime_error("'(' expected after sqrt");
		double d = expression();
		if (d < 0) 
			throw runtime_error("Attempted to use sqrt with a negative number");
		b = ts.get();
		if (b.kind != ')')
			throw runtime_error("')' expected");
		return sqrt(d);
	}
	case power: {
		Token b = ts.get();
		if (b.kind != '(')
			throw runtime_error("'(' expected after pow");
		double base = expression();
		Token c = ts.get();
		if (c.kind != ',') 
			throw runtime_error("',' expected");

		double exp;
		try {
			exp = safe_cast(expression());
		} 
		catch (exception& e) {
			throw runtime_error("Exponent must be an integer");
		}
		b = ts.get();
		if (b.kind != ')')
			throw runtime_error("')' expected");

		return pow(base, exp);
	}
	default:
		throw runtime_error("primary expected");
	}
}

double term()
{
	double left = primary();
	while(true) {
		Token t = ts.get();
		switch(t.kind) {
		case '*':
			left *= primary();
			break;
		case '/':
		{	double d = primary();
			if (d == 0) throw runtime_error("divide by zero");
			left /= d;
			break;
		}
		default:
			ts.unget(t);
			return left;
		}
	}
}

double expression()
{
	double left = term();
	while(true) {
		Token t = ts.get();
		switch(t.kind) {
		case '+':
			left += term();
			break;
		case '-':
			left -= term();
			break;
		default:
			ts.unget(t);
			return left;
		}
	}
}

double assignment() {
	Token t = ts.get();
	if (t.kind != name) throw runtime_error("name expected in assignment");
	Token t2 = ts.get();
	if (t2.kind != '=') throw runtime_error("= missing in assignment of " + t.name);
	double d = expression();
	vl.set_value(t.name, d);
	return d;
}

double declaration()
{
	Token t = ts.get();
	if (t.kind != name) throw runtime_error("name expected in declaration");
	string s = t.name;
	Token t2 = ts.get();
	if (t2.kind != '=') throw runtime_error("= missing in declaration of " + s);
	double d = expression();
	vl.define_value(s,d);
	return d;
}

double statement()
{
	Token t = ts.get();
	switch(t.kind) {
	case let:
		return declaration();
	case set:
		return assignment();
	default:
		ts.unget(t);
		return expression();
	}
}

void clean_up_mess()
{
	ts.ignore(print);
}

const string prompt = "> ";
const string result = "= ";

void calculate()
{
	while(true) try {
		cout << prompt;
		Token t = ts.get();
		while (t.kind == print) t=ts.get();
		if (t.kind == quit) return;
		ts.unget(t);
		cout << result << statement() << endl;
	}
	catch(runtime_error& e) {
		cerr << e.what() << endl;
		clean_up_mess();
	}
}

void add_constants() {
	vl.define_value("k", 1000, true);
	vl.define_value("pi", 3.14159265359, true);
	vl.define_value("e", 2.7182818284, true);
}

int main()

	try {
		add_constants();
		calculate();
		return 0;
	}
	catch (exception& e) {
		cerr << "exception: " << e.what() << endl;
		char c;
		while (cin>>c && c!=';');
		return 1;
	}
	catch (...) {
		cerr << "exception\n";
		char c;
		while (cin>>c && c!=';');
		return 2;
	}
