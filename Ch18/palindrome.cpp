#include <iostream>

using namespace std;

// Dynamic c-string - allows for characters to be
// added during runtime
// Very simple - no protection for members (probably not good)
struct Dynamic_cstr {
	Dynamic_cstr()
		: str{new char[1]}, size{0}, buff_size{1}
	{
		str[0] = 0;
	}

	void push_back(char c); // not const obviously

	~Dynamic_cstr() {
		delete[] str;
	}

	char* str;
	int size;
private:
	int buff_size;
};

void Dynamic_cstr::push_back(char c) {
	if (size+1 == buff_size) {
		char* next_buff = new char[2*buff_size];
		buff_size *= 2;
		copy(str, str+size, next_buff);
		delete[] str;
		str = next_buff;
	}

	str[size] = c;
	str[size+1] = 0;
	++size;
}



bool is_palindrome(const char* s, const int n) {
	int first = 0;
	int last = n-1;
	while (first < last) {
		if (s[first] != s[last]) return false;
		++first;
		--last;
	}
	return true;
}

void read_to_dynamic_cstr(istream& is, Dynamic_cstr& s) {
	char c = ' ';
	is.get(c);
	while (!isspace(c)) {
		s.push_back(c);
		c = is.get();
	}
}

void eat_whitespace(istream& is) {
	char c = ' ';
	while (isspace(c)) {
		cin.get(c);
	}
	cin.putback(c); // putback none-whitespace char
}

// Exercise 18 part 2
int main() {
	while (cin) {
		Dynamic_cstr s;
		eat_whitespace(cin);
		read_to_dynamic_cstr(cin, s);

		cout << s.str << " is";
		if (!is_palindrome(s.str, s.size)) {cout << " not";}
		cout << " a palindrome\n";
	}
	return 0;
}



// istream& read_word(istream& is, char* buffer, int max) {
// 	is.width(max); // accounts for null terminator
// 	is >> buffer;
// 	if (strlen(buffer) == max-1) {
// 		is.clear(ios_base::failbit);
// 	}
// 	return is;
// }

// // Eat input until whitespace
// void eat(istream& is) {
// 	char waste = 'a';
// 	while (!(waste == ' ' || waste == '\t' || waste == '\n')) {
// 		waste = is.get();
// 	}
// }

// // Exercise 18 part 1
// int main() {

// 	constexpr int max = 128;
// 	char s[max]; 
// 	while (true) {
// 		read_word(cin, s, max);
// 		if (cin.eof() && cin.fail()) break;

// 		if (cin.fail()) {
// 			cout << "Word too long! IDIOT...\n";
// 			cin.clear();
// 			eat(cin);
// 			continue;
// 		}

// 		cout << s << " is";
// 		if (!is_palindrome(s)) cout << " not";
// 		cout << " a palindrome\n";
	
// 	}

// 	return 0;
// }



