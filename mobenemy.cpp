#include "enemy.h"
#include "control.h"

void bossenemy::mobrun(std::list<enemy_element> *mob) {
	auto itr = mob->begin();
	while (itr != mob->end()) {
		if (itr->time == 0) {
			bossenemy::allocation_enemygraph(itr);
			bossenemy::mobenemy_shottypecheck(itr);
			bossenemy::allocation_enemymove(itr);
			if (get_presence) {
				bossenemy::allocation_enemybul(itr, &str_bullettype);
				bossenemy::mobbul_hitcheck(itr->mobbullet1, str_bullettype);
			}
			itr->pass_time += 1;
		}
		else {
			itr->time -= 1;
		}
		++itr;
	}
}

void bossenemy::mobbul_hitcheck(std::array<mobbullet, 100> bullet, base bullettype) {
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
		auto t = mob->begin();
		while (t != mob->end()) {
			for (int i = 0; i < 100; i++) {
				t->mobbullet1[i].flag = 0;
			}
			t++;
		}
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
		bul = &bigredbullet;
		break;
	}
}

void bossenemy::mobenemy_shottypecheck(std::list<enemy_element>::iterator iterate) {
	switch (iterate->bulletnum) {
		//3way
	case 0:
		control &controling = control::getinstance();
		double px, py;
		
		if (iterate->pass_time % 120 < 30 && iterate->pass_time % 5 == 0) {
			controling.get_playerposition(&px, &py);
			int j = 0;
			for (auto itr = iterate->mobbullet1.begin(); itr == iterate->mobbullet1.end(); itr++) {
				if (itr->flag == 0) {
					if (j == 0) {
						itr->x = iterate->x + iterate->width / 2 - bigredbullet.width / 2;
						itr->y = iterate->y + iterate->height / 2 - bigredbullet.height / 2;
						itr->angle = atan2(py - (iterate->y + iterate->height / 2), px - (iterate->x + iterate->width / 2));
						itr->range = 6;
						itr->rota = 0;
						itr->flag = 1;
						j=1; 
					}
					else if (j == 1) {
						itr->x = iterate->x + iterate->width / 2 - bigredbullet.width / 2;
						itr->y = iterate->y + iterate->height / 2 - bigredbullet.height / 2;
						itr->angle = atan2(py - (iterate->y + iterate->height / 2), px - (iterate->x + iterate->width / 2)) + DX_PI / 6;
						itr->range = 6;
						itr->rota = 0;
						itr->flag = 1;
						j=2;
					}else if(j == 2){
						itr->x = iterate->x + iterate->width / 2 - bigredbullet.width / 2;
						itr->y = iterate->y + iterate->height / 2 - bigredbullet.height / 2;
						itr->angle = atan2(py - (iterate->y + iterate->height / 2), px - (iterate->x + iterate->width / 2)) - DX_PI / 6;
						itr->range = 6;
						itr->rota = 0;
						itr->flag = 1;
						break;
					}
				}
			}
		}
		auto itr = iterate->mobbullet1.begin();
		while (itr != iterate->mobbullet1.end()) {
			itr->x += cos(itr->angle)*bulletspeed_2;
			itr->y += sin(itr->angle)*bulletspeed_2;
			if (itr->flag == 1) {
				if (itr->y > upperlimit_joydispheight || itr->y < lowerlimit_joydispheight - bigredbullet.height
					|| itr->x > upperlimit_joydispwidth || itr->x < lowerlimit_joydispwidth - bigredbullet.width) {
					itr->flag = 0;
				}
				else {
					DrawGraph(static_cast<int>(itr->x), static_cast<int>(itr->y), bigredbullet.graph, true);
					itr++;
				}
			}
			else {
				itr++;
			}
		}
		break;
	}
}

