#ifndef BLOCKS_H
#define BLOCKS_H

#include <vector>
#include <string>

// Class representing all of falling blocks
// Initially constructed as a 4x4 square
//
class Block {
	// Thinking of block as 4x4 square
	// L-Block: 0 0 0 0 T-Block: 0 0 0 0
	//          0 0 0 0          0 0 0 0
	//          1 0 0 0          1 1 1 0
	//          1 1 1 1          0 1 0 0
	std::vector<std::vector<int>> shape;
	// Colour of the block
	std::string colour;
	// Position of block
	public:
	Block(std::vector<std::vector<int>> shape, std::string colour);
	~Block();
};

#endif
