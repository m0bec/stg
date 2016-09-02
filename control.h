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
	void get_enemyposition(double *x, double *y);
	void get_playerposition(double *x, double *y);
	void firstrun();
	void run();
};