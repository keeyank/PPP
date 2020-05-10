#include "test_class.h"
#include "container_stuff.h"

/*---------------------------------------------*/
/* Link */

template<typename E>
struct Link {
	E val {};
	Link* next = nullptr;
	Link* prev = nullptr;
};

/*---------------------------------------------*/
/* List */

template<typename E>
struct List {	

	// Bidirectional iterator, read/write
	struct Iterator {
		Iterator(Link<E>* c) : curr{c} { }
		// Default copy/move are OK

		Iterator& operator++();
		Iterator& operator--();

		E& operator*();

		bool operator==(const Iterator& it) const 
			{return curr == it.curr;}
		bool operator!=(const Iterator& it) const
			{return !(*this == it);}

		Link<E>* link() {return curr;}
	private:
		Link<E>* curr;
	};

	// Bidirectional iterator, readonly
	struct Const_iterator {
		Const_iterator(Link<E>* c) : curr(c) { }

		Const_iterator& operator++();
		Const_iterator& operator--();

		const E& operator*() const;

		bool operator==(const Const_iterator& it) const
			{return curr == it.curr;}
		bool operator!=(const Const_iterator& it) const
			{return !(*this == it);}
	private:
		Link<E>* curr;
	};

	/* Constructor/destructor/copy */

	List()
		: head{nullptr}, tail{nullptr}, sz{0} { }
	List(initializer_list<E> l);

	List(const List&); 
	List& operator=(const List&); 

	List(List&&);
	List& operator=(List&&);

	~List();

	/* Operations */

	void push_back(const E& val);
	void push_front(const E& val);

	Iterator insert(Iterator pos, const E& val);
	Iterator erase(Iterator pos);

	E& front() {return head->val;}
	const E& front() const {return head->val;}
	E& back() {return tail->val;}
	const E& back() const {return tail->val;}

	int size() const {return sz;}

	/* Iterators */
	/*
	Doesn't return Iterator& - The object would be
	destroyed after the function call!
	Note how begin() == end() if the list is empty
	*/
	Iterator begin() {return Iterator{head};}
	Const_iterator begin() const {return Const_iterator{head};}
	Iterator end() {return Iterator{nullptr};}
	Const_iterator end() const {return Const_iterator{nullptr};}

	Iterator rbegin() {return Iterator{tail};}
	Const_iterator rbegin() const {return Const_iterator{tail};}
	Iterator rend() {return Iterator{nullptr};}
	Const_iterator rend() const {return Const_iterator{nullptr};}

private:

	void cleanup();
	/*
	Invariant:
	head points to first element in sequence
	tail points to last element in sequence
	tail->next is nullptr
	head->prev is nullptr
	If list empty, head and tail are nullptr
	Otherwise, head and tail are valid pointers
	*/
	Link<E>* head;
	Link<E>* tail;

	int sz;
};

/*---------------------------------------------*/
/* Iterator implementation */

template<typename E>
E& List<E>::Iterator::operator*() {
	if (!curr) {
		throw runtime_error("List<E>::Iterator::operator*: "
			"Attempted to dereference beyond List's range");
	}
	return curr->val;
}

template<typename E>
typename List<E>::Iterator& List<E>::Iterator::operator++() {
	if (!curr) {
		throw runtime_error("List<E>::Iterator::operator++: "
			"Attempted to increment beyond allowable range");
	}
	curr = curr->next;
	return *this;
}

template<typename E>
typename List<E>::Iterator& List<E>::Iterator::operator--() {
	if (!curr) {
		throw runtime_error("List<E>::Iterator::operator--: "
			"Attempted to decrement beyond allowable range");
	}
	curr = curr->prev;
	return *this;
}

template <typename E>
const E& List<E>::Const_iterator::operator*() const {
	if (!curr) {
		throw runtime_error("List<E>::Const_iterator::operator*: "
			"Attempted to dereference beyond List's range");
	}
	return curr->val;
}

template<typename E>
typename List<E>::Const_iterator& 
		List<E>::Const_iterator::operator++() 
{
	if (!curr) {
		throw runtime_error("List<E>::Const_iterator::operator++: "
			"Attempted to increment beyond allowable range");
	}
	curr = curr->next;
	return *this;
}

template<typename E>
typename List<E>::Const_iterator& 
		List<E>::Const_iterator::operator--() 
{
	if (!curr) {
		throw runtime_error("List<E>::Const_iterator::operator--: "
			"Attempted to decrement beyond allowable range");
	}
	curr = curr->prev;
	return *this;
}

/*---------------------------------------------*/
/* Implementation functions */

template<typename E>
void List<E>::push_back(const E& val) {
	Link<E>* newlink = new Link<E>{val, nullptr, tail};
	if (head == nullptr) head = newlink;
	else tail->next = newlink;
	tail = newlink;
	++sz;
}

template<typename E>
void List<E>::cleanup() {
	while (head != nullptr) {
		Link<E>* next = head->next;
		delete head;
		head = next;
	}
}

/*---------------------------------------------*/
/* Constructor/destructor/copy */

/*
I forgot to initialize with sz{0}, head{nullptr}, etc.
Lead to a bug - sz was an undefined value...
NEVER FORGET TO INITIALIZE!!! 
*/
template<typename E>
List<E>::List(initializer_list<E> l) 
	: head{nullptr}, tail{nullptr}, sz{0}
{
	for (auto it = l.begin(); it != l.end(); ++it) {
		push_back(*it);
	}
}

template<typename E>
List<E>::List(const List<E>& l) 
	: head{nullptr}, tail{nullptr}, sz{0}
{
	for (auto it = l.begin(); it != l.end(); ++it) {
		push_back(*it);
	}
}

template<typename E>
List<E>& List<E>::operator=(const List<E>& l) {
	cleanup();
	head = nullptr;
	tail = nullptr;
	sz = 0;
	for (auto it = l.begin(); it != l.end(); ++it) {
		push_back(*it);
	}
	return *this;
}

template<typename E>
List<E>::List(List<E>&& l) 
	: head{l.head}, tail{l.tail}, sz{l.sz}
{
	l.head = nullptr;
	l.tail = nullptr;
	l.sz = 0;
}

template<typename E>
List<E>& List<E>::operator=(List<E>&& l) {
	cleanup();
	head = l.head;
	tail = l.tail;
	sz = l.sz;
	l.head = nullptr;
	l.tail = nullptr;
	l.sz = 0;
	return *this;
}

template<typename E>
List<E>::~List() {
	cleanup();
}

/*---------------------------------------------*/
/* Public interface */

template<typename E>
void List<E>::push_front(const E& val) {
	Link<E>* newlink = new Link<E>{val, head, nullptr};
	if (!tail) tail = newlink;
	else head->prev = newlink;
	head = newlink;
	++sz;
}

template<typename E>
typename List<E>::Iterator List<E>::insert(List<E>::Iterator pos,
		const E& val) 
{
	if (pos == end()) {
		push_back(val);
		return end();
	}
	if (pos == begin()) {
		push_front(val);
		return begin();
	}

	Link<E>* curr = pos.link();
	Link<E>* newlink = new Link<E>{val, curr, curr->prev};
	curr->prev->next = newlink;
	curr->prev = newlink;
	++sz;
	return List<E>::Iterator{newlink};
}

template<typename E>
typename List<E>::Iterator List<E>::erase(List<E>::Iterator pos) {
	if (pos == end()) return pos;

	Link<E>* curr = pos.link();
	if (curr != head) curr->prev->next = curr->next;
	else head = curr->next;
	if (curr != tail) curr->next->prev = curr->prev;
	else tail = curr->prev;

	Link<E>* nextlink = curr->next;
	delete curr;
	--sz;
	return Iterator{nextlink};
}

/*---------------------------------------------*/
/* Debug */

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
	// 	//cout << l << endl;
	// 	printout(l.begin(), l.end());
	// 	//l.print_backwards();
	// 	cout << l.size();
	// }

	// {
	// 	const List<int> l {1,2,3,4,5,6};
	// 	printout(l.begin(), l.end());
	// 	print_backwards(l.rbegin(), l.rend());
	// }

	// {
	// 	List<X> l = {X{"one",1}, X{"two",2}};
	// 	l = make_list();
	// 	//List<X> l = make_list();
	// 	l.push_back(X{});
	// 	printout(l.begin(), l.end());
	// }

	// {
	// 	List<int> l;
	// 	l.push_front(2);
	// 	l.push_back(1);
	// 	l.push_front(1);
	// 	l.push_front(0);
	// 	l.push_front(-1);
	// 	l.push_back(199);
	// 	l.front() -= 2;
	// 	l.back() += 1;

	// 	const List<int> cl {5,1,4,2};
	// 	//cl.front() = 4; // Error!!

	// 	cout << l.front() << endl;
	// 	cout << cl.back() << endl;
	// 	printout(cl.begin(), cl.end()); // Error - cl.begin() not const
	// 					// We need to make const_iterators for this
	// 	// We fixed it! Now begin() returns a Const_iterator for cl
	// 	// Const_iterator is a bidirectional iterator that is readonly

	// 	printout(l.begin(), l.end());
	// }

	// {
	// 	List<int> l {5,2,1,4,3};
	// 	List<int>::Iterator itr = l.begin();
	// 	++itr; ++itr; ++itr;
	// 	itr = l.insert(itr, 11);
	// 	++itr; ++itr;
	// 	itr = l.insert(itr, 21);
	// 	++itr; ++itr;
	// 	if (itr == l.end()) 
	// 		cout << "itr == l.end()\n";
	// 	printout(l.begin(), l.end());
	// }

	// {
	// 	List<int> l;
	// 	if (l.begin() == l.end()) {
	// 		cout << "List is empty\n";
	// 	}

	// 	l.insert(l.begin(), 1);
	// 	l.insert(l.begin(), 1);
	// 	auto itr = l.begin(); ++itr;
	// 	l.insert(itr, 4);
	// 	l.insert(l.end(), 5);
	// 	++itr; ++itr;
	// 	l.insert(itr, 11);
	// 	cout << l.size() << endl;
	// 	printout(l.begin(), l.end());

	// 	List<int> l2;
	// 	l2.insert(l2.end(),5);
	// 	cout << l2.size() << endl;
	// 	printout(l2.begin(), l2.end());
	// }

	// {
	// 	List<X> l {X{"one",1},X{"two",2}};
	// 	// List<X> l2 = l;
	// 	// printout(l2.begin(), l2.end());
	// 	List<X> l2 {X{"one",1}};
	// 	l2 = l;
	// 	printout(l2.begin(), l2.end());
	// }

	// {
	// 	List<int> l {4,1,2,3,5,0};
	// 	printout(l.begin(), l.end());
	// 	l.erase(l.begin());
	// 	printout(l.begin(), l.end());
	// 	l.erase(l.end()); // Does nothing
	// 	printout(l.begin(), l.end());
	// 	l.erase(l.rbegin());
	// 	printout(l.begin(), l.end());
	// 	l.erase(++l.begin());
	// 	printout(l.begin(), l.end());
	// 	l.erase(++l.begin());
	// 	printout(l.begin(), l.end());
	// 	l.erase(--l.rbegin());
	// 	printout(l.begin(), l.end());
	// 	l.erase(l.begin());
	// 	printout(l.begin(), l.end());
	// 	l.erase(l.begin());
	// 	printout(l.begin(), l.end());		
	// }

	// {
	// 	List<int> l {6,1,3};
	// 	l.push_back(4);
	// 	auto itr = l.begin();
	// 	++itr; ++itr;
	// 	itr = l.erase(itr);
	// 	printout(l.begin(), l.end());
	// 	itr = l.erase(itr);
	// 	printout(l.begin(), l.end());
	// 	itr = l.erase(itr);
	// 	printout(l.begin(), l.end());
	// 	l.push_back(5);
	// 	l.push_back(6);
	// 	printout(l.begin(), l.end());
	// 	for (auto itr = l.begin(); itr != l.end(); ++itr) {
	// 		l.erase(itr);
	// 		printout(l.begin(), l.end());
	// 	}
	// 	l = List<int>{5,2,5,1,3};
	// 	for (auto itr = l.rbegin(); itr != l.rend(); --itr) {
	// 		l.erase(itr);
	// 		printout(l.begin(), l.end());
	// 	}
	// }

	// {	
	// 	// Exceptions testing
	// 	List<int> l = List<int>{5,2,1};
	// 	List<int>::Iterator it = l.begin();
	// 	--it;
	// 	//++it; // Uh oh, can't increment or decrement a "one-beyond"
	// 		// iterator (it's Link* is nullptr!)
	// 	//*it = 5; // Uh oh AGAIN, we can't dereference one-beyond itr!
	// 	*l.begin() = 10;
	// 	printout(l.begin(), l.end());
	// 	List<int>::Iterator itr = l.end();
	// 	//++itr; // OH NOOO!!!
	// }

	return 0;
}