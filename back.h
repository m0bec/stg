#pragma once
#include "DxLib.h"
#include "structure.h"
#include "define.h"

#define start_point 0

class back {
private:
	basegraph bluebackleft;
	basegraph bluebackright;
	basegraph bluebackup;
	basegraph bluebackdown;
	basegraph blackback;
	

public:
	
	back();
	void firstrun();
	void secondrun();
};

