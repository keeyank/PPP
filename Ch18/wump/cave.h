#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;


struct Room {
	Room(); // Needed for Cave's constructor
	// Invariant - Number within range [0,total_rooms)
	Room(int num);

	int num() const {return n;}

	// Adjacent rooms
	vector<Room*> adj; // Not private (Managed by Cave)

	friend ostream& operator<<(ostream& is, const Room& r);

private:
	int n = -1;
	bool bat = false;
	bool pit = false;
};

// Cave manages the connections between rooms
struct Cave {
	Cave();

	static constexpr int total_rooms = 6;
	static constexpr int adj_count = 3; // Amount of adjacent  
										// rooms for each room

	friend ostream& operator<<(ostream& os, const Cave& c);

private:
	vector<Room> rooms;
	// avail[i] is the set of rooms available for an 
	// edge between room #i
	// Invariant - all integers in the embedded vector are 
	// within the range [0, total_rooms)
	vector<vector<int>> avail; // The vector<int> acts as a set

	void connect_rooms();
};