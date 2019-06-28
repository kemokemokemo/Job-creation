//=============================================================================
//
// テキスト処理 [Text.cpp]
// Author : Kimura Kouta
//
//=============================================================================
#include "GameText.h"
#include "Title.h"//インクルードファイル
#include "input.h"
#include "fade.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TEXT_TEX01 "DATA/TEX/satan_rogo.png"		//読み込むテクスチャファイル名
#define TEXT_TEX02 "DATA/TEX/GameOver000.png"		//読み込むテクスチャファイル名
#define TEXT_TEX03 "DATA/TEX/text000.png"		//読み込むテクスチャファイル名
#define TEXT_TEX04 "DATA/TEX/ENTER.png"		//読み込むテクスチャファイル名
#define TEXT_TEX05 "DATA/TEX/tuto2.png"		//読み込むテクスチャファイル名
#define TEXT_TEX06 "DATA/TEX/zannki.png"		//読み込むテクスチャファイル名
#define TEXT_TEX07 "DATA/TEX/kuria.png"		//読み込むテクスチャファイル名

//=============================================================================
// プロトタイプ宣言
//=============================================================================

//=============================================================================
// グローバル変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9		g_apTextureGameText[MAX_GAMETEXT] = {};	// テクスチャへのポインタ(敵の数の分だけ読み込む)
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGameText = NULL;		// 頂点バッファへのポインタ
GAMETEXT g_aGameText[MAX_GAMETEXT];

float g_GameAlfha;

//=============================================================================
// 初期化処理
//=============================================================================
void InitGameText(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D *pVtx;
	int nCntText= 0;
	g_GameAlfha = 0;

	// 敵の情報を初期化
	for (nCntText = 0; nCntText < MAX_GAMETEXT; nCntText++)
	{
		g_aGameText[nCntText].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGameText[nCntText].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGameText[nCntText].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aGameText[nCntText].sizex = 0;
		g_aGameText[nCntText].sizey = 0;
		g_aGameText[nCntText].bUse = false;
		g_aGameText[nCntText].nType = 0;
		g_aGameText[nCntText].bAlfa = false;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		TEXT_TEX01,
		&g_apTextureGameText[0]);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		TEXT_TEX02,
		&g_apTextureGameText[1]);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		TEXT_TEX03,
		&g_apTextureGameText[2]);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		TEXT_TEX04,
		&g_apTextureGameText[3]);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		TEXT_TEX05,
		&g_apTextureGameText[4]);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		TEXT_TEX06,
		&g_apTextureGameText[5]);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		TEXT_TEX07,
		&g_apTextureGameText[6]);

	// オブジェクトの頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_GAMETEXT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGameText,
		NULL);

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffGameText->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntText = 0; nCntText < MAX_GAMETEXT; nCntText++)
	{
		//頂点座標の設定(右回りで設定する）
		pVtx[0].pos = D3DXVECTOR3(g_aGameText[nCntText].pos.x - g_aGameText[nCntText].sizex, g_aGameText[nCntText].pos.y - g_aGameText[nCntText].sizey , 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aGameText[nCntText].pos.x + g_aGameText[nCntText].sizex, g_aGameText[nCntText].pos.y - g_aGameText[nCntText].sizey , 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aGameText[nCntText].pos.x - g_aGameText[nCntText].sizex, g_aGameText[nCntText].pos.y + g_aGameText[nCntText].sizey , 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aGameText[nCntText].pos.x + g_aGameText[nCntText].sizex, g_aGameText[nCntText].pos.y + g_aGameText[nCntText].sizey , 0.0f);

		//rhwの設定（値は1.0で固定）：2Dとして動かすのに必要なもの
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定(0～255の値で設定）
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	// 頂点データをアンロックする
	g_pVtxBuffGameText->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitGameText(void)
{
	int nCntText = 0;
	for (nCntText = 0; nCntText < MAX_GAMETEXT; nCntText++)
	{
		// テクスチャの開放
		if (g_apTextureGameText[nCntText] != NULL)
		{
			g_apTextureGameText[nCntText]->Release();
			g_apTextureGameText[nCntText] = NULL;
		}

		if (g_pVtxBuffGameText != NULL)
			// 頂点バッファの開放
		{
			g_pVtxBuffGameText->Release();
			g_pVtxBuffGameText = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGameText(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawGameText(void)
{
	int nCntText = 0;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffGameText, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntText = 0; nCntText < MAX_GAMETEXT; nCntText++)
	{
		if (g_aGameText[nCntText].bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_apTextureGameText[g_aGameText[nCntText].nType]);
			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntText, 2);
		}
	}
}

//=============================================================================
// 敵の設定
//=============================================================================
void SetGameText(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, int sizex, int sizey, int nType)
{
	VERTEX_2D *pVtx;
	int nCntText = 0;

	g_pVtxBuffGameText->Lock(0, 0, (void**)&pVtx, 0);		//頂点バッファのロック
	for (nCntText = 0; nCntText < MAX_GAMETEXT; nCntText++)
	{
		if (g_aGameText[nCntText].bUse == false)
		{
			g_aGameText[nCntText].pos = pos;
			g_aGameText[nCntText].sizex = sizex;
			g_aGameText[nCntText].sizey = sizey;
			g_aGameText[nCntText].col = col;
			g_aGameText[nCntText].move = move;
			g_aGameText[nCntText].nType = nType;

			//頂点座標の設定(右回りで設定する）
			pVtx[0].pos = D3DXVECTOR3(g_aGameText[nCntText].pos.x - g_aGameText[nCntText].sizex , g_aGameText[nCntText].pos.y - g_aGameText[nCntText].sizey , 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aGameText[nCntText].pos.x + g_aGameText[nCntText].sizex , g_aGameText[nCntText].pos.y - g_aGameText[nCntText].sizey , 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aGameText[nCntText].pos.x - g_aGameText[nCntText].sizex , g_aGameText[nCntText].pos.y + g_aGameText[nCntText].sizey , 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aGameText[nCntText].pos.x + g_aGameText[nCntText].sizex , g_aGameText[nCntText].pos.y + g_aGameText[nCntText].sizey , 0.0f);

			g_aGameText[nCntText].bUse = true;
			break;

		}
		pVtx += 4;
	}
	g_pVtxBuffGameText->Unlock();		//頂点バッファのアンロック
}

//=============================================================================
// 敵の取得
//=============================================================================
GAMETEXT *GetGameText(void)
{
	return &g_aGameText[0];
}