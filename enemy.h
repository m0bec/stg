#pragma once
#include "DxLib.h"
#include "define.h"

class bossenemy {
private:
	double x;
	double y;
	int graph;
	int width;
	int height;
	int hp;
	int movestate;

public:
	bossenemy();
	void move();
	void startmove();
	void run();
};