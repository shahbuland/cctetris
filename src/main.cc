#include "graphics.h"
#include "constants.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

Constants myconsts;

int main() {
	srand(time(0));
	GameDisplay * display = new GameDisplay(myconsts.HEIGHT, myconsts.WIDTH);
	display->play();
	delete display;
}
