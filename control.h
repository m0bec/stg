#pragma once
#include "back.h"
#include "ziki.h"
#include <memory>

class control {
private:
	std::unique_ptr<back> blue_back;
	std::unique_ptr<ziki> ziki1;

public:
	control();
	void run();
};