//=============================================================================
//
// 爆発処理 [Explosion.cpp]
// Author : Kimura Kouta
//
//=============================================================================
#include "Explosion.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_EXPLOSION (128)								// 発射できる弾の最大数
#define EXPLOSION_TEX "DATA/TEX/explosion000.png"		//読み込むテクスチャファイル名
#define EXPLOSION_SIZE_X	 (100)						//ポリゴンのサイズ(横幅)
#define EXPLOSION_SIZE_Y	 (100)						//ポリゴンのサイズ(立幅)
#define EXPLOSIONCOLOR_TEX   (255)
#define EXPLOSIONALPA_TEX    (255)

//=============================================================================
// 構造体定義
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;				// 位置
	D3DXCOLOR   col;				// 色
	D3DXMATRIX  mtxWorldWall;			//ワールドマトリックス
	bool bUse;						// 使用しているかどうか
	int nCounteAnim;
	int nPatternAnim;
	
}EXPLOSION;

//=============================================================================
// プロトタイプ宣言
//=============================================================================

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureExplosion = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;	// 頂点バッファへのポインタ

EXPLOSION g_aExplosion[MAX_EXPLOSION];

//=============================================================================
// 弾の初期化処理
//=============================================================================
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_3D *pVtx;
	int nCntExplosion;

	// 爆発の情報の初期化
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].col = D3DXCOLOR  (1.0f, 1.0f, 1.0f,1.0f);
		g_aExplosion[nCntExplosion].bUse = false;
		g_aExplosion[nCntExplosion].nCounteAnim = 0;	// アニメーションカウンタ
		g_aExplosion[nCntExplosion].nPatternAnim = 0;   // パターンナンバーの初期化
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		EXPLOSION_TEX,
		&g_pTextureExplosion);

	// オブジェクトの頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		//頂点座標の設定(右回りで設定する）
		pVtx[0].Pos = D3DXVECTOR3(-10.0f, 10.0f, 0.0f);
		pVtx[1].Pos = D3DXVECTOR3(10.0f, 10.0f, 0.0f);
		pVtx[2].Pos = D3DXVECTOR3(-10.0f, -10.0f, 0.0f);
		pVtx[3].Pos = D3DXVECTOR3(10.0f, -10.0f, 0.0f);

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
	// 頂点データをアンロックする
	g_pVtxBuffExplosion->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitExplosion(void)
{
	// テクスチャの開放
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}

	// 頂点バッファの開放
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateExplosion(void)
{
	VERTEX_3D *pVtx;
	// 弾カウンターの初期化
	int nCntExplosion;

	//頂点バッファのロック
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);		
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		// 弾が使用されている
		if (g_aExplosion[nCntExplosion].bUse == true)
		{
			g_aExplosion[nCntExplosion].nCounteAnim++;

			// 一定間隔が経過
			if (g_aExplosion[nCntExplosion].nCounteAnim % 3 == 0)
			{
				// パターンの初期化
				g_aExplosion[nCntExplosion].nPatternAnim = (g_aExplosion[nCntExplosion].nPatternAnim + 1) % 8;
				// テクスチャ座標の指定
				pVtx[0].tex = D3DXVECTOR2(0.0f + (g_aExplosion[nCntExplosion].nPatternAnim * 0.125f), 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.125f + (g_aExplosion[nCntExplosion].nPatternAnim * 0.125f), 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f + (g_aExplosion[nCntExplosion].nPatternAnim * 0.125f), 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.125f + (g_aExplosion[nCntExplosion].nPatternAnim * 0.125f), 1.0f);

				// 一定間隔が経過
				if (g_aExplosion[nCntExplosion].nPatternAnim % 8 == 0)
				{
					g_aExplosion[nCntExplosion].bUse = false;
				}
			}

			//頂点座標の設定(右回りで設定する）
			pVtx[0].Pos = D3DXVECTOR3(-15.0f, 15.0f, 15.0f);
			pVtx[1].Pos = D3DXVECTOR3(15.0, 15.0f, 15.0f);
			pVtx[2].Pos = D3DXVECTOR3(-15.0f, -15.0f, 15.0f);
			pVtx[3].Pos = D3DXVECTOR3(15.0f, -15.0f, 15.0f);
		}
		pVtx += 4; // 弾連射
	}
	//頂点バッファのアンロック
	g_pVtxBuffExplosion->Unlock();		
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			// デバイスの取得

	D3DXMATRIX mtxrot, mtxTrans, mtxView;				//計算用マトリックス

	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aExplosion[nCntExplosion].mtxWorldWall);

			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			g_aExplosion[nCntExplosion].mtxWorldWall._11 = mtxView._11;//X軸
			g_aExplosion[nCntExplosion].mtxWorldWall._12 = mtxView._21;//X軸
			g_aExplosion[nCntExplosion].mtxWorldWall._13 = mtxView._31;//X軸
			g_aExplosion[nCntExplosion].mtxWorldWall._21 = mtxView._12;//Y軸
			g_aExplosion[nCntExplosion].mtxWorldWall._22 = mtxView._22;//Y軸
			g_aExplosion[nCntExplosion].mtxWorldWall._23 = mtxView._32;//Y軸

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxrot,
				rot.y,
				rot.x,
				rot.z);
			D3DXMatrixMultiply(&g_aExplosion[nCntExplosion].mtxWorldWall,
				&g_aExplosion[nCntExplosion].mtxWorldWall,
				&mtxrot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans,
				g_aExplosion[nCntExplosion].pos.x,
				g_aExplosion[nCntExplosion].pos.y,
				g_aExplosion[nCntExplosion].pos.z);
			D3DXMatrixMultiply(&g_aExplosion[nCntExplosion].mtxWorldWall,
				&g_aExplosion[nCntExplosion].mtxWorldWall,
				&mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aExplosion[nCntExplosion].mtxWorldWall);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureExplosion);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntExplosion, 2);
		}
	}
	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
}


//============================================================================
// 爆発の設定
//=============================================================================
void SetExplotion(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	// 変数宣言
	VERTEX_3D *pVtx;
	int nCntExplosion;

	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);		//頂点バッファのロック

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)
		{
			g_aExplosion[nCntExplosion].pos = pos;
			g_aExplosion[nCntExplosion].col = col;
			g_aExplosion[nCntExplosion].bUse = true;
			break;
		}
		pVtx += 4;
	}
	g_pVtxBuffExplosion->Unlock();		//頂点バッファのアンロック
}