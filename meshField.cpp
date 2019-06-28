//=============================================================================
//
// ポリゴン処理 [MeshField.cpp]
// Author : 
//
//=============================================================================
#include "meshField.h"
#include "input.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define POLTGON0_TEX "DATA/TEX/umi.jpg"	//読み込むテクスチャファイル名
#define WIDTH	(20)
#define HEIGHT	(20)
#define SIZE_X	(1200)
#define SIZE_Z	(1200)
#define WAVE_W	(0.003f)
#define WAVE_H	(3.0f)

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void MakeVertexMeshField(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9		 g_pTextureMeshField = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField = NULL;		//頂点バッファへのポインタ
PDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;		//頂点バッファへのポインタ

D3DXVECTOR3 g_PosMeshField;								//ポリゴンの位置
D3DXVECTOR3 g_rotMeshField;								//ポリゴンの向き

D3DXMATRIX  g_mtxWorldMeshField;							//ワールドマトリックス

int nNumrertexMashField;
int nNumIndexMashField;
int nNumPolygonMashField;

int nCntNami;
float pos4;

bool bLUse;

//=============================================================================
// 初期化処理
//=============================================================================
void InitMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	bLUse = false;
	nCntNami = 0;
	// 位置・回転の初期設定
	g_PosMeshField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotMeshField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	nNumrertexMashField = (WIDTH + 1 ) * (HEIGHT + 1);
	nNumIndexMashField = (WIDTH * 2 + 2)*HEIGHT + 2 * (HEIGHT - 1);
	nNumPolygonMashField = WIDTH*HEIGHT * 2 + 4 * (HEIGHT - 1);

	// 頂点情報の作成
	MakeVertexMeshField(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitMeshField(void)
{
	if (g_pTextureMeshField!=NULL)
	{
		g_pTextureMeshField->Release();
		g_pTextureMeshField = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffMeshField != NULL)
	{
		g_pVtxBuffMeshField->Release();
		g_pVtxBuffMeshField = NULL;
	}

	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	// 頂点情報のポインタ
	VERTEX_3D *pVtx;
	float move = WAVE_W;

	//レンダラーステートの設定
	if (GetKeyboardTrigger(DIK_L))
	{
		if (bLUse == false)
		{
			bLUse = true;
		}
		else if(bLUse == true)
		{
			bLUse = false;
		}
	}

	if (bLUse == true)
	{
		pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}

	if (bLUse == false)
	{
		pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}

	//波の上下運動
	nCntNami++;

	if (nCntNami<=200)
	{
		g_PosMeshField.y += sinf(3.0f);
	}
	if (nCntNami >= 200)
	{
		g_PosMeshField.y -= sinf(3.0f);
	}
	if (nCntNami >= 400)
	{
		nCntNami = 0;
	}

	//波の流れ
	pos4 += move;

	g_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);

	for (float nCntH = 0; nCntH < HEIGHT + 1; nCntH++)
	{
		for (float nCntW = 0; nCntW < WIDTH + 1; nCntW++, pVtx++)
		{
			//頂点座標の設定(右回りで設定する）
			pVtx[0].Pos = D3DXVECTOR3((-SIZE_X * WIDTH / 2) + (nCntW * SIZE_X), 0.0f, (SIZE_Z * HEIGHT / 2) - (nCntH * SIZE_Z));

			pVtx[0].tex = D3DXVECTOR2(0.5f * nCntW + pos4 , 0.5f * nCntH);
		}
	}

	g_pVtxBuffMeshField->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawMeshField(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldMeshField);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshField.y, g_rotMeshField.x, g_rotMeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_PosMeshField.x, g_PosMeshField.y, g_PosMeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshField);

	//インデックスバッファの設定
	pDevice->SetIndices(g_pIdxBuffMeshField);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMeshField, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureMeshField);

	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0,0, nNumrertexMashField,0, nNumIndexMashField);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexMeshField(LPDIRECT3DDEVICE9 pDevice)
{
	//変数宣言
	int nCntIdx = 0;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		POLTGON0_TEX,
		&g_pTextureMeshField);

	// 頂点情報のポインタ
	VERTEX_3D *pVtx;

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * nNumrertexMashField,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshField,
		NULL);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(VERTEX_3D) * nNumIndexMashField,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField,
		NULL);

	g_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);

	for (float nCntH = 0; nCntH < HEIGHT + 1; nCntH++)
	{
		for (float nCntW = 0; nCntW < WIDTH + 1; nCntW++, pVtx++)
		{
			//頂点座標の設定(右回りで設定する）
			pVtx[0].Pos = D3DXVECTOR3((-SIZE_X * WIDTH / 2) + (nCntW * SIZE_X), 0.0f, (SIZE_Z * HEIGHT / 2) - (nCntH * SIZE_Z));

			//頂点ベクトルの設定
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//頂点カラーの設定(0～255の値で設定）
			pVtx[0].Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);

			//頂点カラーの設定
			pVtx[0].tex = D3DXVECTOR2(0.5f * nCntW + pos4, 0.5f * nCntH);
		}
	}

	g_pVtxBuffMeshField->Unlock();

	//インデックスデータへのポインタ
	WORD*pIdx;

	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCnt = 0; nCnt < nNumIndexMashField; nCntIdx += 2)
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
	g_pIdxBuffMeshField->Unlock();
}