#pragma once
#include <math.h>
#include <array>
#include "DxLib.h"

struct base {
	int graph;
	int width;
	int height;
	int range;
};

struct basegraph {
	int graph;
	int x;
	int y;
};

struct bullet {
	bullet(double anotherx, double anothery, bool flag) {
		x = anotherx;
		y = anothery;
		presenceflag = flag;
	}
	double x;
	double y;
	bool presenceflag;
};

struct enemybullet {
	enemybullet(double anotherx, double anothery, double anotherangle, double baserange) {
		x = anotherx;
		y = anothery;
		angle = anotherangle;
		elapsedtime = 0;
		range = baserange;
	}
	double x;
	double y;
	double angle;
	unsigned int elapsedtime;
	double range;
};

struct rotabullet {
	rotabullet(double anotherx, double anothery, double anotherangle, double baserange, double anotherrota) {
		x = anotherx;
		y = anothery;
		angle = anotherangle;
		elapsedtime = 0;
		range = baserange;
		rota = anotherrota;
	}
	double x;
	double y;
	double angle;
	unsigned int elapsedtime;
	double range;
	double rota;
};

struct mobbullet {
	mobbullet(double ax, double ay, double aangle, double arange, double arota, int tag, int abullettype) {
		x = ax;
		y = ay;
		angle = aangle;
		elapsedtime = 0;
		range = arange;
		rota = arota;
		bullettag = tag;
		bullettype = abullettype;
	}
	double x;
	double y;
	double angle;
	unsigned int elapsedtime;
	double range;
	double rota;
	int bullettag;
	int bullettype;
};

struct laser_vertex {
	double x;
	double y;
	double r;
};

struct laser {//startx, startyÇÕâÒì]Ç…íÜêSç¿ïW
	laser(double startx, double starty, double anotherx, double anothery, double anotherangle, int width, int height) {
		x = anotherx;
		y = anothery;
		angle = anotherangle;
		elapsedtime = 0;
		vertex[0].x = (x - startx)*cos(angle) - (y - starty)*sin(angle) + startx;
		vertex[0].y = (x - startx)*sin(angle) + (y - starty)*cos(angle) + starty;
		vertex[1].x = (x + width - startx)*cos(angle) - (y - starty)*sin(angle) + startx;
		vertex[1].y = (x + width - startx)*sin(angle) + (y - starty)*cos(angle) + starty;
		vertex[3].x = (x - startx)*cos(angle) - (y + height - starty)*sin(angle) + startx;
		vertex[3].y = (x - startx)*sin(angle) + (y + height - starty)*cos(angle) + starty;
		vertex[2].x = vertex[1].x + vertex[3].x;
		vertex[2].y = vertex[1].y + vertex[3].y;
		for (int i = 0; i < 4; i++) {
			vertex[i].r = 0.0;
		}
	}
	double x;
	double y;
	double angle;
	unsigned int elapsedtime;
	std::array<laser_vertex, 4> vertex;
};

struct vec {
	double x;
	double y;
	double length;
};

struct dis {
	double distance;	
	int num;
};

struct spining_center {
	spining_center(double acx, double acy, double ax, double ay, double aangle, double aspinangle, int arange) {
		cx = acx;
		cy = acy;
		x = ax;
		y = ay;
		angle = aangle;
		spinangle = aspinangle;
		range = arange;
		count = 0;
	}
	double cx;
	double cy;
	double x;
	double y;
	double angle;
	double spinangle;
	int range;
	unsigned int count;
};

//bullettypeÇÕíeÇÃéÌóﬁ,bulletnumÇÕíeÇÃãOìπÇÃéÌóﬁ
struct enemy_element {
	enemy_element(double anx, double any, int anwidth, int anheight, int angraphnum, int anbulletnum, int anmovenum, int anbullettype, int anhp, unsigned int atime, int arollingspeed, unsigned int interval, bool aflag) {
		x = anx;
		originx = anx;
		y = any;
		originy = any;
		width = anwidth;
		height = anheight;
		graphnum = angraphnum;
		bulletnum = anbulletnum;
		movenum = anmovenum;
		bullettype = anbullettype;
		hp = anhp;
		origin_hp = anhp;
		time = atime;
		rollingspeed = arollingspeed;
		pass_time = 0;
		interval_time = interval;
		shotflag = aflag;
	}
	double x;
	double y;
	double originx;
	double originy;
	int width;
	int height;
	int graphnum;
	int bulletnum;
	int movenum;
	int bullettype;
	int hp;
	int origin_hp;
	int rollingspeed;
	unsigned int time;
	unsigned int pass_time;
	unsigned int interval_time;
	bool shotflag;
	
};

struct enemytype {
	int graph;
	int width;
	int height;
};