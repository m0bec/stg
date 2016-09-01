#include "enemy.h"

bossenemy::bossenemy() {
	graph = LoadGraph("graph/enemy.png");
	GetGraphSize(graph, &width, &height);
	x = bossenemy_startpoint_x - width / 2;
	y = bossenemy_startpoint_y;
	movestate = 0;
}

void bossenemy::startmove() {
	y += 5;
	if (y > -(height / 3))	movestate = 1;
	DrawGraph(x, y, graph, true);
}

void bossenemy::move() {
	if(movestate == 0)
		startmove();
	
}

void bossenemy::run() {
	move();
}