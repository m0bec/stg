#include "enemy.h"
#include "ziki.h"
#include "system.h"

void bossenemy::first_set() {
	x = bossenemy_startpoint_x - width / 2;
	y = bossenemy_startpoint_y;
	movestate = 0;
	direct_pattern = 0;
	direct_pattern2 = 0;
	roop_count = 0;
	memoryangle1 = 0;
	memoryangle2 = 0;
	memoryx = 0.0;
	memoryy = 0.0;
	memory_xspeed = 0.0;
	memory_yspeed = 0.0;
	directx = 0.0;
	directy = 0.0;
	directx_flag = 0;
	directy_flag = 0;
	shotflag1 = 0;
	mt.seed(rnd());
	count = 0;
	bulletcount = 0;
	lasercount = 0;
	bullet_directcount = 0;
	ebullethit = false;
	str_mflag = true;
	mobbullet1.clear();
	mobenemy.clear();
	enemybullet1.clear();
	enemybullet2.clear();
	enemybullet3.clear();
	laserbeam1.clear();
	spinbullet1.clear();
	spinbullet2.clear();
	center1.clear();
	mobbullet1.clear();
	effects.clear();
	mobenemy.push_back(enemy_element(upperlimit_joydispwidth + 200, upperlimit_joydispheight + 200, 0, 0, 99, 99, 99, 99, 99, 99, 0, 0, true, 0));
}

void ziki::first_p() {
	x = lowerlimit_joydispwidth + (upperlimit_joydispwidth - lowerlimit_joydispwidth) / 2 - width / 2;
	y = ziki_startposition;
	presenceflag = true;
	lifeflag = true;
	gameover_flag = false;
	lifepoint = 10;
	count = 0;
	invincibletime_counter = 0;
	sortiecounter = 0;
	shotpoint = 0;
	grazepoint = 0;
	grase_count = 0;
	graze_stock = 0;
	bomb_count = 0;
	bomb_flag = false;
	zikibullet.clear();
	effects.flag = false;
	effects.count = 0;

}

void systemm::first_p() {
	arrowy = 512 - startgr.height;
	arrowflag = 0;
	state = 0;
	music_time = 0;
	score1 = 0;
	score2 = 0;
	music_flag = 0;
	gameover = false;
	str_keyflag = true;
}