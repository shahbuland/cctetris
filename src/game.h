#ifndef GAME_H
#define GAME_H

#include <vector>
#include "action.h"
#include "block.h"
#include "square.h"

SCORE_FOR_LINE = 10;

class Game {
	std::vector<std::vector<Square*>> board;
	int HEIGHT, WIDTH;
	int SCORE;
	vector<Block*> all_blocks; // list of all blocks for dtor
	Block * active_block; // block currently being acted on by player 
	bool is_line(int r); // checks if line at row r
	void shift_down(int r); // shifts every row before r down
	void check_for_lines(); // checks board for lines, modifies score and shifts down as required
	Block * spawn_block(); // randomly chooses a block to spawn and creates it
	public:
	Game(int height, int width);
	~Game();
	void step(Action & a); // in charge of calling fall on active object
	void fall(int r, int c); // makes square at r,c fall one unit (assumes this is valid)
};

#endif
