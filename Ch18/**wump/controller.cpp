#include "controller.h"
#include <sstream>

/*
Move to a random room with no bats
(but you can move to a room with wump and bats)
*/
Game_state Controller::bat_move() {
	curr = cave.rand_room();

	if (curr->has_item(Item::wump)) 
		return Game_state::loss_wump;
	if (curr->has_item(Item::bat)) 
		return bat_move();
	if (curr->has_item(Item::pit)) 
		return Game_state::loss_pit;
	return Game_state::resume;
}
 
/*
Move to room #rnum if it's viable from current room.
Else, move to a non-specified viable room. 
Returns pair of Game_states - the first refers to the
win/loss state, second refers to whether bats were encountered.
*/
pair<Game_state, Game_state> Controller::move(int rnum) {
	curr = curr->adj_by_rnum(rnum);
	pair<Game_state, Game_state> gs {Game_state::resume, 
			Game_state::no_bats};

	if (curr->has_item(Item::wump)) 
		gs.first = Game_state::loss_wump;
	if (curr->has_item(Item::bat)) {
		gs.first = bat_move();
		gs.second = Game_state::bats;
	}
	if (curr->has_item(Item::pit)) 
		gs.first = Game_state::loss_pit;

	return gs;
}

/*
Arrow travels through rooms, beginning with arrow_curr
i represents the remaining unprocessed rooms in rnums
Returns proper Game_state based on what arrow hits
*/
Game_state Controller::shoot(const vector<int>& rnums, int i, 
		const Room* arrow_curr) 
{
	if (arrow_curr->has_item(Item::wump)) 
		return Game_state::win;
	if (arrow_curr->num() == curr->num()) 
		return Game_state::loss_shot;

	if (i == rnums.size())
		return Game_state::resume;

	const Room* next = arrow_curr->adj_by_rnum(rnums.at(i));
	return shoot(rnums, i+1, next);
}

/*
Shoot arrow, trajectory defined by rnums.
If the trajectory doesn't make sense with respect to cave layout,
the shot will be "randomized". 
Logically, shoot_arrow handles the boolean logic of the many cases
that occur when you shoot an arrow, calls relevant functions,
and orders the function calls in the proper manner.
*/
Game_state Controller::shoot_arrow(const vector<int>& rnums) {
	if (rnums.size() != arrow_traverse_len) {
		ostringstream error_msg;
		error_msg << "Controller::shoot_arrow: Arrow trajectory "
			"vector must have size " << arrow_traverse_len;
		throw runtime_error(error_msg.str());
	}
	if (a_count <= 0) {
		throw runtime_error("Controller::shoot_arrow: "
			"Called with a_count <= 0");
	}

	// Shoot
	--a_count;

	int i = 0;
	const Room* arrow_next = curr->adj_by_rnum(rnums.at(i));
	Game_state gs = shoot(rnums, i+1, arrow_next);
	if (gs == Game_state::win || gs == Game_state::loss_shot)
		return gs;

	// Move wump
	cave.move_wump();
	if (curr->has_item(Item::wump))
		return Game_state::loss_wump;

	if (a_count == 0) 
		return Game_state::loss_no_arrow;
	return Game_state::resume;
}

// DEBUG
/*
CHANGE ARROW COUNT SIZE ITS TOO BIG RIGHT NOW OKOKOOKOKKOKOK BYE
ALSO MAKE SURE SEEDRAND IS DONE
*/
int main() 
try {

	//srand(time(nullptr)); // GET RID OF THIS TO TEST 

	Cave cave;
	Controller c {cave};
	cout << cave;
	cout << c;
	while (true) {
		int hi;
		cin >> hi;
		//Game_state gs = (c.move(hi)).first; // Cool how you can do this!
		auto gsp = c.move(hi);
		cout << c;

		if (gsp.first == Game_state::loss_wump) {
			cout << "YOU GOT EATEN\n";
		}
		if (gsp.first == Game_state::loss_pit) {
			cout << "YOU GOT FALLED DOWN\n";
		}
		if (gsp.first == Game_state::resume) {
			cout << "You can resume\n";
		}
		if (gsp.second == Game_state::bats) {
			cout << "Bats eated ya\n";
		}
		if (gsp.second == Game_state::no_bats) {
			cout << "Babts non-eated yu\n";
		}

		vector<int> vi(3);
		for (int i = 0; i < 3; ++i) {
			cin >> vi[i];
		}

		Game_state gs = c.shoot_arrow(vi);

		if (gs == Game_state::resume) {
			cout << "You can resume\n";
		}
		if (gs == Game_state::loss_shot)
			cout << "You shot yourself!\n";
		if (gs == Game_state::win) 
			cout << "You won yeehaw\n";
		if (gs == Game_state::loss_wump) {
			cout << "YOU GOT EATEN\n";
		}
		if (gs == Game_state::loss_no_arrow) {
			cout << "No arrow!!!\n";
		}
		
		cout << cave;
	}

	return 0;
}
catch(exception& e) {
	cerr << "Error: " << e.what() << ".\n";
	return 1;
}
catch (...) {
	cerr << "Error: Unknown exception.\n";
	return 2;
}
