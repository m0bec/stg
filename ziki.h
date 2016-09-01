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
	int input_joypad;
	std::vector<bullet> zikibullet;
	unsigned int count;
	int bulletgraph;
	int bulletwidth;
	int  bulletheight;
	int hitrangegraph;
	base hitrange;
	
public:
	ziki();
	void draw();
	void run();
	void move();
	void shot();
};

