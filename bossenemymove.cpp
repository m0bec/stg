#include "enemy.h"
#include "control.h"

//‰æ–Ê‚É“ü‚Á‚Ä‚­‚é
void bossenemy::startmove() {
	y += 5;
	if (y > -(height / 3)) {
		movestate = 1;
		count = 0;
	}
	DrawGraph(static_cast<int>(x), static_cast<int>(y), graph, true);
}

//¶‰E‚ÉˆÚ“®
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

//ã’i’†‰›‚ÉˆÚ“®‚µ‚ÄÃŽ~
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

//Ž©‹@‘¤‚ÉˆÚ“®
void bossenemy::approach() {
	double px, py;
	std::uniform_int_distribution<> rand(0, 100);
	control &controling = control::getinstance();
	controling.get_playerposition(&px, &py);
	if (direct_pattern == 0) {
		if (x + width / 2 > px) {
			directx = x - rand(mt);
		}
		else {
			directx = x + rand(mt);
		}

		if (roop_count % 2 == 0) {
			directy = y + rand(mt);
		}
		else {
			directy = y - rand(mt);
		}
		if (directx < lowerlimit_joydispwidth) directx = lowerlimit_joydispwidth;
		if (directx > upperlimit_joydispwidth - width) directx = upperlimit_joydispwidth - width;
		if (directy > 0) directy = 0;
		if (directy < -(height / 3)) directy = -(height / 3);

		memory_xspeed = (directx - x) / (movetime - roop_count);
		memory_yspeed = (directy - y) / (movetime - roop_count);
		if (roop_count < 30)	roop_count += 1;
		memoryx = x;
		memoryy = y;

		lasercount = 0;
		laserbeam1.erase(laserbeam1.begin(), laserbeam1.end());
		direct_pattern = 1;
	}

	if (direct_pattern == 1) {
		if (x == directx && y == directy) {
			direct_pattern = 2;
		}
		memoryx += memory_xspeed;
		memoryy += memory_yspeed;
		if (abs(directx - memoryx) < abs(memory_xspeed) + 1 || abs(directx - memoryx) < memory_xspeed * 2)	memoryx = directx;
		if (abs(directy - memoryy) < abs(memory_yspeed) + 1 || abs(directy - memoryy) < memory_yspeed * 2)	memoryy = directy;
		x = memoryx;
		y = memoryy;
	}
	DrawGraph(static_cast<int>(x), static_cast<int>(y), graph, true);
}

//‚Ü‚Á‚·‚®ˆÚ“®
void bossenemy::straightmove() {
	y += 7+ 100;
	if (y > upperlimit_joydispheight) {
		movestate = 8;
		count = 0;
	}
	DrawGraph(static_cast<int>(x), static_cast<int>(y), graph, true);
}