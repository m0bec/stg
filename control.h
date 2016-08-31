#pragma once
#include "back.h"
#include "ziki.h"
#include "load.h"
#include <memory>

class control {
private:
	std::unique_ptr<back> blue_back;
	std::unique_ptr<ziki> ziki1;
	std::unique_ptr<load> loading;

public:
	control();
	void firstrun();
	void run();
};