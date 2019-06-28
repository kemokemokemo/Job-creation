//=============================================================================
//
// ICE処理 [ice.h]
// Author :KIMURA KOUTA
//
//=============================================================================
#ifndef _ICE_H_
#define _ICE_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
// 構造体
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posOld;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	D3DXMATRIX  mtxWorldObject;
	float		fDistance;
	int			IdxShadow;
	D3DXVECTOR3 vtxMin;
	D3DXVECTOR3 vtxMax;
	int			nLife;
	bool		bUse;
} ICE;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitIce(void);
void UninitIce(void);
void UpdateIce(void);
void DrawIce(void);
ICE *GetIce(void);

void SetIce(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot);
#endif