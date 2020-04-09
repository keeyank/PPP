#include "cave.h"

/* Cave State Functions */

/*
Add cause item (pit, bat, wump), surrounded by effect item
(wind, breeze, stink) to cave at room r. 
*/
void Cave::add_cause_item(Room& r, Item cause, Item effect) {
	r.add_item(cause);
	for (int i = 0; i < adj_count; ++i) {
		Room& adj_room = *r.adj.at(i);
		adj_room.add_item(effect); 
	}
}

/*
Remove all instances of i from the cave.
*/
void Cave::remove_all(Item itm) {
	for (int i = 0; i < total_rooms; ++i) {
		rooms.at(i).remove_item(itm);
	}
}

/* Constructor Functions */

/*
Return true whenever r1 and r2 are in eachother's 
availability sets
*/
bool Cave::connectable(const Room& r1, const Room& r2) {
	return avail.at(r1.num()).in(r2.num()) 
		&& avail.at(r2.num()).in(r1.num());
}

// Remove room #n from all availability sets
void Cave::remove_from_avail(int n) {
	for (int i = 0; i < total_rooms; ++i) {
		avail.at(i).remove(n);
	}
}

/*
Initialize data structures so rooms can be connected
Set up rooms vector and availability sets
*/
void Cave::construct_rooms() {
	for (int i = 0; i < total_rooms; ++i) {
		rooms.at(i) = Room{i}; // Calls (default) copy assignment

		// Construct avail
		for (int j = 0; j < total_rooms; ++j) {
			if (j != i) {
				avail.at(i).insert(j);
			}
		}
	}
}

/*
Connect 2 rooms, and make the corresponding changes in their
availability set. 
*/
void Cave::connect(Room& r1, Room& r2) {
	// Assertions
	if (!r1.has_adj() || !r2.has_adj()) {
		throw runtime_error("Cave::connect: Attempted to connect"
				" a room that has its adjacency vector full");
	}
	if (!connectable(r1, r2)) {
		throw runtime_error("Cave::connect: Attempted to connect"
				" 2 rooms that aren't in eachother's availability"
				" sets");
	}

	// Add edge between r1 and r2
	int r1_i = 0;
	int r2_i = 0;
	while (r1.adj.at(r1_i) != nullptr) ++r1_i;
	while (r2.adj.at(r2_i) != nullptr) ++r2_i;
	r1.adj.at(r1_i) = &r2;
	r2.adj.at(r2_i) = &r1;

	// r1 and r2 no longer available to eachother
	avail.at(r1.num()).remove(r2.num());
	avail.at(r2.num()).remove(r1.num());

	// Remove fully connected rooms from avail
	if (!r1.has_adj()) {
		remove_from_avail(r1.num());
	}
	if (!r2.has_adj()) {
		remove_from_avail(r2.num());
	}
}

/*
Randomly connect each room in the rooms vector
This is done by setting their adjacency vectors properly
After its execution, each room is connected to exactly 
adj_count rooms. The adj_count rooms are unique and no 
room is connected to itself
*/
void Cave::connect_rooms() {
	for (int i = 0; i < total_rooms; ++i) {
		Room& curr_room = rooms.at(i);

		for (int j = 0; j < adj_count; ++j) {
			if (curr_room.adj.at(j)) // adj[j] already set
				continue;

			Vector_set<int>& curr_avail = avail.at(i);
			int rnum = curr_avail.get_rand();
			Room& rand_room = rooms.at(rnum);

			connect(curr_room, rand_room);
			curr_room.adj.at(j) = &rand_room;
		}
	}
}

/*
Add items to each room, providing the state of each room.
Ensures the cave is in a good state - the rules of Hunt the
Wumpus are not broken.
Doesn't need to be random - the randomness in connect_rooms
takes care of that for us. This allows us to guarantee that
room 0 has no cause items (but it may have effect items)
*/
void Cave::add_states() {
	if (pit_count+bat_count+1 >= total_rooms) { // 1 for wumpus
		throw runtime_error("Cave::add_states: Not enough rooms"
					" to hold all of the items");
	}
	
	int rnum = 1; // Keeps track of current room num
	for (int i = 0; i < pit_count; ++i) {
		add_cause_item(rooms.at(rnum), Item::pit, Item::wind);
		++rnum;
	}
	for (int i = 0; i < bat_count; ++i) {
		add_cause_item(rooms.at(rnum), Item::bat, Item::noise);
		++rnum;
	}
	add_cause_item(rooms.at(rnum), Item::wump, Item::stink);
	wump_rnum = rnum;
}

Cave::Cave()
	: rooms(total_rooms), avail(total_rooms)
{
	construct_rooms();
	connect_rooms();
	add_states();
}

/* Member Functions */

/*
Move wumpus to a random location in an adjacent room.
Ensures the rules of hunt the wumpus are met after the move.
*/
void Cave::move_wump() {
	Room& wump_room = rooms.at(wump_rnum);
	remove_all(Item::wump);
	remove_all(Item::stink);

	int next_rnum = (rand() % (adj_count+1)) - 1;
	Room& next_wump_room = (next_rnum == -1) ? wump_room
			: *wump_room.adj.at(next_rnum);

	add_cause_item(next_wump_room, Item::wump, Item::stink);
	wump_rnum = next_wump_room.num();
}

/* Debug */

ostream& operator<<(ostream& os, const Cave& c) {
	for (int i = 0; i < total_rooms; ++i) {
		os << c.rooms.at(i);
	}
	return os;
}

int main() 
try {

	// Simulate cave management
	srand(time(nullptr));
	Cave c;
	for (int i = 0; i < 10; ++i) {
		cout << *c.rand_room();
	}
	const Room* r = c.rand_room(); // no const gives compile error
						// this is a good thing!!
	Room* r2 = r->adj.at(0);
	r2->adj.at(0) = nullptr;
	r2->adj.at(1) = nullptr;
	r2->adj.at(2) = nullptr;
	cout << *r2 << endl;

	return 0;
}
catch(exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Error: Unknown exception.\n";
}
