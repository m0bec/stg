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
//���Ɉړ����Ȃ��牺��cos
void bossenemy::quadratic_curve1(std::list<enemy_element>::iterator itr) {
	itr->shotflag = true;
	if (itr->time == 0) {
		itr->x -= 3;
		itr->y += 6 * cos(itr->pass_time * 2 * DX_PI / 400);
	}
}
//���ɉ�����Ȃ���E��cos
void bossenemy::quadratic_curve2(std::list<enemy_element>::iterator itr) {
	itr->shotflag = true;
	if (itr->time == 0) {
		itr->x += 8*cos(itr->pass_time * 2 * DX_PI / 400);
		itr->y += 3;
	}
}
//������Ȃ��獶��cos
void bossenemy::quadratic_curve3(std::list<enemy_element>::iterator itr) {
	itr->shotflag = true;
	if (itr->time == 0) {
		itr->x -= 8 * cos(itr->pass_time * 2 * DX_PI / 400);
		itr->y += 1;
	}
}
//�U�����Ȃ���~���
void bossenemy::quadratic_curve4(std::list<enemy_element>::iterator itr) {
	itr->shotflag = true;
	if (itr->time == 0) {
		itr->x += 3 * sin(itr->pass_time * 2 * DX_PI / 600);
		itr->y += 5 * sin(itr->pass_time * 2 * DX_PI / 600);
	}
}
//�~�^�����Ȃ��牺����
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

void bossenemy::straight_leftl(std::list<enemy_element>::iterator itr) {
	itr->x -= 2;
	itr->shotflag = true;
}
void bossenemy::straight_rightl(std::list<enemy_element>::iterator itr) {
	itr->x += 2;
	itr->shotflag = true;
}

void bossenemy::app_straight(std::list<enemy_element>::iterator itr) {
	if (itr->pass_time < 60) {
		itr->y += 6;
	}
	else {
		itr->movenum = stop_num;
	}
}

void bossenemy::stop(std::list<enemy_element>::iterator itr) {
	itr->shotflag = true;
	if (itr->hp < 600) {
		itr->movenum = stop2_num;
		//itr->graphnum = 
	}
}

void bossenemy::aim(std::list<enemy_element>::iterator itr) {
	itr->shotflag = true;
	if (itr->pass_time % 30 == 0) {
		double px, py;
		control &controling = control::getinstance();
		controling.get_playerposition(&px, &py);
		itr->angle = atan2(py - (itr->y + dartenemy.height / 2), px - (itr->x + itr->width / 2 - dartenemy.width / 2));
	}
	itr->x += cos(itr->angle)*bulletspeed_2;
	itr->y += sin(itr->angle)*bulletspeed_2;
}

void bossenemy::stop2(std::list<enemy_element>::iterator itr) {
	itr->shotflag = true;
	if (itr->x + itr->width / 2 < ((upperlimit_joydispwidth - lowerlimit_joydispwidth) / 2 + lowerlimit_joydispwidth)) {
		itr->x += 4;
	}
	if (itr->y + itr->height / 2 < ((upperlimit_joydispheight - lowerlimit_joydispheight) / 2 + lowerlimit_joydispheight)) {
		itr->y += 4;
	}
}

void bossenemy::slide_move(std::list<enemy_element>::iterator itr) {
	double px, py;
	control &controling = control::getinstance();
	
	if (itr->y > lowerlimit_joydispheight + 100) {
		itr->y -= 5;
	}

	if (itr->pass_time % 100 < 30) {
		if (directx_flag == 0) {
			itr->x += 3;
		}
		else {
			itr->x -= 3;
		}
	}
	else if (itr->pass_time % 100 == 30) {
		controling.get_playerposition(&px, &py);
		if (itr->x + itr->width / 2 < px) {
			directx_flag = 0;
		}
		else {
			directx_flag = 1;
		}
	}

	if (itr->x > upperlimit_joydispwidth - itr->width) {
		itr->x = upperlimit_joydispwidth - itr->width - 1;
	}
	else if (itr->x < lowerlimit_joydispwidth) {
		itr->x = lowerlimit_joydispwidth + 1;
	}
	if (boss2flag) {
		if (itr->hp < 10) {
			itr->hp = -1;
			movestate = 19;
		}
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

	case 14:
		straight_leftl(iterate);
		break;

	case 15:
		straight_rightl(iterate);
		break;

	case 16:
		app_straight(iterate);
		break;

	case 17:
		stop(iterate);
		break;

	case 18:
		aim(iterate);
		break;

	case 19:
		stop2(iterate);
		break;

	case 20:
		slide_move(iterate);
		break;

	case 99:
		break;
	}
}