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
#define WIDTH_B 16 //���u���b�N��
#define HEIGHT_B 12 //�c�u���b�N��
extern int map[HEIGHT_B][WIDTH_B];

//human

#define WAIT_CLOCK 16	//������t�̃N���b�N��
#define WAIT_REP_CLOCK 180 //�C������

typedef struct HUMAN
{
	char reverse;	//����
	char velocity;	//����
	int x, y;		//�ʒu
	int xj;		//�����蔻��
	char state;	//gif�n�̉摜�ԍ�
};

typedef struct PLAYER
{
	int walk[2];	//[0]...�����G [1]...�����G
	int doing[2];	//���[�V����
	char doingF;	//���[�V�����̃t���O
	int arrest;		//�ߕ�
	char arrestF;	//�ߕ߃t���O
	HUMAN vec_a;	//���������ʒu
};

typedef struct KEIBI_IMAGE
{
	int walk[2];
	int doing;
	int arrest;
};

typedef struct KEIBI
{
	HUMAN vec_a;	//���������ʒu
	int keibi_clock;//human_clock�Ɠ���
};

typedef struct SHURI_IMAGE
{
	int walk[2];
};

typedef struct SHURI
{
	HUMAN vec_a;	//���������ʒu
	char floor;		//���݂���K�w�̓`�F�b�N���I������
	int shuri_clock;//human_clock�Ɠ���
	char doingF;	//doing�t���O
};

extern KEIBI_IMAGE keibi_i;
extern SHURI_IMAGE shuri_i;

extern PLAYER player;
extern KEIBI *keibi;
extern SHURI *shuri;

extern char keibi_num;
extern char shuri_num;

extern int human_clock;	//����̎�t�A���ۂ̃N���b�N
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

��out of loop
*/
//�摜�؂�ւ��̂��߂̃N���b�N
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
