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
	itr->shotflag = true;
	if (itr->time == 0) {
		itr->x += 3;
		itr->y += 6*cos(itr->pass_time * 2 * DX_PI / 400);
	}
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
//¶‚ÉˆÚ“®‚µ‚È‚ª‚ç‰º‚Écos
void bossenemy::quadratic_curve1(std::list<enemy_element>::iterator itr) {
	itr->shotflag = true;
	if (itr->time == 0) {
		itr->x -= 3;
		itr->y += 6 * cos(itr->pass_time * 2 * DX_PI / 400);
	}
}
//‰º‚É‰º‚ª‚è‚È‚ª‚ç‰E‚Écos
void bossenemy::quadratic_curve2(std::list<enemy_element>::iterator itr) {
	itr->shotflag = true;
	if (itr->time == 0) {
		itr->x += 8*cos(itr->pass_time * 2 * DX_PI / 400);
		itr->y += 3;
	}
}
//‰º‚ª‚è‚È‚ª‚ç¶‚Écos
void bossenemy::quadratic_curve3(std::list<enemy_element>::iterator itr) {
	itr->shotflag = true;
	if (itr->time == 0) {
		itr->x -= 8 * cos(itr->pass_time * 2 * DX_PI / 400);
		itr->y += 1;
	}
}
//U“®‚µ‚È‚ª‚ç~‚è‚é
void bossenemy::quadratic_curve4(std::list<enemy_element>::iterator itr) {
	itr->shotflag = true;
	if (itr->time == 0) {
		itr->x += 3 * sin(itr->pass_time * 2 * DX_PI / 600);
		itr->y += 5 * sin(itr->pass_time * 2 * DX_PI / 600);
	}
}
//‰~‰^“®‚µ‚È‚ª‚ç‰º‚ª‚é
void bossenemy::quadratic_curve5(std::list<enemy_element>::iterator itr) {
	itr->shotflag = true;
	if (itr->time == 0) {
		itr->x = 100 * sin(itr->pass_time * 2 * DX_PI / 300) + itr->originx;
		itr->y = 100 * sin(itr->pass_time * 2 * DX_PI / 300) + itr->originy + itr->pass_time;
	}
}

void bossenemy::straight_up(std::list<enemy_element>::iterator itr) {
	itr->y -= straight_down_speed;
	itr->shotflag = true;
}

void bossenemy::stop_and_go2(std::list<enemy_element>::iterator itr) {
	itr->shotflag = true;
	if (itr->pass_time % 60 >= 40) {
		itr->x += 8;
	}
}

void bossenemy::stop_and_go3(std::list<enemy_element>::iterator itr) {
	itr->shotflag = true;
	if (itr->pass_time % 60 >= 40) {
		itr->x -= 8;
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

	case 6:
		quadratic_curve1(iterate);
		break;

	case 7:
		quadratic_curve2(iterate);
		break;

	case 8:
		quadratic_curve3(iterate);
		break;

	case 9:
		quadratic_curve4(iterate);
		break;

	case 10:
		quadratic_curve5(iterate);
		break;

	case 11:
		straight_up(iterate);
		break;

	case 12:
		stop_and_go2(iterate);
		break;

	case 13:
		stop_and_go2(iterate);
		break;

	case 99:
		break;
	}
}