#pragma once
#include "DxLib.h"
#include "define.h"
#include "structure.h"
#include <vector>
#include <math.h>
#include <random>
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
	int direct_pattern;
	unsigned int count;
	base bigredbullet;
	base bigbluebullet;
	base blue_energybullet;
	base yellow_bullet;
	base greenbullet;
	std::vector<enemybullet> enemybullet1;
	std::vector<enemybullet> enemybullet2;
	std::vector<enemybullet> enemybullet3;
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
	void getposition(double *ex, double *ey, int *ewidth, int *eheight);
	void base_lavishhandout_shot(std::vector<enemybullet> *bullet, double lowrange, double highrange, double centerrange, int hitrange, base bullettype, int bulletspeed);
	bool ebullethit_pass();
	void reset_ebullethit();
	void goto_center();
	void move();
	void startmove();
	void straightaim_player();
	void lavishhandout_shot();
	void miss_player18();
	void two_straightaim_shots();
	void lavishhandout_shot2();
	void ebullethit_checker(std::vector<enemybullet> *bullet, base bullettype);
	void roundtrip_move();
	void run();
};