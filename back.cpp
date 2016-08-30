#include "back.h"

back::back() {
	gh = LoadGraph("graph\\haikei.png");
	x = y = start_point;
}

void back::draw() {
	DrawGraph(x, y, gh, false);
}

void back::all() {
	draw();
}
