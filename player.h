//=============================================================================
//
// モデル処理 [player.h]
// Author : kimura kouta
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "model.h"
#include "TutoModel.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_PLAYER	(10)//読み込むモデルの最大数
#define MAX_PARTS	(10)//表示するモデルの最大数
#define MAX_KEYSET	(30)
#define MAX_CHAR	(30)

//=============================================================================
// 構造体定義
//=============================================================================
typedef enum
{
	MOTION_NEUTRAL = 0,//ニュートラル
					 A,
					 B,
					 C,
					 MOTION_MAX
}MOTIONTYPE;

//読み込んだモデルの構造体
typedef struct
{
	char				pXFileName[MAX_CHAR];	// ファイル名
	LPD3DXMESH			pMesh;					// メッシュ情報
	LPD3DXBUFFER		pBuffMat;				// マテリアル情報へのポイント
	DWORD				NumMat;					// マテリアルの数
	LPDIRECT3DTEXTURE9	*pTexture;				// テクスチャへのポイント
}LoadModel;

typedef struct
{
	D3DXMATRIX  mtxWorld;
	D3DXVECTOR3 pos;								// ポリゴンの位置
	D3DXVECTOR3 rot;								// ポリゴンの向き
	int nIdxModelParent;
	int nType;
}PLAYERMODEL;

typedef struct
{
	D3DXVECTOR3 pos;								// ポリゴンの位置
	D3DXVECTOR3 posOld;								// ポリゴンの位置
	D3DXVECTOR3 rot;								// ポリゴンの向き
	D3DXVECTOR3 move;								// ポリゴンの移動
	float		fMoveSpeed;							// 移動量
	D3DXMATRIX  mtxWorld;							// ワールドマトリックス
	D3DXVECTOR3 vtxMinPlayer;						// 頂点座標の最小値
	D3DXVECTOR3 vtxMaxPlayer;						// 頂点座標の最大値
	float		fRadius;							// 半径
	float		fHeight;							// 高さ
	int			nIdxLine;							// 線の使用番号 [インデックス]
	float		fDestAngle;							// 目的の向き
	int			hIdxShadow;							// 影の設定
	int			nCntDeth;							// 死亡カウント
	int			nZanki;								// 残機のカウント
	bool		bClearFlag1;						// CLEARのフラグ
	bool		bClearFlag2;						// CLEARのフラグ
	D3DXVECTOR3	size;
	D3DXVECTOR3 rotDiffPlayer;
	D3DXVECTOR3 rotDestPlayer;

	//モーション種類
	bool bNolmal;
	bool bWalk;
	bool bJumpMS;
	bool bDeth;

	bool bPlayerDeth;
	bool bPlayerCrear;

	//<<モデル>>
	int		nLoadParts;								// 読み込むモデルの数
	int		nMaxParts;								// 使用するモデルの数
	PLAYERMODEL aPlayerModel[MAX_PLAYER];			//  モデルの情報

	//<<モーション>>
	MOTIONTYPE		nMotionTypeOld;					// 前モーションの種類
	MOTIONTYPE		nMotionType;					// モーションの種類
	int				nFrameALL;						// モーションの最大
	int				nNowFrame;	

	MODEL * pModel;									// モデルの当たり判定の情報
	TUTOMODEL *pTutoModel;

	D3DXVECTOR3 Diffrot;							// ポリゴンの向き
	bool bJump;

}PLAYER;

//モーションの構造体
typedef struct
{
	D3DXVECTOR3 pos;								// ポリゴンの位置
	D3DXVECTOR3 rot;								// ポリゴンの位置
}Offset;

//モーションの構造体
typedef struct
{
	int		nframe;												// フレーム数
	D3DXVECTOR3 pos[MAX_PLAYER];								// ポリゴンの位置
	D3DXVECTOR3 rot[MAX_PLAYER];								// ポリゴンの位置
}KeySet;

typedef struct
{
	int		nLoop;				// ループ情報[0:ループしない,1:ループする]
	int		nNumKey;			// キー数
	KeySet	nKey[MAX_KEYSET];	// キー情報
}Motion;

typedef struct
{
	Motion Motion[MOTION_MAX];				// ループ情報[0:ループしない,1:ループする]
	Offset Offset[MAX_PLAYER];				

}LoadMotion;

//=============================================================================
// プロトタイプ宣言
//==========================================================　===================
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

//モーション
void PlayerMotion(void);		// プレイヤーモーション
void CulFrame(void);			// フレーム計算

// プレイヤ情報の読み込み
void LoadPlayer(void);
void UpdateTitlePlayer(void);

//プレイヤ-の情報
PLAYER *GetPlayer(void);

void CulFrame(void);			// フレーム計算

//プレイヤ-の移動情報
void PlayerMove(void);

//プレイヤ-の当たり判定
void PlayerCollision(void);

//エフェクトの場所
void EffectRound(void);

//プレイヤ-のモーション
void PlayerMotionPlay(void);

//プレイヤ-の死亡情報
void PlayerDeth(void);
#endif