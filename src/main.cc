#include "graphics.h"
#include "constants.h"
#include <iostream>

using namespace std;

const int HEIGHT = 1000;
const int WIDTH = 500;

int main() {
	init_constants();
	GameDisplay * display = new GameDisplay(HEIGHT, WIDTH);
	display->play();
}
