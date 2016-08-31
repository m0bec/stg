#include "control.h"

control::control() {
	blue_back.reset(new back);
	ziki1.reset(new ziki);
	loading.reset(new load);
}

void control::firstrun() {
	ziki1->pass_load(loading->ziki1graph_pass(), loading->ziki1width_pass(), loading->ziki1height_pass());
}
void control::run() {
	blue_back->run();
	ziki1->run();
}