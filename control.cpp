#include "control.h"

control::control() {
	background.reset(new back);
	ziki1.reset(new ziki);
	loading.reset(new load);
	boss.reset(new bossenemy);
	sys.reset(new systemm);
	state = 0;
	point = 0;
}

void control::firstrun() {
	
}

int control::pass_state() {
	return state;
}

void control::get_point() {
	point += ziki1->pass_point();
}

void control::run() {
	if (state == 0) {
		state = sys->pass_state();
		sys->startgraphrun();
	}
	else if (state == 1) {
		background->firstrun();
		ziki1->run();
		boss->run();
		player_lifecheck();
		background->secondrun();
		sys->scoredisp(point);
	}
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

bool control::hitcheck(std::list<enemybullet> *bullet, base bullettype) {
	double zikicx, zikicy;
	ziki1->getposition(&zikicx, &zikicy);
	auto itr = bullet->begin();
	while (itr != bullet->end()) {
		if ((zikicx - itr->x)*(zikicx - itr->x) + (zikicy - itr->y)*(zikicy - itr->y) < (itr->range+ziki1->pass_hitdist())*(itr->range+ziki1->pass_hitdist())) {
			return true;
		}
		else {
			itr++;
		}
	}
	return false;
}

bool control::body_hitcheck(int wid, int heigh, int margin, double positionx, double positiony) {
	double zikicx, zikicy, hitdist;
	ziki1->getposition(&zikicx, &zikicy);
	hitdist = ziki1->pass_hitdist();
	if (positionx + margin < zikicx +  hitdist && positionx + wid - margin > zikicx - hitdist
		&& positiony + margin < zikicy + hitdist && positiony + heigh - margin > zikicy - hitdist) {
		return true;
	}
	return false;
}

bool control::spining_center_hitcheck(std::list<spining_center> *bullet, base bullettype) {
	double zikicx, zikicy;
	ziki1->getposition(&zikicx, &zikicy);
	auto itr = bullet->begin();
	while (itr != bullet->end()) {
		if ((zikicx - itr->x)*(zikicx - itr->x) + (zikicy - itr->y)*(zikicy - itr->y) < (itr->range + ziki1->pass_hitdist())*(itr->range + ziki1->pass_hitdist())) {
			return true;
		}
		else {
			itr++;
		}
	}
	return false;
}

bool control::spinbullet_hitchecker(std::list<rotabullet> *bullet, base bullettype) {
	double zikicx, zikicy;
	ziki1->getposition(&zikicx, &zikicy);
	auto itr = bullet->begin();
	while (itr != bullet->end()) {
		if ((zikicx - itr->x)*(zikicx - itr->x) + (zikicy - itr->y)*(zikicy - itr->y) < (itr->range + ziki1->pass_hitdist())*(itr->range + ziki1->pass_hitdist())) {
			return true;
		}
		else {
			itr++;
		}
	}
	return false;
}

bool control::laser_hitcheck(std::list<laser> *bullet) {
	vec list;
	vec list2;
	dis distance;
	bool flag = false;
	double p_hitdist, nai, gai, kaku, kaku2, dx, dy, zikicx, zikicy, strx, stry, strr;
	ziki1->getposition(&zikicx, &zikicy);
	p_hitdist = ziki1->pass_hitdist();
	auto itr = bullet->begin();
	while (itr != bullet->end()) {
		//長方形の中に円が入り込んでないか
		//ベクトル
		list.x = itr->vertex[1].x - itr->vertex[0].x;
		list.y = itr->vertex[1].y - itr->vertex[0].y;
		list2.x = zikicx - itr->vertex[0].x;
		list2.y = zikicy - itr->vertex[0].y;

		//内積
		nai = list.x*list2.x + list.y*list2.y;
		//外積
		gai = list.x*list2.y + list.y*list2.x;

		kaku = atan2(gai, nai);
		kaku = -(kaku * 180 / DX_PI);

		list.x = itr->vertex[3].x - itr->vertex[2].x;
		list.y = itr->vertex[3].y - itr->vertex[2].y;
		list2.x = zikicx - itr->vertex[2].x;
		list2.y = zikicy - itr->vertex[2].y;

		nai = list.x*list2.x + list.y*list2.y;
		gai = list.x*list2.y + list.y*list2.x;

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
			dx = zikicx - itr->vertex[i].x;
			dy = zikicy - itr->vertex[i].y;
			itr->vertex[i].r = dx*dx + dy*dy;
			if (itr->vertex[i].r < p_hitdist*p_hitdist) {
				return true;
			}
		}

		for (int i = 0; i < 4; i++) {
			for (int j = i + 1; j < 4; j++) {
				if (itr->vertex[i].r > itr->vertex[j].r) {
					strx = itr->vertex[i].x;
					stry = itr->vertex[i].y;
					strr = itr->vertex[i].r;
					itr->vertex[i].x = itr->vertex[j].x;
					itr->vertex[i].y = itr->vertex[j].y;
					itr->vertex[i].r = itr->vertex[j].r;
					itr->vertex[j].x = strx;
					itr->vertex[j].y = stry;
					itr->vertex[j].r = strr;
				}
			}
		}

		list.x = itr->vertex[1].x - itr->vertex[0].x;
		list.y = itr->vertex[1].y - itr->vertex[0].y;
		list2.x = zikicx - itr->vertex[0].x;
		list2.x = zikicy - itr->vertex[0].y;
		list.length = sqrt(list.x*list.x + list.y*list.y);
		nai = list.x*list2.x + list.y*list2.y;
		gai = list.x*list2.y + list.y*list2.x;
		distance.distance = fabs(gai / list.length);
		if (nai > 0 && distance.distance < p_hitdist) {
			return true;
		}
		itr++;
	}
	return false;
}

void control::player_lifecheck() {
	ziki1->lifecheck(boss->ebullethit_pass());
}