#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

constexpr char caps_difference = 'a' - 'A';

const string invalid = "Invalid!";
const string valid = "Valid :)";

// Convert string s to all lowercase
void tolower(string &s) {
	for (int i = 0; i < s.size(); ++i) {
		if (s[i] >= 'A' && s[i] <= 'Z') {
			s[i] += caps_difference;
		}
	}
}

class Stream {
public:
	string get();
	void putback(string s);
private:
	bool full = false;
	string buffer = "";
};

string Stream::get() {
	if (full) {
		full = false;
		return buffer;
	}

	string s;
	cin >> s;
	tolower(s);
	return s;
}

void Stream::putback(string s) {
	if (full) 
		throw runtime_error("Stream::putback called while buffer full.");
	full = true;
	buffer = s;
}

Stream stream;

bool is_verb(string s) {
	return (s == "swim" || s == "fly" || s == "rules");
}

bool is_conjunction(string s) {
	return (s == "and" || s == "but" || s == "or");
}

bool is_noun(string s) {
	return (s == "birds" || s == "fishes" || s == "c++");
}

string sentence() {
	string s;
	while (s != ".") {
		s = stream.get();

		if (s == "the") {
			string lookahead = stream.get();
			if (!is_noun(lookahead))
				return invalid;
			stream.putback(lookahead);
		}

		else if (is_noun(s)) {
			s = stream.get();
			if (!is_verb(s))
				return invalid;
		}

		else if (is_conjunction(s)) {
			string lookahead = stream.get();
			if (!is_noun(lookahead) && lookahead != "the")
				return invalid;
			stream.putback(lookahead);
		}

		else if (s != ".")
			return invalid;
	}
	return valid;
}

int main() 
try {
	cout << sentence() << "\n";
	return 0;
}
catch (exception& e) {
    cerr << e.what() << endl;
    return 1;
}
catch (...) {
    cerr << "exception \n";
    return 2;
}