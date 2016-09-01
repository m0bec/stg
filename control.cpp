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