#ifndef SQUARE_H
#define SQUARE_H

#include <string>

// Square objects are wht constitutes the most basic units
// Can be empty of have something
class Square {
	std::string colour;
	int r,c; // my position
	public:
	Square(std::string colour, int r, int c);
	// No heap allocation, default dtor is enough
	// basic getters
	const std::string get_COLOUR();
	int get_ROW();
	int get_COL();
	// increases r by one (dropping the sqr one tile)
	void drop();
	// Step left or right (for player interaction)
	void left();
	void right();
	// rotates about pivot position [r,c]
	void rotate_about(int r, int c);
};

#endif
