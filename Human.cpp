#include"Value.h"
#include"DxLib.h"
#include"Map.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

PLAYER player;
int player_ite;
int player_clock;

SHURI_IMAGE shuri_i;
SHURI* shuri;
int shuri_ite;
char shuri_num;

void human_ini() {
	int i;

	/***** player *****/
	player.walk[0] = LoadGraph("image/human/left_gakusei_2.png");
	player.walk[1] = LoadGraph("image/human/left_gakusei_1.png");
	player.doing[0] = LoadGraph("image/human/do_gakusei_back1.png");
	player.doing[1] = LoadGraph("image/human/do_gakusei_back2.png");
	player.arrest = LoadGraph("imageg/human/left_gakusei_arrest.png");
	player.vec_a.reverse = FALSE;
	player.vec_a.velocity = 5;
	player.vec_a.x = 0;
	player.vec_a.y = 704;
	player.vec_a.state = 0;
	player.arrestF = player.doingF = 0;

	player_ite = 0;

	/***** keibi ******/


	/***** shuri ******/
	shuri_num = 4;

	shuri_i.walk[0] = LoadGraph("image/human/left_shuri_2.png");
	shuri_i.walk[1] = LoadGraph("image/human/left_shuri_1.png");
	
	shuri = (SHURI*)malloc(sizeof(SHURI) * shuri_num);
	for (i = 0; i < shuri_num; i++) {
		(shuri + i)->vec_a.reverse = FALSE;
		(shuri + i)->vec_a.velocity = 1;
		(shuri + i)->vec_a.x = 0 + i * 192;
		(shuri + i)->vec_a.y = 128 + i * 192;
		(shuri + i)->vec_a.state = 0;
		(shuri + i)->shuri_clock = 0;
		(shuri + i)->doingF = FALSE;
	}
}

void player_G() {
	if (0 <= player_ite && player_ite < 20) {
		if (player.vec_a.reverse) {
			DrawTurnGraph(player.vec_a.x, player.vec_a.y, player.walk[player.vec_a.state], TRUE);
		}
		else {
			DrawGraph(player.vec_a.x, player.vec_a.y, player.walk[player.vec_a.state], TRUE);
		}
	}
	else if (30 < player_ite && player_ite <= 50) {
		DrawGraph(player.vec_a.x, player.vec_a.y, player.doing[player.vec_a.state], TRUE);
	}
}

void player_calc() {
	if (player.vec_a.x < -32) {
		player.vec_a.x = - 32;
	}
	if (player.vec_a.x > 1024 - 32) {
		player.vec_a.x = 1024 - 32;
	}

	//clock sync
	if (human_clock == player_clock + 1) {
		player_clock = human_clock;
	}

	player.vec_a.xj = player.vec_a.x + 32;
	//attack
	if (player.doingF == FALSE && CheckHitKey(KEY_INPUT_F)) {
		player_ite = 30;
		player.doingF = TRUE;
	}
	if (30 <= player_ite  && player_ite <= 50) {
		player_ite++;
		player_clock++;
		if (player_ite < 40) {
			player.vec_a.state = 0;
		}
		else if (player_ite < 50) {
			player.vec_a.state = 1;
		}
		else {
			map_window_break(player.vec_a.xj, player.vec_a.y);
			player.doingF = FALSE;
			player_ite = 0;
		}
	}

	//step-up
	if (human_clock == player_clock) {
		if (CheckHitKey(KEY_INPUT_W)) {
			if (map_step_use(player.vec_a.xj, player.vec_a.y, 'u')) {
				player.vec_a.y -= 192;
				player_clock += WAIT_CLOCK;
			}
		}
		if (CheckHitKey(KEY_INPUT_S)) {
			if (map_step_use(player.vec_a.xj, player.vec_a.y, 'd')) {
				player.vec_a.y += 192;
				player_clock += WAIT_CLOCK;
			}
		}
	}

	//walking
	if (0 <= player_ite && player_ite <= 20) {
		char jadge[2];	//[0]...HitKey(D) [1]...HitKey(A)
		int i;
		for (i = 0; i < 2; i++) {
			jadge[i] = 0;
		}

		if (CheckHitKey(KEY_INPUT_D)) {
			jadge[0] = 1;
		}
		else if (CheckHitKey(KEY_INPUT_A)) {
			jadge[1] = 1;
		}

		if (jadge[0] || jadge[1]) {	//PUSH D or A player_ite guru guru
			player_ite++;
			if (player_ite < 10) {
				player.vec_a.state = 0;
			}
			else if (player_ite < 20) {
				player.vec_a.state = 1;
			}
			else {
				player_ite = 0;
			}
		}
		if (jadge[0]) {
			player.vec_a.reverse = TRUE;
			player.vec_a.x += player.vec_a.velocity;
		}
		else if (jadge[1]) {
			player.vec_a.reverse = FALSE;
			player.vec_a.x -= player.vec_a.velocity;
			player_ite++;
		}
		else {
			player_ite = 0;
			player.vec_a.state = 0;
		}
	}

}

void shuri_G() {
	int i;
	for (i = 0; i < shuri_num; i++) {
		if ((shuri + i)->vec_a.reverse) {
			DrawTurnGraph((shuri + i)->vec_a.x, (shuri + i)->vec_a.y, shuri_i.walk[((shuri + i)->vec_a.state)], TRUE);
		}
		else {
			DrawGraph((shuri + i)->vec_a.x, (shuri + i)->vec_a.y, shuri_i.walk[((shuri + i)->vec_a.state)], TRUE);
		}
	}
}

void shuri_calc() {
	int i;
	for (i = 0; i < shuri_num; i++) {
		(shuri + i)->vec_a.xj = (shuri + i)->vec_a.x+64;
		
		//clock sync
		if (human_clock == (shuri + i)->shuri_clock + 1) {
			(shuri + i)->shuri_clock = human_clock;
			
			//クロックの同期が取れたあと、もしdoingだったら
			if ((shuri + i)->doingF) {
				(shuri + i)->doingF = FALSE;
				if ((shuri + i)->vec_a.reverse) {
					map_rep_Bwindow((shuri + i)->vec_a.x, (shuri + i)->vec_a.y);
				}
				else {
					map_rep_Bwindow((shuri + i)->vec_a.xj, (shuri + i)->vec_a.y);
				}
			}
		}
		else {
			continue;
		}

		//reverse
		if ((shuri + i)->vec_a.x < -32) {
			(shuri + i)->vec_a.x = -32;
			(shuri + i)->vec_a.reverse = TRUE;
		}
		if ((shuri+i)->vec_a.x > 1024 - 32) {
			(shuri + i)->vec_a.x = 1024 - 32;
			(shuri + i)->vec_a.reverse = FALSE;
		}

		//walking
		if ((shuri + i)->vec_a.reverse) {
			(shuri + i)->vec_a.x += (shuri + i)->vec_a.velocity;
		}
		else {
			(shuri + i)->vec_a.x -= (shuri + i)->vec_a.velocity;
		}

		//front of broken window
		if ((shuri + i)->vec_a.reverse) {
			if (map_is_Bwindow((shuri + i)->vec_a.x, (shuri + i)->vec_a.y)) {
				(shuri + i)->shuri_clock += WAIT_REP_CLOCK;
				(shuri + i)->doingF = TRUE;
			}
		}
		else {
			if (map_is_Bwindow((shuri + i)->vec_a.xj, (shuri + i)->vec_a.y)) {
				(shuri + i)->shuri_clock += WAIT_REP_CLOCK;
				(shuri + i)->doingF = TRUE;
			}
		}

		//歩行時のイテレーター
		shuri_ite = (shuri_ite + 1) % 40;
		if (shuri_ite <= 20) {
			(shuri + i)->vec_a.state = 0;
		}
		else {
			(shuri + i)->vec_a.state = 1;
		}

	}
	
}