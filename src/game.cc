#include "game.h"
#include <stdlib.h>
#include "constants.h"
#include <iostream>

using namespace std;

extern Constants myconsts;

bool Game::is_line(int r) {
	for(auto sqr : board[r]) {
		if(!sqr) { return false; }
	}
	return true;
}

// This is assumed to be called when player makes a line
// I.e. we assume everything shifts down above r no matter what
void Game::shift_down(int r) {
	// Assume 0 < r < HEIGHT
	
	// first clear r-th row
	for(int j = 0; j < myconsts.WIDTH; j++) {
		board[r][j] = nullptr;
	}
	for(int i = r; i > 0; i--) {
		board[i] = board[i-1]; // row set to above row
	}
	// clear first row (don't actually delete anything inside)
	for(int i = 0; i < myconsts.WIDTH; i++) {
		board[0][i] = nullptr;
	} 
}

void Game::check_for_lines() {
	for(int i = 0; i < HEIGHT; i++) {
		if(is_line(i)) {
			shift_down(i);
			SCORE += myconsts.SCORE_FOR_LINE;
		}
	}
}

Game::Game(int height, int width): HEIGHT(height), WIDTH(width) {
	// All board positions init to null ptr
	board.resize(HEIGHT);
	for(auto & row : board) {
		row.resize(WIDTH);
	}
	SCORE = 0;
	// Spawn the first block
	active_block = spawn_block();
	all_blocks.push_back(active_block);	
}

Game::~Game() {
	// Just delete all blocks
	for(auto block : all_blocks) {
		if(block) { delete block; }
	}
}

Block * Game::spawn_block() {
	cout << "Score: " << SCORE << endl;
	int n = rand() % 7; // which block is used
	int init_x = rand() % (WIDTH - myconsts.MAX_BLOCK_WIDTH);
	string blockName = myconsts.BlockNames[n];
	Block * newblock = new Block(myconsts.BlockShapes[blockName],
			 		 			myconsts.BlockColours[blockName],
					 			init_x,
					 			this);
	
	all_blocks.push_back(newblock);
	return newblock;
}

// Step function

void Game::step(Action a, bool & done) {
	// Before step, if there are new active blocks, spawn one
	// Then we can always make assumption there is an active block
	// Before the rest of this method
	if(!active_block) {
		active_block = spawn_block();
		justSpawned = true;
	}
	switch(a) {
		case Action::NONE: break;
		case Action::ROTATE: active_block->rotate(); break;
		case Action::MOVE_LEFT: active_block->move_left(); break;
		case Action::MOVE_RIGHT: active_block->move_right(); break;
		default: break; // This is in theory never reached
	}
	// No matter action, active block must now fall
	bool did_fall =	active_block->fall();
	if(!did_fall) { // if it couldn't fall, either at bottom or game over
		// check for game over
		if(justSpawned) {
			cout << "Game over!" << endl;
			done = true;
			return;	
		}
		active_block = nullptr;
		check_for_lines(); 
	} else {
		justSpawned = false;
	}
}

// Getters and setters
const int Game::get_HEIGHT() { return HEIGHT; }

const int Game::get_WIDTH() { return WIDTH; }

const int Game::get_SCORE() { return SCORE; }

Square * Game::get_SQUARE(int r, int c) {
	if(!myconsts.on_board(r,c)) { return nullptr; } 
	return board[r][c];
}

void Game::set_SQUARE(int r, int c, Square * sqr) {
	if(!myconsts.on_board(r,c)) { return; }
	board[r][c] = sqr;
}

ostream & operator<<(ostream & out, Game & g) {
	for(auto row : g.board) {
		for(auto tile : row) {
			if(tile) {
			out << "1" << " ";
			}
			else {
			out << "0" << " ";
			}
		}
		out << endl;
	}	
	return out;
}
