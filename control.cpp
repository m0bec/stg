#include "control.h"

control::control() {
	background.reset(new back);
	ziki1.reset(new ziki);
	loading.reset(new load);
	boss.reset(new bossenemy);
}

void control::firstrun() {
	
}

void control::run() {
	background->firstrun();
	ziki1->run();
	boss->run();
	player_lifecheck();
	background->secondrun();
}

void control::calculation_enemyhp() {
	boss->enemy_damage_counter();
}

void control::get_playerposition(double *centerx, double *centery) {
	double tempx, tempy;

	ziki1->getposition(&tempx, &tempy);

	*centerx = tempx;
	*centery = tempy;
}

void control::get_enemyposition(double *ex, double *ey, int *ewidth, int *eheight) {
	double tempx, tempy;
	int tempwidth, tempheight;

	boss->getposition(&tempx, &tempy, &tempwidth, &tempheight);

	*ex = tempx;
	*ey = tempy;
	*ewidth = tempwidth;
	*eheight = tempheight;
}

void control::get_presenceflag(bool *flag) {
	bool get_presence;
	ziki1->presenceflag_pass(&get_presence);
	*flag = get_presence;
}

bool control::hitcheck(std::vector<enemybullet> *bullet, base bullettype) {
	double zikicx, zikicy;
	ziki1->getposition(&zikicx, &zikicy);
	auto itr = bullet->begin();
	while (itr != bullet->end()) {
		if ((zikicx-itr->x)*(zikicx-itr->x) + (zikicy-itr->y)*(zikicy-itr->y) < (itr->range+ziki1->pass_hitdist())*(itr->range+ziki1->pass_hitdist())) {
			return true;
		}
		else {
			itr++;
		}
	}
	return false;
}

bool control::laser_hitcheck(std::vector<enemybullet> *bullet, laser laserbeam) {
	vec vector;
	vec vector2;
	dis distance;
	bool flag = false;
	double nai, gai, kaku, kaku2, dx, dy, distance, zikicx, zikicy, strx, stry, strr;
	ziki1->getposition(&zikicx, &zikicy);

	//長方形の中に円が入り込んでないか
	//ベクトル
	vector.x = laserbeam.vertex[1].x - laserbeam.vertex[0].x;
	vector.y = laserbeam.vertex[1].y - laserbeam.vertex[0].y;
	vector2.x = zikicx - laserbeam.vertex[0].x;
	vector2.y = zikicy - laserbeam.vertex[0].y;

	//内積
	nai = vector.x*vector2.x + vector.y*vector2.y;
	//外積
	gai = vector.x*vector2.y + vector.y*vector2.x;

	kaku = atan2(gai, nai);
	kaku = -(kaku * 180 / DX_PI);

	vector.x = laserbeam.vertex[3].x - laserbeam.vertex[2].x;
	vector.y = laserbeam.vertex[3].y - laserbeam.vertex[2].y;
	vector2.x = zikicx - laserbeam.vertex[2].x;
	vector2.y = zikicy - laserbeam.vertex[2].y;

	nai = vector.x*vector2.x + vector.y*vector2.y;
	gai = vector.x*vector2.y + vector.y*vector2.x;

	if (atan2(gai, nai) != 0) {
		kaku2 = -(atan2(gai, nai));
	}
	else {
		kaku2 = 0;
	}
	kaku2 = kaku2 * 180 / DX_PI;
	if (0 < kaku && kaku < 90 && 0 < kaku2 && kaku2 < 90)	return true;

	//頂点が円の中にあるか
	for (int i = 0; i < 4; i++) {
		dx = zikicx - laserbeam.vertex[i].x;
		dy = zikicy - laserbeam.vertex[i].y;
		laserbeam.vertex[i].r = dx*dx + dy*dy;
		if (laserbeam.vertex[i].r<ziki1->pass_hitdist()*ziki1->pass_hitdist) {
			return true;
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = i + 1; j < 4; j++) {
			if (laserbeam.vertex[i].r > laserbeam.vertex[j].r) {
				strx = laserbeam.vertex[i].x;
				stry = laserbeam.vertex[i].y;
				strr = laserbeam.vertex[i].r;
				laserbeam.vertex[i].x = laserbeam.vertex[j].x;
				laserbeam.vertex[i].y = laserbeam.vertex[j].y;
				laserbeam.vertex[i].r = laserbeam.vertex[j].r;
				laserbeam.vertex[j].x = strx;
				laserbeam.vertex[j].y = stry;
				laserbeam.vertex[j].r = strr;
			}
		}
	}

	vector.x = laserbeam.vertex[1].x - laserbeam.vertex[0].x;
	vector.y = laserbeam.vertex[1].y - laserbeam.vertex[0].y;
	vector2.x = zikicx - laserbeam.vertex[0].x;
	vector2.x = zikicy - laserbeam.vertex[0].y;
	vector.length = sqrt(vector.x*vector.x + vector.y*vector.y);
	nai = vector.x*vector2.x + vector.y*vector2.y;
	gai = vector.x*vector2.y + vector.y*vector2.x;
	distance.distance = fabs(gai / vector.length);
	if (nai > 0 && distance.distance < ziki1->pass_hitdist) {
		return true;
	}

	return false;
}

void control::player_lifecheck() {
	ziki1->lifecheck(boss->ebullethit_pass());
}