#pragma once
#include "Dxlib.h"
#include "define.h"
#include "structure.h"
#include <math.h>

class systemm {
private:
	base startdisp;
	base gameoverdisp;
	base startgr;
	base quitgr;
	base arrow1;
	base stop_graph;
	base stop_continue;
	base stop_escape;
	base score_backgraph;
	base clear_word;
	base score_plate;
	base enegy_w;
	base graze_w;
	base highscore_w;
	base lifep_w;
	base sco_w;
	std::array<base, 10> scorenum;
	std::array<base, 26> word;
	int arrowy;
	int arrowflag;
	int input_joypad;
	int state;
	int kurame_music;
	int boss1_music;
	int dotyu_music;
	int boss2_music;

	unsigned int music_time;
	unsigned int score1;
	unsigned int score2;
	unsigned int grazen;
	unsigned int gage_color1;
	unsigned int gage_color2;
	unsigned int gage_color3;
	unsigned int gage_color4;
	unsigned int stop_count;
	bool gameover;
	base icon;
	char str_score[10][11];
	unsigned int str_scorenum[10];
	std::array<std::string, 10> strin;
	int music_flag;
	
	bool str_keyflag;
	bool str_keyflag_a;

public:
	systemm();
	void drawstartmenue();
	void stop_menue();
	void movearrow(int flag);
	void startgraphrun();
	void checkkey();
	void music();
	void music2();
	int pass_state();
	void scoredisp(unsigned int score);
	void grasedisp(unsigned int gnum);
	void gage(unsigned int stock);
	void zanki_disp(int zanki);
	void p_state(int pas);
	void first_p();
	void save_score(unsigned int score);
	void instal_score();
	void disp_highscore();
	void disp_gameover();
	void allscore_disp(unsigned int sco);
	void stop_music();
	void stop_run();

	int& set_musicflag();
	bool& set_str_keyflag();
	int& set_state();

	void set_word();
	void clear_graph();
};

