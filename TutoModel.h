//=============================================================================
//
// モデル処理 [TutoModel.h]
// Author : kimura kouta
//
//=============================================================================
#ifndef _TUTOMODEL_H_
#define _TUTOMODEL_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_TUTOMODEL		(7)//表示するモデルの最大数
#define MAX_TUTOMODELTYPE	(6)//読み込むモデルの最大数
#define MAX_TUTOCHARMODEL	(40)

//=============================================================================
// 構造体定義
//=============================================================================
//読み込んだモデルの構造体
typedef struct
{
	char				pXFileTutoName[MAX_TUTOCHARMODEL];	// ファイル名
	LPD3DXMESH			pMeshTutoModel;					// メッシュ情報
	LPD3DXBUFFER		pBuffMatTutoModel;				// マテリアル情報へのポイント
	DWORD				NumMatTutoModel;				// マテリアルの数
	LPDIRECT3DTEXTURE9	*pTextureTutoModel;				// テクスチャへのポイント
}LOADTUTOMODEL;

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
	int hIdxShadow;									//影の設定
	int bUse;										//使われているかどうか
	int nTypeTex;									//テクスチャ
	int nTypeModel;									//モデル
	int nLoad;										// 読み込むモデルの数
	int nMaxModel;									// 使用するモデルの数
}TUTOMODEL;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitTutoModel(void);
void UninitTutoModel(void);
void UpdateTutoModel(void);
void DrawTutoModel(void);
TUTOMODEL *GetTutoModel(void);

bool ColisionTutoModel(
	D3DXVECTOR3 * pPos,
	D3DXVECTOR3 * pPosOld,
	D3DXVECTOR3 * move,
	TUTOMODEL**ppTutoModelRet);

bool ColisionTutoShadow(
	D3DXVECTOR3 * pPos,
	D3DXVECTOR3 * pPosOld,
	D3DXVECTOR3 * move,
	TUTOMODEL**ppTutoModelRet);


void LoadTutoModelText(void);
#endif