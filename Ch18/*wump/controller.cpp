#include "controller.h"

Game_state Controller::move(int rnum) {
	curr = curr->adj_by_rnum(rnum);
	if (curr->has_item(Item::bat)) {
		// return move_to_rand()
		// YOU HAVE TO RETURN SOMETHING HERE
		// otherwise control flow will keep going!
	}
	if (curr->has_item(Item::wump)) {
		return Game_state::loss_wump;
	}
	if (curr->has_item(Item::pit)) {
		return Game_state::loss_pit;
	}
	return Game_state::resume;
}

// DEBUG
int main() 
try {

	srand(time(nullptr));
	Cave cave;
	Controller c {cave};
	cout << cave;
	cout << c;
	while (true) {
		int hi;
		cin >> hi;
		Game_state gs = c.move(hi);
		cout << c;

		if (gs == Game_state::loss_wump) {
			cout << "YOU GOT EATEN\n";
		}
		if (gs == Game_state::loss_pit) {
			cout << "YOU GOT FALLED DOWN\n";
		}
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
