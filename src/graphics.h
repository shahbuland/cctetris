#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <string>

struct Color {
	int r;
	int g;
	int b;
};

// Display can be thought of as a grid of squares

// Class for game display, uses Xwindows
// Stores game model to be able to send input
// and receive state info
class Game;

class GameDisplay {
	// Xwindows vars
	Display * dis;
	int screen;
	Window win;
	GC gc;
	// My vars
	int height, width;
	Game * model;
	public:
	GameDisplay(int r, int c); // init screen, make model
	~GameDisplay(); // clear screen
	void play(); // play the game, enters event loop
	private:
	void update(); // update screen from model
	// Color related helpers
	unsigned long int get_colors(const char * color);
	// Draws box with color col and [r,c]
	void drawBox(std::string color, int r, int c); 
	// Prints string str at r c
	void printStr(std::string str, int r, int c);
};
