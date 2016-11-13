#include "enemy.h"
#include "control.h"

void bossenemy::mobrun(std::list<enemy_element> *mob) {
	if (mobenemy.size() != 0) {
		auto itr = mob->begin();
		while (itr != mob->end()) {
			if (itr->time == 0) {
				//bossenemy::mobenemy_alivecheck(&mobenemy);
				bossenemy::allocation_enemygraph(itr);
				bossenemy::allocation_enemymove(itr);
				if(itr->shotflag)	bossenemy::mobenemy_shottypecheck(itr);
				itr->pass_time += 1;
			}
			else {
				itr->time -= 1;
			}

			bossenemy::pre_flag_judge(itr);
			++itr;
		}
		bossenemy::bullet_move();
		
		if (get_presence) {
			bossenemy::body_hitcheck(&mobenemy);
			bossenemy::mobbul_hitcheck(&mobbullet1, str_bullettype);
		}
	}
	bossenemy::effect_cont();
}

void bossenemy::mobbul_hitcheck(std::list<mobbullet> *bullet, base bullettype) {
	control &controling = control::getinstance();
	
	if (controling.mobbullet_hitchecker(bullet, bullettype)) {
		ebullethit = true;
	}
	
}

void bossenemy::body_hitcheck(std::list<enemy_element> *mobe) {
	control &controling = control::getinstance();
	if (get_presence) {
		if (controling.body_hitcheck2(mobe)) {
			ebullethit = true;
		}
	}
}

//widとheightの代入
void bossenemy::preparation_case8(std::list<enemy_element> *mob, int numenemy, unsigned int enemynum, double anx, double any, int anbulletnum, int anmovenum, int anbullettype, int anhp, unsigned int atime, int rollspeed, unsigned int inter, int marg) {
	int wid, heigh, margine;
	unsigned int input_time;
	switch (numenemy) {
	case 0:
		wid = dartenemy.width;
		heigh = dartenemy.height;
		margine = normal_margine;
		break;
		
	case 1:
		wid = aplane_enemy.width;
		heigh = aplane_enemy.height;
		margine = normal_margine;
		break;

	case 2:
		wid = lase_enemyl.width;
		heigh = lase_enemyl.height;
		margine = normal_margine;
		break;

	case 3:
		wid = lase_enemyr.width;
		heigh = lase_enemyr.height;
		margine = normal_margine;
		break;

	case 4:
		wid = lase_enemy.width;
		heigh = lase_enemy.height;
		margine = normal_margine;
		break;

	case 5:
		wid = big_enemy.width;
		heigh = big_enemy.height;
		margine = boss2_margine;
		break;

	case 6:
		wid = boss2.width;
		heigh = boss2.height;
		margine = boss2_margine;
		break;
	}

	while (enemynum != 0) {
		input_time = 0 + (enemynum-1)*inter;
		mob->push_back(enemy_element(anx, any, wid, heigh, numenemy, anbulletnum, anmovenum, anbullettype, anhp, atime + input_time, rollspeed, inter, false, margine));
		enemynum -= 1;
	}
}

void bossenemy::mobenemy_alivecheck(std::list<enemy_element> *mob) {
	auto itr = mob->begin();
	while (itr != mob->end()) {
		if (itr->y > upperlimit_joydispheight || itr->y < lowerlimit_joydispheight - itr->height
			|| itr->x > upperlimit_joydispwidth || itr->x < lowerlimit_joydispwidth - itr->width) {
			if (!itr->pre_flag) {
				itr->hp = itr->origin_hp;
			}
		}

		if(itr->hp <= 0){
			if (itr->pre_flag) {
				effects.push_back(effect(0, itr->x + itr->width / 2 - explosion_effect_width / 2, itr->y + itr->height / 2 - explosion_effect_height / 2));
				PlaySoundMem(explosion_sound, DX_PLAYTYPE_BACK);
				str_point += 150;
				itr = mob->erase(itr);
			}
			else {
				++itr;
			}
		}
		else if (itr->y > upperlimit_joydispheight || itr->y < lowerlimit_joydispheight - itr->height
			|| itr->x > upperlimit_joydispwidth || itr->x < lowerlimit_joydispwidth -  itr->width) {
			if (itr->pre_flag) {
				itr = mob->erase(itr);
			}
			else {
				++itr;
			}
		}
		else {
			++itr;
		}
	}
}

//graphの割り当て
void bossenemy::allocation_enemygraph(std::list<enemy_element>::iterator iterate) {
		switch (iterate->graphnum) {
		case 0:
			DrawRotaGraph(static_cast<int>(iterate->x), static_cast<int>(iterate->y), 1.0, DX_PI/5*iterate->pass_time, dartenemy.graph, true, false);
			break;

		case 1:
			DrawGraph(static_cast<int>(iterate->x), static_cast<int>(iterate->y), aplane_enemy.graph, true);
			break;

		case 2:
			DrawGraph(static_cast<int>(iterate->x), static_cast<int>(iterate->y), lase_enemyl.graph, true);
			break;

		case 3:
			DrawGraph(static_cast<int>(iterate->x), static_cast<int>(iterate->y), lase_enemyr.graph, true);
			break;

		case 4:
			DrawGraph(static_cast<int>(iterate->x), static_cast<int>(iterate->y), lase_enemy.graph, true);
			break;

		case 5:
			DrawGraph(static_cast<int>(iterate->x), static_cast<int>(iterate->y), big_enemy.graph, true);
			break;

		case 6:
			DrawGraph(static_cast<int>(iterate->x), static_cast<int>(iterate->y), boss2.graph, true);
			break;
		}
}

void bossenemy::allocation_enemyshot(std::list<enemy_element>::iterator iterate) {
	mobenemy_shottypecheck(iterate);
}

void bossenemy::pre_flag_judge(std::list<enemy_element>::iterator itr) {
	if (itr->y < upperlimit_joydispheight && itr->y > lowerlimit_joydispheight - itr->height
		&& itr->x < upperlimit_joydispwidth && itr->x > lowerlimit_joydispwidth - itr->width) {
		itr->pre_flag = true;
	}
}

void bossenemy::allocation_enemybul(int bullettype, base *bul) {
	switch (bullettype) {
	case 0:
		*bul = bigredbullet;
		break;

	case 1:
		*bul = big_yellow;
		break;

	case 2:
		*bul = blue_energybullet;
		break;

	case 3:
		*bul = yellow_bullet;
		break;

	case 4:
		*bul = greenbullet;
		break;

	case 5:
		*bul = bluericebullet;
		break;

	case 6:
		*bul = redbullet;
		break;

	case 7:
		*bul = lightblue_bullet;
		break;

	case 8:
		*bul = purplebullet;
		break;

	case 9:
		*bul = grassgreen_bullet;
		break;

	case 10:
		*bul = bigred_bullet;
		break;
	}
}

void bossenemy::mobenemy_shottypecheck(std::list<enemy_element>::iterator iterate) {
	base str;
	allocation_enemybul(iterate->bullettype, &str);
	control &controling = control::getinstance();
	std::uniform_real_distribution<> rand(0, 2 * DX_PI);
	std::uniform_real_distribution<> rand2(0, 2 * DX_PI);
	if (iterate->y < upperlimit_joydispheight && iterate->y > lowerlimit_joydispheight - iterate->height
		&& iterate->x < upperlimit_joydispwidth && iterate->x > lowerlimit_joydispwidth - iterate->width) {
		switch (iterate->bulletnum) {
			double px, py;
			//3way
		case 0:
			if (iterate->pass_time % 120 < 30 && iterate->pass_time % 5 == 0) {
				controling.get_playerposition(&px, &py);
				mobbullet1.push_back(mobbullet(iterate->x + iterate->width / 2 - str.width / 2, iterate->y + iterate->height / 2 - str.height / 2, atan2(py - (iterate->y + iterate->height / 2 - str.height / 2), px - (iterate->x + iterate->width / 2 - str.width / 2)), str.range, 6, iterate->bulletnum, iterate->bullettype, str, 0));
				mobbullet1.push_back(mobbullet(iterate->x + iterate->width / 2 - str.width / 2, iterate->y + iterate->height / 2 - str.height / 2, atan2(py - (iterate->y + iterate->height / 2 - str.height / 2), px - (iterate->x + iterate->width / 2 - str.width / 2)) + DX_PI / 6, str.range, 6, iterate->bulletnum, iterate->bullettype, str, 0));
				mobbullet1.push_back(mobbullet(iterate->x + iterate->width / 2 - str.width / 2, iterate->y + iterate->height / 2 - bigredbullet.height / 2, atan2(py - (iterate->y + iterate->height / 2 - bigredbullet.height / 2), px - (iterate->x + iterate->width / 2 - bigredbullet.width / 2)) - DX_PI / 6, str.range, 6, iterate->bulletnum, iterate->bullettype, str, 0));
			}
			break;

			//自機外し
		case 1:
			if (iterate->pass_time % 400 < 360 && iterate->pass_time % 5 == 0) {
				controling.get_playerposition(&px, &py);
				mobbullet1.push_back(mobbullet(iterate->x + iterate->width / 2 - str.width / 2, iterate->y + iterate->height / 2 - str.height / 2, atan2(py - (iterate->y + iterate->height / 2 - str.height / 2), px - (iterate->x + iterate->width / 2 - str.width / 2)) + DX_PI / 12, str.range, 6, iterate->bulletnum, iterate->bullettype, str, 0));
				mobbullet1.push_back(mobbullet(iterate->x + iterate->width / 2 - str.width / 2, iterate->y + iterate->height / 2 - str.height / 2, atan2(py - (iterate->y + iterate->height / 2 - str.height / 2), px - (iterate->x + iterate->width / 2 - str.width / 2)) - DX_PI / 12, str.range, 6, iterate->bulletnum, iterate->bullettype, str, 0));
			}
			break;

			//全周16wayショット
		case 2:
			if (iterate->pass_time % 30 == 0) {
				for (int i = 0; i < 16; i++) {
					mobbullet1.push_back(mobbullet(iterate->x + iterate->width / 2 - str.width / 2, iterate->y + iterate->height / 2 - str.height / 2, i * 2 * DX_PI / 16, str.range, 0, iterate->bulletnum, iterate->bullettype, str, 0));
				}
			}
			break;

			//全周囲バラマキ
		case 3:
			mobbullet1.push_back(mobbullet(iterate->x + iterate->width / 2 - str.width / 2, iterate->y + iterate->height / 2 - str.height / 2, rand(mt), str.range, 0, iterate->bulletnum, iterate->bullettype, str, 0));
			break;

			//設置自機狙い
		case 4:
			if (iterate->pass_time % 2 == 0) {
				mobbullet1.push_back(mobbullet(iterate->x + iterate->width / 2 - str.width / 2, iterate->y + iterate->height / 2 - str.height / 2, 0, str.range, 0, iterate->bulletnum, iterate->bullettype, str, 0));
			}
			break;

			//右に飛ぶ弾
		case 5:
			if (iterate->pass_time % 4 == 0 && iterate->pass_time % 120 < 90) {
				mobbullet1.push_back(mobbullet(iterate->x + iterate->width / 2 - str.width / 2, iterate->y + iterate->height / 2 - str.height / 2, 0, str.range, 0, iterate->bulletnum, iterate->bullettype, str, 0));
			}
			break;

			//左に飛ぶ弾
		case 6:
			if (iterate->pass_time % 4 == 0 && iterate->pass_time % 120 < 90) {
				mobbullet1.push_back(mobbullet(iterate->x + iterate->width / 2 - str.width / 2, iterate->y + iterate->height / 2 - str.height / 2, 0, str.range, 0, iterate->bulletnum, iterate->bullettype, str, 0));
			}
			break;

			//下に落下する弾
		case 7:
			if (iterate->pass_time % 4 == 0 && iterate->pass_time % 60 < 40) {
				mobbullet1.push_back(mobbullet(iterate->x + iterate->width / 2 - str.width / 2, iterate->y + iterate->height / 2 - str.height / 2, 0, str.range, 0, iterate->bulletnum, iterate->bullettype, str, 0));
			}
			break;

			//前方4way+4way
		case 8:
			if (iterate->pass_time % 20 == 0) {
				for (int i = 0; i < 4; i++) {
					mobbullet1.push_back(mobbullet(iterate->x + 2 * iterate->width / 3 - str.width / 2, iterate->y + iterate->height / 2 - str.height / 2, i * DX_PI / 8, str.range, 0, iterate->bulletnum, iterate->bullettype, str, 0));
					mobbullet1.push_back(mobbullet(iterate->x + iterate->width / 3 - str.width / 2, iterate->y + iterate->height / 2 - str.height / 2, i * DX_PI / 8 + DX_PI / 2, str.range, 0, iterate->bulletnum, iterate->bullettype, str, 0));
				}
			}
			break;

			//boss2用
		case 9:
			if (iterate->pass_time % 12 == 0) {
				for (int i = 0; i < 16; i++) {
					mobbullet1.push_back(mobbullet(iterate->x + iterate->width / 2 - str.width / 2, iterate->y + iterate->height / 2 - str.height / 2, i * 2 * DX_PI / 16 + iterate->pass_time * DX_PI / (343 * 7), str.range, 1, iterate->bulletnum, iterate->bullettype, str, 0));
					mobbullet1.push_back(mobbullet(iterate->x + iterate->width / 2 - str.width / 2, iterate->y + iterate->height / 2 - str.height / 2, i * 2 * DX_PI / 16 - iterate->pass_time * DX_PI / (343 * 7), str.range, -1, iterate->bulletnum, iterate->bullettype, str, 0));
				}
			}

			if (iterate->hp < 600) {
				boss2_switch1(iterate);
				str_point += 1500;
			}
			break;

		case 10:
			if (iterate->pass_time % 300 == 0) {
				preparation_case8(&mobenemy, dart_num, 1, iterate->x + iterate->width / 2 + dartenemy.width / 2, iterate->y + iterate->height / 2 - dartenemy.height / 2, bullet_line, aim_num, green_bul, 10, 10, 0, 30, normal_margine);
			}
			if (iterate->pass_time % 6 == 0) {
				for (int i = 0; i < 8; i++) {
					mobbullet1.push_back(mobbullet(iterate->x + iterate->width / 2 - str.width / 2, iterate->y + iterate->height / 2 - str.height / 2, i * 2 * DX_PI / 8 + 2 * iterate->pass_time * DX_PI / (343 * 7), str.range, 0, iterate->bulletnum, iterate->bullettype, str, 0));
				}
			}

			if (iterate->hp < 300) {
				boss2_switch2(iterate);
				str_point += 1700;
			}
			break;

		case 11:
			if (iterate->pass_time % 6 == 0) {
				mobbullet1.push_back(mobbullet(iterate->x + iterate->width / 2 - str.width / 2, iterate->y + iterate->height / 2 - str.height / 2, 0, str.range, 0, iterate->bulletnum, iterate->bullettype, str, 0));
			}
			if (iterate->pass_time > 600) {
				iterate->x = 0;
				iterate->y = 0;
			}
			break;

			//全周左
		case 12:
			if (iterate->pass_time % 10 == 0) {
				for (int i = 0; i < 23; i++) {
					mobbullet1.push_back(mobbullet(iterate->x + iterate->width / 2 - str.width / 2, iterate->y + iterate->height / 2 - str.height / 2, i * 2 * DX_PI / 23 + atan2(py - (iterate->y + iterate->height / 2 - str.height / 2), px - (iterate->x + iterate->width / 2 - str.width / 2)), str.range, 1, iterate->bulletnum, iterate->bullettype, str, 0));
				}
			}

			if (iterate->pass_time % 30 == 0) {
				mobbullet1.push_back(mobbullet(iterate->x + iterate->width / 2 - big_yellow.width / 2, iterate->y + iterate->height / 2 - big_yellow.height / 2, 0, big_yellow.range, 0, 13, big_yellowbul, big_yellow, 0));
			}

			if (iterate->pass_time % 1000 == 200) {
				iterate->bulletnum = 14;
				iterate->bullettype = grassgreen_num;
			}
			break;

			//使わない
		case 13:
			for (int i = 0; i < 12; i++) {
				mobbullet1.push_back(mobbullet(iterate->x + iterate->width / 2 - str.width / 2 + 100 * cos(i * DX_PI / 11), iterate->y + iterate->height / 2 - str.height / 2 + 100 * sin(i * DX_PI / 11), 0, str.range, 3, iterate->bulletnum, iterate->bullettype, str, 0));
			}
			iterate->bulletnum = 14;
			iterate->bullettype = grassgreen_num;
			break;

			//自機外し
		case 14:
			if (iterate->pass_time % 1000 > 200 && iterate->pass_time % 60 < 20 && iterate->pass_time % 5 == 0) {
				controling.get_playerposition(&px, &py);
				mobbullet1.push_back(mobbullet(iterate->x + iterate->width / 2 - str.width / 2, iterate->y + iterate->height / 2 - str.height / 2, atan2(py - (iterate->y + iterate->height / 2 - str.height / 2), px - (iterate->x + iterate->width / 2 - str.width / 2)) + DX_PI / 12, str.range, 6, iterate->bulletnum, iterate->bullettype, str, 0));
				mobbullet1.push_back(mobbullet(iterate->x + iterate->width / 2 - str.width / 2, iterate->y + iterate->height / 2 - str.height / 2, atan2(py - (iterate->y + iterate->height / 2 - str.height / 2), px - (iterate->x + iterate->width / 2 - str.width / 2)) - DX_PI / 12, str.range, 6, iterate->bulletnum, iterate->bullettype, str, 0));
			}

			if (iterate->pass_time % 30 == 0) {
				mobbullet1.push_back(mobbullet(iterate->x + iterate->width / 2 - big_yellow.width / 2, iterate->y + iterate->height / 2 - big_yellow.height / 2, 0, big_yellow.range, 0, 13, big_yellowbul, big_yellow, 0));
			}

			if (iterate->pass_time % 1000 == 400) {
				iterate->bulletnum = 15;
				iterate->bullettype = lightblue_num;
			}
			break;

			//全周右
		case 15:
			if (iterate->pass_time % 10 == 0) {
				for (int i = 0; i < 23; i++) {
					mobbullet1.push_back(mobbullet(iterate->x + iterate->width / 2 - str.width / 2, iterate->y + iterate->height / 2 - str.height / 2, i * 2 * DX_PI / 23 + atan2(py - (iterate->y + iterate->height / 2 - str.height / 2), px - (iterate->x + iterate->width / 2 - str.width / 2)), str.range, 2, iterate->bulletnum, iterate->bullettype, str, 0));
				}
			}

			if (iterate->pass_time % 30 == 0) {
				mobbullet1.push_back(mobbullet(iterate->x + iterate->width / 2 - big_yellow.width / 2, iterate->y + iterate->height / 2 - big_yellow.height / 2, 0, big_yellow.range, 0, 13, big_yellowbul, big_yellow, 0));
			}

			if (iterate->pass_time % 1000 == 600) {
				iterate->bulletnum = 17;
				iterate->bullettype = grassgreen_num;
			}
			break;
			//使わない
		case 16:
			for (int i = 0; i < 12; i++) {
				mobbullet1.push_back(mobbullet(iterate->x + iterate->width / 2 - str.width / 2 + 100 * cos(i * DX_PI / 11), iterate->y + iterate->height / 2 - str.height / 2 + 100 * sin(i * DX_PI / 11), 0, str.range, 3, iterate->bulletnum, iterate->bullettype, str, 0));
			}
			iterate->bulletnum = 17;
			iterate->bullettype = grassgreen_num;
			break;

			//自機外し
		case 17:
			if (iterate->pass_time % 60 < 20 && iterate->pass_time % 5 == 0) {
				controling.get_playerposition(&px, &py);
				mobbullet1.push_back(mobbullet(iterate->x + iterate->width / 2 - str.width / 2, iterate->y + iterate->height / 2 - str.height / 2, atan2(py - (iterate->y + iterate->height / 2 - str.height / 2), px - (iterate->x + iterate->width / 2 - str.width / 2)) + DX_PI / 12, str.range, 6, iterate->bulletnum, iterate->bullettype, str, 0));
				mobbullet1.push_back(mobbullet(iterate->x + iterate->width / 2 - str.width / 2, iterate->y + iterate->height / 2 - str.height / 2, atan2(py - (iterate->y + iterate->height / 2 - str.height / 2), px - (iterate->x + iterate->width / 2 - str.width / 2)) - DX_PI / 12, str.range, 6, iterate->bulletnum, iterate->bullettype, str, 0));
			}

			if (iterate->pass_time % 30 == 0) {
				mobbullet1.push_back(mobbullet(iterate->x + iterate->width / 2 - big_yellow.width / 2, iterate->y + iterate->height / 2 - big_yellow.height / 2, 0, big_yellow.range, 0, 13, big_yellowbul, big_yellow, 0));
			}

			if (iterate->pass_time % 1000 == 0) {
				iterate->bulletnum = 12;
				iterate->bullettype = lightblue_num;
			}
			break;
		}
	}
}

void bossenemy::bullet_move() {
	double px, py;
	control &controling = control::getinstance();
	std::uniform_real_distribution<> rand(0,DX_PI/16);
	auto itr = mobbullet1.begin();
	while (itr != mobbullet1.end()) {
		switch (itr->bullettag) {
		case 0:
			itr->x += cos(itr->angle)*bulletspeed_6;
			itr->y += sin(itr->angle)*bulletspeed_6;
			if (itr->y > upperlimit_joydispheight || itr->y < lowerlimit_joydispheight - itr->bul.height
				|| itr->x > upperlimit_joydispwidth || itr->x < lowerlimit_joydispwidth - itr->bul.width) {
				itr = mobbullet1.erase(itr);
			}
			else {
				DrawGraph(static_cast<int>(itr->x), static_cast<int>(itr->y), itr->bul.graph, true);
				itr++;
			}
			break;

		case 1:
			itr->x += cos(itr->angle)*bulletspeed_6;
			itr->y += sin(itr->angle)*bulletspeed_6;
			if (itr->y > upperlimit_joydispheight || itr->y < lowerlimit_joydispheight - itr->bul.height
				|| itr->x > upperlimit_joydispwidth || itr->x < lowerlimit_joydispwidth - itr->bul.width) {
				itr = mobbullet1.erase(itr);
			}
			else {
				DrawGraph(static_cast<int>(itr->x), static_cast<int>(itr->y), itr->bul.graph, true);
				itr++;
			}
			break;

		case 2:
			itr->x += cos(itr->angle)*bulletspeed_5;
			itr->y += sin(itr->angle)*bulletspeed_5;
			if (itr->y > upperlimit_joydispheight || itr->y < lowerlimit_joydispheight - itr->bul.height
				|| itr->x > upperlimit_joydispwidth || itr->x < lowerlimit_joydispwidth - itr->bul.width) {
				itr = mobbullet1.erase(itr);
			}
			else {
				DrawGraph(static_cast<int>(itr->x), static_cast<int>(itr->y), itr->bul.graph, true);
				itr++;
			}
			break;

		case 3:
			itr->x += cos(itr->angle)*bulletspeed_5;
			itr->y += sin(itr->angle)*bulletspeed_5;
			if (itr->y > upperlimit_joydispheight || itr->y < lowerlimit_joydispheight - itr->bul.height
				|| itr->x > upperlimit_joydispwidth || itr->x < lowerlimit_joydispwidth - itr->bul.width) {
				itr = mobbullet1.erase(itr);
			}
			else {
				DrawGraph(static_cast<int>(itr->x), static_cast<int>(itr->y), itr->bul.graph, true);
				itr++;
			}
			break;

		case 4:
			itr->elapsedtime++;
			if(itr->elapsedtime == 60){
				controling.get_playerposition(&px, &py);
				itr->angle = atan2(py - (itr->y + itr->bul.height / 2), px - (itr->x + itr->bul.width / 2));
			}
			else if (itr->elapsedtime > 60 && itr->elapsedtime < 80) {
				itr->x += cos(itr->angle)*bulletspeed_8*sin(DX_PI/(2*20) * itr->elapsedtime);
				itr->y += sin(itr->angle)*bulletspeed_8*sin(DX_PI / (2 * 20) * itr->elapsedtime);
			}
			else if (itr->elapsedtime >= 81) {
				itr->x += cos(itr->angle)*bulletspeed_8;
				itr->y += sin(itr->angle)*bulletspeed_8;
			}

			if (itr->y > upperlimit_joydispheight || itr->y < lowerlimit_joydispheight - itr->bul.height
				|| itr->x > upperlimit_joydispwidth || itr->x < lowerlimit_joydispwidth - itr->bul.width) {
				itr = mobbullet1.erase(itr);
			}
			else {
				DrawGraph(static_cast<int>(itr->x), static_cast<int>(itr->y), itr->bul.graph, true);
				itr++;
			}
			break;

		case 5:
			itr->x += bulletspeed_6;
			if (itr->y > upperlimit_joydispheight || itr->y < lowerlimit_joydispheight - itr->bul.height
				|| itr->x > upperlimit_joydispwidth || itr->x < lowerlimit_joydispwidth - itr->bul.width) {
				itr = mobbullet1.erase(itr);
			}
			else {
				DrawGraph(static_cast<int>(itr->x), static_cast<int>(itr->y), itr->bul.graph, true);
				itr++;
			}
			break;

		case 6:
			itr->x -= bulletspeed_6;
			if (itr->y > upperlimit_joydispheight || itr->y < lowerlimit_joydispheight - itr->bul.height
				|| itr->x > upperlimit_joydispwidth || itr->x < lowerlimit_joydispwidth - itr->bul.width) {
				itr = mobbullet1.erase(itr);
			}
			else {
				DrawGraph(static_cast<int>(itr->x), static_cast<int>(itr->y), itr->bul.graph, true);
				itr++;
			}
			break;

		case 7:
			itr->elapsedtime++;
			if (itr->elapsedtime > 60) {
				itr->y += bulletspeed_6;
				if (itr->y > upperlimit_joydispheight || itr->y < lowerlimit_joydispheight - itr->bul.height
					|| itr->x > upperlimit_joydispwidth || itr->x < lowerlimit_joydispwidth - itr->bul.width) {
					itr = mobbullet1.erase(itr);
				}
				else {
					DrawGraph(static_cast<int>(itr->x), static_cast<int>(itr->y), itr->bul.graph, true);
					++itr;
				}
			}
			else {
				++itr;
			}
			break;

		case 8:
			itr->x += cos(itr->angle)*bulletspeed_6;
			itr->y += sin(itr->angle)*bulletspeed_6;
			if (itr->y > upperlimit_joydispheight || itr->y < lowerlimit_joydispheight - itr->bul.height
				|| itr->x > upperlimit_joydispwidth || itr->x < lowerlimit_joydispwidth - itr->bul.width) {
				itr = mobbullet1.erase(itr);
			}
			else {
				DrawGraph(static_cast<int>(itr->x), static_cast<int>(itr->y), itr->bul.graph, true);
				itr++;
			}
			break;

		case 9:
			itr->elapsedtime += 1;
			if (itr->rota == 1) {
				itr->x += cos(itr->angle)*10;
				itr->y += sin(itr->angle)*10;
				itr->angle += 0.008;
				if (itr->y > upperlimit_joydispheight || itr->y < lowerlimit_joydispheight - itr->bul.height
					|| itr->x > upperlimit_joydispwidth || itr->x < lowerlimit_joydispwidth - itr->bul.width) {
					itr = mobbullet1.erase(itr);
				}
				else {
					DrawGraph(static_cast<int>(itr->x), static_cast<int>(itr->y), itr->bul.graph, true);
					itr++;
				}
			}
			else {
				itr->x += cos(itr->angle)*10;
				itr->y += sin(itr->angle)*10;
				itr->angle -= 0.008;
				if (itr->y > upperlimit_joydispheight || itr->y < lowerlimit_joydispheight - itr->bul.height
					|| itr->x > upperlimit_joydispwidth || itr->x < lowerlimit_joydispwidth - itr->bul.width) {
					itr = mobbullet1.erase(itr);
				}
				else {
					DrawGraph(static_cast<int>(itr->x), static_cast<int>(itr->y), itr->bul.graph, true);
					itr++;
				}
			}
			break;

		case 10:
			itr->elapsedtime += 1;
			itr->x += cos(itr->angle) * 10;
			itr->y += sin(itr->angle) * 10;
			itr->angle += 0.008;

			if (itr->y > upperlimit_joydispheight || itr->y < lowerlimit_joydispheight - itr->bul.height
				|| itr->x > upperlimit_joydispwidth || itr->x < lowerlimit_joydispwidth - itr->bul.width) {
				itr = mobbullet1.erase(itr);
			}
			else {
				DrawGraph(static_cast<int>(itr->x), static_cast<int>(itr->y), itr->bul.graph, true);
				itr++;
			}
			break;

		case 11:
			itr->elapsedtime += 1;
			if (itr->elapsedtime == 300) {
				itr = mobbullet1.erase(itr);
			}

			if (itr->y > upperlimit_joydispheight || itr->y < lowerlimit_joydispheight - itr->bul.height
				|| itr->x > upperlimit_joydispwidth || itr->x < lowerlimit_joydispwidth - itr->bul.width) {
				itr = mobbullet1.erase(itr);
			}
			else {
				DrawGraph(static_cast<int>(itr->x), static_cast<int>(itr->y), itr->bul.graph, true);
				itr++;
			}
			break;

		case 12:
			itr->elapsedtime += 1;
			itr->x += cos(itr->angle) * bulletspeed_6;
			itr->y += sin(itr->angle) * bulletspeed_6;
			itr->angle += 0.005;
			if (itr->y > upperlimit_joydispheight || itr->y < lowerlimit_joydispheight - itr->bul.height
				|| itr->x > upperlimit_joydispwidth || itr->x < lowerlimit_joydispwidth - itr->bul.width) {
				itr = mobbullet1.erase(itr);
			}
			else {
				DrawGraph(static_cast<int>(itr->x), static_cast<int>(itr->y), itr->bul.graph, true);
				itr++;
			}
			break;

		case 13:
			itr->elapsedtime += 1;
			if (itr->elapsedtime % 60 == 30) {
				controling.get_playerposition(&px, &py);
				itr->angle =  atan2(py - (itr->y + itr->bul.height), px - (itr->x + itr->bul.width)) + rand(mt) - DX_PI / 32;

			}

			if (itr->elapsedtime % 60 < 30) {
				itr->x += cos(itr->angle) * bulletspeed_3;
				itr->y += sin(itr->angle) * bulletspeed_3;
			}

			if (itr->elapsedtime > 300) {
				itr->bul = bigred_bullet;
			}
			if (itr->elapsedtime > 400) {
				for (int i = 0; i < 5; i++) {
					controling.get_playerposition(&px, &py);
					mobbullet1.push_back(mobbullet((itr->x + itr->bul.width / 2 - greenbullet.width / 2), (itr->y + itr->bul.height / 2 - greenbullet.height / 2), atan2(py - (itr->y + itr->bul.height / 2), px - (itr->x + itr->bul.width / 2)) + i * 2 * DX_PI / 5, itr->bul.range, 0, 18, green_bul, greenbullet, 0));
				}
				itr->x = 0;
				itr->y = 0;
			}

			if (itr->y > upperlimit_joydispheight || itr->y < lowerlimit_joydispheight - itr->bul.height
				|| itr->x > upperlimit_joydispwidth || itr->x < lowerlimit_joydispwidth - itr->bul.width) {
				itr = mobbullet1.erase(itr);
			}
			else {
				DrawGraph(static_cast<int>(itr->x), static_cast<int>(itr->y), itr->bul.graph, true);
				itr++;
			}
			break;

		case 14:
			itr->x += cos(itr->angle)*bulletspeed_6;
			itr->y += sin(itr->angle)*bulletspeed_6;
			if (itr->y > upperlimit_joydispheight || itr->y < lowerlimit_joydispheight - itr->bul.height
				|| itr->x > upperlimit_joydispwidth || itr->x < lowerlimit_joydispwidth - itr->bul.width) {
				itr = mobbullet1.erase(itr);
			}
			else {
				DrawGraph(static_cast<int>(itr->x), static_cast<int>(itr->y), itr->bul.graph, true);
				itr++;
			}
			break;

		case 15:
			itr->elapsedtime += 1;
			itr->x += cos(itr->angle) * bulletspeed_6;
			itr->y += sin(itr->angle) * bulletspeed_6;
			itr->angle -= 0.005;
			if (itr->y > upperlimit_joydispheight || itr->y < lowerlimit_joydispheight - itr->bul.height
				|| itr->x > upperlimit_joydispwidth || itr->x < lowerlimit_joydispwidth - itr->bul.width) {
				itr = mobbullet1.erase(itr);
			}
			else {
				DrawGraph(static_cast<int>(itr->x), static_cast<int>(itr->y), itr->bul.graph, true);
				itr++;
			}
			break;

		case 16:
			itr->elapsedtime += 1;
			if (itr->elapsedtime % 60 == 30) {
				controling.get_playerposition(&px, &py);
				itr->angle = atan2(py - (itr->y + itr->bul.height), px - (itr->x + itr->bul.width)) + rand(mt) - DX_PI / 32;

			}

			if (itr->elapsedtime % 60 < 30) {
				itr->x += cos(itr->angle) * bulletspeed_2;
				itr->y += sin(itr->angle) * bulletspeed_2;
			}

			if (itr->elapsedtime == 200) {
				itr->bullettype = big_rednum;
			}
			else if (itr->elapsedtime > 400) {
				for (int i = 0; i < 5; i++) {
					mobbullet1.push_back(mobbullet((itr->x + itr->bul.width / 2 - greenbullet.width / 2) + 10 * cos(i * 2 * DX_PI / 5), (itr->y + itr->bul.height / 2 - greenbullet.height / 2) * sin(i * 2 * DX_PI / 5), i * 2 * DX_PI / 5, itr->bul.range, 0, 18, green_bul, greenbullet, 0));
				}
				itr->x = 0;
				itr->y = 0;
			}

			if (itr->y > upperlimit_joydispheight || itr->y < lowerlimit_joydispheight - itr->bul.height
				|| itr->x > upperlimit_joydispwidth || itr->x < lowerlimit_joydispwidth - itr->bul.width) {
				itr = mobbullet1.erase(itr);
			}
			else {
				DrawGraph(static_cast<int>(itr->x), static_cast<int>(itr->y), itr->bul.graph, true);
				itr++;
			}
			break;

		case 17:
			itr->x += cos(itr->angle)*bulletspeed_6;
			itr->y += sin(itr->angle)*bulletspeed_6;
			if (itr->y > upperlimit_joydispheight || itr->y < lowerlimit_joydispheight - itr->bul.height
				|| itr->x > upperlimit_joydispwidth || itr->x < lowerlimit_joydispwidth - itr->bul.width) {
				itr = mobbullet1.erase(itr);
			}
			else {
				DrawGraph(static_cast<int>(itr->x), static_cast<int>(itr->y), itr->bul.graph, true);
				itr++;
			}
			break;

		case 18:
			itr->elapsedtime += 1;
			itr->x += cos(itr->angle)*bulletspeed_5;
			itr->y += sin(itr->angle)*bulletspeed_5;
			if (itr->y > upperlimit_joydispheight || itr->y < lowerlimit_joydispheight - itr->bul.height
				|| itr->x > upperlimit_joydispwidth || itr->x < lowerlimit_joydispwidth - itr->bul.width) {
				itr = mobbullet1.erase(itr);
			}
			else {
				DrawGraph(static_cast<int>(itr->x), static_cast<int>(itr->y), itr->bul.graph, true);
				itr++;
			}
			break;
		}
	}
}

void bossenemy::boss2_switch1(std::list<enemy_element>::iterator iterate) {
	iterate->bulletnum = rota_sixteenway2;
	iterate->movenum = stop2_num;
	iterate->bullettype = green_bul;
}

void bossenemy::boss2_switch2(std::list<enemy_element>::iterator iterate) {
	iterate->bulletnum = boss2_lastshot;
	iterate->movenum = slide_num;
	iterate->bullettype = lightblue_num;
}

void bossenemy::get_mobplace(std::list<enemy_element> *iterate) {
	iterate = &mobenemy;
}




