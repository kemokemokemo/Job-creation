//=============================================================================
//
// 影の処理 [Shadow.cpp]
// Author : kimura kouta
//
//=============================================================================
#include "Shadow.h"
#include "model.h"
#include "player.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define SHADOW_TEX "DATA/TEX/shadow.jpg"	//読み込むテクスチャファイル名
#define MAX_SHADOW	(256)

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void MakeVertexShadow(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// 影の構造体
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;					//ポジション
	D3DXVECTOR3 rot;					//回転
	D3DXMATRIX mtxWorldSadow;			//ワールドマトリックス
	bool		bUse;					//使用しているかどうか
} SHADOW;

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9		 g_pTextureShadow = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;		//頂点バッファへのポインタ

SHADOW    g_Shadow[MAX_SHADOW];

//=============================================================================
// 初期化処理
//=============================================================================
void InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	//変数宣言
	int nCntShadow;

	// 構造体の初期設定
	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		g_Shadow[nCntShadow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Shadow[nCntShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Shadow[nCntShadow].bUse = false;
	}

	MakeVertexShadow(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitShadow(void)
{
	if (g_pTextureShadow !=NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}
	// 頂点バッファの開放
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateShadow(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス
	SHADOW*pShadow;

	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	pShadow = &g_Shadow[0];

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++, pShadow++)
	{
		if (pShadow->bUse)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&pShadow->mtxWorldSadow);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, pShadow->rot.y, pShadow->rot.x, pShadow->rot.z);
			D3DXMatrixMultiply(&pShadow->mtxWorldSadow, &pShadow->mtxWorldSadow, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, pShadow->pos.x, pShadow->pos.y, pShadow->pos.z);
			D3DXMatrixMultiply(&pShadow->mtxWorldSadow, &pShadow->mtxWorldSadow, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &pShadow->mtxWorldSadow);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureShadow);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntShadow, 2);
		}
	}

	//通常ブレンド
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
// 影の作成
//=============================================================================
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//変数宣言
	int nCntShadow;

	// 頂点情報の作成
	VERTEX_3D *pVtx;

	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (!g_Shadow[nCntShadow].bUse)
		{
			g_Shadow[nCntShadow].pos = pos;
			g_Shadow[nCntShadow].rot = rot;
			//大きさを基準に頂点を設定_SIZEを決める
			pVtx[0].Pos = D3DXVECTOR3(-20.0f, 0.0f, 20.0f);
			pVtx[1].Pos = D3DXVECTOR3(20.0, 0.0f, 20.0f);
			pVtx[2].Pos = D3DXVECTOR3(-20.0f, 0.0f, -20.0f);
			pVtx[3].Pos = D3DXVECTOR3(20.0f, 0.0f, -20.0f);
			g_Shadow[nCntShadow].bUse = true;
			break;
		}
		pVtx += 4;
	}
	g_pVtxBuffShadow->Unlock();
	return nCntShadow;
}

//=============================================================================
// 影の消去
//=============================================================================
void DeleteShadow(int hIdxShadow)
{
	g_Shadow[hIdxShadow].bUse = false;
}

//=============================================================================
// 影のポジションの設定
//=============================================================================
void SetPositionShadow(int hIdxShadow, D3DXVECTOR3 pos)
{
	MODEL *pModel;
	pModel = GetModel();

	PLAYER *pPlayer;
	pPlayer = GetPlayer();


	g_Shadow[hIdxShadow].pos = D3DXVECTOR3(pos.x, pos.y, pos.z);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexShadow(LPDIRECT3DDEVICE9 pDevice)
{

	D3DXCreateTextureFromFile(
		pDevice,
		SHADOW_TEX,
		&g_pTextureShadow);

	// 頂点情報の作成
	VERTEX_3D *pVtx;

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		//頂点座標の設定(右回りで設定する）
		pVtx[0].Pos = D3DXVECTOR3(-10.0f, 0.0f, 10.0f);
		pVtx[1].Pos = D3DXVECTOR3(10.0, 0.0f, 10.0f);
		pVtx[2].Pos = D3DXVECTOR3(-10.0f, 0.0f, -10.0f);
		pVtx[3].Pos = D3DXVECTOR3(10.0f, 0.0f, -10.0f);

		//頂点ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラーの設定(0～255の値で設定）
		pVtx[0].Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	g_pVtxBuffShadow->Unlock();
}

