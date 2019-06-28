//=============================================================================
//
// スコア処理 [score.cpp]
// Author : KIMURA KOUTA
//
//=============================================================================
#include "score.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define	TEXTURE_SCORE		"DATA/TEX/number001.png"	// 読み込むテクスチャファイル名
#define MAX_SCORE   (8)
#define SCORE_POS_X	(0)			    //ポリゴンの表示位置(左上X)
#define SCORE_POS_Y	(0)			    //ポリゴンの表示位置(左上Y)
#define SCORE_SIZE_X	(40)			//ポリゴンのサイズ(横幅)
#define SCORE_SIZE_Y	(60)			//ポリゴンのサイズ(立幅)
#define SCORECOLOR_TEX   (255)

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// 構造体定義
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;				// 位置
	bool bUse;						// 死んだかどうか
	int score;
} SCORE;


//=============================================================================
// グローバル変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureScore = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;	// 頂点バッファへのポインタ

int						g_nScore;				// スコア
SCORE                   g_aScore[8];

//=============================================================================
// 初期化処理
//=============================================================================
void InitScore(void)
{

	int nCntScore = 0;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_nScore = 0;


	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
								TEXTURE_SCORE,		// ファイルの名前
								&g_pTextureScore);	// 読み込むメモリー

	// 頂点情報の作成
	MakeVertexScore(pDevice);

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitScore(void)
{
	// テクスチャの開放
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateScore(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawScore(void)
{
	int nCntScore = 0;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureScore);

	for (nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntScore, 2);
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;
	int nCntScore=0;


	// オブジェクトの頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

	// 頂点情報の設定
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		//頂点座標の設定(右回りで設定する）
		pVtx[0].pos = D3DXVECTOR3(SCORE_POS_X + 60 * nCntScore + 30 * 1.0f, SCORE_POS_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCORE_POS_X + 60 * nCntScore + 30 + SCORE_SIZE_X * 1.0f, SCORE_POS_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(SCORE_POS_X + 60 * nCntScore + 30 * 1.0f, SCORE_POS_Y + SCORE_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCORE_POS_X + 60 * nCntScore + 30 + SCORE_SIZE_X * 1.0f, SCORE_POS_Y + SCORE_SIZE_Y, 0.0f);

		//rhwの設定（値は1.0で固定）：2Dとして動かすのに必要なもの
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定(0～255の値で設定）
		pVtx[0].col = D3DCOLOR_RGBA(SCORECOLOR_TEX, SCORECOLOR_TEX, SCORECOLOR_TEX, SCORECOLOR_TEX);
		pVtx[1].col = D3DCOLOR_RGBA(SCORECOLOR_TEX, SCORECOLOR_TEX, SCORECOLOR_TEX, SCORECOLOR_TEX);
		pVtx[2].col = D3DCOLOR_RGBA(SCORECOLOR_TEX, SCORECOLOR_TEX, SCORECOLOR_TEX, SCORECOLOR_TEX);
		pVtx[3].col = D3DCOLOR_RGBA(SCORECOLOR_TEX, SCORECOLOR_TEX, SCORECOLOR_TEX, SCORECOLOR_TEX);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4 ;
	}
	// 頂点データをアンロックする
	g_pVtxBuffScore->Unlock();
}
	
//=============================================================================
// スコアの変更
//=============================================================================
void AddScore(int nValue)
{
	int nCntScore;
	int nScore;
	VERTEX_2D *pVtx;

	g_nScore += nValue;

	if (g_nScore < 0)
	{
		g_nScore = 0;
	}

	// 頂点情報の設定
  	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		nScore = g_nScore % (int)powf(10.0f, 8.0f - nCntScore) / (int)powf(10.0f, 8.0f - 1.0f - nCntScore);

		//テクスチャ画像の設定
		pVtx[0].tex = D3DXVECTOR2((nScore*0.1f) + 0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((nScore*0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((nScore*0.1f) + 0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((nScore*0.1f) + 0.1f, 1.0f);

		pVtx += 4;
	}
	// 頂点データをアンロックする
	g_pVtxBuffScore->Unlock();
}
//==================================================================================================
// スコアの取得
//==================================================================================================
int GetScore(void)
{
	return g_nScore;
}
