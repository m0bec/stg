#include "enemy.h"
#include "control.h"

void bossenemy::straight_down(std::list<enemy_element>::iterator itr) {
	itr->y += straight_down_speed;
}

void bossenemy::straight_downls(std::list<enemy_element>::iterator itr) {
	itr->y += 2;
}

void bossenemy::straight_left(std::list<enemy_element>::iterator itr) {
	itr->x -= 3;
}

void bossenemy::straight_right(std::list<enemy_element>::iterator itr) {
	itr->x += 3;
}

void bossenemy::allocation_enemymove(std::list<enemy_element>::iterator iterate) {
	switch (iterate->movenum) {
	case 0:
		straight_down(iterate);
		break;

	case 1:
		straight_right(iterate);
		break;

	case 2:
		straight_left(iterate);
		break;

	case 3:
		straight_downls(iterate);
		break;

	case 99:
		break;
	}
}