#include "cave.h"

/*
All 'action' member functions of controller should return
a game state, based on the cave layout
*/
enum struct Game_state {
	resume, win, loss_pit, loss_wump, loss_shot, no_arrow
};

/*
Controller deals with the movement of the player.
It doesn't concern itself with cave's representation,
that's the job of cave. However, it does have access to the current
room's representation. It determines the right actions based on
player movement and the room's state, and moves the player. 
*/
struct Controller {
	explicit Controller(Cave& c)
		: cave{c}, curr{c.init_room()} { }

	// Move to room #rnum
	Game_state move(int rnum);
	// Shoot arrow, trajectory defined by rnums
	Game_state shoot_arrow(const vector<int>& rnums);

	friend ostream& operator<<(ostream& os, const Controller& c) {
		return os << "Current room: " << *c.curr << endl;
	}

private:
	Game_state bat_move();

	Game_state shoot(const vector<int>& rnums, int i, 
			const Room* arrow_curr);
	const Room* curr; 
	Cave& cave; // Cave& since Controller shouldn't "own" a cave

	int arrow_count = max_arrow_count;
};