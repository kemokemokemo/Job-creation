//=============================================================================
//
// スコア処理 [zanki.cpp]
// Author : KIMURA KOUTA
//
//=============================================================================
#include "zanki.h"
#include "player.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define	TEXTURE_ZANKI		"DATA/TEX/number002.png"	// 読み込むテクスチャファイル名
#define MAX_ZANKI   (1)
#define ZANKI_POS_X	(1150)			    //ポリゴンの表示位置(左上X)
#define ZANKI_POS_Y	(10)			    //ポリゴンの表示位置(左上Y)
#define ZANKI_SIZE_X	(60)			//ポリゴンのサイズ(横幅)
#define ZANKI_SIZE_Y	(100)			//ポリゴンのサイズ(立幅)
#define ZANKICOLOR_TEX   (255)

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void MakeVertexZanki(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// 構造体定義
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;				// 位置
	bool bUse;						// 死んだかどうか
	int zanki;
} ZANKI;

//=============================================================================
// グローバル変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTexturezanki = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffzanki = NULL;	// 頂点バッファへのポインタ

int						g_nzanki;				// スコア
ZANKI					g_azanki[MAX_ZANKI];
int g_zankirState;
int g_nCntzanki;

//=============================================================================
// 初期化処理
//=============================================================================
void InitZanki(void)
{
	int g_zankirState = 0;
	int nCntzanki = 0;
	int g_nzanki = 0;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
							TEXTURE_ZANKI,		// ファイルの名前
							&g_pTexturezanki);	// 読み込むメモリー

	// 頂点情報の作成
	MakeVertexZanki(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitZanki(void)
{
	// テクスチャの開放
	if (g_pVtxBuffzanki != NULL)
	{
		g_pVtxBuffzanki->Release();
		g_pVtxBuffzanki = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffzanki != NULL)
	{
		g_pVtxBuffzanki->Release();
		g_pVtxBuffzanki = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateZanki(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawZanki(void)
{
	int nCntzanki = 0;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffzanki, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTexturezanki);

	for (nCntzanki = 0; nCntzanki < MAX_ZANKI; nCntzanki++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntzanki, 2);
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
void MakeVertexZanki(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;
	int nCntzanki=0;

	// オブジェクトの頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ZANKI,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffzanki,
		NULL);

	// 頂点情報の設定
	g_pVtxBuffzanki->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntzanki = 0; nCntzanki < MAX_ZANKI; nCntzanki++)
	{
		//頂点座標の設定(右回りで設定する）
		pVtx[0].pos = D3DXVECTOR3(ZANKI_POS_X + 60 * nCntzanki + 30 * 1.0f, ZANKI_POS_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(ZANKI_POS_X + 60 * nCntzanki + 30 + ZANKI_SIZE_X * 1.0f, ZANKI_POS_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(ZANKI_POS_X + 60 * nCntzanki + 30 * 1.0f, ZANKI_POS_Y + ZANKI_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(ZANKI_POS_X + 60 * nCntzanki + 30 + ZANKI_SIZE_X * 1.0f, ZANKI_POS_Y + ZANKI_SIZE_Y, 0.0f);

		//rhwの設定（値は1.0で固定）：2Dとして動かすのに必要なもの
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定(0～255の値で設定）
		pVtx[0].col = D3DCOLOR_RGBA(ZANKICOLOR_TEX, ZANKICOLOR_TEX, ZANKICOLOR_TEX, ZANKICOLOR_TEX);
		pVtx[1].col = D3DCOLOR_RGBA(ZANKICOLOR_TEX, ZANKICOLOR_TEX, ZANKICOLOR_TEX, ZANKICOLOR_TEX);
		pVtx[2].col = D3DCOLOR_RGBA(ZANKICOLOR_TEX, ZANKICOLOR_TEX, ZANKICOLOR_TEX, ZANKICOLOR_TEX);
		pVtx[3].col = D3DCOLOR_RGBA(ZANKICOLOR_TEX, ZANKICOLOR_TEX, ZANKICOLOR_TEX, ZANKICOLOR_TEX);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4 ;
	}
	// 頂点データをアンロックする
	g_pVtxBuffzanki->Unlock();
}
//=============================================================================
// スコアの変更
//=============================================================================
void AddZanki(int nValue)
{
	int nCntzanki;
	int nzanki;
	VERTEX_2D *pVtx;

	g_nzanki += nValue;

	if (g_nzanki < 0)
	{
		g_nzanki = 0;
	}

	// 頂点情報の設定
	g_pVtxBuffzanki->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntzanki = 0; nCntzanki < MAX_ZANKI; nCntzanki++)
	{
		nzanki = g_nzanki / (int)powf(10.0f, MAX_ZANKI - nCntzanki - 1.0f * 1.0f) % 10;

		//テクスチャ画像の設定
		pVtx[0].tex = D3DXVECTOR2((nzanki*0.1f) + 0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((nzanki*0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((nzanki*0.1f) + 0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((nzanki*0.1f) + 0.1f, 1.0f);

		pVtx += 4;
	}
	// 頂点データをアンロックする
	g_pVtxBuffzanki->Unlock();
}

//==================================================================================================
// スコアの取得
//==================================================================================================
int GetZanki(void)
{
	return g_nzanki;
}