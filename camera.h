//=============================================================================
//
// カメラ処理 [camera.h]
// Author : 
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
// カメラの構造体
//=============================================================================
typedef struct
{
	D3DXVECTOR3 posV;
	D3DXVECTOR3 posVDest;
	D3DXVECTOR3 posR;
	D3DXVECTOR3 posRDest;
	D3DXVECTOR3 vecU;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 rotDest;
	D3DXMATRIX mtxProjection;
	D3DXMATRIX mtxView;

}CAMERA;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);

void SetCamera(void);

CAMERA *GetCamera(void);
#endif
