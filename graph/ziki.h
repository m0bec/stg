#ifndef DEF_ZIKI_H

#define DEF_ZIKI_H
#define SHOT_NUM 40
#define E_SHOT_NUM 100
#define E_SHOT_NUM2 300
#define X_CUT 80
#define Y_CUT 80
#define X_CUT_NUM 11
#define Y_CUT_NUM 12
#define AREA 132
#define AREA_NUM 1000
#define ZIKI_START_Y 900



void ZikiController();
void ZikiShot();
void ZikiCore();
int Ziki_S_hit();

struct ZIKI {
	int x;
	int y;
	int width;
	int height;
	int graph;
	int graphL;
	int graphR;
	int direct_flag;
	bool flag;
	double hit_range;
};

struct Core {
	double x;
	double y;
	int graph;
	int width;
	int height;
};


struct SHOT {
	bool flag;
	double x;
	double y;
	int graph;
	int width;
	int	height;
	int shot_count;
};


struct E_SHOT {
	bool flag;
	double x;
	double y;
	double center_x;
	double center_y;
	int graph;
	int width;
	int height;
	double direct_x;
	double direct_y;
	double direct;
	double ang;
	int time_flag;
	double hit_range;
};

extern int disp_width_f;
extern int disp_height_f;
extern int disp_width_s;
extern int disp_height_s;

extern ZIKI Ziki;
extern Core ziki_core;
extern SHOT ziki_shot[SHOT_NUM];
extern E_SHOT Enemy1_shot1[E_SHOT_NUM];
extern int E1_S1_placenum[AREA_NUM];
extern E_SHOT E1_S2[E_SHOT_NUM2];
extern int E1_S2_placenum[AREA_NUM];
extern int count;
extern int damage_count;
extern int ziki_shot_graph;
extern int Ziki_place[9];
extern int z_hitcount;
extern int key;
#endif
