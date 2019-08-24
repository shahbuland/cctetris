#ifndef GAME_H
#define GAME_H

#include <vector>
#include "blocks.h"
#include "square.h"

enum class Action { NONE, ROTATE, MOVE_LEFT, MOVE_RIGHT};

class Game {
	std::vector<std::vector<Square*>> board;
	int HEIGHT, WIDTH;
	int SCORE;
	std::vector<Block*> all_blocks; // list of all blocks for dtor
	Block * active_block; // block currently being acted on by player 
	bool is_line(int r); // checks if line at row r
	void shift_down(int r); // shifts every row before r down
	void check_for_lines(); // checks board for lines, modifies score and shifts down as required
	Block * spawn_block(); // randomly chooses a block to spawn and creates it
	bool justSpawned; // useful for checking for gameover
	public:
	Game(int height, int width);
	~Game();
	void step(Action a, bool & done); // in charge of calling fall on active object
	// Obvious getters
	const int get_HEIGHT();
	const int get_WIDTH();
	const int get_SCORE();
	// Getter and setter for square
	Square * get_SQUARE(int r, int c);
	void set_SQUARE(int r, int c, Square * sqr);
	
	friend std::ostream & operator<<(std::ostream & out, Game & g);
};

std::ostream & operator<<(std::ostream & out, Game & g);

#endif
