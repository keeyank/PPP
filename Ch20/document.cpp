#include <vector>
#include <list>
#include <iostream>
#include <fstream>

using namespace std;

struct Document {

	struct Iterator {
		Iterator(list<vector<char>>::iterator ll, 
				vector<char>::iterator pp);
		char& operator*();
		Iterator& operator++();
		bool operator==(const Iterator& other) const;
		bool operator!=(const Iterator& other) const;

	private:
		list<vector<char>>::iterator ln;
		vector<char>::iterator pos;
	};

	Document() {
		doc.push_back(vector<char>{});
	}

	Iterator begin() {
		return Iterator{doc.begin(), doc.begin()->begin()};
	}
	Iterator end() {
		// auto refers to list<vector<char>>::iterator
		auto last = doc.end();
		--last;
		return Iterator{last, last->end()}; // could also use 
	}							// last->begin() here

	int find_and_replace(string f, string r = "");

	friend istream& operator>>(istream& is, Document& d);
	friend ostream& operator<<(ostream& is, Document& d);
private:
	list<vector<char>> doc;
};

/*---------------------------------------------*/

Document::Iterator::Iterator(list<vector<char>>::iterator ll, 
		vector<char>::iterator pp)
	: ln{ll}, pos{pp} { }

char& Document::Iterator::operator*() {
	return *pos;
}

Document::Iterator& Document::Iterator::operator++() {
	++pos;
	if (pos == ln->end()) {
		++ln;
		pos = ln->begin();
	}
	return *this;
}

bool Document::Iterator::operator==(const Iterator& other) const {
	return ln == other.ln && pos == other.pos;
}
bool Document::Iterator::operator!=(const Iterator& other) const {
	return !(*this == other);
}

/*---------------------------------------------*/

/*
Pass iterators by value - this way, the iterator in 
find_and_replace is unnaffected by this algorithm.

Some semantics with match and it's return value -
if match is unsuccessful, we want to continue iterating 
incrementally without regards to match algorithm. If
match was successful, we want to iterate beginning from
where match left off.
*/
template<typename Iter1, typename Iter2>
	// requires Iter1, Iter2 be forward iterators
bool match(Iter1 f1, const Iter1 e1, Iter2 f2, const Iter2 e2) {
	while (true) {
		if (f2 == e2) return true; 
		if (f1 == e1) return false;
		if (*f1 != *f2) return false;

		++f1;
		++f2;
	}
}

int Document::find_and_replace(string f, string) {
	if (f.size() == 0) return 0;

	Iterator it = begin();
	int count = 0;

	while (true) {
		if (it == end()) return count;
		
		if (*it == f.front()) {
			if (match(it, end(), f.begin(), f.end())) {
				++count;
			}
		}

		++it;
	}
}

/*
Upholds the invariant of Document:
Every line is non-empty, but the last line is empty.
This allows good usage of iterators, in particular,
we can define Document's end() to be end() of the final 
empty vector<char> (which is the same as begin() for that
vector<char>, since it's empty)
*/
istream& operator>>(istream& is, Document& d) {
	for (char ch; is.get(ch);) {
		d.doc.back().push_back(ch);
		if (ch == '\n') {
			d.doc.push_back(vector<char>{});
		}
	}

	if (d.doc.back().size()) { // check if expression != 0
		d.doc.push_back(vector<char>{});
	}

	return is;
}

/*
Note how we can't do a const Document&
Because we haven't set up const iterators for the document!
In theory, we should be able to, but we'd need to do some
extra set up for it.
*/
ostream& operator<<(ostream& os, Document& d) {
	for (auto c : d) {
		os << c;
	}
	return os;
}

/*---------------------------------------------*/

int main() {
	ifstream ifs {"test.txt"};
	Document d;
	ifs >> d;
	
	cout << d.find_and_replace("aa") << endl;
	return 0;
}