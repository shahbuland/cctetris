#include "constants.h"

// All blocks, Z - Squiggly, S - Square, R - Reverse
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
		    {1,0,0,0},
		    {1,0,0,0}};
BlockShapes["L"] = {{0,0,0,0},
		    {0,0,0,0},
		    {1,0,0,0},
		    {1,1,1,0}};
BlockShapes["RL"] = {{0,0,0,0},
		    {0,0,0,0},
		    {0,0,1,0},
		    {1,1,1,0}};
BlockShapes["Z"] = {{0,0,0,0},
		    {0,0,0,0},
		    {0,1,1,0},
		    {1,1,0,0}};
BlockShapes["RZ"] = {{0,0,0,0},
		    {0,0,0,0},
		    {1,1,0,0},
		    {0,1,1,0}};
BlockShapes["S"] = {{0,0,0,0},
		    {0,0,0,0},
		    {1,1,0,0},
		    {1,1,0,0}};
BlockShapes["T"] = {{0,0,0,0},
		    {0,0,0,0},
		    {0,1,0,0},
		    {1,1,1,0}};
