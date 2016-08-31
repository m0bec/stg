#pragma once

#include "Dxlib.h"
#include "load.h"

class ziki {
private:
	int graph;
	int width;
	int height;
	double x;
	double y;
	bool hitflag;
	bool lifeflag;
	int lifepoint;
	int xcenter;
	int ycenter;
	int range;

public:
	ziki();
	void pass_load(int loadgraph, int loadwidth, int loadheight);
};

