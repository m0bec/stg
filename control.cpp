#include "control.h"

control::control() {
	blue_back.reset(new back);
	ziki1.reset(new ziki);
}

void control::run() {
	blue_back->run();
}