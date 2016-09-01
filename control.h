#pragma once
#include "back.h"
#include "ziki.h"
#include "load.h"
#include "enemy.h"
#include <memory>

class control {
private:
	std::unique_ptr<back> background;
	std::unique_ptr<ziki> ziki1;
	std::unique_ptr<load> loading;
	std::unique_ptr<bossenemy> boss;

public:
	control();
	void firstrun();
	void run();
};