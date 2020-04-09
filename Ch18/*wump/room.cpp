#include <sstream>
#include <iomanip>

#include "room.h"

ostream& operator<<(ostream& os, const Item& i) {
	switch (i) {
		case Item::pit:
			os << "Pit"; break;
		case Item::bat:
			os << "Bat"; break;
		case Item::wump:
			os << "Wump"; break;
		case Item::wind:
			os << "Wind"; break;
		case Item::noise:
			os << "Noise"; break;
		case Item::stink:
			os << "Stink"; break;
		case Item::player:
			os << "Player"; break;
	}
	return os;
}

Room::Room() // Needed for Cave's constructor
	: adj(adj_count) { }

Room::Room(int num) 
	: adj(adj_count), n{num}
{
	if (n < 0 || n >= total_rooms) {
		ostringstream error_msg;
		error_msg << "Room::Room: Room number must be within"
			<< " range [0," << total_rooms  
			<< ") (number was " << n << ")";
		throw runtime_error(error_msg.str());
	}
}

bool Room::has_adj() const {
	for (int i = 0; i < adj_count; ++i) {
		if (adj.at(i) == nullptr) return true;
	}
	return false;
}

ostream& operator<<(ostream& os, const Room& r) {
	os << "\nRoom #" << setw(3) << r.n << " at loc "
		<< &r << "\nAdjacents:";
	for (int i = 0; i < adj_count; ++i) {
		if (r.adj.at(i)) {
			os << "\nRoom #" << setw(3) << r.adj.at(i)->n 
				<< " at loc " << r.adj.at(i);
		}
		else {
			os << "\nnullptr";
		}
	}
	os << "\nState: " << r.state << endl;
	return os;
}
