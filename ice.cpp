//=============================================================================
//
// 氷処理 [ice.cpp]
// Author : KIMURA KOUTA
//
//=============================================================================
#include"ice.h"
#include"player.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_ICE	(1)

//=============================================================================
// マクロ定義
//=============================================================================
ICE g_Ice[MAX_ICE];

//=============================================================================
// グローバル変数
//=============================================================================
LPD3DXMESH g_pMeshIce = NULL;							//メッシュ情報へのポインタ
LPD3DXBUFFER g_pBuffMatIce = NULL;						//マテリアル情報へのポインタ
LPDIRECT3DTEXTURE9 g_pTextureIce = NULL;
DWORD g_nNumMatIce = 0;									//マテリアル情報の数

//=============================================================================
// 初期化処理
//=============================================================================
void InitIce(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nCntIce = 0; nCntIce < MAX_ICE; nCntIce++)
	{
		//初期設定
		g_Ice[nCntIce].pos = D3DXVECTOR3(-1200.0f, 300.0f, 800.0f);
		g_Ice[nCntIce].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Ice[nCntIce].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Ice[nCntIce].fDistance = sqrtf(100.0f)*sqrtf(100.0f);
		g_Ice[nCntIce].nLife = 1;
		g_Ice[nCntIce].bUse = false;

		//Xファイルの読み込み
		D3DXLoadMeshFromX("DATA/MODEL/ice.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatIce,
			NULL,
			&g_nNumMatIce,
			&g_pMeshIce);

		//モデルの頂点座標の最大値・最小値の設定
		int nNumVertices;				//頂点数
		DWORD sizeFVF;					//頂点フォーマットのサイズ
		BYTE *pVertexBuffer;			//頂点バッファへのポインタ

		g_Ice[nCntIce].vtxMin = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);
		g_Ice[nCntIce].vtxMax = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);

		//頂点数を取得
		nNumVertices = g_pMeshIce->GetNumVertices();

		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_pMeshIce->GetFVF());

		//頂点バッファをロック
		g_pMeshIce->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertexBuffer);

		for (int nCntVtx = 0; nCntVtx < nNumVertices; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVertexBuffer;

			//すべての頂点情報を比較して最大値・最小値を抜き出す
			if (g_Ice[nCntIce].vtxMin.x > vtx.x)
			{
				g_Ice[nCntIce].vtxMin.x = vtx.x;
			}
			if (g_Ice[nCntIce].vtxMin.y > vtx.y)
			{
				g_Ice[nCntIce].vtxMin.y = vtx.y;
			}
			if (g_Ice[nCntIce].vtxMin.z > vtx.z)
			{
				g_Ice[nCntIce].vtxMin.z = vtx.z;
			}
			if (g_Ice[nCntIce].vtxMax.x < vtx.x)
			{
				g_Ice[nCntIce].vtxMax.x = vtx.x;
			}
			if (g_Ice[nCntIce].vtxMax.y < vtx.y)
			{
				g_Ice[nCntIce].vtxMax.y = vtx.y;
			}
			if (g_Ice[nCntIce].vtxMax.z < vtx.z)
			{
				g_Ice[nCntIce].vtxMax.z = vtx.z;
			}

			pVertexBuffer += sizeFVF;
		}
	}
	//頂点バッファをアンロック
	g_pMeshIce->UnlockVertexBuffer();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEX/thEIAMVSCA.jpg", &g_pTextureIce);

	/*if (g_Ice.bUse == true)
	{
		g_Ice.IdxShadow = SetShadow(g_Ice.pos, g_Ice.rot);
	}*/
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitIce(void)
{
	//メッシュの開放
	if (g_pMeshIce != NULL)
	{
		g_pMeshIce->Release();
		g_pMeshIce = NULL;
	}

	//マテリアルの開放
	if (g_pBuffMatIce != NULL)
	{
		g_pBuffMatIce->Release();
		g_pBuffMatIce = NULL;
	}

	if (g_pTextureIce != NULL)
	{
		g_pTextureIce->Release();
		g_pTextureIce = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateIce(void)
{

	//プレイヤーの取得
	PLAYER * pPlayer;
	pPlayer = GetPlayer();
	int nCntIce = 0;

		//重力処理

		g_Ice[nCntIce].move.y -= 0.1f;


		g_Ice[nCntIce].posOld = g_Ice[nCntIce].pos;

		g_Ice[nCntIce].pos += g_Ice[nCntIce].move;

		g_Ice[nCntIce].pos = pPlayer->pos;

		g_Ice[nCntIce].rot = pPlayer->rot;

		/*if (g_Ice.bUse == true)
		{
			SetPositionShadow(g_Ice.IdxShadow, g_Ice.pos);
		}*/

		if (g_Ice[nCntIce].nLife <= 0)
		{
			g_Ice[nCntIce].bUse = false;
		}



		if (g_Ice[nCntIce].pos.y < 0.0f)
		{
			g_Ice[nCntIce].pos.y = 0.0f;
		}

		//if (pPlayer->nCntDeth == 30)
		//{
		//	g_Ice[nCntIce].move.y += 1;
		//}
	
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawIce(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	D3DXMATERIAL *pMat;
	D3DMATERIAL9 matDef;
	for (int nCntIce = 0; nCntIce < MAX_ICE; nCntIce++)
	{
		if (g_Ice[nCntIce].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Ice[nCntIce].mtxWorldObject);

			// スケールを反映


			//回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Ice[nCntIce].rot.y, g_Ice[nCntIce].rot.x, g_Ice[nCntIce].rot.z);
			D3DXMatrixMultiply(&g_Ice[nCntIce].mtxWorldObject, &g_Ice[nCntIce].mtxWorldObject, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Ice[nCntIce].pos.x, g_Ice[nCntIce].pos.y, g_Ice[nCntIce].pos.z);
			D3DXMatrixMultiply(&g_Ice[nCntIce].mtxWorldObject, &g_Ice[nCntIce].mtxWorldObject, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Ice[nCntIce].mtxWorldObject);

			//現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			//マテリアル情報に対するポインタを取得
			pMat = (D3DXMATERIAL*)g_pBuffMatIce->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_nNumMatIce; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//テクスチャの設定
				pDevice->SetTexture(0, g_pTextureIce);

				//描画
				g_pMeshIce->DrawSubset(nCntMat);
			}

			//マテリアルをデフォルトに戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}

//=============================================================================
// プレイヤーの取得
//=============================================================================
ICE *GetIce(void)
{
	return &g_Ice[0];
}

//=============================================================================
// 氷
//=============================================================================
void SetIce(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot)
{
	for (int nCntIce = 0; nCntIce < MAX_ICE; nCntIce++)
	{
		if (g_Ice[nCntIce].bUse == false)
		{
			g_Ice[nCntIce].pos = pos;
			g_Ice[nCntIce].rot = rot;
			g_Ice[nCntIce].move = move;
			g_Ice[nCntIce].bUse = true;
			break;
		}
	}
}