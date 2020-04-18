#include "cave.h"

/*
All 'action' member functions of controller should return
a game state, based on the cave layout. Every Game_state 
except for resume and bats/no_bats must be followed by
game termination. 
*/
enum struct Game_state {
	resume, win, loss_pit, loss_wump, loss_shot, loss_no_arrow, 
	bats, no_bats
};

/*
Controller deals with the actions of the player. It defines
the interface to the cave and player, defines all of the
logical operations available to a user, and handles the change
in representation of the cave / player position accordingly. 
Essentially, Controller IS the game. It's operations return
Game_state corresponding to the current state of the game.
Additionally, Controller allows its user to read from it, to 
deduce properties of the state of the player / cave.
*/
struct Controller {
	explicit Controller(Cave& c)
		: cave{c}, curr{c.init_room()} { }

	/* Action functions */

	// Move to room #rnum
	pair<Game_state, Game_state> move(int rnum);
	// Shoot arrow, trajectory defined by rnums
	Game_state shoot_arrow(const vector<int>& rnums);

	/* Sense functions */

	int arrow_count() const {
		return a_count;
	}

	bool wind() {
		return curr->has_item(Item::wind);
	}
	bool noise() {
		return curr->has_item(Item::noise);
	}
	bool stink() {
		return curr->has_item(Item::stink);
	}

	int adj_num(int i) {
		return curr->adj(i)->num();
	}
	int num() {
		return curr->num();
	}

private:
	Game_state bat_move();

	Game_state shoot(const vector<int>& rnums, int i, 
			const Room* arrow_curr);
	const Room* curr; 
	Cave& cave; // Cave& since Controller shouldn't "own" a cave

	int a_count = max_arrow_count;
};