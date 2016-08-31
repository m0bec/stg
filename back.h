#pragma once
#include "DxLib.h"

#define start_point 0

class back {
private:
	//座標
	double x, y;
	//グラフィックハンドル
	int gh;

	void draw();

public:
	back();
	void run();
};

