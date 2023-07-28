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
