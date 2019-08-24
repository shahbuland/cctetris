#include "constants.h"

Constants::Constants() {
	// Int constants
	HEIGHT = 80;
	WIDTH = 25;
	BOX_WIDTH = 10;
	BOX_HEIGHT = 10;
	MAX_BLOCK_HEIGHT = 4;
	MAX_BLOCK_WIDTH = 4;
	SCORE_FOR_LINE = 10;
		
	BlockNames = {"I","L","RL","Z","RZ","S","T"};
	// Colours
	BlockColours["I"] = "Cyan";
	BlockColours["L"] = "Dark Blue";
	BlockColours["RL"] = "Dark Orange";
	BlockColours["Z"] = "Chartreuse";
	BlockColours["RZ"] = "Crimson";
	BlockColours["S"] = "Gold";
	BlockColours["T"] = "Dark Violet";

	// Shapes
	BlockShapes["I"] = {{1,0,0,0},
			    {1,0,0,0},
			    {2,0,0,0},
			    {1,0,0,0}};
	BlockShapes["L"] = {{0,0,0,0},
			    {0,0,0,0},
			    {1,0,0,0},
			    {1,2,1,0}};
	BlockShapes["RL"] = {{0,0,0,0},
			    {0,0,0,0},
			    {0,0,1,0},
			    {1,2,1,0}};
	BlockShapes["Z"] = {{0,0,0,0},
			    {0,0,0,0},
			    {0,2,1,0},
			    {1,1,0,0}};
	BlockShapes["RZ"] = {{0,0,0,0},
			    {0,0,0,0},
			    {1,2,0,0},
			    {0,1,1,0}};
	BlockShapes["S"] = {{0,0,0,0},
			    {0,0,0,0},
			    {1,2,0,0},
			    {1,1,0,0}};
	BlockShapes["T"] = {{0,0,0,0},
			    {0,0,0,0},
			    {0,1,0,0},
			    {1,2,1,0}};
}
