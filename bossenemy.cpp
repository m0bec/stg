#include "enemy.h"

bossenemy::bossenemy() {
	graph = LoadGraph("graph/enemy.png");
	GetGraphSize(graph, &width, &height);
	bigredbullet.graph = LoadGraph("graph/ETama1.png");
	GetGraphSize(bigredbullet.graph, &bigredbullet.width, &bigredbullet.height);
	x = bossenemy_startpoint_x - width / 2;
	y = bossenemy_startpoint_y;
	movestate = 0;
	direct_pattern = 0;
}

void bossenemy::getposition(double *centerx, double *centery) {
	*centerx = this->x + this->width / 2;
	*centery = this->y + this->height / 2;
}
void bossenemy::startmove() {
	y += 5;
	if (y > -(height / 3)) {
		movestate = 1;
		count = 0;
	}
	DrawGraph(x, y, graph, true);
}

void bossenemy::roundtrip_move() {
	if (direct_pattern == 0) {
		x += bossenemy_speed1;
	}
	else {
		x -= bossenemy_speed1;
	}

	if (x > upperlimit_joydispwidth - width) {
		x = upperlimit_joydispwidth - width;
		direct_pattern = 1;
	}
	if (x < lowerlimit_joydispwidth) {
		x = lowerlimit_joydispwidth;
		direct_pattern = 0;
	}

	DrawGraph(x, y, graph, true);
}

void bossenemy::move() {
	switch (movestate) {
	case 0:
		startmove();
		break;

	case 1:
		roundtrip_move();
		straightaim_player();
		break;
	}		
}

void bossenemy::run() {
	move();
	count++;
}