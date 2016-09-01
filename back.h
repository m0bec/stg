#pragma once
#include "DxLib.h"
#include "structure.h"
#include "define.h"

#define start_point 0

class back {
private:
	basegraph blueback;
	basegraph blackback;

public:
	back();
	void draw();
	void run();
};

