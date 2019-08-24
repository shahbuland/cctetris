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
