#include "enemy.h"
#include "control.h"

void bossenemy::straight_down(std::list<enemy_element>::iterator itr) {
	itr->y += straight_down_speed;
	itr->shotflag = true;
}

void bossenemy::straight_downls(std::list<enemy_element>::iterator itr) {
	itr->y += 2;
	itr->shotflag = true;
}

void bossenemy::straight_left(std::list<enemy_element>::iterator itr) {
	itr->x -= 3;
	itr->shotflag = true;
}

void bossenemy::straight_right(std::list<enemy_element>::iterator itr) {
	itr->x += 3;
	itr->shotflag = true;
}

void bossenemy::quadratic_curve(std::list<enemy_element>::iterator itr) {
	itr->x += 3;
	itr->y = (itr->x - itr->originx) * (itr->x - itr->originx);
	itr->shotflag = true;
}

void bossenemy::stop_and_go1(std::list<enemy_element>::iterator itr) {
	if (itr->pass_time < 60) {
		itr->y += 3;
	}
	else if(itr->pass_time == 60){
		itr->shotflag = true;
	}
	else if (itr->pass_time > 720) {
		itr->y -= 3;
	}
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

	case 4:
		quadratic_curve(iterate);
		break;

	case 5:
		stop_and_go1(iterate);
		break;

	case 99:
		break;
	}
}