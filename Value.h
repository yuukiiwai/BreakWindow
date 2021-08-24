#ifndef Value_H
#define Value_H

//image-size
#define IMAGE_SIZE 64;

//mouse
extern int mouseX, mouseY, mouseS;

//title
extern int title_i, title_d;

//map
///image
extern int images[5];
enum
{
	FLOOR, 
	WALL, 
	WINDOW, 
	WINDOW_B, 
	STEP
};
///mapnum
#define WIDTH_B 16 //横ブロック数
#define HEIGHT_B 12 //縦ブロック数
extern int map[HEIGHT_B][WIDTH_B];

//human

#define WAIT_CLOCK 16	//操作非受付のクロック数
#define WAIT_REP_CLOCK 180 //修理時間

typedef struct HUMAN
{
	char reverse;	//向き
	char velocity;	//速さ
	int x, y;		//位置
	int xj;		//当たり判定
	char state;	//gif系の画像番号
};

typedef struct PLAYER
{
	int walk[2];	//[0]...立ち絵 [1]...歩き絵
	int doing[2];	//モーション
	char doingF;	//モーションのフラグ
	int arrest;		//逮捕
	char arrestF;	//逮捕フラグ
	HUMAN vec_a;	//向き速さ位置
};

typedef struct KEIBI_IMAGE
{
	int walk[2];
	int doing;
	int arrest;
};

typedef struct KEIBI
{
	HUMAN vec_a;	//向き速さ位置
	int keibi_clock;//human_clockと同期
};

typedef struct SHURI_IMAGE
{
	int walk[2];
};

typedef struct SHURI
{
	HUMAN vec_a;	//向き速さ位置
	char floor;		//存在する階層はチェックし終えたか
	int shuri_clock;//human_clockと同期
	char doingF;	//doingフラグ
};

extern KEIBI_IMAGE keibi_i;
extern SHURI_IMAGE shuri_i;

extern PLAYER player;
extern KEIBI *keibi;
extern SHURI *shuri;

extern char keibi_num;
extern char shuri_num;

extern int human_clock;	//操作の受付、拒否のクロック
extern int player_clock;	//for player
/*
how to use
<< nomal >>
player_clock = human_clock;
<< start timing >>
player_clock = human_clock + n;
<< loop >>
while(human_clock != player){...}
<< why "!=" ? >>
if (player (= human_clock + n)  ==> overflow)

` human_clock(+) < player + n(-) `

↑out of loop
*/
//画像切り替えのためのクロック
extern int player_ite; //0~10 walk[0], 10~20 walk[1], 30~40 doing[0], 40~50 doing[1]
extern int keibi_ite;
extern int shuri_ite;

//main -phase
enum 
{
	TITLE,
	STAGE
};

#endif
