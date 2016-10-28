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
	unsigned int grazen;
	unsigned int gage_color1;
	unsigned int gage_color2;
	unsigned int gage_color3;
	unsigned int gage_color4;

public:
	systemm();
	void drawstartmenue();
	void movearrow(int flag);
	void startgraphrun();
	void checkkey();
	void music();
	int pass_state();
	void scoredisp(unsigned int score);
	void grasedisp(unsigned int gnum);
	void gage(unsigned int stock);
};

