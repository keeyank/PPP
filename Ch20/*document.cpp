#include <vector>
#include <list>
#include <iostream>
#include <fstream>

using namespace std;

/*
Invariants: 
Each line ends with a \n, apart from final line
Always atleast 1 line
Final line is empty vector
*/
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

	bool find_and_replace(string f, string r = "");

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

We make use of the fact that every line ends with a \n, and have
match return e1 on failure. 
*/
template<typename Iter1, typename Iter2>
	// requires Iter1, Iter2 be forward iterators
Iter1 match(Iter1 f1, const Iter1 e1, Iter2 f2, const Iter2 e2) {
	while (true) {
		if (f2 == e2) return f1; 
		if (f1 == e1) return e1;
		if (*f1 != *f2) return e1;

		++f1;
		++f2;
	}
}

/*
Note the usage of integer index rather than iterators for vectors.
This is because vector iterators can (and likely will) be
invalidated after our vector resize operations, like erase and
insert.
\n cannot be in either strings. Having it in r will falsify
Document's invariant.
Return value indicates whether function succeeded.
*/
bool Document::find_and_replace(string f, string r) {
	if (f.size() == 0) return false;
	if (find(f.begin(), f.end(), '\n') != f.end()) return false;
	if (find(r.begin(), r.end(), '\n') != r.end()) return false;

	for (auto ln_it = doc.begin(); ln_it != doc.end(); ++ln_it) {

		int i = 0;
		while (ln_it->begin() + i != ln_it->end()) {
			auto it_endpos = match(ln_it->begin()+i, ln_it->end(),
					f.begin(), f.end());

			if (it_endpos != ln_it->end()) {
				ln_it->erase(ln_it->begin()+i, it_endpos);
				ln_it->insert(ln_it->begin()+i, 
						r.begin(), r.end());
				i += r.size();
			}
			else {
				++i;
			}
		}
	}
	return true;
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

	// Make sure invariant holds
	if (d.doc.back().size()) { // check if expression != 0
		d.doc.back().push_back('\n');
		d.doc.push_back(vector<char>{});
	}

	return is;
}

/*
Note how we can't do a const Document&
Because we haven't set up const iterators for the document!
*/
ostream& operator<<(ostream& os, Document& d) {
	for (auto c : d) {
		os << c;
	}
	return os;
}

/*---------------------------------------------*/

int count_chars(Document& d) {
	int count = 0;
	for (char c : d) {
		if (!isspace(c)) ++count;
	}
	return count;
}

int count_words1(Document& d) {
	int count = 0;
	bool prev_space = true;
	for (char c : d) {
		if (prev_space && !isspace(c)) {
			prev_space = false;
			++count;
		}

		if (isspace(c)) prev_space = true;
	}
	return count;
}

int count_words2(Document& d) {
	int count = 0;
	bool prev_nonalpha = true;
	for (char c : d) {
		if (prev_nonalpha && isalpha(c)) {
			prev_nonalpha = false;
			++count;
		}

		if (!isalpha(c)) {
			prev_nonalpha = true;
		}
	}
	return count;
}

/*---------------------------------------------*/

int main() {
	ifstream ifs {"test.txt"};
	Document d;
	ifs >> d;
	if (d.find_and_replace(" ", " ")) cout << d;
	cout << "\n" << count_words1(d) << endl;
	cout << count_words2(d) << endl;
	return 0;
}