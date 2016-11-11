#include "ziki.h"
#include "control.h"

ziki::ziki() {
	graph = LoadGraph("graph/ziki1.png");
	GetGraphSize(graph, &width, &height);
	bulletgraph = LoadGraph("graph/ZTama.png");
	GetGraphSize(bulletgraph, &bulletwidth, &bulletheight);
	bgraph = LoadGraph("graph/ziki1_.png");
	x = lowerlimit_joydispwidth + (upperlimit_joydispwidth - lowerlimit_joydispwidth)/2- width/2;
	y = ziki_startposition;

	hitrange.graph = LoadGraph("graph/core.png");
	GetGraphSize(hitrange.graph, &hitrange.width, &hitrange.height);
		
	presenceflag = true;
	lifeflag = true; 	
	gameover_flag = false;
	lifepoint = 10;
	count = 0;
	invincibletime_counter = 0;
	sortiecounter = 0;
	shotpoint = 0;
	grazepoint = 0;
	grase_count = 0;
	graze_stock = 0;
	bomb_count = 0;
	bomb_flag = false;
	
	zbullet_erase_sound = LoadSoundMem("music/se_zshot_erase.ogg");
	ChangeVolumeSoundMem(255 * 50 / 100, zbullet_erase_sound);
	finish_charge_sound = LoadSoundMem("music/se_finish_charge.ogg");
	invalid_sound = LoadSoundMem("music/se_invalid.ogg");
	grazestock_sound = LoadSoundMem("music/se_grazestock.ogg");
	ChangeVolumeSoundMem(255 * 70 / 100, grazestock_sound);

	hitdist = hit_distance;
	graze_range = graze_distance;

	set_explosion_gr();
	effects.flag = false;
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

double ziki::pass_grazedist() {
	return graze_range;
}

unsigned int ziki::pass_grazestock() {
	return graze_stock;
}

void ziki::draw() {
	if (!bomb_flag) {
		DrawGraph(static_cast<int>(x), static_cast<int>(y), graph, true);
		DrawGraph(static_cast<int>(x + width / 2 - hitrange.width / 2), static_cast<int>(y + height / 2 - hitrange.height / 2), hitrange.graph, true);
	}
	else {
		DrawGraph(static_cast<int>(x), static_cast<int>(y), bgraph, true);
		DrawGraph(static_cast<int>(x + width / 2 - hitrange.width / 2), static_cast<int>(y + height / 2 - hitrange.height / 2), hitrange.graph, true);
	}
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
	bool flag = true;
	
	input_joypad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	controling.get_enemyposition(&ex, &ey, &ewidth, &eheight);
	
	if (input_joypad & PAD_INPUT_1 && count % 4 == 0) {
		zikibullet.push_back(bullet(x + width/2 - bulletwidth/2, y-bulletheight, true));
	}
	auto itr = zikibullet.begin();
	
	auto eitr = controling.boss->mobenemy.begin();
	while (itr != zikibullet.end()) {
		flag = true;
		itr->y -= zikishot_speed;
		eitr = controling.boss->mobenemy.begin();
		if (controling.boss->mobenemy.size() != 0) {
			while (eitr != controling.boss->mobenemy.end()) {
				if (itr->y < upperlimit_joydispheight || itr->y > lowerlimit_joydispheight - 10
					|| itr->x < upperlimit_joydispwidth || itr->x > lowerlimit_joydispwidth - 10) {
					if (itr->x + bulletwidth > eitr->x && itr->x < eitr->x + eitr->width && itr->y < eitr->y + eitr->height && itr->y + bulletheight > eitr->y) {
						PlaySoundMem(zbullet_erase_sound, DX_PLAYTYPE_BACK);
						flag = false;
						eitr->hp -= 1;
						shotpoint += 3;
						if (flag != true)	break;
					}
					eitr++;
				}
				else {
					eitr++;
				}
			}
		
		}
		if (flag) {
			if (itr->y < lowerlimit_joydispheight) {
				itr = zikibullet.erase(itr);
			}
			else if (itr->x + bulletwidth > ex && itr->x < ex + ewidth && itr->y + shot_margin < ey + eheight && itr->y + bulletheight > ey) {
				PlaySoundMem(zbullet_erase_sound, DX_PLAYTYPE_BACK);
				itr = zikibullet.erase(itr);
				controling.calculation_enemyhp();
				shotpoint += 5;
			}
			else {
				DrawGraph(static_cast<int>(itr->x), static_cast<int>(itr->y), bulletgraph, true);
				itr++;
			}
		}
		else {
			itr = zikibullet.erase(itr);
		}
	}
}

void ziki::graze_counter() {
	++grase_count;
	++graze_stock;
	grazepoint += 3;
	PlaySoundMem(grazestock_sound, DX_PLAYTYPE_BACK);
	if (graze_stock == 100) {
		PlaySoundMem(finish_charge_sound, DX_PLAYTYPE_BACK);
	}
}

unsigned int ziki::pass_point() {
	return (shotpoint + grazepoint);
}

unsigned int ziki::pass_grazenum() {
	return grase_count;
}

int ziki::pass_zanki() {
	return lifepoint;
}

//復活してからの時間を管理
void ziki::sortiecounter_controler() {
	sortiecounter++;

	if (sortiecounter == 200) {
		presenceflag = true;
		sortiecounter = 0;
	}
}

void ziki::bomb_start() {
	if (graze_stock >= 100) {
		if (input_joypad & PAD_INPUT_5) {
			bomb_flag = true;
			graze_stock = 0;
			bomb_count = 200;
			PlaySoundMem(invalid_sound, DX_PLAYTYPE_BACK);
		}
	}
}

bool ziki::bomb() {
	return bomb_flag;
}

void ziki::invalid() {
	if (bomb_count > 0) {
		bomb_flag = true;
		bomb_count--;
	}
	else {
		bomb_flag = false;
	}
}

int ziki::life_damage() {
	lifepoint -= 1;
	if (lifepoint < 0) {
		return -1;
	}
	else {
		effects.x = x + width / 2 - explosion_effect_width / 2;
		effects.y = y + height / 2 - explosion_effect_height / 2;
		effects.flag = true;
		return 0;
	}
}

void ziki::set_explosion_gr() {
	explosion_gr[0] = LoadGraph("graph/exp_00000.png");
	explosion_gr[1] = LoadGraph("graph/exp_00001.png");
	explosion_gr[2] = LoadGraph("graph/exp_00002.png");
	explosion_gr[3] = LoadGraph("graph/exp_00003.png");
	explosion_gr[4] = LoadGraph("graph/exp_00004.png");
	explosion_gr[5] = LoadGraph("graph/exp_00005.png");
	explosion_gr[6] = LoadGraph("graph/exp_00006.png");
	explosion_gr[7] = LoadGraph("graph/exp_00007.png");
	explosion_gr[8] = LoadGraph("graph/exp_00008.png");
	explosion_gr[9] = LoadGraph("graph/exp_00009.png");
	explosion_gr[10] = LoadGraph("graph/exp_00010.png");
	explosion_gr[11] = LoadGraph("graph/exp_00011.png");
	explosion_gr[12] = LoadGraph("graph/exp_00012.png");
	explosion_gr[13] = LoadGraph("graph/exp_00013.png");
	explosion_gr[14] = LoadGraph("graph/exp_00014.png");
	explosion_gr[15] = LoadGraph("graph/exp_00015.png");
	explosion_gr[16] = LoadGraph("graph/exp_00016.png");
	explosion_gr[17] = LoadGraph("graph/exp_00017.png");
	explosion_gr[18] = LoadGraph("graph/exp_00018.png");
	explosion_gr[19] = LoadGraph("graph/exp_00019.png");
	explosion_gr[20] = LoadGraph("graph/exp_00020.png");
	explosion_gr[21] = LoadGraph("graph/exp_00021.png");
	explosion_gr[22] = LoadGraph("graph/exp_00022.png");
	explosion_gr[23] = LoadGraph("graph/exp_00023.png");
	explosion_gr[24] = LoadGraph("graph/exp_00024.png");
	GetGraphSize(explosion_gr[0], &explosion_effect_width, &explosion_effect_height);
}

void ziki::draw_effect() {
	if (effects.flag) {
		DrawGraph(static_cast<int>(effects.x), static_cast<int>(effects.y), explosion_gr[effects.count / 4], true);
		if (effects.count >= 99) {
			effects.flag = false;
			effects.count = 0;
		}
		effects.count += 1;
	}
}

void ziki::run() {
	if (presenceflag) {
		move();
		bomb_start();
		invalid();
		draw();
	}
	else {
		resortie();
		sortiecounter_controler();
	}
	draw();
	shot();
	draw_effect();
	count++;
}