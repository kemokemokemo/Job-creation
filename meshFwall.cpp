//=============================================================================
//
// ポリゴン処理 [MeshWall.cpp]
// Author : KIM JOHNUN
//
//=============================================================================
#include "meshFwall.h"
#include "input.h"

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void MakeVertexMeshWall(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9		 g_pTextureMeshWall = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshWall = NULL;		//頂点バッファへのポインタ
PDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshWall = NULL;		//頂点バッファへのポインタ

MESHWALL		g_MeshWall[MAX_WALL];

int nNumrertexMashWall;
int nNumIndexMashWall;
int nNumPolygonMashWall;

//=============================================================================
// 初期化処理
//=============================================================================
void InitMeshWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	// 位置・回転の初期設定
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		g_MeshWall[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_MeshWall[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_MeshWall[nCntWall].bUse = false;
	}

	nNumrertexMashWall = (WIDTH + 1) * (HEIGHT + 1);
	nNumIndexMashWall = (WIDTH * 2 + 2)*HEIGHT + 2 * (HEIGHT - 1);
	nNumPolygonMashWall = WIDTH*HEIGHT * 2 + 4 * (HEIGHT - 1);

	// 頂点情報の作成
	MakeVertexMeshWall(pDevice);
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitMeshWall(void)
{
	if (g_pTextureMeshWall!=NULL)
	{
		g_pTextureMeshWall->Release();
		g_pTextureMeshWall = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffMeshWall != NULL)
	{
		g_pVtxBuffMeshWall->Release();
		g_pVtxBuffMeshWall = NULL;
	}

	if (g_pIdxBuffMeshWall != NULL)
	{
		g_pIdxBuffMeshWall->Release();
		g_pIdxBuffMeshWall = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateMeshWall(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawMeshWall(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				// 計算用マトリックス

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_MeshWall[nCntWall].bUse)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_MeshWall[nCntWall].mtxWorldWall);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_MeshWall[nCntWall].rot.y, g_MeshWall[nCntWall].rot.x, g_MeshWall[nCntWall].rot.z);
			D3DXMatrixMultiply(&g_MeshWall[nCntWall].mtxWorldWall, &g_MeshWall[nCntWall].mtxWorldWall, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_MeshWall[nCntWall].pos.x, g_MeshWall[nCntWall].pos.y, g_MeshWall[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_MeshWall[nCntWall].mtxWorldWall, &g_MeshWall[nCntWall].mtxWorldWall, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_MeshWall[nCntWall].mtxWorldWall);

			//インデックスバッファの設定
			pDevice->SetIndices(g_pIdxBuffMeshWall);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffMeshWall, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureMeshWall);

			// ポリゴンの描画
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, nNumrertexMashWall, 0, nNumIndexMashWall);
		}
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexMeshWall(LPDIRECT3DDEVICE9 pDevice)
{
	//変数宣言
	int nCntIdx = 0;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		POLTGON0_TEX,
		&g_pTextureMeshWall);

	// 頂点情報のポインタ
	VERTEX_3D *pVtx;

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * nNumrertexMashWall,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshWall,
		NULL);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(VERTEX_3D) * nNumIndexMashWall,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshWall,
		NULL);

	g_pVtxBuffMeshWall->Lock(0, 0, (void**)&pVtx, 0);

		for (float nCntH = 0; nCntH < HEIGHT + 1; nCntH++)
		{
			for (float nCntW = 0; nCntW < WIDTH + 1; nCntW++)
			{
				//頂点座標の設定(右回りで設定する）
				pVtx[0].Pos = D3DXVECTOR3((-SIZE_X * WIDTH / 2) + (nCntW * SIZE_X),(SIZE_Y * HEIGHT / 2) - (nCntH * SIZE_Y),  0.0f);

				//頂点ベクトルの設定
				pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

				//頂点カラーの設定(0～255の値で設定）
				pVtx[0].Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				pVtx[0].tex = D3DXVECTOR2(0.5f * nCntW, 0.5f * nCntH);
				pVtx += 1; 
			}
		}

	g_pVtxBuffMeshWall->Unlock();

	//インデックスデータへのポインタ
	WORD*pIdx;

	g_pIdxBuffMeshWall->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCnt = 0; nCnt < nNumIndexMashWall; nCntIdx += 2)
	{
		if ((nCntIdx + 2) % ((WIDTH + 1) * 2 + 2) == 0 && nCntIdx != 0)
		{
			pIdx[nCntIdx] = nCnt - 1;
			pIdx[nCntIdx + 1] = (WIDTH + 1 + nCnt);
		}
		else
		{
			pIdx[nCntIdx] = (WIDTH +1 + nCnt);
			pIdx[nCntIdx +1] = nCnt;
			nCnt++;
		}
	}
	g_pIdxBuffMeshWall->Unlock();
}
//=============================================================================
// 壁の取得
//=============================================================================
int SetMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//変数宣言
	int nCntWall;

	// 頂点情報の作成
	VERTEX_3D *pVtx;

	g_pVtxBuffMeshWall->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (!g_MeshWall[nCntWall].bUse)
		{
			g_MeshWall[nCntWall].pos = pos;
			g_MeshWall[nCntWall].rot = rot;
			g_MeshWall[nCntWall].bUse = true;
			break;
		}
	}
	g_pVtxBuffMeshWall->Unlock();
	return nCntWall;
}

//=======================================================================================================
// 壁の取得
//=======================================================================================================
MESHWALL * GetMeshWall(void)
{
	return &g_MeshWall[0];
}

