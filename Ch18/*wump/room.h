#include <iostream>

#include "constants.h"
#include "vector_set.h"

using namespace std;

enum struct Item {
	pit, bat, wump, wind, noise, stink, player
};

ostream& operator<<(ostream& os, const Item& i);

struct Room {
	Room(); // Needed for Cave's constructor
	// Invariant - Number within range [0,total_rooms)
	Room(int num);

	int num() const {return n;}

	// Adjacent rooms
	vector<Room*> adj; // Not private (Managed by Cave)
	bool has_adj() const;

	// Item access functions
	// Add item. Ignores duplicate items, since Vector_set's 
	// insert ignores duplicate items.
	void add_item(Item i) {
		state.insert(i);
	}
	// Remove item.
	// Does nothing if item not currently in room's state
	void remove_item(Item i) {
		state.remove(i);
	}

	friend ostream& operator<<(ostream& is, const Room& r);

private:
	int n = -1;
	Vector_set<Item> state;
};