#include "system.h"
#include "control.h"
#include <fstream>
#include <string>

systemm::systemm() {
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


	kurame_music = LoadSoundMem("music/KURAME_NO_BGM.wav");
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
	gameover = false;
	str_keyflag = true;

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
		StopSoundMem(kurame_music);
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
	}
}

void systemm::stop_music() {
	StopSoundMem(kurame_music);
	StopSoundMem(boss1_music);
	StopSoundMem(boss2_music);
}

void systemm::startgraphrun() {
	systemm::checkkey();
	systemm::movearrow(arrowflag);
	systemm::drawstartmenue();
	systemm::music();
}

void systemm::disp_gameover() {
	input_joypad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	DrawGraph(0, 0, gameoverdisp.graph, false);
	if (!(input_joypad & PAD_INPUT_1))	str_keyflag = true;
	if (str_keyflag) {
		if (input_joypad & PAD_INPUT_1) {
			state = 3;
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
	for (int i = 0; i < 10; i++)
	{
		number = str_high % 10;
		str_high = str_high / 10;
		DrawGraph(drawx, 10, scorenum[number].graph, true);
		drawx = drawx - scorenum[0].width;
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
	error = fopen_s(&fp, "score.txt", "wb");
	if (error != 0)	return;
	std::ofstream ofs("score.txt", std::ios::out);
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

void systemm::instal_score() {
	FILE *fp;
	errno_t error;
	error = fopen_s(&fp, "score.txt", "rb");
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