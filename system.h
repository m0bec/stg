#pragma once
#include "Dxlib.h"
#include "define.h"
#include "structure.h"
#include <math.h>

class systemm {
private:
	base startdisp;
	base startgr;
	base quitgr;
	base arrow1;
	std::array<base, 10> scorenum;
	int arrowy;
	int arrowflag;
	int input_joypad;
	int state;
	int kurame_music;
	unsigned int music_time;
	unsigned int score1;
	unsigned int score2;

public:
	systemm();
	void drawstartmenue();
	void movearrow(int flag);
	void startgraphrun();
	void checkkey();
	void music();
	int pass_state();
	void scoredisp();
};

