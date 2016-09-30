#pragma once
#include "DxLib.h"
#include "define.h"
#include "structure.h"
#include <list>
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
	int size;
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
	unsigned int bullet_directcount;
	unsigned int bulletcount;
	
	base bigredbullet;
	base bigbluebullet;
	base blue_energybullet;
	base yellow_bullet;
	base greenbullet;
	base laserbeam[5];
	base bluericebullet;
	std::list<enemybullet> enemybullet1;
	std::list<enemybullet> enemybullet2;
	std::list<enemybullet> enemybullet3;
	std::list<laser> laserbeam1;
	std::list<rotabullet> spinbullet1;
	std::list<rotabullet> spinbullet2;
	std::list<spining_center> center1;
	
	double memoryangle1;
	double memoryangle2;
	double memoryangle3;
	int shotflag1;
	bool ebullethit;
	bool get_presence;

	//mobenemy
	std::list<enemy_element> mobenemy;
	enemytype dartenemy;
public:
	bossenemy();
	void set_enemyhp(int enemyhp);
	void enemy_damage_counter();
	void elaserthit_checker(std::list<laser> *bullet);
	void espinbullet_hitchecker(std::list<rotabullet> *bullet, base bullettype);
	void espining_center_hitchecker(std::list<spining_center> *bullet, base bullettype);
	void getposition(double *ex, double *ey, int *ewidth, int *eheight);
	void base_lavishhandout_shot(std::list<enemybullet> *bullet, double lowrange, double highrange, double centerrange, int hitrange, base bullettype, int bulletspeed);
	bool ebullethit_pass();
	void reset_ebullethit();
	void goto_center();
	void approach();
	void move();
	void startmove();
	void straightmove();
	void straightaim_player();
	void lavishhandout_shot();
	void miss_player18();
	void two_straightaim_shots();
	void lavishhandout_shot2();
	void straight_intersection_shot();
	void ebullethit_checker(std::list<enemybullet> *bullet, base bullettype);
	void laser_aimplayer(std::list<laser> *laserbeam, base *laserbase);
	void enemybody_hitcheck(int wid, int heigh, int margin, double positionx, double positiony);
	void circlemovebullet();
	void roundtrip_move();
	void run();

	//mobenemy
	void allocation_enemygraph(std::list<enemy_element> *mob);
	void allocation_enemymove(std::list<enemy_element> *mob);
	void straight_down(double x);
};

