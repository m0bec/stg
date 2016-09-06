#include "enemy.h"

//��ʂɓ����Ă���
void bossenemy::startmove() {
	y += 5;
	if (y > -(height / 3)) {
		movestate = 1;
		count = 0;
	}
	DrawGraph(static_cast<int>(x), static_cast<int>(y), graph, true);
}

//���E�Ɉړ�
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

	DrawGraph(static_cast<int>(x), static_cast<int>(y), graph, true);
}

//��i�����Ɉړ����ĐÎ~
void bossenemy::goto_center() {
	if ((x - lowerlimit_joydispwidth + width/2) - (upperlimit_joydispwidth - lowerlimit_joydispwidth) / 2 > bossenemy_speed2+1) {
		x -= bossenemy_speed2;
	}
	else if ((x - lowerlimit_joydispwidth + width / 2) - (upperlimit_joydispwidth - lowerlimit_joydispwidth) / 2 < -(bossenemy_speed2+1)) {
		x += bossenemy_speed2;
	}
	else {
		x = (upperlimit_joydispwidth - lowerlimit_joydispwidth) / 2 + lowerlimit_joydispwidth - width / 2;
	}

	if (y + height / 3 > bossenemy_speed2 + 1) {
		y -= bossenemy_speed2;
	}
	else if (y + height / 3 < -(bossenemy_speed2+1)) {
		y += bossenemy_speed2;
	}
	else {
		y = -(height) / 3;
	}

	DrawGraph(static_cast<int>(x), static_cast<int>(y), graph, true);

	if (x == (upperlimit_joydispwidth - lowerlimit_joydispwidth) / 2 + lowerlimit_joydispwidth - width / 2 && y == -(height / 3)) {
		movestate = 3;
	}
}