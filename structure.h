#pragma once
#include <math.h>
#include <array>
#include "DxLib.h"

struct base {
	int graph;
	int width;
	int height;
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

struct laser_vertex {
	double x;
	double y;
	double r;
};

struct laser {
	laser(double anotherx, double anothery, double anotherangle, int width, int height) {
		x = anotherx;
		y = anothery;
		angle = anotherangle;
		elapsedtime = 0;
		vertex[0].x = x;
		vertex[0].y = y;
		vertex[1].x = x + width*sin(DX_PI / 2 - anotherangle);
		vertex[1].y = y - height*cos(DX_PI / 2 - anotherangle);
		vertex[3].x = x + height*sin(anotherangle);
		vertex[3].y = y + height*cos(anotherangle);
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