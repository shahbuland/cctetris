#include "graphics.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <unistd.h>

using namespace std;

// All boxes should have fixed size
const int BOX_WIDTH = 50;
const int BOX_HEIGHT = 50;

GameDisplay::GameDisplay(int r, int c): height(r), width(c) {
	
	// Init display

	unsigned long black,white;

	dis=XOpenDisplay((char *)0);
	screen=DefaultScreen(dis);
	black=BlackPixel(dis,screen),	/* get color black */
	white=WhitePixel(dis, screen);  /* get color white */

	win=XCreateSimpleWindow(dis,DefaultRootWindow(dis),0,0,	
				c, r, 5, white, black);

	XSetStandardProperties(dis,win,"Tetris","Tetris",None,NULL,0,NULL);

	XSelectInput(dis, win, ExposureMask|ButtonPressMask|KeyPressMask);

	gc=XCreateGC(dis, win, 0,0);        

	XSetBackground(dis,gc,white);
	XSetForeground(dis,gc,black);

	XClearWindow(dis, win);
	XMapRaised(dis, win);
}

GameDisplay::~GameDisplay() {
	XFreeGC(dis, gc);
	XDestroyWindow(dis, win);
	XCloseDisplay(dis);
}

void GameDisplay::play() { 
	XEvent event;
	KeySym key;
	char text[255];
	int x = 50;
	bool done = false;
	while(1) {
		if(done) { break; }
		XNextEvent(dis, &event);
		if(event.type==Expose && event.xexpose.count==0) {
			update();
		}
		if(event.type==KeyPress&&XLookupString(&event.xkey,text,255,&key,0)==1) {
			switch(text[0]) {
				case 'q': done = true; break;
				default: break;
			}
		}
		if(event.type==ButtonPress) {
			cout << "You pressed a button at" << endl;
		}
		XClearWindow(dis, win);
		drawBox("red",x,50); x+=BOX_HEIGHT;
		usleep(100000);
	}
}

void GameDisplay::update() {
	// Looks through game model
	return;
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
	XFillRectangle(dis, win, gc, c, r, BOX_WIDTH, BOX_HEIGHT);
	
}

void GameDisplay::printStr(string str, int r, int c) {
	XDrawString(dis, win, gc, r, c, str.c_str(), str.length());
}
