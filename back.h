#pragma once
#include "DxLib.h"
#include "structure.h"
#include "define.h"

#define start_point 0

class back {
private:
	basegraph bluebackleft;
	basegraph bluebackright;
	basegraph bluebackup;
	basegraph bluebackdown;
	basegraph blackback;
	basegraph random03;
	basegraph random03r;
	basegraph random03rc;
	basegraph random03rcr;
	basegraph random14;
	basegraph random08;
	basegraph back1781;
	basegraph back1765;
	int state;
	int drowx;
	int drowy;
	int drowx2;
	int drowy2;
	int drowx3;
	int drowy3;
	

public:
	
	back();
	void firstrun();
	void secondrun();
	int& set_state();
};

