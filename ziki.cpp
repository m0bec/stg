#include "ziki.h"

ziki::ziki() {
	x = 0;
	y = 0;
	presenceflag = true;
	lifeflag = true; 	
	count = 0;
}

void ziki::pass_load(int loadgraph, int loadwidth, int loadheight) {
	graph = loadgraph;
	width = loadwidth;
	height = loadheight;
}

void ziki::draw() {
	DrawGraph(static_cast<int>(x), static_cast<int>(y), graph, true);
}

void ziki::move() {
	input_joypad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	if (input_joypad & PAD_INPUT_UP) {
		if (input_joypad & PAD_INPUT_2) {
			y -= slowmove;
		}
		else {
			y -= normalmove;
		}
	}
	if (input_joypad & PAD_INPUT_DOWN) {
		if (input_joypad & PAD_INPUT_2) {
			y += slowmove;
		}
		else {
			y += normalmove;
		}
	}
	if (input_joypad & PAD_INPUT_LEFT) {
		if (input_joypad & PAD_INPUT_2) {
			x -= slowmove;
		}
		else {
			x -= normalmove;
		}
	}
	if (input_joypad & PAD_INPUT_RIGHT) {
		if (input_joypad & PAD_INPUT_2) {
			x += slowmove;
		}
		else {
			x += normalmove;
		}
	}

	//âÊñ äOÇ…èoÇ»Ç¢ólÇ…Ç∑ÇÈ
	if (x < lowerlimit_joydispwidth)	x = lowerlimit_joydispwidth;
	if (x + width > upperlimit_joydispwidth) x = upperlimit_joydispwidth - width;
	if (y < lowerlimit_joydispheight) y = lowerlimit_joydispheight;
	if (y + height > upperlimit_joydispheight) y = upperlimit_joydispheight - height;
}

void ziki::shot(int bulletheight, int bulletgraph) {
	input_joypad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (input_joypad & PAD_INPUT_1 && count % 4 == 0) {
		zikibullet.push_back(bullet(x, y-bulletheight, true));
	}
	
	auto itr = zikibullet.begin();
	while (itr != zikibullet.end()) {
		itr->y -= zikishot_speed;
		if (itr->y < lowerlimit_joydispheight) {
			itr = zikibullet.erase(itr);
		}
		else {
			DrawGraph(itr->x, itr->y, bulletgraph, true);
			++itr;
		}
	}
	
	zikibullet.shrink_to_fit();
	
}

void ziki::run(int bulletheight, int bulletgraph) {
	draw();
	move();
	shot(bulletheight, bulletgraph);
	count++;
}