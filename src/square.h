#ifndef SQUARE_H
#define SQUARE_H

// Square objects are wht constitutes the most basic units
// Can be empty of have something
class Square {
	std::string colour;
	int r,c; // my position
	public:
	Square(std::string colour, int r, int c);
	~Square();
	// No heap allocation, default dtor is enough
	const std::string get_COLOUR();
};

#endif
