#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <vector>
#include <map>

using namespace std;

// Names of blocks, colours associated and shapes associated
string BlockNames[7] = {"I","L","RL","Z","RZ","S","T"};
map<string, string> BlockColours;
map<string, vector<vector<int>>> BlockShapes;

// definitions

void init_constants();

#endif
