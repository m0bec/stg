

#include "DxLib.h"
#include "control.h"

// WinMain関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(FALSE);
	// 画面モードの設定
	SetGraphMode(1280, 1024, 16);

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1) return -1;

	control &main_run = control::getinstance();

	// グラフィックの描画先を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);

	main_run.firstrun();
	// 移動ルーチン
	while (1)
	{
		// 画面を初期化(真っ黒にする)
		ClearDrawScreen();

		main_run.run();
		if (CheckHitKey(KEY_INPUT_P) == 1) {
			SaveDrawScreen(0, 0, 1280, 1024, "Save.bmp");
		}
		// 裏画面の内容を表画面にコピーする
		ScreenFlip();
		

		// Windows 特有の面倒な処理をＤＸライブラリにやらせる
		// -1 が返ってきたらループを抜ける
		if (ProcessMessage() < 0) break;

		// もしＥＳＣキーが押されていたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;
		if (main_run.pass_state() == 99) break;
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;					// ソフトの終了
}

