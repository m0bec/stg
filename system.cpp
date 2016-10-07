#include "system.h"

systemm::systemm() {
	startdisp.graph = LoadGraph("graph/startdisp.png");
	GetGraphSize(startdisp.graph, &startdisp.width, &startdisp.height);
	startgr.graph = LoadGraph("graph/selectstart.png");
	GetGraphSize(startgr.graph, &startgr.width, &startgr.height);
	quitgr.graph = LoadGraph("graph/escape.png");
	GetGraphSize(quitgr.graph, &quitgr.width, &quitgr.width);
	arrow1.graph = LoadGraph("graph/yazi.png");
	GetGraphSize(arrow1.graph, &arrow1.width, &arrow1.height);

	arrowy = 512 - startgr.height;
	state = 0;
}

void systemm::drawstartmenue() {
	DrawGraph(0, 0, startdisp.graph, false);
	DrawGraph(500, 512 - startgr.height, startgr.graph, true);
	DrawGraph(500, 512, quitgr.graph, true);
	DrawGraph(500 - arrow1.width, arrowy, arrow1.graph, true);
}

void systemm::movearrow(int arrowflag) {
	switch (arrowflag) {
	case 0:
		arrowy = 512 - startgr.height;
		break;
	case 1:
		arrowy = 512;
		break;
	}
}

void systemm::checkkey() {
	input_joypad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (input_joypad & PAD_INPUT_UP)	arrowflag = 0;
	if (input_joypad & PAD_INPUT_DOWN)	arrowflag = 1;
	if (input_joypad & PAD_INPUT_1) {
		if (arrowflag == 0) {
			state = 1;
		}
		else if(arrowflag = 1){
			state = 2;
		}
	}
}

void systemm::startgraphrun() {
	systemm::checkkey();
	systemm::movearrow(arrowflag);
	systemm::drawstartmenue();
}

int systemm::pass_state() {
	return state;
}