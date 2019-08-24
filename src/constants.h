#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <vector>
#include <map>

using namespace std;

// Wrapper class that contains all required constants
class Constants {
	public:
	// Names of blocks, colours associated and shapes associated

	vector<string> BlockNames;
	map<string, string> BlockColours;
	map<string, vector<vector<int>>> BlockShapes;

	// Board width, height (in terms of squares not pixels)

	const int HEIGHT = 60;
	const int WIDTH = 20;

	// Square size

	const int BOX_WIDTH = 10;
	const int BOX_HEIGHT = 10;

	// Max block width and height (max width or height any type of blick may have)

	const int MAX_BLOCK_HEIGHT = 4;
	const int MAX_BLOCK_WIDTH = 4;

	// Score from forming a line

	const int SCORE_FOR_LINE = 10;

	// definitions

	void init_constants();

};
#endif
