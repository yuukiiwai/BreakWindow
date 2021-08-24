#include"DxLib.h"
#include"mouse.h"
#include"Value.h"
#include<string.h>

int images[5];
int map[HEIGHT_B][WIDTH_B];
#define IMAGE_SIZE 64

void map_ini() {
	int i,j;

	char paths[][40] = { {"image/map/floor.png"},{"image/map/wall.png"},{"image/map/window_glass.png"},{"image/map/window_glass_broken.png"},{"image/map/step.png"} };
	for (i = 0; i < 5; i++) {
		images[i] = LoadGraph(paths[i]);
	}

	for (i = 0; i < HEIGHT_B; i++) {
		for (j = 0; j < WIDTH_B; j++) {
			map[i][j] = WALL;
		}
		i++;
		for (j = 0; j < WIDTH_B; j++) {
			if (j % 3) {
				map[i][j] = WINDOW;
			}
			else {
				map[i][j] = WALL;
			}
		}
		i++;
		for (j = 0; j < WIDTH_B; j++) {
			if ((j - 3) % 9) {
				map[i][j] = FLOOR;
			}
			else {
				map[i][j] = STEP;
			}
		}
	}
}

void map_G() {
	int h, w;
	DrawGraph(0, 0, map[0][0], TRUE);
	for (h = 0; h < HEIGHT_B; h++) {
		for (w = 0; w < WIDTH_B; w++) {
			DrawGraph(w * IMAGE_SIZE, h * IMAGE_SIZE, images[map[h][w]], TRUE);
		}
	}
}

void map_window_break(int x, int y) {
	int w = x / 64;
	int h = y / 64 - 1;
	if (map[h][w] == WINDOW) {
		map[h][w] = WINDOW_B;
	}
}

char map_is_step(int x, int y) {
	int w = x / 64;
	int h = y / 64;
	char ret = FALSE;
	if (map[h][w] == STEP) {
		ret = TRUE;
	}

	return ret;
}

char map_step_use(int x, int y, char com) {
	int w = x / 64;
	int h = y / 64;
	char ret;
	if ((h == 2 && com == 'u') || (h == 11 && com == 'd')) {
		ret = FALSE;
	}
	else if (map[h][w] == STEP) {
		ret = TRUE;
	}
	else {
		ret = FALSE;
	}
	return ret;
}

//‰ó‚ê‚Ä‚¢‚é‚©‚ÌŠm”F
char map_is_Bwindow(int x, int y) {
	char broken = FALSE;
	int w = x / 64;
	int h = y / 64 - 1;
	if (map[h][w] == WINDOW_B) {
		broken = TRUE;
	}

	return broken;
}

//C—‚·‚é
void map_rep_Bwindow(int x, int y) {
	int w = x / 64;
	int h = y / 64 - 1;
	if (map[h][w] == WINDOW_B) {
		map[h][w] = WINDOW;
	}
}