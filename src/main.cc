#include "graphics.h"
#include "constants.h"
#include <iostream>

using namespace std;

Constants myconsts;

int main() {
	myconsts.init_constants();
	GameDisplay * display = new GameDisplay(myconsts.HEIGHT, myconsts.WIDTH);
	display->play();
	delete display;
}
