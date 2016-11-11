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
	std::array<int, 25> explosion_gr;
	
	base bigredbullet;
	base bigbluebullet;
	base blue_energybullet;
	base yellow_bullet;
	base big_yellow;
	base greenbullet;
	base laserbeam[5];
	base bluericebullet;
	base redbullet;
	base purplebullet;
	base lightblue_bullet;
	base grassgreen_bullet;
	base bigred_bullet;
	std::list<enemybullet> enemybullet1;
	std::list<enemybullet> enemybullet2;
	std::list<enemybullet> enemybullet3;
	std::list<laser> laserbeam1;
	std::list<rotabullet> spinbullet1;
	std::list<rotabullet> spinbullet2;
	std::list<spining_center> center1;
	std::list<mobbullet> mobbullet1;
	
	double memoryangle1;
	double memoryangle2;
	double memoryangle3;
	int shotflag1;
	bool ebullethit;
	bool get_presence;

	//mobenemy
	
	enemytype dartenemy;
	enemytype aplane_enemy;
	enemytype lase_enemy;
	enemytype lase_enemyr;
	enemytype lase_enemyl;
	enemytype big_enemy;
	enemytype boss2;
	base str_bullettype;

	void set_explosion_gr();

public:
	bossenemy();
	std::list<enemy_element> mobenemy;
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
	void mobrun(std::list<enemy_element> *mob);
	void allocation_enemygraph(std::list<enemy_element>::iterator iterate);
	void allocation_enemymove(std::list<enemy_element>::iterator iterate);
	void allocation_enemyshot(std::list<enemy_element>::iterator iterate);
	void allocation_enemybul(int bullettype, base *bul);
	void straight_down(std::list<enemy_element>::iterator itrate);
	void preparation_case8(std::list<enemy_element> *mob, int numenemy, unsigned int enemynum, double anx, double any, int anbulletnum, int anmovenum, int anbullettype, int anhp, unsigned int atime, int rollspeed, unsigned int inter, int margine);
	void mobenemy_alivecheck(std::list<enemy_element> *mob);
	void mobenemy_shottypecheck(std::list<enemy_element>::iterator iterate);
	void mobbul_hitcheck(std::list<mobbullet> *bullet, base bullettype);
	void get_mobplace(std::list<enemy_element> *iterate);
	void pre_flag_judge(std::list<enemy_element>::iterator iterate);
	void boss2_switch1(std::list<enemy_element>::iterator iterate);
	void boss2_switch2(std::list<enemy_element>::iterator iterate);

	void straight_left(std::list<enemy_element>::iterator itr);
	void straight_right(std::list<enemy_element>::iterator itr);
	void straight_leftl(std::list<enemy_element>::iterator itr);
	void straight_rightl(std::list<enemy_element>::iterator itr);
	void straight_downls(std::list<enemy_element>::iterator itrate);
	void quadratic_curve(std::list<enemy_element>::iterator itr);
	void quadratic_curve1(std::list<enemy_element>::iterator itr);
	void quadratic_curve2(std::list<enemy_element>::iterator itr);
	void quadratic_curve3(std::list<enemy_element>::iterator itr);
	void quadratic_curve4(std::list<enemy_element>::iterator itr);
	void quadratic_curve5(std::list<enemy_element>::iterator itr);
	void quadratic_curve6(std::list<enemy_element>::iterator itr);
	void quadratic_curve7(std::list<enemy_element>::iterator itr);
	void quadratic_curve8(std::list<enemy_element>::iterator itr);
	void quadratic_curve9(std::list<enemy_element>::iterator itr);
	void straight_up(std::list<enemy_element>::iterator itr);
	void stop_and_go1(std::list<enemy_element>::iterator itr);
	void stop_and_go2(std::list<enemy_element>::iterator itr);
	void stop_and_go3(std::list<enemy_element>::iterator itr);
	void app_straight(std::list<enemy_element>::iterator itr);
	void stop(std::list<enemy_element>::iterator itr);
	void aim(std::list<enemy_element>::iterator itr);
	void stop2(std::list<enemy_element>::iterator itr);
	void slide_move(std::list<enemy_element>::iterator itr);
	void body_hitcheck(std::list<enemy_element> *mobe);
	void bullet_move();
	void first_set();
};

class mob {

};

