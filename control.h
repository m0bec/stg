#pragma once
#include "back.h"
#include "ziki.h"
#include "load.h"
#include "enemy.h"

#include <memory>

class control {
private:
	control();
	std::unique_ptr<back> background;
	std::unique_ptr<ziki> ziki1;
	std::unique_ptr<load> loading;
	std::unique_ptr<bossenemy> boss;

public:
	static control& getinstance() {
		static control singleton_control;
		return singleton_control;
	}
	void get_enemyposition(double *ex, double *ey, int *ewidtn, int *eheight);
	void get_playerposition(double *x, double *y);
	bool hitcheck(std::vector<enemybullet> *bullet, base bullettype);
	void get_presenceflag(bool *flag);
	void calculation_enemyhp();
	void player_lifecheck();
	void firstrun();
	void run();
};