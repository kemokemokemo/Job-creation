//=============================================================================
//
// 爆発処理 [Explosion.h]
// Author : Kimura Kouta
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);

void SetExplotion(D3DXVECTOR3 pos, D3DXCOLOR col);

#endif
