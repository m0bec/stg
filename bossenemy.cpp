#include "enemy.h"
#include "control.h"

bossenemy::bossenemy() {
	graph = LoadGraph("graph/enemy.png");
	GetGraphSize(graph, &width, &height);
	bigredbullet.graph = LoadGraph("graph/ETama1.png");
	GetGraphSize(bigredbullet.graph, &bigredbullet.width, &bigredbullet.height);
	bigbluebullet.graph = LoadGraph("graph/ETama2.png");
	GetGraphSize(bigbluebullet.graph, &bigbluebullet.width, &bigbluebullet.height);
	blue_energybullet.graph = LoadGraph("graph/ETama4.png");
	GetGraphSize(blue_energybullet.graph, &blue_energybullet.width, &blue_energybullet.height);
	yellow_bullet.graph = LoadGraph("graph/ETama3.png");
	GetGraphSize(yellow_bullet.graph, &yellow_bullet.width, &yellow_bullet.height);
	greenbullet.graph = LoadGraph("graph/ETama5.png");
	GetGraphSize(greenbullet.graph, &greenbullet.width, &greenbullet.height);
	laserbeam[0].graph = LoadGraph("graph/laser5.png");
	GetGraphSize(laserbeam[0].graph, &laserbeam[0].width, &laserbeam[0].height);
	laserbeam[1].graph = LoadGraph("graph/laser4.png");
	GetGraphSize(laserbeam[1].graph, &laserbeam[1].width, &laserbeam[1].height);
	laserbeam[2].graph = LoadGraph("graph/laser3.png");
	GetGraphSize(laserbeam[2].graph, &laserbeam[2].width, &laserbeam[2].height);
	laserbeam[3].graph = LoadGraph("graph/laser2.png");
	GetGraphSize(laserbeam[3].graph, &laserbeam[3].width, &laserbeam[3].height);
	laserbeam[4].graph = LoadGraph("graph/laser1.png");
	GetGraphSize(laserbeam[4].graph, &laserbeam[4].width, &laserbeam[4].height);
	bluericebullet.graph = LoadGraph("graph/ETama6.png");
	GetGraphSize(bluericebullet.graph, &bluericebullet.width, &bluericebullet.height);
	big_yellow.graph = LoadGraph("graph/big_yello.png");
	GetGraphSize(big_yellow.graph, &big_yellow.width, &big_yellow.height);

	//mobenemy
	dartenemy.graph = LoadGraph("graph/dart.png");
	GetGraphSize(dartenemy.graph, &dartenemy.width, &dartenemy.height);
	
	x = bossenemy_startpoint_x - width / 2;
	y = bossenemy_startpoint_y;
	movestate = 0;
	direct_pattern = 0;
	direct_pattern2 = 0;
	roop_count = 0;
	memoryangle1 = 0;
	memoryangle2 = 0;
	memoryx = 0.0;
	memoryy = 0.0;
	memory_xspeed = 0.0;
	memory_yspeed = 0.0;
	directx = 0.0;
	directy = 0.0;
	directx_flag = 0;
	directy_flag = 0;
	shotflag1 = 0;
	mt.seed(rnd());
	count = 0;
	bulletcount = 0;
	lasercount = 0;
	bullet_directcount = 0;
	ebullethit = false;

	mobenemy.push_back(enemy_element(1000, 1000, 0, 0, 99, 99, 99, 99, 99, 99, 0));
}


void bossenemy::set_enemyhp(int enemyhp) {
	hp = enemyhp;
}

void bossenemy::enemy_damage_counter() {
	hp -= 1;
	if (hp == 0) {
		movestate++;
	}
}

bool bossenemy::ebullethit_pass() {
	return ebullethit;
}

void bossenemy::getposition(double *ex, double *ey, int *ewidth, int *eheight) {
	*ex = this->x;
	*ey = this->y;
	*ewidth = this->width;
	*eheight = this->height;
}

void bossenemy::enemybody_hitcheck(int wid, int heigh, int margin, double positionx, double positiony) {
	control &controling = control::getinstance();
	if (controling.body_hitcheck(width, height, bossenemy_bodymargin, x, y)) {
		ebullethit = true;
	}

}

void bossenemy::move() {
	control &controling = control::getinstance();
	switch (movestate) {
	case 0:
		startmove();
		set_enemyhp(bossenemy_hp1);
		break;

	/*case 1:
		reset_ebullethit();
		roundtrip_move();
		straightaim_player();
		lavishhandout_shot();
		controling.get_presenceflag(&get_presence);
		if (get_presence) {
			bossenemy::enemybody_hitcheck(width, height, bossenemy_bodymargin, x, y);
			bossenemy::ebullethit_checker(&enemybullet1, bigredbullet);
			bossenemy::ebullethit_checker(&enemybullet2, bigbluebullet);
		}
		break;*/

	case 2:
		enemybullet1.erase(enemybullet1.begin(), enemybullet1.end());
		enemybullet2.erase(enemybullet2.begin(), enemybullet2.end());
		goto_center();
		count = 0;
		memoryangle1 = 0.0;
		memoryangle2 = 0.0;
		set_enemyhp(bossenemy_hp1);
		break;
		
	case 3:
		reset_ebullethit();
		DrawGraph(static_cast<int>(x), static_cast<int>(y), graph, true);
		miss_player18();
		two_straightaim_shots();
		base_lavishhandout_shot(&enemybullet3, 0.0, 2*DX_PI, DX_PI, 4, greenbullet, bulletspeed_2);
		controling.get_presenceflag(&get_presence);
		if (get_presence) {
			bossenemy::enemybody_hitcheck(width, height, bossenemy_bodymargin, x, y);
			bossenemy::ebullethit_checker(&enemybullet1, blue_energybullet);
			bossenemy::ebullethit_checker(&enemybullet2, yellow_bullet);
			bossenemy::ebullethit_checker(&enemybullet3, greenbullet);
		}
		break;

	case 4:
		enemybullet1.erase(enemybullet1.begin(), enemybullet1.end());
		enemybullet2.erase(enemybullet2.begin(), enemybullet2.end());
		enemybullet3.erase(enemybullet3.begin(), enemybullet3.end());
		count = 0;
		memoryangle1 = 0.0;
		memoryangle2 = 0.0;
		memoryangle3 = 0.0;
		direct_pattern = 0;
		movestate = 5;
		set_enemyhp(bossenemy_hp2);
		break;

	case 5:
		reset_ebullethit();
		approach();
		if (direct_pattern >= 2) {
			laser_aimplayer(&laserbeam1, laserbeam);
		}
		straight_intersection_shot();
		bossenemy::circlemovebullet();
		controling.get_presenceflag(&get_presence);
		if (get_presence) {
			bossenemy::enemybody_hitcheck(width, height, bossenemy_bodymargin, x, y);
			bossenemy::espinbullet_hitchecker(&spinbullet1, bluericebullet);
			bossenemy::espinbullet_hitchecker(&spinbullet2, bluericebullet);
			bossenemy::espining_center_hitchecker(&center1, greenbullet);
			//bossenemy::elaserthit_checker(&laserbeam1);
		}
		break;

	case 6:
		spinbullet1.erase(spinbullet1.begin(), spinbullet1.end());
		spinbullet2.erase(spinbullet2.cbegin(), spinbullet2.end());
		center1.erase(center1.begin(), center1.end());
		count = 0;
		memoryangle1 = 0.0;
		memoryangle2 = 0.0;
		direct_pattern = 0;
		bullet_directcount = 0;
		bulletcount = 0;
		memoryangle3 = 0.0;
		movestate = 7;
		break;

	case 1:
		reset_ebullethit();
		controling.get_presenceflag(&get_presence);
		straightmove();
		if (get_presence) {
			bossenemy::enemybody_hitcheck(width, height, bossenemy_bodymargin, x, y);
		}
		if (y > upperlimit_joydispheight)	movestate = 8;
		break;

	case 8:
		//double anx, double any, int anwidth, int anheight, int angraphnum, int anbulletnum, int anmovenum, int anbullettype, int anhp, unsigned int atime, int arollingspeed)
		//std::list<enemy_element> *mob, int numenemy, unsigned int enemynum, double anx, double any, int anbulletnum, int anmovenum, int anbullettype, int anhp, unsigned int atime, int rollspeed) 
		bossenemy::preparation_case8(&mobenemy, dart_num, 5, 640, -50, aimstraight_3wayshotnum, straight_downnum, 0, 5, 20, static_cast<int>(DX_PI / 20));
		bossenemy::preparation_case8(&mobenemy, dart_num, 5, 400, -50, aimstraight_3wayshotnum, straight_downnum, 0, 5, 20, static_cast<int>(DX_PI / 20));
		bossenemy::preparation_case8(&mobenemy, dart_num, 6, upperlimit_joydispwidth + 50 , lowerlimit_joydispheight + 150, notaim_2way, straight_leftnum, big_yellowbul, 5, 120, static_cast<int>(DX_PI / 20));
		bossenemy::preparation_case8(&mobenemy, dart_num, 6, lowerlimit_joydispwidth - 50, lowerlimit_joydispheight + 100, notaim_2way, straight_rightnum, big_yellowbul, 5, 120, static_cast<int>(DX_PI / 20));
		movestate = 9;
		break;

	case 9:
		reset_ebullethit();
		controling.get_presenceflag(&get_presence);
		bossenemy::mobrun(&mobenemy);
		bossenemy::mobenemy_alivecheck(&mobenemy);
		break;
	}		
}

void bossenemy::run() {
	move();
	count++;
}