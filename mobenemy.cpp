#include "enemy.h"
#include "control.h"

void bossenemy::mobrun(std::list<enemy_element> *mob) {
	auto itr = mob->begin();
	while (itr != mob->end()) {
		if (itr->time == 0) {
			bossenemy::allocation_enemygraph(itr);
			bossenemy::allocation_enemymove(itr);
			itr->pass_time += 1;
		}
		else {
			itr->time -= 1;
		}
		++itr;
	}
}

void bossenemy::preparation_case8(std::list<enemy_element> *mob, int numenemy, unsigned int enemynum, double anx, double any, int anbulletnum, int anmovenum, int anhp, unsigned int atime, int rollspeed) {
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
		mob->push_back(enemy_element(anx, any, wid, heigh, numenemy, anbulletnum, anmovenum, anhp, input_time, rollspeed));
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

void bossenemy::mobenemy_shottypecheck(std::list<enemy_element>::iterator iterate) {
	switch (iterate->bulletnum) {
	case 0:

		break;
	}
}

