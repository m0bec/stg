#pragma once

#include "Dxlib.h"
#include "load.h"
#include "define.h"

#define slowmove 3
#define normalmove 5

class ziki {
private:
	int graph;
	int width;
	int height;
	double x;
	double y;
	//���@����ʂɑ��݂��Ă��邩�i�e�ɂ������Ă��Ȃ�&&�o�����[�V�������łȂ��j
	bool presenceflag;
	bool lifeflag;
	int lifepoint;
	int xcenter;
	int ycenter;
	int range;
	int input_joypad;

public:
	ziki();
	void pass_load(int loadgraph, int loadwidth, int loadheight);
	void draw();
	void run();
	void move();
};

