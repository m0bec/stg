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
	x = bossenemy_startpoint_x - width / 2;
	y = bossenemy_startpoint_y;
	movestate = 0;
	direct_pattern = 0;
	memoryangle1 = 0;
	memoryangle2 = 0;
	shotflag1 = 0;
	mt.seed(rnd());
	count = 0;
	ebullethit = false;
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

void bossenemy::move() {
	control &controling = control::getinstance();
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
			//bossenemy::ebullethit_checker(&enemybullet1, bigredbullet);
			//bossenemy::ebullethit_checker(&enemybullet2, bigbluebullet);
		}
		break;

	case 2:
		enemybullet1.erase(enemybullet1.begin(), enemybullet1.end());
		enemybullet1.shrink_to_fit();
		enemybullet2.erase(enemybullet2.begin(), enemybullet2.end());
		enemybullet2.shrink_to_fit();
		goto_center();
		count = 0;
		memoryangle1 = 0.0;
		memoryangle2 = 0.0;
		break;

	case 3:
		reset_ebullethit();
		DrawGraph(static_cast<int>(x), static_cast<int>(y), graph, true);
		miss_player18();
		two_straightaim_shots();
		//lavishhandout_shot2();
		base_lavishhandout_shot(&enemybullet3, 0.0, 2*DX_PI, DX_PI, 4, greenbullet, bulletspeed_4);
		controling.get_presenceflag(&get_presence);
		if (get_presence) {
			//bossenemy::ebullethit_checker(&enemybullet1, blue_energybullet);
			//bossenemy::ebullethit_checker(&enemybullet2, yellow_bullet);
			//bossenemy::ebullethit_checker(&enemybullet3, greenbullet);
		}
		break;
	}		
}

void bossenemy::run() {
	move();
	count++;
}