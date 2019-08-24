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

	int HEIGHT;
	int WIDTH;

	// Square size

	int BOX_WIDTH;
	int BOX_HEIGHT;

	// Max block width and height (max width or height any type of blick may have)

	int MAX_BLOCK_HEIGHT;
	int MAX_BLOCK_WIDTH;

	// Score from forming a line

	int SCORE_FOR_LINE;

	// definitions

	Constants();

};
#endif
