#include <iostream>
#include "link.h"

using namespace std;

Link* Link::insert(Link* n) {
	if (n==nullptr) return this;
	n->succ = this;
	if (prev) prev->succ = n;
	n->prev = prev;
	prev = n;
	return n;
}

Link* Link::find(const string& s) {
	Link* curr = this;
	while (curr) {
		if (curr->value == s) return curr;
		curr = curr->succ;
	}
	return nullptr;
}

void erase(Link* n) {
	if (n->succ) n->succ->prev = n->prev;
	if (n->prev) n->prev->succ = n->succ;
	delete n;
}

void cleanup(Link* first) {
	Link* curr = first;
	while (curr != nullptr) {
		Link* next = curr->succ;
		delete curr;
		curr = next;
	}
}

void print(Link* p) {
	Link* curr = p;
	while (curr != nullptr) {
		cout << curr->value << ' ';
		curr = curr->succ;
	}
	cout << endl;
}

int main() {
	Link* norse_gods = new Link{"Thor"};
	norse_gods = norse_gods->insert(new Link{"Odin"});
	norse_gods = norse_gods->insert(new Link{"Zeus"});
	norse_gods = norse_gods->insert(new Link{"Freia"});
	Link* p = norse_gods->find("Freia");
	if (p) p->value = "handkerchief";
	norse_gods = norse_gods->succ;
	erase(norse_gods->prev);
	print(norse_gods);
	cleanup(norse_gods);
	
	return 0;
}