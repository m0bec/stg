#include "control.h"

control::control() {
	background.reset(new back);
	ziki1.reset(new ziki);
	loading.reset(new load);
	boss.reset(new bossenemy);
}

void control::firstrun() {
	
}
void control::run() {
	background->firstrun();
	ziki1->run();
	boss->run();
	background->secondrun();
}

void control::get_playerposition(double *centerx, double *centery) {
	double tempx, tempy;

	ziki1->getposition(&tempx, &tempy);

	*centerx = tempx;
	*centery = tempy;
}

void control::get_enemyposition(double *centerx, double *centery) {
	double tempx, tempy;

	boss->getposition(&tempx, &tempy);

	*centerx = tempx;
	*centery = tempy;
}