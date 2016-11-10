#include "control.h"

control::control() {
	background.reset(new back);
	ziki1.reset(new ziki);
	loading.reset(new load);
	boss.reset(new bossenemy);
	sys.reset(new systemm);
	state = 0;
	point = 0; 
	graze = 0;
	graze_stock = 0;
	zanki = 10;
	bomb_flag = false;
	are.graph = LoadGraph("graph/ziki1.png");
	
}

void control::firstrun() {
	
}

int control::pass_state() {
	return state;
}

void control::get_point() {
	point = ziki1->pass_point();
}

void control::get_graze() {
	graze = ziki1->pass_grazenum();
	graze_stock = ziki1->pass_grazestock();
}

void control::run() {
	if (state == 0) {
		state = sys->pass_state();
		sys->startgraphrun();
		sys->instal_score();
	}
	else if (state == 1) {
		background->firstrun();
		ziki1->run();
		boss->run();
		player_lifecheck();
		background->secondrun();
		get_point();
		get_graze();
		get_bombflag();
		get_ziki(&zanki);
		sys->disp_highscore();
		sys->scoredisp(point);
		sys->grasedisp(graze);
		sys->gage(graze_stock);
		sys->zanki_disp(zanki);
		sys->music2();
	}
	else if (state == 2) {
		state = 0;
		sys->save_score(point);
		sys->p_state(state);
		boss->first_set();
		ziki1->first_p();
		background->set_state() = 0;
	}
}

void control::calculation_enemyhp() {
	boss->enemy_damage_counter();
}

int control::pass_zanki() {
	int str = ziki1->pass_zanki();
	return str;
}

void control::first_p() {
	state = 0;
	point = 0;
	graze = 0;
	graze_stock = 0;
	zanki = 10;
	bomb_flag = false;
}

void control::get_bombflag() {
	bomb_flag = ziki1->bomb();
}

void control::pass_bombflag(bool *flag) {
	*flag = bomb_flag;
}

void control::pass_bstate(int sta) {
	background->set_state() = sta;
}

void control::pass_musicfla(int fla) {
	sys->set_musicflag() = fla;
}

void control::get_ziki(int *zik) {
	*zik = ziki1->pass_zanki();
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

void control::get_mobposition(std::list<enemy_element> *mob_) {
	boss->get_mobplace(mob_);
}

void control::get_presenceflag(bool *flag) {
	bool get_presence;
	ziki1->presenceflag_pass(&get_presence);
	*flag = get_presence;
	if (bomb_flag) {
		*flag = false;
	}
}

bool control::hitcheck(std::list<enemybullet> *bullet, base bullettype) {
	double zikicx, zikicy;
	int check;
	ziki1->getposition(&zikicx, &zikicy);
	auto itr = bullet->begin();
	while (itr != bullet->end()) {
		if ((zikicx - itr->x)*(zikicx - itr->x) + (zikicy - itr->y)*(zikicy - itr->y) < (itr->range + ziki1->pass_grazedist())*(itr->range + ziki1->pass_grazedist())) {
			ziki1->graze_counter();
			if ((zikicx - itr->x)*(zikicx - itr->x) + (zikicy - itr->y)*(zikicy - itr->y) < (itr->range + ziki1->pass_hitdist())*(itr->range + ziki1->pass_hitdist())) {
				check = ziki1->life_damage();
				if (check == -1) {
					state = 2;
				}
				return true;
			}
			else {
				itr++;
			}
		}
		else {
			itr++;
		}
	}
	return false;
}

bool control::body_hitcheck2(std::list<enemy_element> *mobe) {
	double zikicx, zikicy, hitdist;
	int check;
	ziki1->getposition(&zikicx, &zikicy);
	hitdist = ziki1->pass_hitdist();
	auto itr = mobe->begin();
	while (itr != mobe->end()) {
		if (itr->x + itr->margine < zikicx + hitdist && itr->x + itr->width - itr->margine > zikicx - hitdist
			&& itr->y + itr->margine < zikicy + hitdist && itr->y + itr->height - itr->margine > zikicy - hitdist) {
			check = ziki1->life_damage();
			if (check == -1) {
				state = 2;
			}
			return true;
		}
		else {
			++itr;
		}
	}
	return false;
}

bool control::body_hitcheck(int wid, int heigh, int margin, double positionx, double positiony) {
	double zikicx, zikicy, hitdist;
	int check;
	ziki1->getposition(&zikicx, &zikicy);
	hitdist = ziki1->pass_hitdist();
	if (positionx + margin < zikicx +  hitdist && positionx + wid - margin > zikicx - hitdist
		&& positiony + margin < zikicy + hitdist && positiony + heigh - margin > zikicy - hitdist) {
		check = ziki1->life_damage();
		if (check == -1) {
			state = 2;
		}
		return true;
	}
	return false;
}

bool control::spining_center_hitcheck(std::list<spining_center> *bullet, base bullettype) {
	double zikicx, zikicy;
	int check;
	ziki1->getposition(&zikicx, &zikicy);
	auto itr = bullet->begin();
	while (itr != bullet->end()) {
		if ((zikicx - itr->x)*(zikicx - itr->x) + (zikicy - itr->y)*(zikicy - itr->y) < (itr->range + ziki1->pass_grazedist())*(itr->range + ziki1->pass_grazedist())) {
			ziki1->graze_counter();
			if ((zikicx - itr->x)*(zikicx - itr->x) + (zikicy - itr->y)*(zikicy - itr->y) < (itr->range + ziki1->pass_hitdist())*(itr->range + ziki1->pass_hitdist())) {
				check = ziki1->life_damage();
				if (check == -1) {
					state = 2;
				}
				return true;
			}
			else {
				itr++;
			}
		}
		else {
			itr++;
		}
	}
	return false;
}

bool control::spinbullet_hitchecker(std::list<rotabullet> *bullet, base bullettype) {
	double zikicx, zikicy;
	int check;
	ziki1->getposition(&zikicx, &zikicy);
	auto itr = bullet->begin();
	while (itr != bullet->end()) {
		if ((zikicx - itr->x)*(zikicx - itr->x) + (zikicy - itr->y)*(zikicy - itr->y) < (itr->range + ziki1->pass_grazedist())*(itr->range + ziki1->pass_grazedist())) {
			ziki1->graze_counter();
			if ((zikicx - itr->x)*(zikicx - itr->x) + (zikicy - itr->y)*(zikicy - itr->y) < (itr->range + ziki1->pass_hitdist())*(itr->range + ziki1->pass_hitdist())) {
				check = ziki1->life_damage();
				if (check == -1) {
					state = 2;
				}
				return true;
			}
			else {
				itr++;
			}
		}
		else {
			itr++;
		}
	}
	return false;
}

bool control::mobbullet_hitchecker(std::list<mobbullet> *bullet, base bullettype) {
	double zikicx, zikicy, str;
	int check;
	bool flag = false;
	int count = 0;
	std::array<vec, 5> vect;	//target
	std::array<vec, 5> vecs;
	std::array<square, 5> squ;
	ziki1->getposition(&zikicx, &zikicy);
	auto itr = bullet->begin();
	while (itr != bullet->end()) {
		if (itr->hit_type == 0) {
			if ((zikicx - itr->x)*(zikicx - itr->x) + (zikicy - itr->y)*(zikicy - itr->y) < (itr->range + ziki1->pass_grazedist())*(itr->range + ziki1->pass_grazedist())) {
				ziki1->graze_counter();
				if ((zikicx - itr->x)*(zikicx - itr->x) + (zikicy - itr->y)*(zikicy - itr->y) < (itr->range + ziki1->pass_hitdist())*(itr->range + ziki1->pass_hitdist())) {
					check = ziki1->life_damage();
					if (check == -1) {
						state = 2;
					}
					return true;
				}
				else {
					itr++;
				}
			}
			else {
				itr++;
			}
		}
		else if (itr->hit_type == 1) {
			squ[0].x = itr->x;	squ[1].x = itr->x + itr->bul.width * cos(itr->angle);	squ[3].x = itr->x - itr->bul.height*sin(itr->angle);	squ[2].x = squ[1].x + squ[3].x;	squ[4].x = squ[0].x;
			squ[0].y = itr->y;	squ[1].y = itr->y - itr->bul.width * sin(itr->angle);	squ[3].y = itr->y + itr->bul.height*cos(itr->angle);	squ[2].y = squ[1].y + squ[3].y;	squ[4].y = squ[0].y;
			for (int i = 0 ; i < 4; i++) {
				vecs[i].x = squ[i + 1].x - squ[i].x;	vecs[i].y = squ[i + 1].y - squ[i].y;
				vect[i].x = zikicx - squ[i].x;	vect[i].y = zikicy - squ[i].y;
			}	vect[4].x = zikicx - squ[4].x; vect[4].y = zikicy - squ[4].y;

			for (int i = 0; i < 4; i++) {
				if (vecs[i].x * vect[i].y - vecs[i].y * vect[i].x <= 0) {
					++count;
					if(count == 4)	flag = true;
				}
			}

			if (!flag) {
				for (int i = 0; i < 4; i++) {
					str = (vect[i].x * vecs[i].y - vecs[i].x * vect[i].y) * (vect[i].x * vecs[i].y - vecs[i].x * vect[i].y);
					if (str <= (vecs[i].x * vecs[i].x + vecs[i].y * vecs[i].y)* ziki1->pass_grazedist()) {
						if ((vecs[i].x * vect[i].x + vecs[i].y * vect[i].y) * (vecs[i].x * vect[i + 1].x + vecs[i].y * vect[i + 1].y) <= 0) {
							ziki1->graze_counter();
							if (str <= (vecs[i].x * vecs[i].x + vecs[i].y * vecs[i].y)* ziki1->pass_hitdist()) {
								flag = true;
								break;
							}
						}
					}
				}
			}

			if (flag) {
				return true;
			}
			else {
				++itr;
			}
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