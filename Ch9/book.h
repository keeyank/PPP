#include <string>
#include <iostream>

namespace Lib {


enum class Genre {
	first = -1,
	fiction, nonfiction, periodical, biography, children,
	last
};
const vector<string> genre_map 
		{"Fiction", "Non-Fiction", "Periodical", 
			"Biography", "Children"};

const std::string name_default = "DEFAULT";
const std::string isbn_default = "0-0-0-0";
constexpr Genre genre_default = Genre::fiction;

class Book {
private:
	std::string isbn = isbn_default;
	std::string title = name_default;
	std::string author = name_default;
	Genre genre = genre_default;
	bool checked_in = true;
public:
	Book(std::string i, std::string t, std::string a, Genre g, bool ci);
	Book(std::string i, std::string t, std::string a, Genre g);

	std::string get_isbn() const {return isbn;}
	std::string get_title() const {return title;}
	std::string get_author() const {return author;}
	Genre get_genre() const {return genre;}
	bool is_checked_in() const {return checked_in;}

	void check_in() {
		checked_in = true;
	}
	void check_out() {
		checked_in = false;
	}
};

std::ostream& operator<<(std::ostream& os, const Book& b);
// Equality is based purely on isbn
bool operator==(const Book& b1, const Book& b2);
bool operator!=(const Book& b1, const Book& b2);

// Return true if isbn is valid, false otherwise
bool valid_isbn(const std::string& isbn);

// Converts specified enum to string
std::string tostring(Genre g); 
// Return true if genre is in the valid closed interval, 
// false otherwise
bool valid_genre(Genre g);







}