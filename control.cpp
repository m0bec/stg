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

void control::player_lifecheck() {
	ziki1->lifecheck(boss->ebullethit_pass());
}