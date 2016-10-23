#include "ziki.h"
#include "control.h"

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
	gameover_flag = false;
	lifepoint = 3;
	count = 0;
	invincibletime_counter = 0;
	sortiecounter = 0;

	hitdist = hit_distance;
}

//弾に当たったらfalse
void ziki::lifecheck(bool checker) {
	if (checker) {
		//lifepoint -= 1;
		if (lifepoint > 0) {
			lifeflag = true;
			presenceflag = false;
		}
		else {
			gameover_flag = true;
		}
	}
}

void ziki::presenceflag_pass(bool *flag) {
	*flag = presenceflag;
}

void ziki::getposition(double *centerx, double *centery) {
	*centerx = this->x +this->width / 2;
	*centery = this->y +this->height / 2;
}

double ziki::pass_hitdist() {
	return hitdist;
}

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

	//画面外に出ない様にする
	if (x < lowerlimit_joydispwidth)	x = lowerlimit_joydispwidth;
	if (x + width > upperlimit_joydispwidth) x = upperlimit_joydispwidth - width;
	if (y < lowerlimit_joydispheight) y = lowerlimit_joydispheight;
	if (y + height > upperlimit_joydispheight) y = upperlimit_joydispheight - height;
}

//再出撃自の挙動
void ziki::resortie() {
	if (sortiecounter == 0) y = 1000;
	if (sortiecounter > 20 && sortiecounter < 41) {
			y -= 5;
	}
	if (sortiecounter > 40) {
		move();
	}

	if (sortiecounter % 6 < 3) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
		DrawGraph(static_cast<int>(x), static_cast<int>(y), graph, TRUE);
		DrawGraph(static_cast<int>(x), static_cast<int>(y), graph, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else {
		DrawGraph(static_cast<int>(x), static_cast<int>(y), graph, true);
	}
}

void ziki::shot() {
	control &controling = control::getinstance();
	double ex, ey;
	int ewidth, eheight;
	input_joypad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	controling.get_enemyposition(&ex, &ey, &ewidth, &eheight);

	if (input_joypad & PAD_INPUT_1 && count % 4 == 0) {
		zikibullet.push_back(bullet(x + width/2 - bulletwidth/2, y-bulletheight, true));
	}
	
	auto itr = zikibullet.begin();
	while (itr != zikibullet.end()) {
		itr->y -= zikishot_speed;
		if (itr->y < lowerlimit_joydispheight) {
			itr = zikibullet.erase(itr);
		}
		else if (itr->x + bulletwidth > ex && itr->x < ex + ewidth && itr->y + shot_margin < ey + eheight && itr->y + bulletheight > ey) {
			itr = zikibullet.erase(itr);
			controling.calculation_enemyhp();
			point += 5;
		}
		else {
			DrawGraph(static_cast<int>(itr->x), static_cast<int>(itr->y), bulletgraph, true);
			itr++;
		}
	}
}

unsigned int ziki::pass_point() {
	return point;
}

//復活してからの時間を管理
void ziki::sortiecounter_controler() {
	sortiecounter++;

	if (sortiecounter == 200) {
		presenceflag = true;
		sortiecounter = 0;
	}
}

void ziki::run() {
	if (presenceflag) {
		move();
		draw();
	}
	else {
		resortie();
		sortiecounter_controler();
	}
	draw();
	shot();
	count++;
}