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
	}
	return os;
}

/* Pre Cave Construction */

Room::Room() // Needed for Cave's constructor
	: adjc(adj_count) { }

Room::Room(int num) 
	: adjc(adj_count), n{num}
{
	if (n < 0 || n >= total_rooms) {
		ostringstream error_msg;
		error_msg << "Room::Room: Room number must be within"
			<< " range [0," << total_rooms  
			<< ") (number was " << n << ")";
		throw runtime_error(error_msg.str());
	}
}

void Room::set_adj(Room* r) {
	if (!has_adj()) {
		ostringstream error_msg;
		error_msg << "Room::set_adj: All adjacent rooms"
			<< " are already set (room #" << n << ")";
		throw runtime_error(error_msg.str());
	}
	int i = 0;
	while (adjc.at(i) != nullptr) ++i;
	adjc.at(i) = r;
}

bool Room::has_adj() const {
	for (int i = 0; i < adj_count; ++i) {
		if (adjc.at(i) == nullptr) return true;
	}
	return false;
}

/* Post Cave construction */

const Room* Room::adj_by_rnum(int rnum) const {
	int i = 0;
	for (; i < adj_count-1; ++i) {
		if (adj(i)->num() == rnum) break;
	}
	return adj(i);
}

ostream& operator<<(ostream& os, const Room& r) {
	os << "\nRoom #" << setw(3) << r.n << " at loc "
		<< &r << "\nAdjacents:";
	for (int i = 0; i < adj_count; ++i) {
		if (r.adjc.at(i)) {
			os << "\nRoom #" << setw(3) << r.adjc.at(i)->n 
				<< " at loc " << r.adjc.at(i);
		}
		else {
			os << "\nnullptr";
		}
	}
	os << "\nState: " << r.state << endl;
	return os;
}
