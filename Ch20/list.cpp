#include "test_class.h"

/*---------------------------------------------*/

template<typename Elem>
struct Link {
	Elem val {};
	Link* next = nullptr;
	Link* prev = nullptr;
};

/*---------------------------------------------*/

template<typename Elem>
struct List {	
	struct Iterator;

	/* Constructor/destructor/copy */

	List()
		: head{nullptr}, tail{nullptr}, sz{0} { }
	List(initializer_list<Elem> l);

	List(const List&) = delete; // MAKE WHEN ITERATORS ARE DONE
	List& operator=(const List&) = delete; // MAKE WHEN ITERATORS ARE DONE

	List(List&&);
	List& operator=(List&&);

	~List();

	/* Operations */

	void push_back(const Elem& e);

	int size() const {
		return sz;
	}

	/* Debug */

	friend ostream& operator<<(ostream& os, const List& l) {
		Link<Elem>* curr = l.head;
		os << "{";
		while (curr != nullptr) {
			cout << curr->val;
			if (curr->next != nullptr) os << ", ";
			curr = curr->next;
		}
		return os << "}";
	}
	void print_backwards();
private:

	void cleanup();
	/*
	Invariant:
	head points to first element in sequence
	tail points to last element in sequence
	tail->next is nullptr
	head->prev is nullptr
	If list empty, head and tail are nullptr
	*/
	Link<Elem>* head;
	Link<Elem>* tail;

	int sz;
};

/*---------------------------------------------*/

template<typename Elem>
void List<Elem>::push_back(const Elem& e) {
	Link<Elem>* newlink = new Link<Elem>{e, nullptr, tail};
	if (head == nullptr) head = newlink;
	else tail->next = newlink;
	tail = newlink;
	++sz;
}

template<typename Elem>
void List<Elem>::cleanup() {
	while (head != nullptr) {
		Link<Elem>* next = head->next;
		delete head;
		head = next;
	}
}

/*---------------------------------------------*/

/*
I forgot to initialize with sz{0}, head{nullptr}, etc.
Lead to a bug - sz was an undefined value...
NEVER FORGET TO INITIALIZE!!! 
*/
template<typename Elem>
List<Elem>::List(initializer_list<Elem> l) 
	: head{nullptr}, tail{nullptr}, sz{0}
{
	for (auto it = l.begin(); it != l.end(); ++it) {
		push_back(*it);
	}
}

template<typename Elem>
List<Elem>::List(List<Elem>&& l) 
	: head{l.head}, tail{l.tail}, sz{l.sz}
{
	l.head = nullptr;
	l.tail = nullptr;
	l.sz = 0;
}

template<typename Elem>
List<Elem>& List<Elem>::operator=(List<Elem>&& l) {
	cleanup();
	head = l.head;
	tail = l.tail;
	sz = l.sz;
	l.head = nullptr;
	l.tail = nullptr;
	l.sz = 0;
	return *this;
}

template<typename Elem>
List<Elem>::~List() {
	cleanup();
}

/*---------------------------------------------*/

template<typename Elem>
void List<Elem>::print_backwards() {
	Link<Elem>* curr = tail;
	cout << "{";
	while (curr != nullptr) {
		cout << curr->val;
		if (curr->prev != nullptr) cout << ", ";
		curr = curr->prev;
	}
	cout << "}\n";
}
/*---------------------------------------------*/

List<X> make_list() {
	List<X> l {X{"two",2},X{"three",3},X{"five",5}};
	return l;
}

int main() {
	// {
	// 	List<X> l;
	// 	l.push_back(X{"steve", 5});
	// 	l.push_back(X{"Paraman", 102});
	// 	l.push_back(X{"Wakango", 13});
	// 	l.push_back(X{"Scottyboy!!", -3});
	// 	cout << l << endl;
	// 	l.print_backwards();
	// 	cout << l.size();
	// }

	// {
	// 	List<int> l {1,2,3,4,5,6};
	// 	cout << l << endl << l.size() << endl;
	// 	l.print_backwards();
	// }

	{
		List<X> l = {X{"one",1}, X{"two",2}};
		l = make_list();
		//List<X> l = make_list();
		l.push_back(X{});
		cout << l << endl;
	}

	return 0;
}