#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>

using namespace std;


struct Room {

	Room() // Needed for Cave's constructor
		: adj(adj_count) { }

	// Invariant - Number within range [0,total_rooms)
	Room(int num);

	friend ostream& operator<<(ostream& is, const Room& r);

	int num() const {return n;}

	// Adjacent rooms
	vector<Room*> adj; // Not private (Managed by Cave)

private:
	int n = -1;
	bool bat = false;
	bool pit = false;
};

ostream& operator<<(ostream& os, const Room& r) {
	os << "\nRoom #" << setw(3) << r.n << " at loc "
		<< &r << "\nAdjacents:";
	for (int i = 0; i < adj_count; ++i) {
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

// Cave manages the connections between rooms
struct Cave {
	Cave();

	friend ostream& operator<<(ostream& os, const Cave& c);
private:
	vector<Room> rooms;

	void connect_rooms();
};

void Cave::connect_rooms() {
	srand(time(nullptr));
	for (int i = 0; i < total_rooms; ++i) {
		Room& curr_room = rooms.at(i);

		for (int j = 0; j < adj_count; ++j) {

			Room* rand_room = &rooms.at(rand() % total_rooms);
			while (rand_room->num() == curr_room.num()) {
				rand_room = &rooms.at(rand() % total_rooms);
			}
			
			curr_room.adj.at(j) = rand_room;
		}
	}
}

Cave::Cave()
	: rooms(total_rooms)
{
	for (int i = 0; i < total_rooms; ++i) {
		rooms.at(i) = Room{i}; // Calls (default) copy assignment
	}
	connect_rooms();
}

ostream& operator<<(ostream& os, const Cave& c) {
	for (int i = 0; i < total_rooms; ++i) {
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
