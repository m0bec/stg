#include "DxLib.h"
#include "ziki.h"
#include "player.h"
#include "Enemy1.h"


// ボール君のグラフィックをメモリにロード＆表示座標をセット

//自機の操作
void ZikiController(){

	Ziki.direct_flag = 0;
	key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	if (Ziki.flag) {
		if (key & PAD_INPUT_UP){ 
			if (key & PAD_INPUT_2) {
				Ziki.y -= 3;
			}
			else {
				Ziki.y -= 5;
			}
		}
		if (key & PAD_INPUT_DOWN) {
			if (key & PAD_INPUT_2) {
				Ziki.y += 3;
			}
			else {
				Ziki.y += 5;
			}
		}
		if (key & PAD_INPUT_LEFT) {
			if (key & PAD_INPUT_2) {
				Ziki.x -= 3;
			}
			else {
				Ziki.x -= 5;
			}
			Ziki.direct_flag = 1;
		}
		if (key & PAD_INPUT_RIGHT) {
			if(key & PAD_INPUT_2){
				Ziki.x += 3;
			}
			else {
				Ziki.x += 5;
			}
			Ziki.direct_flag = 2;
		}


		if (Ziki.x < disp_width_s) Ziki.x = disp_width_s;
		if (Ziki.x > disp_width_f - 64) Ziki.x = disp_width_f - 64;
		if (Ziki.y < disp_height_s) Ziki.y = disp_height_s;
		if (Ziki.y > disp_height_f - 64) Ziki.y = disp_height_f - 64;

		if (Ziki.direct_flag == 0) {
			DrawGraph(Ziki.x, Ziki.y, Ziki.graph, TRUE);
		}
		else if (Ziki.direct_flag == 1) {
			DrawGraph(Ziki.x, Ziki.y, Ziki.graphL, TRUE);
		}
		else if (Ziki.direct_flag == 2) {
			DrawGraph(Ziki.x, Ziki.y, Ziki.graphR, TRUE);
		}
	}
	else {
		if (damage_count > 20) {
			if (damage_count < 41) {
				if (damage_count % 2 == 0) {
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
					DrawGraph(Ziki.x, Ziki.y, Ziki.graph, TRUE);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

				}
				Ziki.y -= 5;
			}
			else {
				if (key & PAD_INPUT_UP) {
					if (key & PAD_INPUT_2) {
						Ziki.y -= 3;
					}
					else {
						Ziki.y -= 5;
					}
				}
				if (key & PAD_INPUT_DOWN) {
					if (key & PAD_INPUT_2) {
						Ziki.y += 3;
					}
					else {
						Ziki.y += 5;
					}
				}
				if (key & PAD_INPUT_LEFT) {
					if (key & PAD_INPUT_2) {
						Ziki.x -= 3;
					}
					else {
						Ziki.x -= 5;
					}
					Ziki.direct_flag = 1;
				}
				if (key & PAD_INPUT_RIGHT) {
					if (key & PAD_INPUT_2) {
						Ziki.x += 3;
					}
					else {
						Ziki.x += 5;
					}
					Ziki.direct_flag = 2;
				}


				if (Ziki.x < disp_width_s) Ziki.x = disp_width_s;
				if (Ziki.x > disp_width_f - 64) Ziki.x = disp_width_f - 64;
				if (Ziki.y < disp_height_s) Ziki.y = disp_height_s;
				if (Ziki.y > disp_height_f - 64) Ziki.y = disp_height_f - 64;

				if (Ziki.direct_flag == 0) {
					DrawGraph(Ziki.x, Ziki.y, Ziki.graph, TRUE);
				}
				else if (Ziki.direct_flag == 1) {
					DrawGraph(Ziki.x, Ziki.y, Ziki.graphL, TRUE);
				}
				else if (Ziki.direct_flag == 2) {
					DrawGraph(Ziki.x, Ziki.y, Ziki.graphR, TRUE);
				}
				if (damage_count % 2 == 0) {
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
					DrawGraph(Ziki.x, Ziki.y, Ziki.graph, TRUE);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				}
				else {
					DrawGraph(Ziki.x, Ziki.y, Ziki.graph, TRUE);
				}
			}
		}
		damage_count++;
	}
	
	
	if (damage_count == 200) {
		Ziki.flag = TRUE;
		damage_count = 0;
	}
}

//自機のあたり範囲の描画
void ZikiCore() {
	ziki_core.x = Ziki.x + Ziki.width / 2 - ziki_core.width / 2;
	ziki_core.y = Ziki.y + Ziki.height / 2 - ziki_core.height / 2;
	DrawGraph(ziki_core.x, ziki_core.y, ziki_core.graph, TRUE);
}

//自機のショット
void ZikiShot() {
	z_hitcount = 0;
	if (key & PAD_INPUT_1 && count % 4 == 0) {
		for (int i = 0; i < SHOT_NUM; i++) {
			if (ziki_shot[i].flag == false) {
				ziki_shot[i].flag = true;
				ziki_shot[i].x = Ziki.x +(Ziki.width/2)-16;
				ziki_shot[i].y = Ziki.y + ziki_shot[i].height;
				break;
			}
		}
	}

	for (int i = 0; i < SHOT_NUM; i++) {
		if (ziki_shot[i].flag) {
			ziki_shot[i].y -= ZIKI_SHOT_SPEED;

			if (ziki_shot[i].y < disp_height_s - 10) {
				ziki_shot[i].flag = false;
			}
		}
	}

	//弾の当たり判定
	

	for (int i = 0; i < SHOT_NUM; i++) {
		if (ziki_shot[i].flag) {
			DrawGraph(ziki_shot[i].x, ziki_shot[i].y, ziki_shot_graph, TRUE);
		}
	}
}

int  Ziki_S_hit() {
	for (int i = 0; i < SHOT_NUM; i++) {
		if (ziki_shot[i].flag) {
			if (ziki_shot[i].x + ziki_shot[i].width > Enemy1.x && ziki_shot[i].x<Enemy1.x + Enemy1.width && ziki_shot[i].y<Enemy1.y + Enemy1.height - 20) {
				ziki_shot[i].flag = false;
				z_hitcount++;
			}
		}
	}
	return z_hitcount;
}