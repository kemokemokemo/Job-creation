// ====================================================================================================
//
// ランキング処理 [ranking.cpp]
// Author : Kimura kouta
// ====================================================================================================
#include <stdio.h>              // 一般的なヘッダー
#include "road.h"				// ロードヘッダー
#include "ranking.h"			// ランキングヘッダー
#include "input.h"
#include "fade.h"
#include "score.h"
#include "rankbg.h"
#include "Controlar.h"
// ====================================================================================================
//
// マクロ定義
//
// ====================================================================================================
#define	TEXTURE_RANKING		"DATA/TEX/number001.png"	// 読み込むテクスチャファイル名
#define RANKING_SIZE (20)									// ランキングボードの大きさ
#define RANKING_MAX (10)									// 数値
#define RANKING_DATE (5)									// ランキング数
#define SAVE_FILE_NAME ("text.txt")							// セーブファイル

// ====================================================================================================
//
// プロトタイプ宣言
//
// ====================================================================================================
void MakeVertexRanking(LPDIRECT3DDEVICE9 pDevice);

// ====================================================================================================
//
// グローバル変数宣言
//
// ====================================================================================================
LPDIRECT3DTEXTURE9		g_pTextureRanking = NULL;				// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL;				// 頂点バッファへのポインタ
D3DXVECTOR3				g_RankingPos;							// ランキングボードのポジション
RANKING					g_aRankin[RANKING_DATE];				// ランキング変数
int						g_nRanking;								// ランキング
int g_nRNKData;

// ====================================================================================================
//
// 初期化処理
//
// ====================================================================================================
void InitRanking(void)
{
	InitRankbg();

	int nCntRank;
	g_nRNKData = 0;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	g_RankingPos = D3DXVECTOR3(800.0f, 150.0f, 0.0f);
	g_nRanking = 0;
	
	for (nCntRank = 0; nCntRank < RANKING_DATE; nCntRank++)
	{
		g_aRankin[nCntRank].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRankin[nCntRank].aName[0];
		g_aRankin[nCntRank].nPoint = 0;
	}
	
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_RANKING,							// ファイルの名前
		&g_pTextureRanking);						// 読み込むメモリー

	// 頂点情報の作成
	MakeVertexRanking(pDevice);
}

// ====================================================================================================
//
// 終了処理
//
// ====================================================================================================
void UninitRanking(void)
{
	UninitRankbg();

	// テクスチャの開放
	if (g_pTextureRanking != NULL)
	{
		g_pTextureRanking->Release();
		g_pTextureRanking = NULL;
	}
	// 頂点バッファの開放
	if (g_pVtxBuffRanking != NULL)
	{
		// 頂点バッファの開放
		g_pVtxBuffRanking->Release();
		g_pVtxBuffRanking = NULL;
	}
}

// ====================================================================================================
//
// 更新処理
//
// ====================================================================================================
void UpdateRanking(void)
{
	UpdateRankbg();
}

// ====================================================================================================
//
// 描画処理
//
// ====================================================================================================
void DrawRanking(void)
{
	DrawRankbg();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntRanking;

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffRanking, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureRanking);

		for (nCntRanking = 0; nCntRanking < RANKING_MAX * RANKING_DATE; nCntRanking++)
		{
			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntRanking, 2);
		}
}

// ====================================================================================================
//
// 頂点の作成
//
// ====================================================================================================
void MakeVertexRanking(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;			// 頂点情報へのポイント
	int nCntRanking;			// ランキングカウント
	int nCntRankingData;		// ランキングカウント

	// オブジェクトの頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * RANKING_MAX * RANKING_DATE, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffRanking, NULL);

	// 頂点情報の設定
	// 頂点データの範囲をロックし、頂点バッファへのポインタ
	g_pVtxBuffRanking->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntRankingData = 0; nCntRankingData < RANKING_DATE; nCntRankingData++)
	{
		for (nCntRanking = 0; nCntRanking < RANKING_MAX; nCntRanking++)
		{
			pVtx[0].pos = D3DXVECTOR3(g_RankingPos.x + (-RANKING_SIZE / 2) - (RANKING_SIZE + 20) * nCntRanking,	
				g_RankingPos.y + (-RANKING_SIZE / 2) + (RANKING_SIZE + 50) * nCntRankingData, 0.0f);							// 一つ目の頂点
			pVtx[1].pos = D3DXVECTOR3(g_RankingPos.x + (RANKING_SIZE / 2) - (RANKING_SIZE + 20) * nCntRanking + RANKING_SIZE,
				g_RankingPos.y + (-RANKING_SIZE / 2) + (RANKING_SIZE + 50) * nCntRankingData, 0.0f);							// 二つ目の頂点
			pVtx[2].pos = D3DXVECTOR3(g_RankingPos.x + (-RANKING_SIZE / 2) - (RANKING_SIZE + 20) * nCntRanking,
				g_RankingPos.y + (RANKING_SIZE / 2) + (RANKING_SIZE + 50) * nCntRankingData + RANKING_SIZE, 0.0f);				// 三つ目の頂点
			pVtx[3].pos = D3DXVECTOR3(g_RankingPos.x + (RANKING_SIZE / 2) - (RANKING_SIZE + 20) * nCntRanking + RANKING_SIZE,
				g_RankingPos.y + (RANKING_SIZE / 2) + (RANKING_SIZE + 50) * nCntRankingData + RANKING_SIZE, 0.0f);				// 四つ目の頂点

			pVtx[0].rhw = 1.0f;	// 一つ目の頂点作成
			pVtx[1].rhw = 1.0f;	// 二つ目の頂点作成
			pVtx[2].rhw = 1.0f;	// 三つ目の頂点作成
			pVtx[3].rhw = 1.0f;	// 四つ目の頂点作成

			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// 一つ目の色設定
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// 二つ目の色設定
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// 三つ目の色設定
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// 四つ目の色設定

			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);		// 一つ目のテクスチャ
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);		// 二つ目のテクスチャ
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);		// 三つ目のテクスチャ
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);		// 四つ目のテクスチャ

			pVtx += 4;
		}
	}
	// アンロック
	g_pVtxBuffRanking->Unlock();
}

// ====================================================================================================
//
// ランキングの変更
//
// ====================================================================================================
void AddRanking(int nPoint,int nRankingCnt)
{
	VERTEX_2D *pVtx;		// 頂点情報へのポイント
	int nCntRanking;		// ランキングカウント
	int nCntRankingData;	// ランキングカウント
	int nRanking;			// 桁ランキング
	float fRanking;
	ROAD *pLoad;

	pLoad = GetLoad();

	// 頂点データの範囲をロックし、頂点バッファへのポインタ
	g_pVtxBuffRanking->Lock(0, 0, (void **)&pVtx, 0);


	for (nCntRankingData = 0; nCntRankingData < RANKING_DATE; nCntRankingData++, pLoad++)
	{
		g_aRankin[nCntRankingData].nPoint = pLoad->nPoint;

		for (nCntRanking = 0; nCntRanking < RANKING_MAX; nCntRanking++)
		{
			nRanking = g_aRankin[nCntRankingData].nPoint % (int)powf(10.0f, (float)nCntRanking + 1.0f) / (int)powf(10.0f, (float)nCntRanking);
			fRanking = (float)nRanking / 10.0f;

			pVtx[0].pos = D3DXVECTOR3(g_RankingPos.x + (-RANKING_SIZE / 2) - (RANKING_SIZE + 20) * nCntRanking,
				g_RankingPos.y + (-RANKING_SIZE / 2) + (RANKING_SIZE + 60) * nCntRankingData, 0.0f);							// 一つ目の頂点
			pVtx[1].pos = D3DXVECTOR3(g_RankingPos.x + (RANKING_SIZE / 2) - (RANKING_SIZE + 20) * nCntRanking + RANKING_SIZE,
				g_RankingPos.y + (-RANKING_SIZE / 2) + (RANKING_SIZE + 60) * nCntRankingData, 0.0f);							// 二つ目の頂点
			pVtx[2].pos = D3DXVECTOR3(g_RankingPos.x + (-RANKING_SIZE / 2) - (RANKING_SIZE + 20) * nCntRanking,
				g_RankingPos.y + (RANKING_SIZE / 2) + (RANKING_SIZE + 60) * nCntRankingData + RANKING_SIZE, 0.0f);				// 三つ目の頂点
			pVtx[3].pos = D3DXVECTOR3(g_RankingPos.x + (RANKING_SIZE / 2) - (RANKING_SIZE + 20) * nCntRanking + RANKING_SIZE,
				g_RankingPos.y + (RANKING_SIZE / 2) + (RANKING_SIZE + 60) * nCntRankingData + RANKING_SIZE, 0.0f);				// 四つ目の頂点

			pVtx[0].tex = D3DXVECTOR2(fRanking,  0.0f);				// 一つ目のテクスチャ
			pVtx[1].tex = D3DXVECTOR2(fRanking + 0.1f, 0.0f);		// 二つ目のテクスチャ
			pVtx[2].tex = D3DXVECTOR2(fRanking,  1.0f);				// 三つ目のテクスチャ
			pVtx[3].tex = D3DXVECTOR2(fRanking + 0.1f, 1.0f);		// 四つ目のテクスチャ

			pVtx += 4;
		}
	}
	// アンロック
	g_pVtxBuffRanking->Unlock();
}