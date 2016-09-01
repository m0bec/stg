#include "back.h"

back::back() {
	blueback.graph = LoadGraph("graph/haikei.png");
	blueback.x = blueback.y = start_point;

	blackback.graph = LoadGraph("graph/back.png");
	blackback.x = lowerlimit_joydispwidth;
	blackback.y = lowerlimit_joydispheight;

}

void back::draw() {
	DrawGraph(blueback.x, blueback.y, blueback.graph, false);
	DrawGraph(blackback.x, blackback.y, blackback.graph, false);
}

void back::run() {
	draw();
}
