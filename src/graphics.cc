#include "graphics.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include "game.h"
#include "constants.h"

using namespace std;

extern Constants myconsts;

GameDisplay::GameDisplay(int r, int c): height(r*myconsts.BOX_HEIGHT), width(c*myconsts.BOX_WIDTH) {
	
	// Init display

	unsigned long black,white;

	dis=XOpenDisplay((char *)0);
	if(!dis) {
		cerr << "Error opening display (most likely X11 not setup)" << endl;
		exit(1);	
	}
	screen=DefaultScreen(dis);
	black=BlackPixel(dis,screen),	/* get color black */
	white=WhitePixel(dis, screen);  /* get color white */

	win=XCreateSimpleWindow(dis,DefaultRootWindow(dis),0,0,	
				width, height, 5, white, black);

	XSetStandardProperties(dis,win,"Tetris","Tetris",None,NULL,0,NULL);

	XSelectInput(dis, win, ExposureMask|ButtonPressMask|KeyPressMask);

	gc=XCreateGC(dis, win, 0,0);        

	XSetBackground(dis,gc,white);
	XSetForeground(dis,gc,black);

	XClearWindow(dis, win);
	XMapRaised(dis, win);

	model = new Game(r,c);	
}

GameDisplay::~GameDisplay() {
	XFreeGC(dis, gc);
	XDestroyWindow(dis, win);
	XCloseDisplay(dis);
	if(model) { delete model; }
}

void GameDisplay::play() { 
	XEvent event;
	KeySym key;
	char text[255];
	bool done = false;
	Action a;
	while(!done) {
		update();
		a = Action::NONE;
		XNextEvent(dis, &event);
		if(event.type==Expose && event.xexpose.count==0) {
		}
		if(event.type==KeyPress&&XLookupString(&event.xkey,text,255,&key,0)==1) {
			switch(text[0]) {
				case 'q': done = true; break;
				case 'a': a = Action::MOVE_LEFT; break;
				case 'd': a = Action::MOVE_RIGHT; break;
				case 'w': a = Action::ROTATE; break;
				case 's': break;
				default: break;
			}
		}
		if(event.type==ButtonPress) {
		}
		model->step(a, done);
		XClearWindow(dis, win);
	}
	delete model;
}

void GameDisplay::update() {
	// iterate through board
	int rows = model->get_HEIGHT();
	int cols = model->get_WIDTH();
	// y-pos will be i*BOX_HEIGHT
	// x-pos will be i*BOX_WIDTH
	Square * sqr;
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			sqr = model->get_SQUARE(i,j);
			if(sqr) {
				drawBox(sqr->get_COLOUR(), i*myconsts.BOX_HEIGHT, j*myconsts.BOX_WIDTH);
			}
		}
	}	
}

// Some funcs for colours
unsigned long int GameDisplay::get_colors(const char * color) {
	XColor tmp;
	XParseColor(dis, DefaultColormap(dis, screen), color, &tmp);
	XAllocColor(dis, DefaultColormap(dis, screen), &tmp);
	return tmp.pixel;
}

void GameDisplay::drawBox(string colour, int r, int c) {
	XSetForeground(dis, gc, get_colors(colour.c_str()));
	XFillRectangle(dis, win, gc, c, r, myconsts.BOX_WIDTH, myconsts.BOX_HEIGHT);
	XSetForeground(dis,gc, get_colors("Black"));
	XDrawRectangle(dis, win, gc, c, r, myconsts.BOX_WIDTH, myconsts.BOX_HEIGHT);	
}

void GameDisplay::printStr(string str, int r, int c) {
	XDrawString(dis, win, gc, r, c, str.c_str(), str.length());
}
