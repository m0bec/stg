#include "enemy.h"
#include "control.h"

void bossenemy::straight_down(double x) {
	x += straight_down_speed;
}

void bossenemy::allocation_enemymove(std::list<enemy_element> *mob) {
	auto itr = mob->begin();
	switch (itr->movenum) {
	case 0:
		straight_down(itr->x);
		break;
	}
}