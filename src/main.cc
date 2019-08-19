#include "graphics.h"
#include <iostream>

using namespace std;

const int HEIGHT = 1000;
const int WIDTH = 500;

int main() {
	GameDisplay * display = new GameDisplay(HEIGHT, WIDTH);
	display->play();
}
