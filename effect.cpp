//=============================================================================
//
// エフェクトの処理 [effect.cpp]
// Author : KIMURA KOUTA
//
//=============================================================================
#include "effect.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define	TEXTURE_EFFECT		"DATA/TEX/effect000.jpg"		// 読み込むテクスチャファイル名
#define	TEXTURE_EFFECT2		"DATA/TEX/effect001.jpg"		// 読み込むテクスチャファイル名
#define	TEXTURE_EFFECT3		"DATA/TEX/efect002.jpg"			// 読み込むテクスチャファイル名
#define	TEXTURE_EFFECT4		"DATA/TEX/effect003.jpg"		// 読み込むテクスチャファイル名
#define	TEXTURE_EFFECT5		"DATA/TEX/effect004.jpg"		// 読み込むテクスチャファイル名
#define	TEXTURE_EFFECT6		"DATA/TEX/effect005.jpg"		// 読み込むテクスチャファイル名
#define	MAX_EFFECT			(5000)							// エフェクトの最大数

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureEffect[MAX_EFFECT] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;	// 頂点バッファへのポインタ

EFFECT					g_aEffect[MAX_EFFECT];		// エフェクト情報

//=============================================================================
// 初期化処理
//=============================================================================
void InitEffect(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//変数の初期化
	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		g_aEffect[nCntEffect].fRadius = 50.0f;
		g_aEffect[nCntEffect].nType = 0;
		g_aEffect[nCntEffect].ParticlenType = 0;
		g_aEffect[nCntEffect].nLife = 0;
		g_aEffect[nCntEffect].bUse = false;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_EFFECT,		// ファイルの名前
		&g_pTextureEffect[0]);	// 読み込むメモリー

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_EFFECT2,		// ファイルの名前
		&g_pTextureEffect[1]);	// 読み込むメモリー

	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_EFFECT3,		// ファイルの名前
		&g_pTextureEffect[2]);	// 読み込むメモリー

	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_EFFECT4,		// ファイルの名前
		&g_pTextureEffect[3]);	// 読み込むメモリー

	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_EFFECT5,		// ファイルの名前
		&g_pTextureEffect[4]);	// 読み込むメモリー

	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_EFFECT5,		// ファイルの名前
		&g_pTextureEffect[5]);	// 読み込むメモリー

	// 頂点情報の作成
	MakeVertexEffect(pDevice);

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEffect(void)
{
	// テクスチャの開放
	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_pTextureEffect[nCntEffect] != NULL)
		{
			g_pTextureEffect[nCntEffect]->Release();
			g_pTextureEffect[nCntEffect] = NULL;
		}
	}

	// 頂点バッファの開放
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEffect(void)
{
	//変数宣言
	int nCntEffect = 0;
	int nLife = 0;
	VERTEX_3D *pVtx;


	// 頂点情報の設定
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)					 
		{
			g_aEffect[nCntEffect].nLife--;
			g_aEffect[nCntEffect].fRadius -= 3.0f;
			if (g_aEffect[nCntEffect].fRadius <= 0)
			{
				g_aEffect[nCntEffect].fRadius = 0;
			}

			g_aEffect[nCntEffect].pos += g_aEffect[nCntEffect].move;

			if (g_aEffect[nCntEffect].nType == 0)
			{
				//頂点座標の設定(右回りで設定する）
				pVtx[0].Pos = D3DXVECTOR3(-2.5f, 2.5f, 0.0f);
				pVtx[1].Pos = D3DXVECTOR3(2.5f, 2.5f, 0.0f);
				pVtx[2].Pos = D3DXVECTOR3(-2.5f, -2.5f, 0.0f);
				pVtx[3].Pos = D3DXVECTOR3(2.5f, -2.5f, 0.0f);
			}

			if (g_aEffect[nCntEffect].nType == 1)
			{
				//頂点座標の設定(右回りで設定する）
				pVtx[0].Pos = D3DXVECTOR3(-2.5f, 100.5f, 0.0f);
				pVtx[1].Pos = D3DXVECTOR3(2.5f, 100.5f, 0.0f);
				pVtx[2].Pos = D3DXVECTOR3(-2.5f, -100.5f, 0.0f);
				pVtx[3].Pos = D3DXVECTOR3(2.5f, -100.5f, 0.0f);
			}

			//頂点カラーの設定(0～255の値で設定）
			pVtx[0].Col = g_aEffect[nCntEffect].col, g_aEffect[nCntEffect].col,g_aEffect[nCntEffect].col,g_aEffect[nCntEffect].col;
			pVtx[1].Col = g_aEffect[nCntEffect].col, g_aEffect[nCntEffect].col,g_aEffect[nCntEffect].col,g_aEffect[nCntEffect].col;
			pVtx[2].Col = g_aEffect[nCntEffect].col, g_aEffect[nCntEffect].col,g_aEffect[nCntEffect].col,g_aEffect[nCntEffect].col;
			pVtx[3].Col = g_aEffect[nCntEffect].col, g_aEffect[nCntEffect].col,g_aEffect[nCntEffect].col,g_aEffect[nCntEffect].col;

			if (g_aEffect[nCntEffect].nLife == 0)
			{
				g_aEffect[nCntEffect].bUse = false;
			}

			if (g_aEffect[nCntEffect].pos.y <= 0)
			{
				g_aEffect[nCntEffect].bUse = false;
			}

		}
		pVtx += 4;
	}
	// 頂点データをアンロックする
	g_pVtxBuffEffect->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntEffect = 0;

	D3DXMATRIX mtxrot, mtxTrans, mtxView;				//計算用マトリックス

	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// レンダーステート(加算合成処理)
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);				//アルファブレンドを行う
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	// ポリゴンの描画
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aEffect[nCntEffect].mtxWorldWall);

			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			g_aEffect[nCntEffect].mtxWorldWall._11 = mtxView._11;//X軸
			g_aEffect[nCntEffect].mtxWorldWall._12 = mtxView._21;//X軸
			g_aEffect[nCntEffect].mtxWorldWall._13 = mtxView._31;//X軸
			g_aEffect[nCntEffect].mtxWorldWall._21 = mtxView._12;//Y軸
			g_aEffect[nCntEffect].mtxWorldWall._22 = mtxView._22;//Y軸
			g_aEffect[nCntEffect].mtxWorldWall._23 = mtxView._32;//Y軸

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxrot,
				rot.y,
				rot.x,
				rot.z);
			D3DXMatrixMultiply(&g_aEffect[nCntEffect].mtxWorldWall,
				&g_aEffect[nCntEffect].mtxWorldWall,
				&mtxrot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans,
				g_aEffect[nCntEffect].pos.x,
				g_aEffect[nCntEffect].pos.y,
				g_aEffect[nCntEffect].pos.z);
			D3DXMatrixMultiply(&g_aEffect[nCntEffect].mtxWorldWall,
				&g_aEffect[nCntEffect].mtxWorldWall,
				&mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aEffect[nCntEffect].mtxWorldWall);

			// 頂点バッファをデータストリームにバインド
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureEffect[g_aEffect[nCntEffect].nType]);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntEffect, 2);

		}
	}

	// レンダーステート(通常ブレンド処理)
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);				//アルファブレンドを行う
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

}

//=============================================================================
// 頂点の作成
//=============================================================================
void MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D *pVtx;
	int nCntEffect = 0;

	// オブジェクトの頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	// 頂点情報の設定
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		//頂点座標の設定(右回りで設定する）
		pVtx[0].Pos = D3DXVECTOR3(-15.0f, 15.0f, 0.0f);
		pVtx[1].Pos = D3DXVECTOR3(15.0f, 15.0f, 0.0f);
		pVtx[2].Pos = D3DXVECTOR3(-15.0f, -15.0f, 0.0f);
		pVtx[3].Pos = D3DXVECTOR3(15.0f, -15.0f, 0.0f);

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

		//テクスチャの設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	// 頂点データをアンロックする
	g_pVtxBuffEffect->Unlock();
}

//=============================================================================
// エフェクト設定
//=============================================================================
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, int nLife,int nType)
{
	//変数宣言
	int nCntEffect;
	VERTEX_3D *pVtx;

	// 頂点情報の設定
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == false)
		{
			g_aEffect[nCntEffect].pos = pos;
			g_aEffect[nCntEffect].move = move;
			g_aEffect[nCntEffect].col = col;
			g_aEffect[nCntEffect].nType = nType;
			g_aEffect[nCntEffect].fRadius = fRadius;
			g_aEffect[nCntEffect].nLife = nLife;
			g_aEffect[nCntEffect].bUse = true;
			break;
		}
		pVtx += 4;
	}
	// 頂点データをアンロックする
	g_pVtxBuffEffect->Unlock();
}

//=============================================================================
// パーティクル設定
//=============================================================================
void SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, int nLife, int nType)
{
	int nCntParticle;
	VERTEX_3D *pVtx;

	// 頂点情報の設定
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntParticle = 0; nCntParticle < MAX_EFFECT; nCntParticle++)
	{
		if (g_aEffect[nCntParticle].bUse == false)
		{
			g_aEffect[nCntParticle].pos = pos;
			g_aEffect[nCntParticle].move = move;
			g_aEffect[nCntParticle].col = col;
			g_aEffect[nCntParticle].nType = nType;
			g_aEffect[nCntParticle].fRadius = fRadius;
			g_aEffect[nCntParticle].nLife = nLife;
			g_aEffect[nCntParticle].bUse = true;
			break;
		}
		pVtx += 4;
	}
	// 頂点データをアンロックする
	g_pVtxBuffEffect->Unlock();
}
