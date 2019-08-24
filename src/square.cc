#include "square.h"

using namespace std;

Square::Square(string colour, int r, int c): colour(colour), r(r), c(c) {}

// Getters

const string Square::get_COLOUR() { return colour; }

int Square::get_ROW() { return r; }
int Square::get_COL() { return c; }

// Note: All moving functions assume validity of move

// Function to drop the block
void Square::drop() { r++; }

void Square::left() { c--; }

void Square::right() { c++; }

// rotate follows same method as in blocks.cc
void Square::rotate_about(int rp, int cp) {
	int newr = rp + cp - c;
	int newc = cp - rp + r;
	r = newr;
	c = newc;
}
