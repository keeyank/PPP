#include "cave.h"

/* Cave State Functions */

/*
Add cause item (pit, bat, wump), surrounded by effect item
(wind, breeze, stink) to cave at room r. 
*/
void Cave::add_cause_item(Room& r, Item cause, Item effect) {
	r.add_item(cause);
	for (int i = 0; i < adj_count; ++i) {
		r.adj(i)->add_item(effect);
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
bool Cave::connectable(int r1_num, int r2_num) {
	return avail.at(r1_num).in(r2_num) 
		&& avail.at(r2_num).in(r1_num);
}

// Remove room #n from all availability sets
void Cave::remove_from_avail(int n) {
	for (int i = 0; i < total_rooms; ++i) {
		avail.at(i).remove(n);
	}
}

/*
Initialize data structures so rooms can be connected
Set up rooms vector and availability sets. 
Overwrite previous rooms vector and availability sets if needed
*/
void Cave::construct_rooms() {
	for (int i = 0; i < total_rooms; ++i) {
		rooms.at(i) = Room{i}; // Calls (default) copy assignment

		// Construct (or reconstruct) avail
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
	if (!connectable(r1.num(), r2.num())) {
		throw runtime_error("Cave::connect: Attempted to connect"
				" 2 rooms that aren't in eachother's availability"
				" sets");
	}

	r1.set_adj(&r2);
	r2.set_adj(&r1);

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
Randomly connect each room in the rooms vector.
Make sure the connections leave the cave in a good state
(each room has 3 connected rooms, the connection is both ways).
May fail or succeed, and must be called again if failure.
Fails when the availability set of a room is 0 when it 
shouldn't be.
*/
bool Cave::connect_rooms() {
	for (int i = 0; i < total_rooms; ++i) {
		Room& curr_room = rooms.at(i);

		for (int j = 0; j < adj_count; ++j) {
			if (curr_room.adj(j)) // adj[j] already set
				continue;

			Vector_set<int>& curr_avail = avail.at(i);
			if (curr_avail.size() == 0) return false; // Failure

			int rnum = curr_avail.get_rand();
			Room& rand_room = rooms.at(rnum);

			connect(curr_room, rand_room);
		}
	}
	return true;
}

/*
Add items to each room, providing the state of each room.
Ensures the cave is in a good state - the rules of Hunt the
Wumpus are not broken. Guarantee's room 0 has no cause items.
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
	bool success = false;
	while (!success) {
		construct_rooms();
		success = connect_rooms();
	}
	// Every room that Cave has is fully connected at this point.
	add_states();
}

/* Member Functions */

/*
Move wumpus to a random location in an adjacent room.
Alternatively, wumpus may stay in the same room.
Ensures the rules of hunt the wumpus are met after the move.
*/
void Cave::move_wump() {
	Room& wump_room = rooms.at(wump_rnum);
	remove_all(Item::wump);
	remove_all(Item::stink);

	int index = (rand() % (adj_count+1)) - 1;
	Room& next_wump_room = (index == -1) ? wump_room
			: *wump_room.adj(index);

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