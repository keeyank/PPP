#include <iostream>

#include "constants.h"
#include "vector_set.h"

using namespace std;

enum struct Item {
	pit, bat, wump, wind, noise, stink
};

ostream& operator<<(ostream& os, const Item& i);

struct Room {

	// Constructors

	Room(); 
	Room(int num);

	/* Pre Cave Construction Member Function */
	/*
	These functions don't assume that adjc is set for each
	index. It's possible for an index in adjc to have nullptr
	as its value.
	*/

	// Get i'th adjacent room
	Room* adj(int i) {
		return adjc.at(i);
	}
	// Return true if i'th adjacent room available
	bool adj_available(int i) const {
		return adjc.at(i) == nullptr;
	}
	// Set an available adjacent room
	void set_adj(Room* r);
	// Return true if this room has an available adjacent room
	bool has_adj() const;

	// Item access functions Follows Vector_set rules 
	// for duplicates/lack of specified item

	// Add item. 
	void add_item(Item i) {
		state.insert(i);
	}
	// Remove item.
	void remove_item(Item i) {
		state.remove(i);
	}
	// Return true if i is in this room's state
	bool has_item(Item i) const {
		return state.in(i);
	}

	/* Post Cave Construction Member Functions */
	/*
	These functions have the fundamental assertion that every
	room has every adjacent room set. In general, these functions
	are to be used by Controller only, once every room is set up
	by Cave.
	*/

	// Get adjacent room with number rnum
	// If no such room exists, return last room
	const Room* adj_by_rnum(int rnum) const;
	
	const Room* adj(int i) const {
		return adjc.at(i);
	}

	// Miscellaneous

	// Get room number
	int num() const {return n;}
	
private:
	// Room number
	int n = -1;
	// Set which represents the state of the room (aka it's items)
	Vector_set<Item> state;
	// adj_count pointers to adjacent rooms
	// nullptr means the room hasn't been set yet.
	vector<Room*> adjc;
};