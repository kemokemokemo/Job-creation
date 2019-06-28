//=============================================================================
//
// 影の処理 [Shadow.h]
// Author : 
//
//=============================================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);

int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
void DeleteShadow(int hIdxShadow);
void SetPositionShadow(int hIdxShadow, D3DXVECTOR3 pos);


#endif
