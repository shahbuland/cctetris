#include "blocks.h"
#include "game.h"
#include "constants.h"
#include <iostream>

using namespace std;

extern Constants myconsts;

Block::Block(vector<vector<int>> shape, string colour,
			 int start_x, Game * model): shape(shape),
			 colour(colour), model(model) {
	Square * sqr = nullptr; // var to store current added sqr
	// Outer loop is rows, we start creating the new block at row 0
	for(int i = 0; i < myconsts.MAX_BLOCK_HEIGHT; i++) {
		// Inner loop is columns, we start at start_x
		for(int j = 0; j < myconsts.MAX_BLOCK_WIDTH; j++) {
			if(shape[i][j] == 1) {
				sqr = new Square(colour,i,j);
				mysqrs.push_back(sqr);
				model->set_SQUARE(i,j,sqr);
			}		
		}	
	}	
}

// Needs to delete all squares that belong to this block
Block::~Block() {
	for(auto sqr : mysqrs) {
		delete sqr;
	}
}

// Helper to set squares to board in model
void Block::set_SQRS() {
	int r, c;
	for(auto sqr : mysqrs) {
		r = sqr->get_ROW();
		c = sqr->get_COL();
		model->set_SQUARE(r,c,sqr);
	}
}

// Helper to unset squares on board in model
void Block::unset_SQRS() {
	int r, c;
	for(auto sqr : mysqrs) {
		r = sqr->get_ROW();
		c = sqr->get_COL();
		model->set_SQUARE(r,c,nullptr);
	}
}

bool Block::fall() {
	// First we must make sure that all blocks can fall
	// If any is obstructed, we will just return false,
	// Otherwise move everything down and return true
	int r,c;
	// First nullify all my squares so we aren't accidentally checking for self collision
	unset_SQRS();
	for(auto sqr : mysqrs) {
		r = sqr->get_ROW();
		c = sqr->get_COL();
		// Firstly, if its already at the bottom, it obviously can't fall
		if(r == myconsts.HEIGHT-1) { set_SQRS(); return false; }	
		// We will check by checking next row down
		// If the tile below is empty (nullptr) we are good,
		// otherwise just return false and stop
		// i.e. if next square NOT nullptr, return false
		if(model->get_SQUARE(r+1,c)) { set_SQRS(); return false; }
		// Past this point, means this specific sqr can fall, 
		// Now iterate to the next one
	}
	// At this point, all squares can fall, so lets make them fall then
	// return true
	for(auto sqr : mysqrs) {
		sqr->drop(); // increase r on sqr by 1
		model->set_SQUARE(sqr->get_ROW(),sqr->get_COL(),sqr); // update proper tile on game to sqr
	}	

	return true;
}

string Block::get_COLOUR() { return colour; }


// Player interactions

// NOTE: invalid moves do nothing

void Block::move_left() {
	// We have to check if  moving left is valid
	int r,c;
	unset_SQRS();
	for(auto sqr : mysqrs) {
		r = sqr->get_ROW();
		c = sqr->get_COL();
		if(c - 1 < 0) { set_SQRS(); return; } // in bounds
		if(model->get_SQUARE(c-1,r)) { set_SQRS(); return; } // blocked by other sqr	
	}
	// Getting to this point, assume move is valid
	for(auto sqr : mysqrs) {
		sqr->left(); // move left
		model->set_SQUARE(sqr->get_ROW(),sqr->get_COL(),sqr); // set on left
	}
	
}

void Block::move_right() {
	// Check if right move is valid
	int r,c;
	unset_SQRS();
	for(auto sqr : mysqrs) {
		r = sqr->get_ROW();
		c = sqr->get_COL();
		if(c + 1 >= myconsts.WIDTH) { set_SQRS(); return; }
		if(model->get_SQUARE(c+1,r)) { set_SQRS(); return; }
	}
	// Getting here, assume validity
	for(auto sqr : mysqrs) {
		sqr->right(); // move left
		model->set_SQUARE(sqr->get_ROW(),sqr->get_COL(),sqr); // set on left
	}
}

void Block::rotate() {
	// Check if rotate valid
}
