#include "room.h"

/*
Cave manages the connections between rooms, sets up the state
of each room, and handles everything related to cave layout
You must call srand() before declaring a cave, because it 
uses rand() (indirectly via vector_set)
*/
struct Cave {
	Cave();

	// Move wump to a random location adjacent room
	void move_wump();
	// Get a random room
	// Const pointer - you can't 
	const Room* rand_room() {
		return &rooms.at(rand() % total_rooms);
	}

	friend ostream& operator<<(ostream& os, const Cave& c);

private:
	vector<Room> rooms;

	// avail[i] is the set of rooms available for an 
	// edge between room #i
	// Invariant - all integers in the vector set are 
	// within the range [0, total_rooms)
	vector<Vector_set<int>> avail; 

	// Room number where wumpus resides
	int wump_rnum = -1;

	// Cave construction
	void construct_rooms();
	bool connect_rooms();
	void connect(Room& r1, Room& r2);
	bool connectable(const Room& r1, const Room& r2);
	void remove_from_avail(int n);

	// State management
	void add_states();
	void add_cause_item(Room& r, Item cause, Item effect);
	void remove_all(Item i);

};