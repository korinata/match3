#include"Stage.h"
#include"DxLib.h"
#include"InputControl.h"

/************************************************

*マクロ定義

************************************************/

#define HEIGHT									(12)
#define WIDTH									(12)
#define BLOCKSIZE								(48)
#define BLOCK_IMAGE_MAX							(10)

#define ITEM_MAX								(8)

#define SELECT_CURSOR							(0)
#define NEXT_CURSOR								(1)
#define TMP_CURSOR								(2)

/************************************************

*型定義

************************************************/

typedef struct
{
	int flg;
	int x, y;
	int width, height;
	int image;
	int backup;
}T_Object;
typedef struct
{
	int x;
	int y;
}T_CURSOR;

enum
{
	E_NONE,
	E_ONCE,
	E_SECOND
};

/************************************************

*変数定義

************************************************/

T_Object Block[HEIGHT][WIDTH];
T_CURSOR Select[3];
int Item[ITEM_MAX];
int ClickStatus;
int Stage_State;
int Stage_Mission;
int Stage_Score;
int ClearFlag;

int BlockImage[BLOCK_IMAGE_MAX];
int StageImage;
int ClickSE;
int FadeOutSE;
int MoveBlockSE;

/************************************************

*プロトタイプ宣言

************************************************/

int combo_check(int x, int y);
void combo_check_h(int y, int x, int* cnt, int* col);
void combo_check_w(int y, int x, int* cnt, int* col);
void save_block(void);
void restore_block(void);

/************************************************

*ステージ制御機能：初期化処理
* 引　数：なし
* 戻り値：エラー情報

************************************************/

int StageInitialize(void)
{
	int ret = 0;
	int i;

	//画面読み込み
	LoadDivGraph("images/block.png", BLOCK_IMAGE_MAX, BLOCK_IMAGE_MAX, 1, BLOCKSIZE, BLOCKSIZE, BlockImage);
	StageImage = LoadGraph("images/stage.png");
	
	//音源読み込み
	ClickSE = LoadSoundMem("sounds/click_se.mp3");
	FadeOutSE = LoadSoundMem("sounds/fadeout_se.mp3");
	MoveBlockSE = LoadSoundMem("sounds/moveblock_se.mp3");

	//ブロック生成処理
	CreateBlock();

	ClickStatus = E_NONE;
	Stage_State = 0;
	Stage_Score = 0;
	ClearFlag = FALSE;

	for (i = 0; i < 3; i++)
	{
		Select[i].x = 0;
		Select[i].y = 0;
	}

	//エラーチェック
	for (i = 0; i < BLOCK_IMAGE_MAX; i++)
	{
		if (BlockImage[i] == -1)
		{
			ret = -1;
			break;
		}
	}
	if (StageImage == -1)
	{
		ret = -1;
	}
	if (ClickSE == -1)
	{
		ret = -1;
	}
	if (FadeOutSE == -1)
	{
		ret = -1;
	}
	if (MoveBlockSE == -1)
	{
		ret = -1;
	}
	return ret;
}

/************************************************

*ステージ制御機能：ステージの描画
* 引　数：なし
* 戻り値：なし

************************************************/

void StageDraw(void) {
	DrawGraph(0, 0, StageImage, FALSE);

	//アイテムの取得個数を描画
	for (int i = 0; i < ITEM_MAX; i++)
	{
		DrawRotaGraph(540, 245 + i * 30, 0.5f, 0, BlockImage[i + 1], TRUE, 0);
		DrawFormatString(580, 235 + i * 30, 0xffffff, "%3d", Item[i]);
	}
}