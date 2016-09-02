#pragma once
#include "DxLib.h"
#include "define.h"
#include "structure.h"
#include <vector>
#include <math.h>

class bossenemy {
private:
	double x;
	double y;
	int graph;
	int width;
	int height;
	int hp;
	int movestate;
	int direct_pattern;
	unsigned int count;
	base bigredbullet;
	std::vector<enemybullet> enemybullet1;
	

public:
	bossenemy();
	void getposition(double *cebterx, double *centery);
	void move();
	void startmove();
	void straightaim_player();
	void lavishhandout_shot();
	void roundtrip_move();
	void run();
};