#include "enemy.h"
#include "control.h"

void bossenemy::mobrun(std::list<enemy_element> *mob) {
	if (mobenemy.size() != 0) {
		auto itr = mob->begin();
		while (itr != mob->end()) {
			if (itr->time == 0) {
				bossenemy::mobenemy_alivecheck(&mobenemy);
				bossenemy::allocation_enemygraph(itr);
				bossenemy::mobenemy_shottypecheck(itr);
				bossenemy::allocation_enemymove(itr);
				bossenemy::allocation_enemybul(itr, &str_bullettype);

				itr->pass_time += 1;
			}
			else {
				itr->time -= 1;
			}
			++itr;
		}
		bossenemy::bullet_move();
		if (get_presence) {
			DrawGraph(400, 400, bigbluebullet.graph, true);
			bossenemy::mobbul_hitcheck(&mobbullet1, str_bullettype);
		}
	}
}

void bossenemy::mobbul_hitcheck(std::list<mobbullet> *bullet, base bullettype) {
	control &controling = control::getinstance();
	if (controling.mobbullet_hitchecker(bullet, bullettype)) {
		ebullethit = true;
	}
}

void bossenemy::preparation_case8(std::list<enemy_element> *mob, int numenemy, unsigned int enemynum, double anx, double any, int anbulletnum, int anmovenum, int anbullettype, int anhp, unsigned int atime, int rollspeed) {
	int wid, heigh;
	unsigned int input_time;
	switch (numenemy) {
	case 0:
		wid = dartenemy.width;
		heigh = dartenemy.height;
		break;
	}

	while (enemynum != 0) {
		input_time = 0 + (enemynum-1)*atime;
		mob->push_back(enemy_element(anx, any, wid, heigh, numenemy, anbulletnum, anmovenum, anbullettype, anhp, input_time, rollspeed));
		enemynum -= 1;
	}
}

void bossenemy::mobenemy_alivecheck(std::list<enemy_element> *mob) {
	auto itr = mob->begin();
	while (itr != mob->end()) {
		if (itr->hp <= 0) {
			itr = mob->erase(itr);
		}
		else {
			++itr;
		}
	}
}

void bossenemy::allocation_enemygraph(std::list<enemy_element>::iterator iterate) {
		switch (iterate->graphnum) {
		case 0:
			DrawRotaGraph(static_cast<int>(iterate->x), static_cast<int>(iterate->y), 1.0, DX_PI/5*iterate->pass_time, dartenemy.graph, true, false);
			break;
		}
}

void bossenemy::allocation_enemyshot(std::list<enemy_element>::iterator iterate) {
	mobenemy_shottypecheck(iterate);
}

void bossenemy::allocation_enemybul(std::list<enemy_element>::iterator iterate, base *bul) {
	switch (iterate->bullettype) {
	case 0:
		*bul = bigredbullet;
		break;
	}
}

void bossenemy::mobenemy_shottypecheck(std::list<enemy_element>::iterator iterate) {
	control &controling = control::getinstance();
	switch (iterate->bulletnum) {
		//3way
	case 0:
		double px, py;
		if (iterate->pass_time % 120 < 30 && iterate->pass_time % 5 == 0) {
			controling.get_playerposition(&px, &py);
			mobbullet1.push_back(mobbullet(iterate->x + iterate->width / 2 - bigredbullet.width / 2, iterate->y + iterate->height / 2 - bigredbullet.height / 2, atan2(py - (iterate->y + iterate->height / 2 - bigredbullet.height / 2), px - (iterate->x + iterate->width / 2 - bigredbullet.width / 2)), 6, 6, iterate->bullettype));
			mobbullet1.push_back(mobbullet(iterate->x + iterate->width / 2 - bigredbullet.width / 2, iterate->y + iterate->height / 2 - bigredbullet.height / 2, atan2(py - (iterate->y + iterate->height / 2 - bigredbullet.height / 2), px - (iterate->x + iterate->width / 2 - bigredbullet.width / 2)) + DX_PI / 6, 6, 6, iterate->bullettype));
			mobbullet1.push_back(mobbullet(iterate->x + iterate->width / 2 - bigredbullet.width / 2, iterate->y + iterate->height / 2 - bigredbullet.height / 2, atan2(py - (iterate->y + iterate->height / 2 - bigredbullet.height / 2), px - (iterate->x + iterate->width / 2 - bigredbullet.width / 2)) - DX_PI / 6, 6, 6, iterate->bullettype));
			int j = 0;
			auto itr = mobbullet1.begin();
		}
		break;
	}
}

void bossenemy::bullet_move() {
	auto itr = mobbullet1.begin();
	while (itr != mobbullet1.end()) {
		switch (itr->bullettag) {
		case 0:
			itr->x += cos(itr->angle)*bulletspeed_8;
			itr->y += sin(itr->angle)*bulletspeed_8;
			if (itr->y > upperlimit_joydispheight || itr->y < lowerlimit_joydispheight - str_bullettype.height
				|| itr->x > upperlimit_joydispwidth || itr->x < lowerlimit_joydispwidth - str_bullettype.width) {
				itr = mobbullet1.erase(itr);
			}
			else {
				DrawGraph(static_cast<int>(itr->x), static_cast<int>(itr->y), bigredbullet.graph, true);
				itr++;
			}
			break;
		}
	}
}

void bossenemy::get_mobplace(std::list<enemy_element> *iterate) {
	iterate = &mobenemy;
}

void bossenemy::mob_damage(unsigned int cou) {
	auto itr = mobenemy.begin();
	for (unsigned int i = cou; i != 0; i--) {
		itr++;
	}
	itr->hp -= 1;
}

int bossenemy::pass_size() {
	return static_cast<int>(mobenemy.size());
}

void bossenemy::pass_position(double *ex, double *ey, int *ewidth, int *eheight, int count) {
	auto itr = mobenemy.begin();
	for (int i = count; i > 0; i--)	itr++;
	*ex = itr->x;
	*ey = itr->y;
	*ewidth = itr->width;
	*eheight = itr->height;
}