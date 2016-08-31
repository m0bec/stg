#include "ziki.h"

ziki::ziki() {
	hitflag = false;
	lifeflag = true; 
}

void ziki::pass_load(int loadgraph, int loadwidth, int loadheight) {
	graph = loadgraph;
	width = loadwidth;
	height = loadheight;
}

void ziki::draw() {
	x = 0;
	y = 0;
	DrawGraph(x, y, graph, true);
}

void ziki::run() {
	draw();
}