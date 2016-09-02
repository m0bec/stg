#include "ziki.h"

ziki::ziki() {
	graph = LoadGraph("graph/ziki1.png");
	GetGraphSize(graph, &width, &height);
	bulletgraph = LoadGraph("graph/ZTama.png");
	GetGraphSize(bulletgraph, &bulletwidth, &bulletheight);
	x = lowerlimit_joydispwidth + (upperlimit_joydispwidth - lowerlimit_joydispwidth)/2- width/2;
	y = ziki_startposition;

	hitrange.graph = LoadGraph("graph/core.png");
	GetGraphSize(hitrange.graph, &hitrange.width, &hitrange.height);
		
	presenceflag = true;
	lifeflag = true; 	
	count = 0;
}

void ziki::getposition(double *centerx, double *centery) {
	*centerx = this->x + this->width / 2;
	*centery = this->y + this->height / 2;
}

double ziki::pass_centerx() { return x + width / 2; }
double ziki::pass_centery() { return y + height / 2; }

void ziki::draw() {
	DrawGraph(static_cast<int>(x), static_cast<int>(y), graph, true);
	DrawGraph(static_cast<int>(x + width / 2 - hitrange.width / 2), static_cast<int>(y + height / 2 - hitrange.height / 2), hitrange.graph, true);
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

void ziki::shot() {
	input_joypad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	
	if (input_joypad & PAD_INPUT_1 && count % 4 == 0) {
		zikibullet.push_back(bullet(x + width/2 - bulletwidth/2, y-bulletheight, true));
	}
	
	auto itr = zikibullet.begin();
	while (itr != zikibullet.end()) {
		itr->y -= zikishot_speed;
		if (itr->y < lowerlimit_joydispheight) {
			itr = zikibullet.erase(itr);
		}
		else {
			DrawGraph(static_cast<int>(itr->x), static_cast<int>(itr->y), bulletgraph, true);
			itr++;
		}
	}
	
	zikibullet.shrink_to_fit();
	
}

void ziki::run() {
	draw();
	move();
	shot();
	count++;
}