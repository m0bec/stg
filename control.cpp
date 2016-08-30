#include "control.h"

control::control() {
	blue_back.reset(new back);
}

void control::run() {
	blue_back->run();
}