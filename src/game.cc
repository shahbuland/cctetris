#include "game.h"
#include <stdlib.h>
#include "constants.h"

using namespace std;

bool Game::is_line(int r) {
	for(auto sqr : board[r]) {
		if(sqr == nullptr) { return false; }
	}
	return true;
}

// This is assumed to be called when player makes a line
// I.e. we assume everything shifts down above r no matter what
void Game::shift_down(int r) {
	// Assume 0 < r < HEIGHT
	
	// first delete r-th row
	for(auto sqr : board[r]) {
		delete sqr;
	}
	for(int i = r; i > 0; i--) {
		board[i] = board[i-1]; // row set to above row
	}
	// clear first row (don't actually delete anything inside)
	for(int i = 0; i < WIDTH; i++) {
		board[0][i] = nullptr;
	} 
}

void Game::check_for_lines() {
	for(int i = 0; i < HEIGHT; i++) {
		if(is_line(i)) {
			shift_down(i);
			SCORE += SCORE_FOR_LINE;
		}
	}
}

Game::Game(int height, int width): HEIGHT(height), WIDTH(width) {
	// All board positions init to null ptr
	board.resize(HEIGHT);
	for(auto row : board) {
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
		delete block;
	}
	// To save some effort, blocks will not be responsible
	// for their squares, this is so game can delete for lines
	// delete all squares now
	for(auto row : board) {
		for(auto sqr : row) {
			delete sqr;
		}
	}
}

Block * Game::spawn_block() {
	int n = rand() % 7;
	string blockName = BlockNames[n];
	return new Block(BlockShapes[blockName],
			 BlockColours[blockName]);
}

const int Game::get_HEIGHT() { return HEIGHT; }
const int Game::get_WIDTH() { return WIDTH; }
const int Game::get_SCORE() { return SCORE; }
const Square * Game::get_SQUARE(int r, int c) { return board[r][c]; }
