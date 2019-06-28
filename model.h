//=============================================================================
//
// モデル処理 [model.h]
// Author : 
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_MODEL		(46)//表示するモデルの最大数
#define MAX_MODELTYPE	(26)//読み込むモデルの最大数
#define MAX_CHARMODEL	(40)

//=============================================================================
// 構造体定義
//=============================================================================
//読み込んだモデルの構造体
typedef struct
{
	char				pXFileName[MAX_CHARMODEL];	// ファイル名
	LPD3DXMESH			pMeshModel;					// メッシュ情報
	LPD3DXBUFFER		pBuffMatModel;				// マテリアル情報へのポイント
	DWORD				NumMatModel;				// マテリアルの数
	LPDIRECT3DTEXTURE9	*pTextureModel;				// テクスチャへのポイント
}LOADMODEL;

typedef struct
{
	D3DXVECTOR3 Pos;								//ポリゴンの位置
	D3DXVECTOR3 Posold;								//前回位置
	D3DXVECTOR3 move;								//ポリゴンの移動
	D3DXVECTOR3 scale;								//ポリゴンの拡大,縮小
	D3DXVECTOR3 rot;								//ポリゴンの向き
	D3DXVECTOR3 Diffrot;							//ポリゴンの向き
	D3DXMATRIX mtxWorldModel;						//ワールドマトリック
	D3DXVECTOR3 vtxMaxModel;						//Xファイルの最大値取得
	D3DXVECTOR3 vtxMinModel;						//Xファイルの最小値取得
	float fRadius;									// 半径
	float fHeight;									// 高さ
	float fDistance;
	int hIdxShadow;									//影の設定
	int bUse;										//使われているかどうか
	int nTypeTex;									//テクスチャ
	int nTypeModel;									//モデル
	int nLoad;										// 読み込むモデルの数
	int MaxModel;									// 使用するモデルの数
}MODEL;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
MODEL *GetModel(void);

bool ColisionModel(
	D3DXVECTOR3 * pPos,
	D3DXVECTOR3 * pPosOld,
	D3DXVECTOR3 * move,
	MODEL**ppModelRet);

bool ColisionShadow(
	D3DXVECTOR3 * pPos,
	D3DXVECTOR3 * pPosOld,
	D3DXVECTOR3 * move,
	MODEL**ppModelRet);

void LoadModelText(void);
void CrearModel(void);
#endif