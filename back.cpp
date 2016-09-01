#include "back.h"

back::back() {
	bluebackleft.graph = LoadGraph("graph/haikeiL.png");
	bluebackleft.x = bluebackleft.y = start_point;
	bluebackup.graph = LoadGraph("graph/haikeiup.png");
	bluebackup.x = bluebackup.y = start_point;
	bluebackdown.graph = LoadGraph("graph/haikeidown.png");
	bluebackdown.x = start_point;
	bluebackdown.y = upperlimit_joydispheight;
	bluebackright.graph = LoadGraph("graph/haikeiR.png");
	bluebackright.x = upperlimit_joydispwidth;
	bluebackright.y = start_point;

	blackback.graph = LoadGraph("graph/back.png");
	blackback.x = lowerlimit_joydispwidth;
	blackback.y = lowerlimit_joydispheight;

}

void back::firstrun() {
	DrawGraph(blackback.x, blackback.y, blackback.graph, false);
}

void back::secondrun() {
	DrawGraph(bluebackleft.x, bluebackleft.y, bluebackleft.graph, false);
	DrawGraph(bluebackup.x, bluebackup.y, bluebackup.graph, false);

	DrawGraph(bluebackdown.x, bluebackdown.y, bluebackdown.graph, false);
	DrawGraph(bluebackright.x, bluebackright.y, bluebackright.graph, false);
}
