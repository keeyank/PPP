#include <string>

class Link {
public:
	std::string value;

	Link(const std::string& v, Link* p = nullptr, Link* s = nullptr)
		: value{v}, prev{p}, succ{s} { }

	Link* insert(Link* n);
	//Link* add(Link* n);
	Link* find(const std::string& s);

	//Link* advance(int n) const;

	Link* prev;
	Link* succ;
};

void erase(Link* n);

// Frees any heap memory allocated to links, starting with first
void cleanup(Link* first);

void print(Link* p);



