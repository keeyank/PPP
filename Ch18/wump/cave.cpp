#include <sstream>
#include <iomanip>

#include "cave.h"

Room::Room() // Needed for Cave's constructor
	: adj(Cave::adj_count) { }

Room::Room(int num) 
	: adj(Cave::adj_count), n{num}
{
	if (n < 0 || n >= Cave::total_rooms) {
		ostringstream error_msg;
		error_msg << "Room::Room: Room number must be within"
			<< " range [0," << Cave::total_rooms  
			<< ") (number was " << n << ")";
		throw runtime_error(error_msg.str());
	}
}

bool Room::has_adj() {
	for (int i = 0; i < Cave::adj_count; ++i) {
		if (adj.at(i) == nullptr) return true;
	}
	return false;
}

ostream& operator<<(ostream& os, const Room& r) {
	os << "\nRoom #" << setw(3) << r.n << " at loc "
		<< &r << "\nAdjacents:";
	for (int i = 0; i < Cave::adj_count; ++i) {
		if (r.adj.at(i)) {
			os << "\nRoom #" << setw(3) << r.adj[i]->n 
				<< " at loc " << r.adj[i];
		}
		else {
			os << "\nnullptr";
		}
	}
	return os << endl;
}

/*
Return true whenever r1 and r2 are in eachother's 
availability sets
*/
bool Cave::connectable(const Room& r1, const Room& r2) {
	return avail.at(r1.num()).in(r2.num()) 
		&& avail.at(r2.num()).in(r1.num());
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

// Remove room #n from all availability sets
void Cave::remove_from_avail(int n) {
	for (int i = 0; i < total_rooms; ++i) {
		avail.at(i).remove(n);
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
			int room_num = curr_avail.get_rand();
			Room& rand_room = rooms.at(room_num);

			connect(curr_room, rand_room);
			curr_room.adj.at(j) = &rand_room;
		}
	}
}

Cave::Cave()
	: rooms(total_rooms), avail(total_rooms)
{
	for (int i = 0; i < total_rooms; ++i) {
		rooms.at(i) = Room{i}; // Calls (default) copy assignment

		// Construct avail
		for (int j = 0; j < total_rooms; ++j) {
			if (j != i) {
				avail.at(i).insert(j);
			}
		}
	}
	connect_rooms();
}

ostream& operator<<(ostream& os, const Cave& c) {
	for (int i = 0; i < Cave::total_rooms; ++i) {
		os << c.rooms.at(i);
	}
	return os;
}

int main() 
try {

	// Simulate cave management
	Cave c; 
	cout << c;

	return 0;
}
catch(exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Error: Unknown exception.\n";
}
