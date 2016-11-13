#pragma once
#include "back.h"
#include "ziki.h"
#include "load.h"
#include "enemy.h"
#include "system.h"
#include <math.h>
#include <memory>

class control {
private:
	control();
	std::unique_ptr<back> background;
	std::unique_ptr<ziki> ziki1;
	std::unique_ptr<load> loading;
	
	std::unique_ptr<systemm> sys;
	int state;
	unsigned int point;
	unsigned int str_point;
	unsigned int graze;
	unsigned int graze_stock;
	bool bomb_flag;
	bool str_flag;
	int zanki;
	base are;

public:
	static control& getinstance() {
		static control singleton_control;
		return singleton_control;
	}
	std::unique_ptr<bossenemy> boss;
	void get_enemyposition(double *ex, double *ey, int *ewidtn, int *eheight);
	void get_playerposition(double *x, double *y);
	bool hitcheck(std::list<enemybullet> *bullet, base bullettype);
	bool laser_hitcheck(std::list<laser> *bullet);
	bool body_hitcheck(int wid, int heigh, int margin, double potisionx, double positiony);
	bool body_hitcheck2(std::list<enemy_element> *mobe);
	bool spining_center_hitcheck(std::list<spining_center> *bullet, base bullettype);
	bool spinbullet_hitchecker(std::list<rotabullet> *bullet, base bullettype);
	bool mobbullet_hitchecker(std::list<mobbullet> *bullet, base bullettype);
	void get_presenceflag(bool *flag);
	void get_mobposition(std::list<enemy_element> *mob_);
	void calculation_enemyhp();
	void player_lifecheck();
	int pass_zanki();
	int pass_state();
	void get_point();
	void get_graze();
	void get_ziki(int *zik);
	void first_p();
	void get_bombflag();
	void firstrun();
	void run();
	void pass_bombflag(bool *flag);
	void pass_bstate(int sta);
	void pass_musicfla(int fla);
	void finish();		
	void get_epoint();
};