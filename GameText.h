//=============================================================================
//
// テキスト処理 [Text.h]
// Author :  Kimura Kouta
//
//=============================================================================
#ifndef _GAMETEXT_H_
#define _GAMETEXT_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_GAMETEXT (20)


//=============================================================================
// 構造体定義
//=============================================================================
typedef enum
{
	GAMETEXTTYPE_TITLELOG = 0,
	GAMETEXTTYPE_MAX,

} GAMETEXTTYPE;
typedef struct
{
	D3DXVECTOR3 pos;				// 位置
	D3DXVECTOR3 move;				// 移動量
	D3DXCOLOR col;					//色の変更
	int nType;						// 敵の種類
	int sizex;
	int sizey;
	bool bUse;						// 死んだかどうか
	bool bAlfa;
}GAMETEXT;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitGameText(void);
void UninitGameText(void);
void UpdateGameText(void);
void DrawGameText(void);

void SetGameText(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col,int sizex,int sizey, int nType);
GAMETEXT *GetGameText(void);
#endif
