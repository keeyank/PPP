#include <sstream>
#include <iomanip>

#include "room.h"

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
