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
		for(int j = start_x; j < start_x + myconsts.MAX_BLOCK_WIDTH; j++) {
			if(shape[i][j-start_x] != 0) {
				sqr = new Square(colour,i,j);
				mysqrs.push_back(sqr);
				model->set_SQUARE(i,j,sqr);
				if(shape[i][j-start_x] == 2) { pivot = sqr; }	
			}		
		}	
	}	
}

// Needs to delete all squares that belong to this block
Block::~Block() {
	for(auto sqr : mysqrs) {
		if(sqr) { delete sqr; }
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
		if(model->get_SQUARE(r,c-1)) { set_SQRS(); return; } // blocked by other sqr	
	}
	// Getting to this point, assume move is valid
	for(auto sqr : mysqrs) {
		sqr->left(); // move left
	}
	set_SQRS();	
}

void Block::move_right() {
	// Check if right move is valid
	int r,c;
	unset_SQRS();
	for(auto sqr : mysqrs) {
		r = sqr->get_ROW();
		c = sqr->get_COL();
		if(c + 1 >= myconsts.WIDTH) { set_SQRS(); return; }
		if(model->get_SQUARE(r,c+1)) { set_SQRS(); return; }
	}
	// Getting here, assume validity
	for(auto sqr : mysqrs) {
		sqr->right(); // move left
	}
	set_SQRS();
}

// quick check if point is on board
bool on_board(int r, int c) {
	if(r < 0) { return false; }
	if(c < 0) { return false; }
	if(r > myconsts.HEIGHT) { return false; }
	if(c > myconsts.WIDTH) { return false; }
	return true;
}

// only clockwise rotation
void Block::rotate() {
	// Base off pivot
	// First check if a rotate is valid
	int r,c;
	unset_SQRS();
	// let r,c be pos of point to rotate, rp,cp pos of pivot

	// projected positions can be found by
	//  applying 90 deg rotation matrix [[0,-1],[1,0]]
	// to vector of [dc,-dr] where dr = r - rp, dc = c - cp

	// and the switch from [dr,dc] to [dc,-dr] to get change in [x,y] 
	// (this is difference between point and pivot)

	// now apply rotation matrix to get vector [dr, dc] which is [x,y] change
	// the subsequent [r,c] change is [-dc,dr]

	// i.e. if a square is at point [r,c], and we wish to find [r',c']
	// of rotated point, we find
	// [dr,dc] = [-dc,dr] for the new point
	// dr = r - rp, dc = c - cp
	// then 
	// -dc = r' - rp, dr = c' - cp
	// r' = rp - dc, c' = cp + dr
	// r' = rp - (c - cp), c' = cp + (r - rp)
	
	// TO GIVE FINAL EQUATION:
	// r' = rp + cp - c, c' = cp - rp + r 
	int rp = pivot->get_ROW();
	int cp = pivot->get_COL();
	
	int newr, newc;
	for(auto sqr : mysqrs) {
		r = sqr->get_ROW();
		c = sqr->get_COL();
		newr = rp + cp - c;
		newc = cp - rp + r;
		if(!on_board(newr, newc)) { set_SQRS(); return; }
		if(model->get_SQUARE(newr, newc)) { set_SQRS(); return; }
	}
	// Get here, assume valid
	for(auto sqr : mysqrs) {
		sqr->rotate_about(rp,cp);
	}
	set_SQRS();
}
