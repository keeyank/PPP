#include <string>
#include <sstream>
#include <utility>

#include "controller.h"

enum struct Action {
	move, shoot, bad_action, bad_move, bad_shoot, quit
};

/* Input functions */

// Continuously eat whitespace until non-whitespace found
istream& eat_space(istream& is) {
	char c = ' ';
	while (isspace(c) && is) { 
		is.get(c);
	}
	if (is) is.putback(c);
	return is;
}

Action get_input_move(istream& is, vector<int>& act_seq)
{
	char num_test {};
	is.get(num_test);
	if (!is || !isdigit(num_test)) {
		return Action::bad_move;
	}
	is.putback(num_test);

	is >> act_seq.at(0);

	if (!is.eof()) {
		return Action::bad_move;
	}

	return Action::move;
}

Action get_input_shoot(istream& is, vector<int>& act_seq)
{
	for (int i = 0; i < arrow_traverse_len; ++i) {
		char num_test {};
		is.get(num_test);
		if (!is || !isdigit(num_test))
			return Action::bad_shoot;
		is.putback(num_test);

		is >> act_seq.at(i);

		if (i != arrow_traverse_len - 1) {
			char dash_test {};
			is.get(dash_test);
			if (!is || dash_test != '-') 
				return Action::bad_shoot;
		}
		else {
			if (!is.eof()) 
				return Action::bad_shoot;
		}
	}

	return Action::shoot;
}

Action get_input_quit(istream& is) {
	is.get(); // Weird, but doesn't work properly otherwise
	if (!is.eof()) {
		return Action::bad_action;
	}
	return Action::quit;
}

/*
Read and parse input, act indicates success of read.
act_seq[0] read into for move, entire act_seq vector read into for
shoot. Reads a single line of input. 
*/
Action get_input(istream& is, vector<int>& act_seq) {
	string err_msg = "get_input: Input stream in bad state";
	eat_space(is);
	if (!is) throw runtime_error(err_msg);

	string line;
	getline(is, line);
	if (!is) throw runtime_error(err_msg);

	istringstream iss {line};

	// iss has atleast 1 char
	char act_ch {}; // action char
	iss.get(act_ch);

	switch (act_ch) {
		case 'm':
			return get_input_move(iss, act_seq);
		case 's':
			return get_input_shoot(iss, act_seq);
		case 'q':
			return get_input_quit(iss);
		default:
			return Action::bad_action;
	}
}

/* Output functions */
/* 
If the return value is bool, it is to let caller know
whether we should quit the game or not. If the return value
is void, there is no ambiguity over whether or not to quit.
*/

bool output_move(pair<Game_state, Game_state> gsp) {
	if (gsp.second == Game_state::bats) {
		cout << "You enter a room full of super bats. They "
			<< "pick you up with their sharp talons and fly "
			<< "you to an unfamiliar room.\n";
	}

	switch (gsp.first) {
		case Game_state::loss_wump:
			cout << "You enter a room, and notice a big yucky "
				"Wumpus who looks really hungry! "
				"He eats you and you die.\n";
			return true;
		case Game_state::loss_pit:
			cout << "You fall through a bottomless pit."
				<< " In other words, you die.\n";
			return true;
		case Game_state::resume:
			cout << "You're safe, for now.\n";
			return false;
		default:
			throw runtime_error("output_move: Invalid Game_state "
					"from Move action");
	}
}

bool output_shoot(Game_state gs) {
	switch (gs) {
		case Game_state::win:
			cout << "You shot the wumpus with a sleepy dart! "
				"Now he can finally relax. Congratulations!!!\n";
			return true;
		case Game_state::loss_shot:
			cout << "Ouchies, you shot yourself! The sleepy juice "
				"dosage is too strong for you to handle. That means "
				"you died (painfully!).\n";
			return true;
		case Game_state::loss_wump:
			cout << "OH NO!!! You missed your shot, and "
				"the wumpus entered your room! It "
				"decides to eat you unfortunately. So you die.\n";
			return true;
		case Game_state::loss_no_arrow:
			cout << "You shot your last dart, but you didn't hit "
				"Wumpus. Out of options, you give up and go home."
				" While you're walking home, a guy sneaks up behind "
				"you and kills you with a hammer. You die!\n";
			return true;
		case Game_state::resume:
			cout << "You shot the sleepy dart, but you didn't hit "
				"the wumpus. You hear a faint rumbling from somewhere "
				"in the cave.\n";
			return false;
		default:
			throw runtime_error("output_shoot: Invalid Game_state "
					"from Shoot action");
	}
}

void output_bad_move() {
	cout << "Invalid command (to move, the command is"
		" \"m[room#]\")\n";
}

void output_bad_shoot() {
	cout << "Invalid command (to shoot, the command is \"s";
	for (int i = 0; i < arrow_traverse_len; ++i) {
		cout << "[room#]";
		if (i < arrow_traverse_len-1) {
			cout << "-";
		}
	}
	cout << "\")\n";
}

void output_bad_action() {
	cout << "Invalid command.\n";
}

void output_curr_room(Controller& c) {
	cout << "\nCurrent room: " << c.num()
		<< "\nAdjacent rooms: ";
	for (int i = 0; i < adj_count; ++i) {
		cout << c.adj_num(i);
		if (i < adj_count-1) cout << ", ";
	}
	cout << "\n\n";

	if (c.wind()) {
		cout << "You feel a slight breeze.\n";
	}
	if (c.noise()) {
		cout << "You hear a distant screeching noise.\n";
	}
	if (c.stink()) {
		cout << "Something smells awful...\n";
	}
	return;
}

void output_arrow_count(int arrow_count) {
	cout << "You have " << arrow_count << " arrows remaining.\n";
}

int main() 
try {

	// Generate cave + controller
	//srand(time(nullptr));
	Cave cave; 
	Controller c {cave};

	vector<int> act_seq(arrow_traverse_len); // action sequence
	Action act {};

	output_curr_room(c);

	while (true) {
		cout << '>';

		act = get_input(cin, act_seq);

		switch (act) {
			case Action::move: { // Scope for variable definitions
				auto gsp {c.move(act_seq.at(0))};
				bool end_game = output_move(gsp);
				if (end_game) return 0;
				output_curr_room(c);
				break;
			}
			case Action::shoot: {
				Game_state gs = c.shoot_arrow(act_seq);
				bool end_game = output_shoot(gs);
				if (end_game) return 0;
				output_arrow_count(c.arrow_count());
				output_curr_room(c);
				break;
			}
			case Action::bad_move:
				output_bad_move();
				break;
			case Action::bad_shoot:
				output_bad_shoot();
				break;
			case Action::bad_action:
				output_bad_action();
				break;
			case Action::quit:
				return 0;
		}
	} 

	return 0;
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
	return 1;
}
catch (...) {
	cerr << "Error: Unknown exception.\n";
	return 2;
}