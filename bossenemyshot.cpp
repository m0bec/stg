#include "enemy.h"
#include "control.h"

void bossenemy::ebullethit_checker(std::vector<enemybullet> *bullet, base bullettype) {
	control &controling = control::getinstance();
	if (controling.hitcheck(bullet, bullettype)) {
		ebullethit = true;
	}
}

void bossenemy::elaserthit_checker(std::vector<laser> *bullet) {
	control &controling = control::getinstance();
	if (controling.laser_hitcheck(bullet)) {
		ebullethit = true;
	}
}

void bossenemy::reset_ebullethit() {
	ebullethit = false;
}

//3way
void bossenemy::straightaim_player() {
	control &controling = control::getinstance();
	double px, py;
	if (count % 120 < 30 && count % 5 == 0) {
		controling.get_playerposition(&px, &py);
		enemybullet1.push_back(enemybullet(x + width/2 - bigredbullet.width/2, y + height, atan2(py - (y + height + bigredbullet.height/2), px - (x + width/2)), 6));
		enemybullet1.push_back(enemybullet(x + width / 2 - bigredbullet.width / 2, y + height, atan2(py - (y + height + bigredbullet.height / 2), px - (x + width / 2)) + DX_PI / 6, 6));
		enemybullet1.push_back(enemybullet(x + width / 2 - bigredbullet.width / 2, y + height, atan2(py - (y + height + bigredbullet.height / 2), px - (x + width / 2)) - DX_PI / 6, 6));
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
}

//バラマキ
void bossenemy::lavishhandout_shot() {
	std::uniform_real_distribution<> rand15(0.0, 1.5);
	control &controling = control::getinstance();
	double px, py;
	if (count % 120 == 0) {
		controling.get_playerposition(&px, &py);
		memoryangle1 = atan2(py - (y + height + bigbluebullet.height / 2), px - (x + width / 3));
		memoryangle2 = atan2(py - (y + height + bigbluebullet.height / 2), px - (x + 2 * width / 3));
	}
	
	if (count % 120 < 30) {
		controling.get_playerposition(&px, &py);
		enemybullet2.push_back(enemybullet(x + width / 3 - bigbluebullet.width / 2, y + height, memoryangle1 + rand15(mt) - 0.75, 7));
		enemybullet2.push_back(enemybullet(x + 2 * width / 3 -  bigbluebullet.width / 2, y + height, memoryangle2 + rand15(mt) - 0.75, 7));
	}

	auto itr = enemybullet2.begin();
	while (itr != enemybullet2.end()) {
		itr->x += cos(itr->angle)*(bulletspeed_6 - itr->elapsedtime*bulletspeed_down_003);
		itr->y += sin(itr->angle)*(bulletspeed_6 - itr->elapsedtime*bulletspeed_down_003);
		if (itr->y > upperlimit_joydispheight || itr->y < lowerlimit_joydispheight - bigbluebullet.height
			|| itr->x > upperlimit_joydispwidth || itr->x < lowerlimit_joydispwidth - bigbluebullet.width) {
			itr = enemybullet2.erase(itr);
		}
		else {
			DrawGraph(static_cast<int>(itr->x), static_cast<int>(itr->y), bigbluebullet.graph, true);
			if (itr->elapsedtime < 100) {
				itr->elapsedtime += 1;
			}
			else if(count % 20 == 0){
				itr->elapsedtime += 1;
			}
			
			itr++;
		}

	}
}

//自機外し全周18way(enemybullet1 & memoryangle1を使用)
void bossenemy::miss_player18() {
	double px, py;
	if (shotflag1 == 0) {
		control &controling = control::getinstance();
		controling.get_playerposition(&px, &py);
		memoryangle1 = atan2(py - (y + height / 2), px - (x + width / 2));
		shotflag1 = 1;
	}

	if (count % 200 > 0 && count % 200 < 50) { 
		memoryangle1 += 0.005;
	}
	else if (count % 200 > 50 && count % 200 < 100) {
		memoryangle1 -= 0.005;
	}
	else if (count % 200 > 100 && count % 200 < 150) {
		memoryangle1 -= 0.005;
	}
	else if (count % 200 > 150 && count % 200 < 200) {
		memoryangle1 += 0.005;
	}
	
	if (count % 4 == 0) {
		for (int i = 0; i < 18; i++) {
			enemybullet1.push_back(enemybullet(x + width / 2 - blue_energybullet.width / 2, y + height / 2 - blue_energybullet.height / 2, memoryangle1 + i*DX_PI/9, 4));
		}
	}

	auto itr = enemybullet1.begin();
	while (itr != enemybullet1.end()) {
		itr->x += cos(itr->angle)*bulletspeed_8;
		itr->y += sin(itr->angle)*bulletspeed_8;
		if (itr->y > upperlimit_joydispheight || itr->y < lowerlimit_joydispheight - blue_energybullet.height
			|| itr->x > upperlimit_joydispwidth || itr->x < lowerlimit_joydispwidth - blue_energybullet.width) {
			itr = enemybullet1.erase(itr);
		}
		else { 
			DrawGraph(static_cast<int>(itr->x), static_cast<int>(itr->y), blue_energybullet.graph, true);
			itr++;
		}
	}
}

//両サイドから自機狙い(enemybullet2 & memoryangle2 & memoryangle3を使用)
void bossenemy::two_straightaim_shots() {
	if (count % 24 == 1) {
		double px, py;
		control &controling = control::getinstance();
		controling.get_playerposition(&px, &py);
		memoryangle2 = atan2(py - (y + height / 2), px - (x + width / 3));
		memoryangle3 = atan2(py - (y + height / 2), px - (x + 2 * width / 3));
	}

	if (count % 24 < 16 && count % 3 == 1) {
		for (int i = 0; i < bullet_num5; i++) {
			enemybullet2.push_back(enemybullet(x + width / 3 - yellow_bullet.width / 2, y + height / 2 - yellow_bullet.height / 2, memoryangle2, 4));
			enemybullet2.push_back(enemybullet(x + 2 * width / 3 - yellow_bullet.width / 2, y + height / 2 - yellow_bullet.height / 2, memoryangle3, 4));
		}
	}

	auto itr = enemybullet2.begin();
	while (itr != enemybullet2.end()) {
		itr->x += cos(itr->angle)*bulletspeed_8;
		itr->y += sin(itr->angle)*bulletspeed_8;
		if (itr->y > upperlimit_joydispheight || itr->y < lowerlimit_joydispheight - bigredbullet.height
			|| itr->x > upperlimit_joydispwidth || itr->x < lowerlimit_joydispwidth - bigredbullet.width) {
			itr = enemybullet2.erase(itr);
		}
		else {
			DrawGraph(static_cast<int>(itr->x), static_cast<int>(itr->y), yellow_bullet.graph, true);
			itr++;
		}
	}
}

//中央からバラマキ(enemybullet3を使用)
void bossenemy::lavishhandout_shot2() {
	std::uniform_real_distribution<> rand(0.0, 2*DX_PI);
	control &controling = control::getinstance();
	double px, py;
	controling.get_playerposition(&px, &py);

	enemybullet3.push_back(enemybullet(x + width / 2 - greenbullet.width / 2, y + height / 2 - greenbullet.height / 2, atan2(py - (y + height / 2), px - (x + width / 2)) + rand(mt) - DX_PI, 4));

	auto itr = enemybullet3.begin();
	while (itr != enemybullet3.end()) {
		itr->x += cos(itr->angle)*bulletspeed_4;
		itr->y += sin(itr->angle)*bulletspeed_4;
		if (itr->y > upperlimit_joydispheight || itr->y < lowerlimit_joydispheight - bigbluebullet.height
			|| itr->x > upperlimit_joydispwidth || itr->x < lowerlimit_joydispwidth - bigbluebullet.width) {
			itr = enemybullet3.erase(itr);
		}
		else {
			DrawGraph(static_cast<int>(itr->x), static_cast<int>(itr->y), greenbullet.graph, true);
			itr++;
		}

	}
}

//中央からバラマキ
void bossenemy::base_lavishhandout_shot(std::vector<enemybullet> *bullet, double lowrange, double highrange, double centerrange, int hitrange, base bullettype, int bulletspeed) {
	std::uniform_real_distribution<> rand(lowrange, highrange);
	control &controling = control::getinstance();
	double px, py;
	controling.get_playerposition(&px, &py);

	bullet->push_back(enemybullet(x + width / 2 - bullettype.width / 2, y + height / 2 - bullettype.height / 2, atan2(py - (y + height / 2), px - (x + width / 2)) + rand(mt) - centerrange, hitrange));

	auto itr = bullet->begin();
	while (itr != bullet->end()) {
		itr->x += cos(itr->angle)*bulletspeed;
		itr->y += sin(itr->angle)*bulletspeed;
		if (itr->y > upperlimit_joydispheight || itr->y < lowerlimit_joydispheight - bullettype.height
			|| itr->x > upperlimit_joydispwidth || itr->x < lowerlimit_joydispwidth - bullettype.width) {
			itr = bullet->erase(itr);
		}
		else {
			DrawGraph(static_cast<int>(itr->x), static_cast<int>(itr->y), bullettype.graph, true);
			itr++;
		}

	}
}

void bossenemy::laser_aimplayer(std::vector<laser> *laserbeam, base *laserbase) {
	control &controling = control::getinstance();
	double px, py;
	controling.get_playerposition(&px, &py);

	if (direct_pattern == 2) {
		laserbeam->push_back(laser(x + width / 3, y + height / 2, x + width / 3 - laserbase[0].width/2, y + height / 2, atan2(py - (y + height / 2), px - (x + width / 3)) - DX_PI/4.0, laserbase[0].width, laserbase[0].height));
		laserbeam->push_back(laser(x + 2 * width / 3 - laserbase[0].width / 2, y + height / 2, x + 2 * width / 3, y + height / 2, atan2(py - (y + height / 2), px - (x + 2 * width / 3)) + DX_PI / 4.0 + DX_PI, laserbase[0].width, laserbase[0].height));
		direct_pattern = 3;
	}

	auto itr = laserbeam->begin();
	while (itr != laserbeam->end()) {
		if (lasercount < 15) {
			SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
			DrawRotaGraph2(itr->x + laserbase[0].width / 2, itr->y, laserbase[0].width / 2, 0, 1.0, itr->angle, laserbase[0].graph, TRUE, FALSE);
			DrawRotaGraph2(itr->x + laserbase[0].width / 2, itr->y , laserbase[0].width / 2, 0, 1.0, itr->angle, laserbase[0].graph, TRUE, FALSE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
		else if (lasercount < 20) {
			SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
			DrawRotaGraph2(itr->x + laserbase[1].width / 2, itr->y , laserbase[1].width / 2, 0, 1.0, itr->angle, laserbase[1].graph, TRUE, FALSE);
			DrawRotaGraph2(itr->x + laserbase[1].width / 2, itr->y , laserbase[1].width / 2, 0, 1.0, itr->angle, laserbase[1].graph, TRUE, FALSE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
		else if (lasercount < 25) {
			SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
			DrawRotaGraph2(itr->x + laserbase[2].width / 2, itr->y , laserbase[2].width / 2, 0, 1.0, itr->angle, laserbase[2].graph, TRUE, FALSE);
			DrawRotaGraph2(itr->x + laserbase[2].width / 2, itr->y , laserbase[2].width / 2, 0, 1.0, itr->angle, laserbase[2].graph, TRUE, FALSE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
		else if (lasercount < 30) {
			SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
			DrawRotaGraph2(itr->x + laserbase[3].width / 2, itr->y, laserbase[3].width / 2, 0, 1.0, itr->angle, laserbase[3].graph, TRUE, FALSE);
			DrawRotaGraph2(itr->x + laserbase[3].width / 2, itr->y , laserbase[3].width / 2, 0, 1.0, itr->angle, laserbase[3].graph, TRUE, FALSE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
		else {
			SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
			DrawRotaGraph2(itr->x + laserbase[4].width / 2, itr->y , laserbase[4].width / 2, 0, 1.0, itr->angle, laserbase[4].graph, TRUE, FALSE);
			DrawRotaGraph2(itr->x + laserbase[4].width / 2, itr->y , laserbase[4].width / 2, 0, 1.0, itr->angle, laserbase[4].graph, TRUE, FALSE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
		
		if (lasercount > 200) {
			direct_pattern = 0;
			lasercount = 0;
		}
		lasercount += 1;
		itr++;
	}
	

}