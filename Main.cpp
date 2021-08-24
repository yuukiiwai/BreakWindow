#include"DxLib.h"
#include"Value.h"
#include"mouse.h"
#include"Title.h"
#include"Map.h"
#include"Human.h"

int human_clock;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreveInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (ChangeWindowMode(TRUE) != 0) {
		return 0;
	}
	if (DxLib_Init() != 0) {
		return 0;
	}
	if (SetGraphMode(1024, 768, 16) != DX_CHANGESCREEN_OK) {
		return 0;
	}
	if (SetWindowSizeChangeEnableFlag(TRUE, TRUE) != 0) {
		return 0;
	}

	if (SetDrawScreen(DX_SCREEN_BACK) != 0) {
		DxLib_End();
		return 0;
	}


	SetMouseDispFlag(TRUE);

	SetWindowText("卒業させろや");
	//phase初期化
	char phase = TITLE;

	//初期セッティング
	human_clock = 0;
	title_ini();
	map_ini();
	human_ini();

	while (1) {
		if (ScreenFlip() != 0) {
			break;
		}
		if (ProcessMessage() != 0) {
			break;
		}
		if (ClearDrawScreen() != 0) {
			break;
		}
		
		if (phase == TITLE) {
			title_G();
			if (CheckHitKey(KEY_INPUT_SPACE)) {
				phase = STAGE;
			}
		}
		if (phase == STAGE) {
			human_clock++;
			map_G();

			/* shuri operation */
			shuri_calc();
			shuri_G();

			/* keibi operation */
			keibi_calc();
			keibi_G();

			/* player operation */
			player_calc();
			player_G();

			/* last process (back menu) */
			if (CheckHitKey(KEY_INPUT_ESCAPE)) {
				phase = TITLE;
			}
		}			   
	}
	DxLib_End(); // lDXライブラリ終了処理
	return 0;
}