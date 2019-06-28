//=============================================================================
//
// モデル処理 [model.cpp]
// Author : KIMURA KOUTA
//
//=============================================================================
#include "model.h"
#include "input.h"
#include "camera.h"
#include "Shadow.h"
#include "bullet.h"
#include "effect.h"
#include "player.h"
#include "Game.h"
#include "fade.h"
#include "Controlar.h"
#include "GameText.h"
#include "sound.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MODEL_FILE		"DATA/road/model.txt"					//ファイル名

#define SPEED			(0.5f)									//プレイヤースピード

//=============================================================================
// グローバル変数
//=============================================================================
MODEL					 g_Model[MAX_MODEL];					// 読み込んだモデルの情報
LOADMODEL				 g_LoadModel[MAX_MODEL];				// 読み込んだモデルの情報

D3DXVECTOR3				g_fDistance;
int g_nCntCrear;

//=============================================================================
// 初期化処理
//=============================================================================
void InitModel(void)
{
	int nCntModel = 0;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		// 位置・向きの初期設定
		g_Model[nCntModel].Pos = D3DXVECTOR3(100.0f, 0.0f, 0.0f);
		g_Model[nCntModel].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Model[nCntModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Model[nCntModel].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_Model[nCntModel].Diffrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Model[nCntModel].nTypeTex = 0;
		g_Model[nCntModel].nTypeModel = 0;
		g_Model[nCntModel].bUse = false;
		g_Model[nCntModel].fRadius = 0;
		g_Model[nCntModel].fHeight = 0;
		g_Model[nCntModel].nLoad = MAX_MODELTYPE;
		g_Model[nCntModel].MaxModel = MAX_MODEL;
		g_Model[nCntModel].vtxMinModel = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
		g_Model[nCntModel].vtxMaxModel = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);
	}

	g_nCntCrear = 0;

	//==============================
	// ファイル読み込み
	//==============================
	LoadModelText();

	for(nCntModel = 0; nCntModel < g_Model[nCntModel].nLoad; nCntModel++)
	{
		// Xファイルの読み込み
		D3DXLoadMeshFromX(g_LoadModel[nCntModel].pXFileName,					// 読み込むXファイル名
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_LoadModel[nCntModel].pBuffMatModel,								// マテリアル情報ポインタ
			NULL,
			&g_LoadModel[nCntModel].NumMatModel,								// マテリアル情報の数
			&g_LoadModel[nCntModel].pMeshModel);								// メッシュ情報ポイント

		//テクスチャの読み込み
		D3DXMATERIAL *pMat;														// Xファイルから取り出したマテリアル情報を入れる

		// Xファイルからマテリアル情報を取得
		pMat = (D3DXMATERIAL*)g_LoadModel[nCntModel].pBuffMatModel->GetBufferPointer();

		// テクスチャのポインタをマテリアル情報の数分配列化
		g_LoadModel[nCntModel].pTextureModel = new LPDIRECT3DTEXTURE9[(int)g_LoadModel[nCntModel].NumMatModel];	// int型に直す

		// 取得したファイル名を入力
		for (int nCntNumMat = 0; nCntNumMat < (int)g_LoadModel[nCntModel].NumMatModel; nCntNumMat++)	// DWORD型からint型に変換する
		{
			// テクスチャのポインタ初期化
			g_LoadModel[nCntModel].pTextureModel[nCntNumMat] = NULL;

			// テクスチャファイル名が入っている場合、読み込む
			if (pMat[nCntNumMat].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFile(pDevice, pMat[nCntNumMat].pTextureFilename,
				&g_LoadModel[nCntModel].pTextureModel[nCntNumMat]);
			}
		}
	}

	//Xファイルから最大値と最小値の設定
	int nNumVertices;						//頂点数
	DWORD sizeFVF;							//頂点フォーマットのサイズ
	BYTE *pVertexBuffer;					//頂点バッファのポインタ

	for (nCntModel = 0; nCntModel < g_Model[nCntModel].MaxModel; nCntModel++)
	{
		//頂点数を取得
		nNumVertices = g_LoadModel[g_Model[nCntModel].nTypeModel].pMeshModel->GetNumVertices();

		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_LoadModel[g_Model[nCntModel].nTypeModel].pMeshModel->GetFVF());

		//頂点バッファをロック
		g_LoadModel[g_Model[nCntModel].nTypeModel].pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertexBuffer);

		for (int nCntvtx = 0; nCntvtx < nNumVertices; nCntvtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVertexBuffer;

			//すべての変数を比較して最小・最大値を決める
			if (g_Model[nCntModel].vtxMinModel.x > vtx.x)
			{
				g_Model[nCntModel].vtxMinModel.x = vtx.x;
			}
			if (g_Model[nCntModel].vtxMaxModel.x < vtx.x)
			{
				g_Model[nCntModel].vtxMaxModel.x = vtx.x;
			}
			if (g_Model[nCntModel].vtxMinModel.y > vtx.y)
			{
				g_Model[nCntModel].vtxMinModel.y = vtx.y;
			}
			if (g_Model[nCntModel].vtxMaxModel.y < vtx.y)
			{
				g_Model[nCntModel].vtxMaxModel.y = vtx.y;
			}
			if (g_Model[nCntModel].vtxMinModel.z > vtx.z)
			{
				g_Model[nCntModel].vtxMinModel.z = vtx.z;
			}
			if (g_Model[nCntModel].vtxMaxModel.z < vtx.z)
			{
				g_Model[nCntModel].vtxMaxModel.z = vtx.z;
			}

			pVertexBuffer += sizeFVF;		//サイズ分ポインタを進める
		}
		//頂点バッファのアンロック
		g_LoadModel[g_Model[nCntModel].nTypeModel].pMeshModel->UnlockVertexBuffer();
	}
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitModel(void)
{
		for (int nCntModel = 0; nCntModel < g_Model[nCntModel].MaxModel; nCntModel++)
		{
			// メッシュの開放
			if (g_LoadModel[g_Model[nCntModel].nTypeModel].pMeshModel != NULL)
			{
				g_LoadModel[g_Model[nCntModel].nTypeModel].pMeshModel->Release();
				g_LoadModel[g_Model[nCntModel].nTypeModel].pMeshModel = NULL;
			}

			// マテリアルの開放
			if (g_LoadModel[g_Model[nCntModel].nTypeModel].pBuffMatModel != NULL)
			{
				g_LoadModel[g_Model[nCntModel].nTypeModel].pBuffMatModel->Release();
				g_LoadModel[g_Model[nCntModel].nTypeModel].pBuffMatModel = NULL;
			}
		}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateModel(void)
{
	int nCntModel = 0;

	//プレイヤーの取得
	PLAYER * pPlayer;
	pPlayer = GetPlayer();

	for (nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		g_Model[nCntModel].Pos += g_Model[nCntModel].move;

		if (g_Model[nCntModel].nTypeModel == 7)
		{
			g_Model[nCntModel].move = D3DXVECTOR3(0.0f, 0.0f, -3.0f);

			if (g_Model[nCntModel].Pos.z <= -1000)
			{
				g_Model[nCntModel].Pos = D3DXVECTOR3(3800.0f, 0.0f, 1500.0f);
			}
		}
		if (g_Model[nCntModel].nTypeModel == 9)
		{
			g_Model[nCntModel].move = D3DXVECTOR3(0.0f, 0.0f, 3.0f);

			if (g_Model[nCntModel].Pos.z >= 1200)
			{
				g_Model[nCntModel].Pos = D3DXVECTOR3(2700.0f, 0.0f, -1500.0f);
			}
		}
		if (g_Model[nCntModel].nTypeModel == 10)
		{
			g_Model[nCntModel].rot.y -= 0.1f;
		}
		if (g_Model[nCntModel].nTypeModel == 19)
		{
			g_Model[nCntModel].rot.y -= 0.1f;
		}
		if (pPlayer->bClearFlag1 == true)
		{
			if (g_Model[nCntModel].nTypeModel == 22)
			{
				g_Model[nCntModel].bUse = false;
			}
		}
		if (pPlayer->bClearFlag2 == true)
		{
			if (g_Model[nCntModel].nTypeModel == 23)
			{
				g_Model[nCntModel].bUse = false;
			}
		}

		if (g_Model[nCntModel].nTypeModel == 24)
		{
			if (g_Model[nCntModel].bUse)
			{

			}
		}
		g_Model[nCntModel].Pos.y;
	}

	CrearModel();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxSize, mtxRot, mtxTrans;				//計算用
	D3DXMATERIAL*pMat;
	D3DMATERIAL9 matDef;

	for (int nCntModel = 0; nCntModel < g_Model[nCntModel].MaxModel; nCntModel++)
	{
		if (g_Model[nCntModel].bUse)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Model[nCntModel].mtxWorldModel);

			// スケールを反映
			D3DXMatrixScaling(&mtxSize, g_Model[nCntModel].scale.x, g_Model[nCntModel].scale.y, g_Model[nCntModel].scale.z);
			D3DXMatrixMultiply(&g_Model[nCntModel].mtxWorldModel, &g_Model[nCntModel].mtxWorldModel, &mtxSize);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Model[nCntModel].rot.y, g_Model[nCntModel].rot.x, g_Model[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_Model[nCntModel].mtxWorldModel, &g_Model[nCntModel].mtxWorldModel, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Model[nCntModel].Pos.x, g_Model[nCntModel].Pos.y, g_Model[nCntModel].Pos.z);
			D3DXMatrixMultiply(&g_Model[nCntModel].mtxWorldModel, &g_Model[nCntModel].mtxWorldModel, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Model[nCntModel].mtxWorldModel);

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			// マテリアル情報に対するポインタを取得
			pMat = (D3DXMATERIAL*)g_LoadModel[g_Model[nCntModel].nTypeModel].pBuffMatModel->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_LoadModel[g_Model[nCntModel].nTypeModel].NumMatModel; nCntMat++)
			{
				// テクスチャの設定
				pDevice->SetTexture(0, g_LoadModel[g_Model[nCntModel].nTypeModel].pTextureModel[nCntMat]);

				// マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// 描画
				g_LoadModel[g_Model[nCntModel].nTypeModel].pMeshModel->DrawSubset(nCntMat);
			}
		}
		// マテリアルをデフォルトに戻す
		pDevice->SetMaterial(&matDef);
	}
}

//============================================================================
// モデルの取得
//=============================================================================
MODEL * GetModel(void)
{
	return &g_Model[0];
}

//=======================================================================================
// モデルの当たり判定
//=======================================================================================
bool ColisionModel(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * move, MODEL**ppModelRet)
{
	bool bLand = false;
	int nCntModel;

	//プレイヤーの取得
	PLAYER * pPlayer;
	pPlayer = GetPlayer();

	if (*ppModelRet != NULL)
	{
		*ppModelRet = NULL;
	}

		for (nCntModel = 0; nCntModel < g_Model[nCntModel].MaxModel; nCntModel++)
		{
			if (pPlayer->bPlayerDeth==false)
			{
				if (g_Model[nCntModel].bUse)
				{

					if (pPos->y + pPlayer->size.y <g_Model[nCntModel].vtxMaxModel.y + g_Model[nCntModel].Pos.y &&
						pPos->y - pPlayer->size.y >g_Model[nCntModel].vtxMinModel.y + g_Model[nCntModel].Pos.y)
					{
						if (pPos->z + pPlayer->size.z <g_Model[nCntModel].vtxMaxModel.z + g_Model[nCntModel].Pos.z &&
							pPos->z - pPlayer->size.z >g_Model[nCntModel].vtxMinModel.z + g_Model[nCntModel].Pos.z)
						{
							//左
							if (pPos->x + pPlayer->size.x > g_Model[nCntModel].vtxMinModel.x + g_Model[nCntModel].Pos.x&&
								pPosOld->x - pPlayer->size.x < g_Model[nCntModel].vtxMinModel.x + g_Model[nCntModel].Pos.x)
							{
								pPos->x = g_Model[nCntModel].vtxMinModel.x + g_Model[nCntModel].Pos.x - pPlayer->size.x;

								if (g_Model[nCntModel].nTypeModel == 10)
								{
									g_Model[nCntModel].bUse = false;
									pPlayer->bClearFlag1 = true;
									PlaySound(SOUND_LABEL_SE_KEYGET);
								}
								if (g_Model[nCntModel].nTypeModel == 19)
								{
									g_Model[nCntModel].bUse = false;
									pPlayer->bClearFlag2 = true;
									PlaySound(SOUND_LABEL_SE_KEYGET);
								}
								if (g_Model[nCntModel].nTypeModel == 20)
								{
									if (pPlayer->bClearFlag1 == true && pPlayer->bClearFlag2 == true)
									{
										pPlayer->bPlayerCrear = true;
									}
								}
								move->x = 0.0f;
							}
							//右
							else if (pPos->x + pPlayer->size.x < g_Model[nCntModel].vtxMaxModel.x + g_Model[nCntModel].Pos.x &&
								pPosOld->x + pPlayer->size.x > g_Model[nCntModel].vtxMaxModel.x + g_Model[nCntModel].Pos.x)
							{
								pPos->x = g_Model[nCntModel].vtxMaxModel.x + g_Model[nCntModel].Pos.x + pPlayer->size.x;
								if (g_Model[nCntModel].nTypeModel == 10)
								{
									g_Model[nCntModel].bUse = false;
									pPlayer->bClearFlag1 = true;
									PlaySound(SOUND_LABEL_SE_KEYGET);
								}
								if (g_Model[nCntModel].nTypeModel == 19)
								{
									g_Model[nCntModel].bUse = false;
									pPlayer->bClearFlag2 = true;
									PlaySound(SOUND_LABEL_SE_KEYGET);
								}
								if (g_Model[nCntModel].nTypeModel == 20)
								{
									if (pPlayer->bClearFlag1 == true && pPlayer->bClearFlag2 == true)
									{
										pPlayer->bPlayerCrear = true;
									}
								}
								move->x = 0.0f;
							}
						}
					}
					if (pPos->y + pPlayer->size.y <g_Model[nCntModel].vtxMaxModel.y + g_Model[nCntModel].Pos.y &&
						pPos->y - pPlayer->size.y >g_Model[nCntModel].vtxMinModel.y + g_Model[nCntModel].Pos.y)
					{
						if (pPos->x + pPlayer->size.x <g_Model[nCntModel].vtxMaxModel.x + g_Model[nCntModel].Pos.x&&
							pPos->x + pPlayer->size.x >g_Model[nCntModel].vtxMinModel.x + g_Model[nCntModel].Pos.x)
						{
							//下
							if (pPos->z - pPlayer->size.z > g_Model[nCntModel].vtxMinModel.z + g_Model[nCntModel].Pos.z &&
								pPosOld->z - pPlayer->size.z < g_Model[nCntModel].vtxMinModel.z + g_Model[nCntModel].Pos.z)
							{
								pPos->z = g_Model[nCntModel].vtxMinModel.z + g_Model[nCntModel].Pos.z - pPlayer->size.z;
								if (g_Model[nCntModel].nTypeModel == 10)
								{
									g_Model[nCntModel].bUse = false;
									pPlayer->bClearFlag1 = true;
									PlaySound(SOUND_LABEL_SE_KEYGET);
								}
								if (g_Model[nCntModel].nTypeModel == 19)
								{
									g_Model[nCntModel].bUse = false;
									pPlayer->bClearFlag2 = true;
									PlaySound(SOUND_LABEL_SE_KEYGET);
								}
								if (g_Model[nCntModel].nTypeModel == 20)
								{
									if (pPlayer->bClearFlag1 == true && pPlayer->bClearFlag2 == true)
									{
										pPlayer->bPlayerCrear = true;
									}
								}
								move->z = 0.0f;
							}
							//上
							else if (pPos->z + pPlayer->size.z < g_Model[nCntModel].vtxMaxModel.z + g_Model[nCntModel].Pos.z&&
								pPosOld->z + pPlayer->size.z > g_Model[nCntModel].vtxMaxModel.z + g_Model[nCntModel].Pos.z)
							{
								pPos->z = g_Model[nCntModel].vtxMaxModel.z + g_Model[nCntModel].Pos.z + pPlayer->size.z;
								if (g_Model[nCntModel].nTypeModel == 10)
								{
									g_Model[nCntModel].bUse = false;
									pPlayer->bClearFlag1 = true;
									PlaySound(SOUND_LABEL_SE_KEYGET);
								}
								if (g_Model[nCntModel].nTypeModel == 19)
								{
									g_Model[nCntModel].bUse = false;
									pPlayer->bClearFlag2 = true;
									PlaySound(SOUND_LABEL_SE_KEYGET);
								}
								if (g_Model[nCntModel].nTypeModel == 20)
								{
									if (pPlayer->bClearFlag1 == true && pPlayer->bClearFlag2 == true)
									{
										pPlayer->bPlayerCrear = true;
									}
								}
								//影のセット
								move->z = 0.0f;
							}
						}
					}
					if (pPos->z + pPlayer->size.z <g_Model[nCntModel].vtxMaxModel.z + g_Model[nCntModel].Pos.z &&
						pPos->z - pPlayer->size.z >g_Model[nCntModel].vtxMinModel.z + g_Model[nCntModel].Pos.z)
					{
						if (pPos->x + pPlayer->size.x <g_Model[nCntModel].vtxMaxModel.x + g_Model[nCntModel].Pos.x&&
							pPos->x + pPlayer->size.x >g_Model[nCntModel].vtxMinModel.x + g_Model[nCntModel].Pos.x)
						{
							//上の当たり判定処理
							if (pPosOld->y + pPlayer->size.y > g_Model[nCntModel].vtxMinModel.y + g_Model[nCntModel].Pos.y &&
								pPos->y + pPlayer->size.y < g_Model[nCntModel].vtxMaxModel.y + g_Model[nCntModel].Pos.y)
							{
								bLand = true;
								*ppModelRet = &g_Model[nCntModel];
								pPos->y = g_Model[nCntModel].Pos.y - pPlayer->size.y + g_Model[nCntModel].vtxMaxModel.y;

								if (g_Model[nCntModel].nTypeModel == 5)
								{
									if (GetKeyboardPress(DIK_J) || GetJoypadTrigger(0, JOYPADKEY_X))
									{
										pPlayer->pos = D3DXVECTOR3(4200.0f, 1000.0f, 0.0f);
									}
								}

								if (g_Model[nCntModel].nTypeModel == 6)
								{
									if (GetKeyboardPress(DIK_J) || GetJoypadTrigger(0, JOYPADKEY_X))
									{
										pPlayer->pos = D3DXVECTOR3(-4400.0f, 1000.0f, 0.0f);
									}
								}
								if (g_Model[nCntModel].nTypeModel == 11)
								{
									if (GetKeyboardPress(DIK_J) || GetJoypadTrigger(0, JOYPADKEY_X))
									{
										pPlayer->pos = D3DXVECTOR3(-1200, 1000.0f, 0.0f);
									}
								}

								if (g_Model[nCntModel].nTypeModel == 12)
								{
									if (GetKeyboardPress(DIK_J) || GetJoypadTrigger(0, JOYPADKEY_X))
									{
										pPlayer->pos = D3DXVECTOR3(1200, 1000.0f, 0.0f);
									}
								}
							}
						}
					}
				}
			}
		}
	return bLand;
}

//=======================================================================================
// モデルの当たり判定
//=======================================================================================
bool ColisionShadow(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * move, MODEL**ppModelRet)
{
	bool bLand = false;

	//プレイヤーの取得
	PLAYER * pPlayer;
	pPlayer = GetPlayer();

	for (int nCntModel = 0; nCntModel < g_Model[nCntModel].MaxModel; nCntModel++)
	{
		if (g_Model[nCntModel].bUse)
		{
			if (pPos->z + pPlayer->size.z <g_Model[nCntModel].vtxMaxModel.z + g_Model[nCntModel].Pos.z &&
				pPos->z + pPlayer->size.z >g_Model[nCntModel].vtxMinModel.z + g_Model[nCntModel].Pos.z&&
				pPos->x + pPlayer->size.x <g_Model[nCntModel].vtxMaxModel.x + g_Model[nCntModel].Pos.x&&
				pPos->x + pPlayer->size.x >g_Model[nCntModel].vtxMinModel.x + g_Model[nCntModel].Pos.x)
			{
					bLand = true;
					g_Model[nCntModel].fDistance = pPos->y - g_Model[nCntModel].vtxMaxModel.y;
					*ppModelRet = &g_Model[nCntModel];
		
			}
		}
	}
	
	for (int nCntModel = 0; nCntModel < g_Model[nCntModel].MaxModel; nCntModel+=2)
	{
		if (g_Model[nCntModel].bUse)
		{
			if (pPos->z + pPlayer->size.z <g_Model[nCntModel].vtxMaxModel.z + g_Model[nCntModel].Pos.z &&
				pPos->z + pPlayer->size.z >g_Model[nCntModel].vtxMinModel.z + g_Model[nCntModel].Pos.z&&
				pPos->x + pPlayer->size.x <g_Model[nCntModel].vtxMaxModel.x + g_Model[nCntModel].Pos.x&&
				pPos->x + pPlayer->size.x >g_Model[nCntModel].vtxMinModel.x + g_Model[nCntModel].Pos.x)
			{
				bLand = true;
				g_Model[nCntModel].fDistance = pPos->y - g_Model[nCntModel].vtxMaxModel.y;
				*ppModelRet = &g_Model[nCntModel];
			}
		}
	}
	return bLand;
}

//===============================================================================
// モデルの読み込み
//===============================================================================
void LoadModelText(void)
{
	//読み込んだモデルの情報の初期化
	for (int nCntPlayer = 0; nCntPlayer < g_Model[nCntPlayer].MaxModel; nCntPlayer++)
	{
		for (int nText = 0; nText < MAX_CHARMODEL; nText++)
		{
			g_LoadModel[nCntPlayer].pXFileName[nText] = NULL;		//ファイル名
		}
		g_LoadModel[nCntPlayer].pMeshModel = NULL;						//メッシュ情報へのポインタ
		g_LoadModel[nCntPlayer].pBuffMatModel = NULL;					//マテリアル情報へのポインタ
		g_LoadModel[nCntPlayer].NumMatModel = 0;						//マテリアルの数
		g_LoadModel[nCntPlayer].pTextureModel = NULL;					//テクスチャへのポインタ
	}

	//#if 1
	// ローカル変数宣言
	FILE *pFile;				// ファイルのポインタ
	char ReadText[256];			// 読み込んだ文字列を入れておく
	char HeadText[256];			// 比較用
	char DustBox[256];			// 使用しないものを入れておく
	int nCntText = 0;			// モデルファイル名
	int nCntModel = 0;			// モデル数

	// ファイルオープン
	pFile = fopen(MODEL_FILE, "r");		// ファイルを開く[読み込み型]

	if (pFile != NULL)		// ファイルが空ではない
	{//ファイルが開けた場合
		while (strcmp(HeadText, "SCRIPT") != 0)
		{// "SCRIPT" が読み込まれるまで繰り返し文字列を読み取る
			fgets(ReadText, sizeof(ReadText), pFile);
			sscanf(ReadText, "%s", &HeadText);
		}

		if (strcmp(HeadText, "SCRIPT") == 0)
		{// "SCRIPT" が読み取れた場合、処理開始
			while (strcmp(HeadText, "END_SCRIPT") != 0)
			{// "END_SCRIPT" が読み込まれるまで繰り返し文字列を読み取る
				fgets(ReadText, sizeof(ReadText), pFile);
				sscanf(ReadText, "%s", &HeadText);

				if (strcmp(HeadText, "\n") == 0)
				{// 文字列の先頭が [\n](改行) の場合処理しない

				}
				if (strcmp(HeadText, "NUM_MODEL") == 0)
				{// 読み込むモデルの最大数
					sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &g_Model[nCntModel].nLoad);
				}
				else if (strcmp(HeadText, "MODEL_FILENAME") == 0)
				{// モデルファイル名
					if (g_Model[nCntModel].nLoad > nCntText)
					{// 最大数以上処理しない
						sscanf(ReadText, "%s %c %s", &DustBox, &DustBox, &g_LoadModel[nCntText].pXFileName[0]);
						nCntText++;
					}
				}
				else if (strcmp(HeadText, "MODELSET") == 0)
				{//--- キャラクター情報 ---//
					while (strcmp(HeadText, "END_MODELSET") != 0)
					{// "END_CHARACTERSET" が読み取れるまで繰り返し文字列を読み取る
						// モデルの配置情報
						fgets(ReadText, sizeof(ReadText), pFile);
						sscanf(ReadText, "%s", &HeadText);

						if (strcmp(HeadText, "\n") == 0)
						{// 文字列の先頭が [\n](改行) の場合処理しない
							int nCnt = 0;
						}
						else if (strcmp(HeadText, "NUM_PARTS") == 0)
						{// プレイヤー１体に対するモデルの使用数
							sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &g_Model[nCntModel].MaxModel);
						}

						if (strcmp(HeadText, "PARTSSET") == 0)
						{
							if (g_Model[nCntModel].MaxModel > nCntModel)
							{
								while (strcmp(HeadText, "END_PARTSSET") != 0)
								{// "END_PARTSSET" が読み取れるまで繰り返し文字列を読み取る
									fgets(ReadText, sizeof(ReadText), pFile);
									sscanf(ReadText, "%s", &HeadText);

									if (strcmp(HeadText, "POS") == 0)
									{// 位置
										sscanf(ReadText, "%s %c %f %f %f", &DustBox, &DustBox,
											&g_Model[nCntModel].Pos.x,
											&g_Model[nCntModel].Pos.y,
											&g_Model[nCntModel].Pos.z);
									}
									else if (strcmp(HeadText, "ROT") == 0)
									{// 向き
										sscanf(ReadText, "%s %c %f %f %f", &DustBox, &DustBox,
											&g_Model[nCntModel].rot.x,
											&g_Model[nCntModel].rot.y,
											&g_Model[nCntModel].rot.z);
									}
									else if (strcmp(HeadText, "TYPE") == 0)
									{// 部位
										sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &g_Model[nCntModel].nTypeModel);
									}

									g_Model[nCntModel].bUse = true;

									if (g_Model[nCntModel].nTypeModel == 24)
									{
										g_Model[nCntModel].bUse = false;
									}
								}
								nCntModel++;		// モデル数を進める
							}
						}
					}
				}
			}
		}
		// ファイルを閉じる
		fclose(pFile);
	}
	else
	{// 開けなかった場合
		MessageBox(NULL, "キャラクター情報ファイルが開けませんでした。", NULL, MB_OK);
	}
}
//===============================================================================
// モデルの読み込み
//===============================================================================
void CrearModel(void)
{
	//プレイヤーの取得
	PLAYER * pPlayer;
	pPlayer = GetPlayer();

	g_nCntCrear = 0;

	for (int nCntModel = 0; nCntModel < g_Model[nCntModel].MaxModel; nCntModel++)
	{
		if (pPlayer->bPlayerCrear == true)
		{
			PlaySound(SOUND_LABEL_SE_CLEAR);
			g_nCntCrear++;
			if (g_Model[nCntModel].nTypeModel == 21)
			{
				g_Model[nCntModel].rot.z = -0.8f;
			}

			if (g_Model[nCntModel].nTypeModel == 24)
			{
				g_Model[nCntModel].bUse = true;
			}

			if (GetMode() == MODE_GAME)
			{
				SetGameText(D3DXVECTOR3(670.0f, 600.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 400, 200, 6);
			}

			if (g_nCntCrear >= 30)
			{

					SetGameState(GAMESTATE_END);
					//プレイヤーの初期化処理
					InitPlayer();

			}
		}
	}

}