#include "system.h"
#include "control.h"
#include <fstream>
#include <string>

systemm::systemm() {
	stop_graph.graph = LoadGraph("graph/haikei.png");
	score_backgraph.graph = LoadGraph("graph/haikei_score.png");
	stop_continue.graph = LoadGraph("graph/continue.png");
	GetGraphSize(stop_continue.graph, &stop_continue.width, &stop_continue.height);
	stop_escape.graph = LoadGraph("graph/escape2.png");
	GetGraphSize(stop_escape.graph, &stop_escape.width, &stop_escape.height);
	startdisp.graph = LoadGraph("graph/startdisp.png");
	GetGraphSize(startdisp.graph, &startdisp.width, &startdisp.height);
	gameoverdisp.graph = LoadGraph("graph/gameover.png");
	startgr.graph = LoadGraph("graph/selectstart.png");
	GetGraphSize(startgr.graph, &startgr.width, &startgr.height);
	quitgr.graph = LoadGraph("graph/escape.png");
	GetGraphSize(quitgr.graph, &quitgr.width, &quitgr.width);
	arrow1.graph = LoadGraph("graph/yazi.png");
	GetGraphSize(arrow1.graph, &arrow1.width, &arrow1.height);
	scorenum[0].graph = LoadGraph("graph/number0.png");
	GetGraphSize(scorenum[0].graph, &scorenum[0].width, &scorenum[0].height);
	scorenum[1].graph = LoadGraph("graph/number1.png");
	GetGraphSize(scorenum[1].graph, &scorenum[1].width, &scorenum[1].height);
	scorenum[2].graph = LoadGraph("graph/number2.png");
	GetGraphSize(scorenum[2].graph, &scorenum[2].width, &scorenum[2].height);
	scorenum[3].graph = LoadGraph("graph/number3.png");
	GetGraphSize(scorenum[3].graph, &scorenum[3].width, &scorenum[3].height);
	scorenum[4].graph = LoadGraph("graph/number4.png");
	GetGraphSize(scorenum[4].graph, &scorenum[4].width, &scorenum[4].height);
	scorenum[5].graph = LoadGraph("graph/number5.png");
	GetGraphSize(scorenum[5].graph, &scorenum[5].width, &scorenum[5].height);
	scorenum[6].graph = LoadGraph("graph/number6.png");
	GetGraphSize(scorenum[6].graph, &scorenum[6].width, &scorenum[6].height);
	scorenum[7].graph = LoadGraph("graph/number7.png");
	GetGraphSize(scorenum[7].graph, &scorenum[7].width, &scorenum[7].height);
	scorenum[8].graph = LoadGraph("graph/number8.png");
	GetGraphSize(scorenum[8].graph, &scorenum[8].width, &scorenum[8].height);
	scorenum[9].graph = LoadGraph("graph/number9.png");
	GetGraphSize(scorenum[9].graph, &scorenum[9].width, &scorenum[9].height);
	icon.graph = LoadGraph("graph/zanki.png");
	GetGraphSize(icon.graph, &icon.width, &icon.width);
	set_word();


	kurame_music = LoadSoundMem("music/KURAME_NO_BGM.ogg");
	ChangeVolumeSoundMem(255 * 80 / 100, kurame_music);
	boss1_music = LoadSoundMem("music/bgm_boss1.ogg");
	boss2_music = LoadSoundMem("music/bgm_boss2.ogg");
	dotyu_music = LoadSoundMem("music/bgm_doutyu.ogg");
	
	arrowy = 512 - startgr.height;
	arrowflag = 0;
	state = 0;
	music_time = 0;
	score1 = 0;
	score2 = 0;
	music_flag = 0;
	stop_count = 0;
	gameover = false;
	str_keyflag = false;
	str_keyflag_a = false;


	gage_color1 = GetColor(23, 96, 16);
	gage_color2 = GetColor(59, 241, 41);
	gage_color3 = GetColor(248, 110, 114);
	gage_color4 = GetColor(0, 0, 0);
}

void systemm::drawstartmenue() {
	DrawGraph(0, 0, startdisp.graph, false);
	DrawGraph(500, 512 - startgr.height, startgr.graph, true);
	DrawGraph(500, 512, quitgr.graph, true);
	DrawGraph(500 - arrow1.width, arrowy, arrow1.graph, true);
}

void systemm::movearrow(int arrowflag) {
	switch (arrowflag) {
	case 0:
		arrowy = 512 - startgr.height;
		break;
	case 1:
		arrowy = 512;
		break;
	}
}

void systemm::checkkey() {
	input_joypad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (!(input_joypad & PAD_INPUT_1))	str_keyflag = true;
	if (input_joypad & PAD_INPUT_UP)	arrowflag = 0;
	if (input_joypad & PAD_INPUT_DOWN)	arrowflag = 1;
	if (str_keyflag) {
		if (input_joypad & PAD_INPUT_1) {
			if (arrowflag == 0) {
				StopSoundMem(kurame_music);
				state = 1;
				music_flag = 1;
				str_keyflag = false;
			}
			else if (arrowflag = 1) {
				state = 99;
			}
		}
	}
}

void systemm::music() {
	if (music_time % (14*60 + 45) == 0) {
		PlaySoundMem(kurame_music, DX_PLAYTYPE_BACK);
		music_time = 0;
	}
	++music_time;
}

void systemm::music2() {
	switch (music_flag) {
	case 0:
		break;

	case 1:
		PlaySoundMem(boss1_music, DX_PLAYTYPE_LOOP);
		music_flag = 0;
		break;

	case 2:
		StopSoundMem(boss1_music);
		PlaySoundMem(dotyu_music, DX_PLAYTYPE_LOOP);
		music_flag = 0;
		break;

	case 3:
		StopSoundMem(dotyu_music);
		PlaySoundMem(boss2_music, DX_PLAYTYPE_LOOP);
		music_flag = 0;
		break;

	case 4:
		StopSoundMem(boss2_music);
		music_flag = 0;
		break;

	case 5:
		PlaySoundMem(kurame_music, DX_PLAYTYPE_LOOP);
		music_flag = 0;
		break;
	}
}

void systemm::stop_music() {
	StopSoundMem(kurame_music);
	StopSoundMem(boss1_music);
	StopSoundMem(boss2_music);
	StopSoundMem(dotyu_music);
}

void systemm::startgraphrun() {
	systemm::checkkey();
	systemm::movearrow(arrowflag);
	systemm::drawstartmenue();
	//systemm::music2();
	//systemm::music();
}

void systemm::disp_gameover() {
	input_joypad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	DrawGraph(0, 0, gameoverdisp.graph, false);
	if (!(input_joypad & PAD_INPUT_1))	str_keyflag = true;
	if (str_keyflag) {
		if (input_joypad & PAD_INPUT_1) {
			str_keyflag = false;
			stop_count = 0;
			state = 4;
		}
	}

}

int systemm::pass_state() {
	return state;
}

void systemm::p_state(int pas) {
	state = pas;
}

void systemm::scoredisp(unsigned int point) {
	score1 = point;
	int number;
	int drawx = upperlimit_width - scorenum[0].width - 50;
	for (int i = 0; i < 10; i++) {
		number = score1 % 10;
		score1 = score1 / 10;
		DrawGraph(drawx,50, scorenum[number].graph, true);
		drawx = drawx - scorenum[0].width;
	}
}

void systemm::disp_highscore() {
	unsigned int number;
	unsigned int str_high = str_scorenum[0];
	int drawx = upperlimit_width - scorenum[0].width - 50;
	for (int i = 0; i < 10; i++) {
		number = str_high % 10;
		str_high = str_high / 10;
		DrawGraph(drawx, 10, scorenum[number].graph, true);
		drawx = drawx - scorenum[0].width;
	}
}

void systemm::allscore_disp() {
	input_joypad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (!(input_joypad & PAD_INPUT_1))	str_keyflag = true;
	DrawGraph(0, 0, score_backgraph.graph, false);

	unsigned int number;
	unsigned int str_high;
	int drawx;
	for (int j = 0; j < 10; j++) {
		str_high = str_scorenum[j];
		drawx = upperlimit_width / 2 + scorenum[0].width * 10;
		str_high = str_high / 10;
		for (int i = 0; i < 10; i++) {
			number = str_high % 10;
			str_high = str_high / 10;
			DrawGraph(drawx, scorenum[0].height * j + 20 + 300, scorenum[number].graph, true);
			drawx = drawx - scorenum[0].width;
		}
	}

	if (stop_count > 10) {
		if (str_keyflag) {
			if (input_joypad & PAD_INPUT_1) {
				str_keyflag = false;
				stop_count = 0;
				state = 3;
			}
		}
	}
	else {
		++stop_count;
	}
}

void systemm::grasedisp(unsigned int gnum) {
	grazen = gnum;
	int number;
	int drawx = upperlimit_width - scorenum[0].width - 50;
	for (int i = 0; i < 10; i++) {
		number = grazen % 10;
		grazen = grazen / 10;
		DrawGraph(drawx, 200, scorenum[number].graph, true);
		drawx = drawx - scorenum[0].width;
	}
}

void systemm::zanki_disp(int life) {
	int zanki;
	int drawx = upperlimit_width - scorenum[0].width - 50;
	zanki = life - 1;
	for (int i = 0; i < zanki; i++) {
		DrawGraph(drawx, 400, icon.graph, true);
		drawx -= icon.width;
	}
	

}

void systemm::gage(unsigned int stock) {
	DrawBox(upperlimit_joydispwidth + 40, 290, upperlimit_joydispwidth + 260, 370, gage_color3, true);
	DrawBox(upperlimit_joydispwidth + 50, 300, upperlimit_joydispwidth + 250, 360, gage_color4, true);
	if (stock < 100) {
		DrawBoxAA(upperlimit_joydispwidth + 50, 300, upperlimit_joydispwidth + 50 + 200 * static_cast<float>(stock) / 100, 360, gage_color1, true);
	}
	else {
		DrawBoxAA(upperlimit_joydispwidth + 50, 300, upperlimit_joydispwidth + 250, 360, gage_color2, true);
	}
}

void systemm::save_score(unsigned int sco) {
	score1 = sco;
	FILE *fp;
	errno_t error;
	error = fopen_s(&fp, "score.dat", "wb");
	if (error != 0)	return;
	//std::ofstream ofs("score.txt", std::ios::out);
	for (int i = 0; i < 10; i++) {
		if (score1 > str_scorenum[i]) {
			unsigned int str = str_scorenum[i];
			str_scorenum[i] = score1;
			score1 = str;
		}
		fwrite(&str_scorenum[i], sizeof(unsigned int), 1, fp);
		
	}
	fclose(fp);

}

void systemm::stop_run() {
	input_joypad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (!(input_joypad & PAD_INPUT_4))	str_keyflag_a = true;
	//Aƒ{ƒ^ƒ“
	if (str_keyflag_a) {
		if (input_joypad & PAD_INPUT_4) {
			state = 90;
			arrowflag = 0;
			str_keyflag = false;
			str_keyflag_a = false;
		}
	}
}

void systemm::stop_menue() {
	input_joypad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (!(input_joypad & PAD_INPUT_1))	str_keyflag = true;
	if (input_joypad & PAD_INPUT_UP)	arrowflag = 0;
	if (input_joypad & PAD_INPUT_DOWN)	arrowflag = 1;
	DrawGraph(0, 0, stop_graph.graph, true);
	if (arrowflag == 0) {
		DrawGraph(upperlimit_joydispwidth / 2 - stop_continue.width / 2, upperlimit_joydispheight / 2 - stop_continue.height, stop_continue.graph, true);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawGraph(upperlimit_joydispwidth / 2 - stop_escape.width / 2, upperlimit_joydispheight / 2 + stop_escape.height, stop_escape.graph, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else if (arrowflag == 1) {
		DrawGraph(upperlimit_joydispwidth / 2 - stop_escape.width / 2, upperlimit_joydispheight / 2 + stop_escape.height, stop_escape.graph, true);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawGraph(upperlimit_joydispwidth / 2 - stop_continue.width / 2, upperlimit_joydispheight / 2 - stop_continue.height, stop_continue.graph, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	if (stop_count > 10) {
		if (str_keyflag) {
			if (input_joypad & PAD_INPUT_1) {
				if (arrowflag == 0) {
					state = 1;
					stop_count = 0;
					str_keyflag = false;
				}
				else if (arrowflag = 1) {
					stop_count = 0;
					state = 3;
					str_keyflag = false;
				}
			}
		}
	}
	else {
		++stop_count;
	}
}

void systemm::instal_score() {
	FILE *fp;
	errno_t error;
	error = fopen_s(&fp, "score.dat", "rb");
	if (error != 0) {
		str_scorenum[0] = 10;
	}
	else {
		for (int i = 0; i < 10; i++) {
			fread(&str_scorenum[i], sizeof(str_scorenum[0]), 1, fp);
		}
	}
	
	fclose(fp);
}

int& systemm::set_musicflag() {
	return this->music_flag;
}

bool& systemm::set_str_keyflag() {
	return this->str_keyflag;
}

int& systemm::set_state() {
	return this->state;
}

void systemm::set_word() {
	word[0].graph = LoadGraph("graph/wA.png");
	GetGraphSize(word[0].graph, &word[0].width, &word[0].height);
	word[1].graph = LoadGraph("graph/wB.png");
	word[2].graph = LoadGraph("graph/wC.png");
	word[3].graph = LoadGraph("graph/wd.png");
	word[4].graph = LoadGraph("graph/we.png");
	word[5].graph = LoadGraph("graph/wf.png");
	word[6].graph = LoadGraph("graph/wg.png");
	word[7].graph = LoadGraph("graph/wh.png");
	word[8].graph = LoadGraph("graph/wi.png");
	word[9].graph = LoadGraph("graph/wj.png");
	word[10].graph = LoadGraph("graph/wk.png");
	word[11].graph = LoadGraph("graph/wl.png");
	word[12].graph = LoadGraph("graph/wm.png");
	word[13].graph = LoadGraph("graph/wn.png");
	word[14].graph = LoadGraph("graph/wo.png");
	word[15].graph = LoadGraph("graph/wp.png");
	word[16].graph = LoadGraph("graph/wq.png");
	word[17].graph = LoadGraph("graph/wr.png");
	word[18].graph = LoadGraph("graph/ws.png");
	word[19].graph = LoadGraph("graph/wt.png");
	word[20].graph = LoadGraph("graph/wu.png");
	word[21].graph = LoadGraph("graph/wv.png");
	word[22].graph = LoadGraph("graph/ww.png");
	word[23].graph = LoadGraph("graph/wx.png");
	word[24].graph = LoadGraph("graph/wy.png");
	word[25].graph = LoadGraph("graph/wz.png");
}