#pragma once

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
	enemybullet(double anotherx, double anothery, double anotherangle) {
		x = anotherx;
		y = anothery;
		angle = anotherangle;
	}
	double x;
	double y;
	double angle;
};