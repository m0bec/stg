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
	scorenum[0].graph = LoadGraph("graph/number0.png");
	GetGraphSize(scorenum[0].graph, &scorenum[0].width, &scorenum[0].height);
	scorenum[1].graph = LoadGraph("graph/number1.png");
	GetGraphSize(scorenum[1].graph, &scorenum[1].width, &scorenum[1].height);
	scorenum[2].graph = LoadGraph("graph/number2.png");
	GetGraphSize(scorenum[2].graph, &scorenum[2].width, &scorenum[2].height);
	scorenum[3].graph = LoadGraph("graph/number3.png");
	GetGraphSize(scorenum[3].graph, &scorenum[3].width, &scorenum[3].height);
	scorenum[4].graph = LoadGraph("graph/number4.png");
	GetGraphSize(scorenum[4].graph, &scorenum[4].width, &scorenum[4].height);
	scorenum[5].graph = LoadGraph("graph/number5.png");
	GetGraphSize(scorenum[5].graph, &scorenum[5].width, &scorenum[5].height);
	scorenum[6].graph = LoadGraph("graph/number6.png");
	GetGraphSize(scorenum[6].graph, &scorenum[6].width, &scorenum[6].height);
	scorenum[7].graph = LoadGraph("graph/number7.png");
	GetGraphSize(scorenum[7].graph, &scorenum[7].width, &scorenum[7].height);
	scorenum[8].graph = LoadGraph("graph/number8.png");
	GetGraphSize(scorenum[8].graph, &scorenum[8].width, &scorenum[8].height);
	scorenum[9].graph = LoadGraph("graph/number9.png");
	GetGraphSize(scorenum[9].graph, &scorenum[9].width, &scorenum[9].height);


	kurame_music = LoadSoundMem("music/KURAME_NO_BGM.wav");
	arrowy = 512 - startgr.height;
	arrowflag = 0;
	state = 0;
	music_time = 0;
	score1 = 0;
	score2 = 0;
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

void systemm::music() {
	if (music_time % (14*60 + 45) == 0) {
		PlaySoundMem(kurame_music, DX_PLAYTYPE_BACK);
		music_time = 0;
	}
	++music_time;
}

void systemm::startgraphrun() {
	systemm::checkkey();
	systemm::movearrow(arrowflag);
	systemm::drawstartmenue();
	systemm::music();
}

int systemm::pass_state() {
	return state;
}

void systemm::scoredisp(unsigned int point) {
	score1 = point;
	int number;
	int drawx = upperlimit_width - scorenum[0].width - 50;
	for (int i = 0; i < 10; i++) {
		number = score1 % 10;
		score1 = score1 / 10;
		DrawGraph(drawx,50, scorenum[number].graph, true);
		drawx = drawx - scorenum[0].width;
	}
}

void systemm::grasedisp(unsigned int gnum) {
	grazen = gnum;
	int number;
	int drawx = upperlimit_width - scorenum[0].width - 50;
	for (int i = 0; i < 10; i++) {
		number = grazen % 10;
		grazen = grazen / 10;
		DrawGraph(drawx, 200, scorenum[number].graph, true);
		drawx = drawx - scorenum[0].width;
	}
}
