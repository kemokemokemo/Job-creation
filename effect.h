//=============================================================================
//
// エフェクトの処理 [effect.h]
// Author : KIMURA KOUTA
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
// 構造体定義
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 move;		// 移動
	D3DXMATRIX  mtxWorldWall;			//ワールドマトリックス
	D3DXCOLOR col;			// 色
	float fRadius;			// 半径
	int nLife;				// ライフ
	int nType;
	int ParticlenType;
	bool bUse;				// 使用しているかどうか
} EFFECT;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);

void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, int nLife,int nType);
void SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, int nLife, int nType);

#endif
