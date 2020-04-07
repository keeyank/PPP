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
Randomly connect each room in the rooms vector
This is done by setting their adjacency vectors properly
After its execution, each room is connected to exactly 3 rooms
The 3 rooms are unique and no room is connected to itself
Easier said than done!
*/
void Cave::connect_rooms() {
	srand(time(nullptr));

	for (int i = 0; i < total_rooms; ++i) {
		Room& curr_room = rooms.at(i);

		for (int j = 0; j < adj_count; ++j) {
			vector<int>& curr_avail = avail.at(i);

			int range = curr_avail.size();
			int room_num = curr_avail.at(rand() % range);

			Room* rand_room = &rooms.at(room_num);
			curr_room.adj.at(j) = rand_room;
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
				avail.at(i).push_back(j);
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
