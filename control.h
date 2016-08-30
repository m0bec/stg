#pragma once
#include "back.h"
#include <memory>

class control {
private:
	std::unique_ptr<back> blue_back;

public:
	control();
	void run();
};