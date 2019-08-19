#ifndef SQUARE_H
#define SQUARE_H

// Square objects are wht constitutes the most basic units
// Can be empty of have something
class Square {
	std::string colour;
	int r,c; // my position
	bool canFall(Game & game); // is there a block below me?
	public:
	Square(std::string colour, int r, int c);
	// No heap allocation, default dtor is enough
	void fall(Game & game);
}

#endif
