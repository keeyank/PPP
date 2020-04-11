#include "cave.h"

/*
All 'action' member functions of controller should return
a game state, based on the cave layout
*/
enum struct Game_state {
	resume, win, loss_pit, loss_wump, loss_shot
};

/*
Controller deals with the movement of the player.
It doesn't concern itself with cave's representation,
that's the job of cave. However, it does have access to the current
room's representation. It determines the right actions based on
player movement and the room's state, and moves the player. 
*/
struct Controller {
	Controller(Cave& c)
		: cave{c}, curr{c.init_room()} { }

	Game_state move(int rnum);

	friend ostream& operator<<(ostream& os, const Controller& c) {
		return os << "Current room: " << *c.curr << endl;
	}

private:
	const Room* curr; 
	Cave& cave; // Cave& since Controller shouldn't "own" a cave
};