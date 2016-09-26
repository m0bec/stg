#pragma once

#include "Dxlib.h"
#include "load.h"
#include "define.h"
#include <list>
#include "structure.h"

#define slowmove 3
#define normalmove 5

class ziki {
private:
	int graph;
	int width;
	int height;
	double x;
	double y;
	//自機が画面に存在しているか（弾にあたっていない&&出撃モーション中でない）
	bool presenceflag;
	//残機に関するフラグ
	bool lifeflag;
	int lifepoint;
	int input_joypad;
	std::list<bullet> zikibullet;
	unsigned int invincibletime_counter;
	unsigned int sortiecounter;
	unsigned int count;
	int bulletgraph;
	int bulletwidth;
	int  bulletheight;
	int hitrangegraph;
	base hitrange;
	double hitdist;
	bool gameover_flag;
	
public:
	ziki();
	void getposition(double *centerx, double *centery);
	void lifecheck(bool cheacker);
	void sortiecounter_controler();
	void resortie();
	void presenceflag_pass(bool *flag);
	double pass_hitdist();
	void draw();
	void run();
	void move();
	void shot();
};

