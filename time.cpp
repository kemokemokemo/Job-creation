//=============================================================================
//
// スコア処理 [Time.cpp]
// Author : KIMURA KOUTA
//
//=============================================================================
#include "Time.h"
#include "Game.h"
#include "fade.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define	TEXTURE_Time		"DATA/TEX/number001.png"	// 読み込むテクスチャファイル名
#define MAX_Time   (3)
#define Time_POS_X	(0)			    //ポリゴンの表示位置(左上X)
#define Time_POS_Y	(0)			    //ポリゴンの表示位置(左上Y)
#define Time_SIZE_X	(40)			//ポリゴンのサイズ(横幅)
#define Time_SIZE_Y	(60)			//ポリゴンのサイズ(立幅)
#define TimeCOLOR_TEX   (255)

#define MAX_TIMER   (300)

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void MakeVertexTime(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// 構造体定義
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;				// 位置
	bool bUse;						// 死んだかどうか
	int Time;
} TIME;


//=============================================================================
// グローバル変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureTime = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;	// 頂点バッファへのポインタ

int						g_nTime;				// スコア
TIME					g_aTime[8];
int g_TimerState;
int g_nCntTime;
//=============================================================================
// 初期化処理
//=============================================================================
void InitTime(void)
{
	int g_TimerState = 0;
	int nCntTime = 0;
	int g_nTime = 0;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
								TEXTURE_Time,		// ファイルの名前
								&g_pTextureTime);	// 読み込むメモリー

	// 頂点情報の作成
	MakeVertexTime(pDevice);

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTime(void)
{
	// テクスチャの開放
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();
		g_pVtxBuffTime = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();
		g_pVtxBuffTime = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTime(void)
{
	if (g_TimerState < MAX_TIMER)
	{
		g_nCntTime++;
	}
	if (g_nCntTime >= 60)
	{
		AddTime(-1);
		g_nCntTime = 0;
		g_TimerState++;

		if (g_TimerState >= MAX_TIMER)
		{
			SetGameState(GAMESTATE_END2);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTime(void)
{
	int nCntTime = 0;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffTime, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTime);

	for (nCntTime = 0; nCntTime < MAX_Time; nCntTime++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntTime, 2);
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
void MakeVertexTime(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;
	int nCntTime=0;


	// オブジェクトの頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_Time,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime,
		NULL);

	// 頂点情報の設定
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTime = 0; nCntTime < MAX_Time; nCntTime++)
	{
		//頂点座標の設定(右回りで設定する）
		pVtx[0].pos = D3DXVECTOR3(Time_POS_X + 60 * nCntTime + 30 * 1.0f, Time_POS_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(Time_POS_X + 60 * nCntTime + 30 + Time_SIZE_X * 1.0f, Time_POS_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(Time_POS_X + 60 * nCntTime + 30 * 1.0f, Time_POS_Y + Time_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(Time_POS_X + 60 * nCntTime + 30 + Time_SIZE_X * 1.0f, Time_POS_Y + Time_SIZE_Y, 0.0f);

		//rhwの設定（値は1.0で固定）：2Dとして動かすのに必要なもの
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定(0～255の値で設定）
		pVtx[0].col = D3DCOLOR_RGBA(TimeCOLOR_TEX, TimeCOLOR_TEX, TimeCOLOR_TEX, TimeCOLOR_TEX);
		pVtx[1].col = D3DCOLOR_RGBA(TimeCOLOR_TEX, TimeCOLOR_TEX, TimeCOLOR_TEX, TimeCOLOR_TEX);
		pVtx[2].col = D3DCOLOR_RGBA(TimeCOLOR_TEX, TimeCOLOR_TEX, TimeCOLOR_TEX, TimeCOLOR_TEX);
		pVtx[3].col = D3DCOLOR_RGBA(TimeCOLOR_TEX, TimeCOLOR_TEX, TimeCOLOR_TEX, TimeCOLOR_TEX);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4 ;
	}
	// 頂点データをアンロックする
	g_pVtxBuffTime->Unlock();
}
	
//=============================================================================
// スコアの変更
//=============================================================================
void AddTime(int nValue)
{
	int nCntTime;
	int nTime;
	VERTEX_2D *pVtx;

	g_nTime += nValue;

	if (g_nTime > 300)
	{
		g_nTime = 300;
	}
	if (g_nTime < 0)
	{
		g_nTime = 0;
	}

	// 頂点情報の設定
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTime = 0; nCntTime < MAX_Time; nCntTime++)
	{
		nTime = g_nTime / (int)powf(10.0f, MAX_Time - nCntTime - 1.0f * 1.0f) % 10;

		//テクスチャ画像の設定
		pVtx[0].tex = D3DXVECTOR2((nTime*0.1f) + 0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((nTime*0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((nTime*0.1f) + 0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((nTime*0.1f) + 0.1f, 1.0f);

		pVtx += 4;
	}
	// 頂点データをアンロックする
	g_pVtxBuffTime->Unlock();
}
//==================================================================================================
// スコアの取得
//==================================================================================================
int GetTime(void)
{
	return g_nTime;
}
