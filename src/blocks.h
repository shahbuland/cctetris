#ifndef BLOCKS_H
#define BLOCKS_H

#include <vector>
#include <string>
#include "square.h"

// Class representing all of falling blocks
// Initially constructed as a 4x4 square
//

class Game;

class Block {
	// Thinking of block as 4x4 square
	// L-Block: 0 0 0 0 T-Block: 0 0 0 0
	//          0 0 0 0          0 0 0 0
	//          1 0 0 0          1 1 1 0
	//          1 1 1 1          0 1 0 0
	std::vector<std::vector<int>> shape;
	// Colour of the block
	std::string colour;
	// My individual squares
	std::vector<Square*> mysqrs;
	// Pointer to game master object
	Game * model;
	// Square about which rotation happens
	Square * pivot;	
	// Some private helpers
	void set_SQRS(); // Set all my squares on the models board
	void unset_SQRS(); // Unset all my sqaures on model
	public:
	// shape and colour as described in above fields
	// Assumes 0 <= start_x <= WIDTH (where WIDTH is game board width)
	// takes the Game object as model 
	// i.e. Game should call block ctor with "this"
	Block(std::vector<std::vector<int>> shape,
		  std::string colour,
          int start_x,
		  Game * model);
	~Block();
	// Tries to make block fall one unit
	// Returns false if it can't fall
	// True if it falls
	bool fall();
	// Returns the colour of the block
	std::string get_COLOUR();

	// Player interaction method
	void move_left();
	void move_right();
	void rotate();
};

#endif
