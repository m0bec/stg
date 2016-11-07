#include "back.h"
#include "control.h"

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
	random03.graph = LoadGraph("graph/B_Random03.png");
	GetGraphSize(random03.graph, &random03.width, &random03.height);
	random03.x = start_point;
	random03.y = lowerlimit_joydispheight;
	random03r.graph = LoadGraph("graph/RB_Random03.png");
	GetGraphSize(random03r.graph, &random03r.width, &random03r.height);
	random03r.x = start_point;
	random03r.y = lowerlimit_joydispheight;
	random14.graph = LoadGraph("graph/B_Random14.png");
	random14.x = start_point;
	random14.y = 0;
	random08.graph = LoadGraph("graph/B_Random08.png");
	random08.x = start_point;
	random08.y = 0;
	back1781.graph = LoadGraph("graph/17_8_1.png");
	back1781.x = start_point;
	back1781.y = 0;
	back1765.graph = LoadGraph("graph/17_6_5.png");
	back1765.x = start_point;
	back1765.y = lowerlimit_joydispheight;

	blackback.graph = LoadGraph("graph/back.png");
	blackback.x = lowerlimit_joydispwidth;
	blackback.y = lowerlimit_joydispheight;

	

}

void back::firstrun() {
	bool flag;
	control &controling = control::getinstance();
	controling.pass_bombflag(&flag);
	if (flag) {

	}
	else {
		//DrawGraph(blackback.x, blackback.y, blackback.graph, false);
		DrawGraph(random03.x, random03.y, random03.graph, false);
		DrawGraph(random03r.x, random03.y + random03r.height, random03r.graph, false);
	}
}

void back::secondrun() {
	DrawGraph(static_cast<int>(bluebackleft.x), static_cast<int>(bluebackleft.y), bluebackleft.graph, false);
	DrawGraph(static_cast<int>(bluebackup.x), static_cast<int>(bluebackup.y), bluebackup.graph, false);

	DrawGraph(static_cast<int>(bluebackdown.x), static_cast<int>(bluebackdown.y), bluebackdown.graph, false);
	DrawGraph(static_cast<int>(bluebackright.x), static_cast<int>(bluebackright.y), bluebackright.graph, false);
}
