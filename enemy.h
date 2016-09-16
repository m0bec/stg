#pragma once
#include "DxLib.h"
#include "define.h"
#include "structure.h"
#include <vector>
#include <math.h>
#include <random>
#include <array>
#define number1 0.0
#define number2 1.5

class bossenemy {
private:
	std::random_device rnd;
	std::mt19937 mt;
	double x;
	double y;
	int graph;
	int width;
	int height;
	int hp;
	int movestate;
	int roop_count;
	int direct_pattern;
	int direct_pattern2;
	int directx_flag;
	int directy_flag;
	double directx;
	double directy;
	double memoryx;
	double memoryy;
	double memory_xspeed;
	double memory_yspeed;
	unsigned int count;
	unsigned int lasercount;
	base bigredbullet;
	base bigbluebullet;
	base blue_energybullet;
	base yellow_bullet;
	base greenbullet;
	base laserbeam[5];
	base bluericebullet;
	std::vector<enemybullet> enemybullet1;
	std::vector<enemybullet> enemybullet2;
	std::vector<enemybullet> enemybullet3;
	std::vector<laser> laserbeam1;
	std::vector<rotabullet> spinbullet1;
	std::vector<rotabullet> spinbullet2;
	double memoryangle1;
	double memoryangle2;
	double memoryangle3;
	int shotflag1;
	bool ebullethit;
	bool get_presence;
public:
	bossenemy();
	void set_enemyhp(int enemyhp);
	void enemy_damage_counter();
	void elaserthit_checker(std::vector<laser> *bullet);
	void espinbullet_hitchecker(std::vector<rotabullet> *bullet, base bullettype);
	void getposition(double *ex, double *ey, int *ewidth, int *eheight);
	void base_lavishhandout_shot(std::vector<enemybullet> *bullet, double lowrange, double highrange, double centerrange, int hitrange, base bullettype, int bulletspeed);
	bool ebullethit_pass();
	void reset_ebullethit();
	void goto_center();
	void approach();
	void move();
	void startmove();
	void straightaim_player();
	void lavishhandout_shot();
	void miss_player18();
	void two_straightaim_shots();
	void lavishhandout_shot2();
	void straight_intersection_shot();
	void ebullethit_checker(std::vector<enemybullet> *bullet, base bullettype);
	void laser_aimplayer(std::vector<laser> *laserbeam, base *laserbase);
	void roundtrip_move();
	void run();
};