#include"DxLib.h"

int title_i, title_d;

void title_ini() {
	char path_i[] = "image/title/title.png";
	char path_d[] = "image/title/dispS.png";
	
	title_i = -1;
	title_d = -1;
	if ((title_i = LoadGraph(path_i)) == -1) {
		printfDx("i err");
		exit(1);
	}
	if ((title_d = LoadGraph(path_d)) == -1) {
		printfDx("d err");
		exit(1);
	}
}

void title_G() {
	DrawGraph(0, 0, title_i, TRUE);
	DrawGraph(0, 618, title_d, TRUE);
}