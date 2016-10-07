#pragma once
#include "Dxlib.h"
#include "define.h"
#include "structure.h"

class systemm {
private:
	base startdisp;
	base startgr;
	base quitgr;
	base arrow1;
	int arrowy;
	int arrowflag;
	int input_joypad;
	int state;

public:
	systemm();
	void drawstartmenue();
	void movearrow(int flag);
	void startgraphrun();
	void checkkey();
	int pass_state();
};

