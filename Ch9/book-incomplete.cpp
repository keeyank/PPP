#include "book.h"

#include <vector>
#include <ctype.h>

using namespace std;

namespace Lib {

// Book Member Functions 

Book::Book(string i, string t, string a, Genre g, bool ci):
			isbn{i}, title{t}, author{a}, genre{g} checked_in{ci}
{
	if (!valid_isbn(i))
		throw runtime_error("Book::Book: Bad initialization (invalid isbn).");
	if (t == "" || a == "")
		throw runtime_error("Book::Book: Bad initialization (empty string).");
	if (!valid_genre(g))
		throw runtime_error("Book::Book: Bad initialization (genre out of range).");
}

Book::Book(string i, string t, string a, Genre g):
			isbn{i}, title{t}, author{a}, genre{g}
{
	if (!valid_isbn(i))
		throw runtime_error("Book::Book: Bad initialization (invalid isbn).");
	if (t == "" || a == "")
		throw runtime_error("Book::Book: Bad initialization (empty string).");
	if (!valid_genre(g))
		throw runtime_error("Book::Book: Bad initialization (genre out of range).");
}

// Helper Functions

ostream& operator<<(ostream& os, Book& b) {
	return os << "\"" << b.get_title() << "\"\n" 
		<< b.get_author() << "\n" 
		<< tostring(b.get_genre()) << '\n'
		<< b.get_isbn() << '\n';
}

bool operator==(const Book& b1, const Book& b2) {
	return b1.get_isbn() == b2.get_isbn();
}

bool operator!=(const Book& b1, const Book& b2) {
	return !(b1 == b2);
}

bool valid_isbn(const string& isbn) {
	int dash_count = 0;
	bool num_found = false;

	if (isbn.size() < 6) {
		return false;
	}
	if (!isalnum(isbn[isbn.size()-1]) ||
			isbn[isbn.size()-2] != '-') {
		// isbn doesn't end with "-[alnum]"
		return false;
	}

	for (int i = 0; i < isbn.size()-1; ++i) {
		if (isdigit(isbn[i])) {
			num_found = true;
		}

		else if (isbn[i] == '-') {
			if (!num_found) { // no number before this dash
				return false;
			}
			++dash_count;
			num_found = false;
		}

		else { // isbn[i] is not a digit or dash
			return false;
		}
	}

	if (dash_count != 3) {
		return false;
	}

	return true;
}

string tostring(Genre g) {
	if (!valid_genre) {
		throw runtime_error("tostring: Invalid genre.");
	}
	return genre_map[(int)g];
}

bool valid_genre(Genre g) {
	if (g <= Genre::first || g >= Genre::last)
		return false;
	return true;
}


}

using namespace Lib;

// For testing
int main() {
	string i, t, a;
	bool ci;
	Book prev{"1-1-1-1", "a", "b", Genre::nonfiction};

	cout << ">";
	while (cin >> i >> t >> a >> ci) {
		Book curr{i, t, a, ci, fiction};
		cout << curr << endl;
		cout << prev << endl;
		cout << "curr == prev: " << (curr == prev) << endl;
		cout << "curr != prev: " << (curr != prev) << endl;
		cout << ">";
	}
	return 0;
}