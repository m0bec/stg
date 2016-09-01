#pragma once

#include "Dxlib.h"
#include "load.h"
#include "define.h"
#include <vector>
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
	//���@����ʂɑ��݂��Ă��邩�i�e�ɂ������Ă��Ȃ�&&�o�����[�V�������łȂ��j
	bool presenceflag;
	//�c�@�Ɋւ���t���O
	bool lifeflag;
	int lifepoint;
	int xcenter;
	int ycenter;
	int range;
	int input_joypad;
	std::vector<bullet> zikibullet;
	int count;

public:
	ziki();
	void pass_load(int loadgraph, int loadwidth, int loadheight);
	void draw();
	void run(int bulletheight, int bulletgraph);
	void move();
	void shot(int bulletheight, int bulletgraph);
};

