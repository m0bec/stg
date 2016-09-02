#include "enemy.h"
#include "control.h"

void bossenemy::straightaim_player() {
	control &controling = control::getinstance();
	double px, py;
	if (count % 60 < 10) {
		controling.get_playerposition(&px, &py);
		enemybullet1.push_back(enemybullet(x + width/2, y + height, atan2(py - (y + height + bigredbullet.height/2), px - (x + width/2))));
	}

	auto itr = enemybullet1.begin();
	while (itr != enemybullet1.end()) {
		itr->x += cos(itr->angle)*bulletspeed_8;
		itr->y += sin(itr->angle)*bulletspeed_8;
		if (itr->y > upperlimit_joydispheight || itr->y < lowerlimit_joydispheight - bigredbullet.height
			|| itr->x > upperlimit_joydispwidth || itr->x < lowerlimit_joydispwidth - bigredbullet.width) {
			itr = enemybullet1.erase(itr);
		}
		else {
			DrawGraph(static_cast<int>(itr->x), static_cast<int>(itr->y), bigredbullet.graph, true);
			itr++;
		}
		
	}
	enemybullet1.shrink_to_fit();
}
