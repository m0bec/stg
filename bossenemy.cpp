#include "enemy.h"
#include "control.h"
#include "back.h"

bossenemy::bossenemy() {
	graph = LoadGraph("graph/enemy.png");
	GetGraphSize(graph, &width, &height);
	bigredbullet.graph = LoadGraph("graph/ETama1.png");
	GetGraphSize(bigredbullet.graph, &bigredbullet.width, &bigredbullet.height);
	bigredbullet.range = 6;
	bigbluebullet.graph = LoadGraph("graph/ETama2.png");
	GetGraphSize(bigbluebullet.graph, &bigbluebullet.width, &bigbluebullet.height);
	bigbluebullet.range = 6;
	blue_energybullet.graph = LoadGraph("graph/ETama4.png");
	GetGraphSize(blue_energybullet.graph, &blue_energybullet.width, &blue_energybullet.height);
	blue_energybullet.range = 4;
	yellow_bullet.graph = LoadGraph("graph/ETama3.png");
	GetGraphSize(yellow_bullet.graph, &yellow_bullet.width, &yellow_bullet.height);
	yellow_bullet.range = 4;
	greenbullet.graph = LoadGraph("graph/ETama5.png");
	GetGraphSize(greenbullet.graph, &greenbullet.width, &greenbullet.height);
	greenbullet.range = 4;
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
	bluericebullet.range = 2;
	big_yellow.graph = LoadGraph("graph/big_yello.png");
	GetGraphSize(big_yellow.graph, &big_yellow.width, &big_yellow.height);
	big_yellow.range = 10;
	redbullet.graph = LoadGraph("graph/ETama7.png");
	GetGraphSize(redbullet.graph, &redbullet.width, &redbullet.height);
	redbullet.range = 4;
	lightblue_bullet.graph = LoadGraph("graph/ETama8.png");
	GetGraphSize(lightblue_bullet.graph, &lightblue_bullet.width, &lightblue_bullet.height);
	lightblue_bullet.range = 4;
	purplebullet.graph = LoadGraph("graph/ETama9.png");
	GetGraphSize(purplebullet.graph, &purplebullet.width, &purplebullet.height);
	purplebullet.range = 4;
	grassgreen_bullet.graph = LoadGraph("graph/ETama10.png");
	GetGraphSize(grassgreen_bullet.graph, &grassgreen_bullet.width, &grassgreen_bullet.height);
	grassgreen_bullet.range = 4;
	bigred_bullet.graph = LoadGraph("graph/big_red.png");
	GetGraphSize(bigred_bullet.graph, &bigred_bullet.width, &bigred_bullet.height);
	bigred_bullet.range = 10;

	//mobenemy
	dartenemy.graph = LoadGraph("graph/dart.png");
	GetGraphSize(dartenemy.graph, &dartenemy.width, &dartenemy.height);
	aplane_enemy.graph = LoadGraph("graph/ene2.png");
	GetGraphSize(aplane_enemy.graph, &aplane_enemy.width, &aplane_enemy.height);
	lase_enemy.graph = LoadGraph("graph/ene3.png");
	GetGraphSize(lase_enemy.graph, &lase_enemy.width, &lase_enemy.height);
	lase_enemyr.graph = LoadGraph("graph/ene3r.png");
	GetGraphSize(lase_enemyr.graph, &lase_enemyr.width, &lase_enemyr.height);
	lase_enemyl.graph = LoadGraph("graph/ene3l.png");
	GetGraphSize(lase_enemyl.graph, &lase_enemyl.width, &lase_enemyl.height);
	big_enemy.graph = LoadGraph("graph/ene4.png");
	GetGraphSize(big_enemy.graph, &big_enemy.width, &big_enemy.height);
	boss2.graph = LoadGraph("graph/ene4_.png");
	GetGraphSize(boss2.graph, &boss2.width, &boss2.height);

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

	mobenemy.push_back(enemy_element(0, 0, 0, 0, 99, 99, 99, 99, 99, 99, 0, 0, true, 0));
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
	std::uniform_real_distribution<> rand2(0, 20);
	switch (movestate) {
	case 0:
		startmove();
		set_enemyhp(bossenemy_hp1);
		break;

	case 1:
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
		break;

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

	case 7:
		reset_ebullethit();
		controling.get_presenceflag(&get_presence);
		straightmove();
		if (get_presence) {
			bossenemy::enemybody_hitcheck(width, height, bossenemy_bodymargin, x, y);
		}
		if (y > upperlimit_joydispheight)	movestate = 8;
		controling.pass_bstate(1);
		break;

	case 8:
		//double anx, double any, int anwidth, int anheight, int angraphnum, int anbulletnum, int anmovenum, int anbullettype, int anhp, unsigned int atime, int arollingspeed)
		//std::list<enemy_element> *mob, int numenemy, unsigned int enemynum, double anx, double any, int anbulletnum, int anmovenum, int anbullettype, int anhp, unsigned int atime, int rollspeed, unsigned int inter) 
		bossenemy::preparation_case8(&mobenemy, dart_num, 5, 640, -dartenemy.height, aimstraight_3wayshotnum, straight_downnum, 0, 5, 20, static_cast<int>(DX_PI / 20), 20, normal_margine);
		bossenemy::preparation_case8(&mobenemy, dart_num, 5, 400, -dartenemy.height, aimstraight_3wayshotnum, straight_downnum, 0, 5, 20, static_cast<int>(DX_PI / 20), 20, normal_margine);
		bossenemy::preparation_case8(&mobenemy, dart_num, 6, upperlimit_joydispwidth + dartenemy.width , lowerlimit_joydispheight + 150, notaim_2way, straight_leftnum, big_yellowbul, 5, 120, static_cast<int>(DX_PI / 20), 20, normal_margine);
		bossenemy::preparation_case8(&mobenemy, dart_num, 6, lowerlimit_joydispwidth - dartenemy.width, lowerlimit_joydispheight + 100, notaim_2way, straight_rightnum, big_yellowbul, 5, 120, static_cast<int>(DX_PI / 20), 20, normal_margine);
		movestate = 9;
		break;

	case 9:
		reset_ebullethit();
		controling.get_presenceflag(&get_presence);
		bossenemy::mobrun(&mobenemy);
		bossenemy::mobenemy_alivecheck(&mobenemy);
		++count;
		if (count > 580)	movestate = 10;
		break;

	case 10:
		bossenemy::preparation_case8(&mobenemy, aplane_num, 1, 500 - aplane_enemy.width / 2, -50, sixteenway, straight_downlsnum, yel_bul, 20, 50, 0, 1, normal_margine);
		bossenemy::preparation_case8(&mobenemy, aplane_num, 1, 300 - aplane_enemy.width / 2, -50, sixteenway, straight_downlsnum, yel_bul, 20, 150, 0, 1, normal_margine);
		bossenemy::preparation_case8(&mobenemy, aplane_num, 1, 700 - aplane_enemy.width / 2, -50, sixteenway, straight_downlsnum, yel_bul, 20, 150, 0, 1, normal_margine);
		bossenemy::preparation_case8(&mobenemy, dart_num, 1, 500 - dartenemy.width / 2, -50, randomway, stop_and_gonum, green_bul, 50, 480, static_cast<int>(DX_PI / 20), 1, normal_margine);
		bossenemy::preparation_case8(&mobenemy, dart_num, 1, 300 - dartenemy.width / 2, -50, randomway, stop_and_gonum, green_bul, 50, 600, static_cast<int>(DX_PI / 20), 1, normal_margine);
		bossenemy::preparation_case8(&mobenemy, dart_num, 1, 700 - dartenemy.width / 2, -50, randomway, stop_and_gonum, green_bul, 50, 730, static_cast<int>(DX_PI / 20), 1, normal_margine);
		bossenemy::mobrun(&mobenemy);
		bossenemy::mobenemy_alivecheck(&mobenemy);
		count = 0;
		movestate = 11;
		break;

	case 11:
		reset_ebullethit();
		controling.get_presenceflag(&get_presence);
		bossenemy::mobrun(&mobenemy);
		bossenemy::mobenemy_alivecheck(&mobenemy);
		++count;
		if (count > 2000)	movestate = 12;
		break;

	case 12:
		bossenemy::preparation_case8(&mobenemy, dart_num, 1, 200 - dartenemy.width / 2, -50, put_pway, quadratic_curvenum, green_bul, 20, 10, static_cast<int>(DX_PI / 20), 20, normal_margine);
		bossenemy::preparation_case8(&mobenemy, dart_num, 1, 700 - dartenemy.width / 2, -50, put_pway, quadratic_curvenum1, green_bul, 20, 70, static_cast<int>(DX_PI / 20), 20, normal_margine);
		bossenemy::preparation_case8(&mobenemy, dart_num, 1,  - dartenemy.width / 2, 0, put_pway, quadratic_curvenum2, green_bul, 20, 180, static_cast<int>(DX_PI / 20), 20, normal_margine);
		bossenemy::preparation_case8(&mobenemy, dart_num, 1, upperlimit_joydispwidth + 50, 0, put_pway, quadratic_curvenum3, green_bul, 20, 240, static_cast<int>(DX_PI / 20), 20, normal_margine);
		bossenemy::preparation_case8(&mobenemy, dart_num, 1, 200 - dartenemy.width / 2, -50, put_pway, quadratic_curvenum4, green_bul, 20, 300, static_cast<int>(DX_PI / 20), 20, normal_margine);
	    bossenemy::preparation_case8(&mobenemy, dart_num, 1, 500 - dartenemy.width / 2, -50, put_pway, quadratic_curvenum5, green_bul, 20, 10, static_cast<int>(DX_PI / 20), 20, normal_margine);
		bossenemy::mobrun(&mobenemy);
		bossenemy::mobenemy_alivecheck(&mobenemy);
		count = 0;
		movestate = 13;
		break;

	case 13:
		reset_ebullethit();
		controling.get_presenceflag(&get_presence);
		bossenemy::mobrun(&mobenemy);
		bossenemy::mobenemy_alivecheck(&mobenemy);
		count++;
		if (count > 1700)	movestate = 14;
		break;

	case 14:
		bossenemy::preparation_case8(&mobenemy, lase_numl, 10, upperlimit_joydispwidth - aplane_enemy.width, -50, left_way, straight_downlsnum, yel_bul, 15, 50, 0, 60, normal_margine);
		bossenemy::preparation_case8(&mobenemy, lase_numr, 10, lowerlimit_joydispwidth + 5, upperlimit_joydispheight + 50, right_way, straight_upnum, yel_bul, 20, 50, 0, 60, normal_margine);
		bossenemy::preparation_case8(&mobenemy, lase_numc, 2, 50 - aplane_enemy.width / 2, 100, down_way, stop_and_gonumr, blue_energybul, 15, 50, 0, 60 + static_cast<unsigned int>(rand2(mt)), normal_margine);
		bossenemy::preparation_case8(&mobenemy, lase_numc, 2, 950 - aplane_enemy.width / 2, 100, down_way, stop_and_gonumr, blue_energybul, 15, 40, 0, 60 + static_cast<unsigned int>(rand2(mt)), normal_margine);
		bossenemy::preparation_case8(&mobenemy, lase_numc, 2, 50 - aplane_enemy.width / 2, 100, down_way, stop_and_gonumr, blue_energybul, 15, 150, 0, 60 + static_cast<unsigned int>(rand2(mt)), normal_margine);
		bossenemy::preparation_case8(&mobenemy, lase_numc, 2, 950 - aplane_enemy.width / 2, 100, down_way, stop_and_gonumr, blue_energybul, 15, 155, 0, 60 + static_cast<unsigned int>(rand2(mt)), normal_margine);
		bossenemy::preparation_case8(&mobenemy, lase_numc, 2, 50 - aplane_enemy.width / 2, 100, down_way, stop_and_gonumr, blue_energybul, 15, 250, 0, 60 + static_cast<unsigned int>(rand2(mt)), normal_margine);
		bossenemy::preparation_case8(&mobenemy, lase_numc, 2, 950 - aplane_enemy.width / 2, 100, down_way, stop_and_gonumr, blue_energybul, 15, 230, 0, 60 + static_cast<unsigned int>(rand2(mt)), normal_margine);
		bossenemy::preparation_case8(&mobenemy, lase_numc, 2, 50 - aplane_enemy.width / 2, 100, down_way, stop_and_gonumr, blue_energybul, 15, 350, 0, 60 + static_cast<unsigned int>(rand2(mt)), normal_margine);
		bossenemy::preparation_case8(&mobenemy, lase_numc, 2, 950 - aplane_enemy.width / 2, 100, down_way, stop_and_gonumr, blue_energybul, 15, 340, 0, 60 + static_cast<unsigned int>(rand2(mt)), normal_margine);
		bossenemy::preparation_case8(&mobenemy, big_num, 4, upperlimit_joydispwidth, lowerlimit_joydispheight + 50, forward_eightway, straight_leftnuml, green_bul, 20, 1000, 0, 200, boss2_margine);
		bossenemy::preparation_case8(&mobenemy, big_num, 4, lowerlimit_joydispwidth - big_enemy.width, lowerlimit_joydispheight + big_enemy.height + 10, forward_eightway, straight_rightnuml, green_bul, 20, 1000, 0, 200, boss2_margine);
		count = 0;
		movestate = 15;
		break;

	case 15:
		reset_ebullethit();
		controling.get_presenceflag(&get_presence);
		bossenemy::mobrun(&mobenemy);
		bossenemy::mobenemy_alivecheck(&mobenemy);
		count++;
		if (count > 4200) {
			movestate = 16;
			controling.pass_bstate(2);
		}
		break;

	case 16:
		reset_ebullethit();
		controling.get_presenceflag(&get_presence);
		bossenemy::preparation_case8(&mobenemy, boss2_num, 1, 500 - boss2.width / 2, lowerlimit_joydispheight - boss2.height, rota_sixteenway, app_straightnum, yel_bul, 900, 50, 0, 60, boss2_margine);
		bossenemy::mobrun(&mobenemy);
		bossenemy::mobenemy_alivecheck(&mobenemy);
		count = 0;
		movestate = 17;
		break;

	case 17:
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