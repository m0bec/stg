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
	random03.graph = LoadGraph("graph/b_random03_.png");
	GetGraphSize(random03.graph, &random03.width, &random03.height);
	random03.x = start_point;
	random03.y = lowerlimit_joydispheight;
	random03r.graph = LoadGraph("graph/rb_Random03_.png");
	GetGraphSize(random03r.graph, &random03r.width, &random03r.height);
	random03r.x = start_point;
	random03r.y = lowerlimit_joydispheight;
	random03rc.graph = LoadGraph("graph/RCB_Random03.png");
	GetGraphSize(random03rc.graph, &random03rc.width, &random03rc.height);
	random03rc.x = start_point;
	random03rc.y = lowerlimit_joydispheight;
	random03rcr.graph = LoadGraph("graph/RCRB_Random03.png");
	GetGraphSize(random03rcr.graph, &random03rcr.width, &random03rcr.height);
	random03rcr.x = start_point;
	random03rcr.y = lowerlimit_joydispheight;
	random14.graph = LoadGraph("graph/B_Random14.png");
	random14.x = start_point;
	random14.y = 0;
	random08.graph = LoadGraph("graph/tb_random08_.png");
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

	
	state = 0;
	drowx = start_point;
	drowy = lowerlimit_joydispheight;
	drowx2 = start_point;
	drowy2 = lowerlimit_joydispheight - random03.height;//‚¤‚¦
}

void back::firstrun() {
	bool flag;
	control &controling = control::getinstance();
	controling.pass_bombflag(&flag);
	if (flag) {
		if (state == 0 || state == 1) {
			DrawGraph(drowx, drowy, random03.graph, false);
			DrawGraph(drowx2, drowy2, random03.graph, false);
			DrawGraph(drowx, drowy, random08.graph, false);
			DrawGraph(drowx2, drowy2, random08.graph, false);
		}
	}
	else {
		if (state == 0 || state == 1) {
			DrawGraph(drowx, drowy, random03.graph, false);
			DrawGraph(drowx2, drowy2, random03.graph, false);
		}
	}

	if (state == 1) {
		drowy += 8;
		drowy2 += 8;

		if (drowy > upperlimit_joydispheight - 10) {
			drowy = drowy2 - random03.height;
		}
		else if (drowy2 > upperlimit_joydispheight - 10) {
			drowy2 = drowy - random03.height;
		}
	}
}

void back::secondrun() {
	DrawGraph(static_cast<int>(bluebackleft.x), static_cast<int>(bluebackleft.y), bluebackleft.graph, false);
	DrawGraph(static_cast<int>(bluebackup.x), static_cast<int>(bluebackup.y), bluebackup.graph, false);

	DrawGraph(static_cast<int>(bluebackdown.x), static_cast<int>(bluebackdown.y), bluebackdown.graph, false);
	DrawGraph(static_cast<int>(bluebackright.x), static_cast<int>(bluebackright.y), bluebackright.graph, false);
}

int& back::set_state() {
	return this->state;
}