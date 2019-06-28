//=============================================================================
//
// モデル処理 [model.cpp]
// Author : KIMURA KOUTA
//
//=============================================================================
#include "TutoModel.h"
#include "input.h"
#include "camera.h"
#include "Shadow.h"
#include "bullet.h"
#include "effect.h"
#include "player.h"
#include "Game.h"
#include "fade.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TUTOMODEL_FILE		"DATA/road/TutoModel.txt"					//ファイル名

#define SPEED			(0.5f)									//プレイヤースピード

//=============================================================================
// グローバル変数
//=============================================================================
TUTOMODEL					 g_TutoModel[MAX_TUTOMODEL];					// 読み込んだモデルの情報
LOADTUTOMODEL				 g_LoadTutoModel[MAX_TUTOMODEL];					// 読み込んだモデルの情報

//=============================================================================
// 初期化処理
//=============================================================================
void InitTutoModel(void)
{
	int nCntModel = 0;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (nCntModel = 0; nCntModel < MAX_TUTOMODEL; nCntModel++)
	{
		// 位置・向きの初期設定
		g_TutoModel[nCntModel].Pos = D3DXVECTOR3(100.0f, 0.0f, 0.0f);
		g_TutoModel[nCntModel].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_TutoModel[nCntModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_TutoModel[nCntModel].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_TutoModel[nCntModel].Diffrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_TutoModel[nCntModel].nTypeTex = 0;
		g_TutoModel[nCntModel].nTypeModel = 0;
		g_TutoModel[nCntModel].bUse = false;
		g_TutoModel[nCntModel].fRadius = 0;
		g_TutoModel[nCntModel].fHeight = 0;
		g_TutoModel[nCntModel].nLoad = MAX_TUTOMODELTYPE;
		g_TutoModel[nCntModel].nMaxModel = MAX_TUTOMODEL;
		g_TutoModel[nCntModel].vtxMinModel = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
		g_TutoModel[nCntModel].vtxMaxModel = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);
	}

	//==============================
	// ファイル読み込み
	//==============================
	LoadTutoModelText();

	for(nCntModel = 0; nCntModel < g_TutoModel[nCntModel].nLoad; nCntModel++)
	{
		// Xファイルの読み込み
		D3DXLoadMeshFromX(g_LoadTutoModel[nCntModel].pXFileTutoName,					// 読み込むXファイル名
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_LoadTutoModel[nCntModel].pBuffMatTutoModel,								// マテリアル情報ポインタ
			NULL,
			&g_LoadTutoModel[nCntModel].NumMatTutoModel,								// マテリアル情報の数
			&g_LoadTutoModel[nCntModel].pMeshTutoModel);								// メッシュ情報ポイント

		//テクスチャの読み込み
		D3DXMATERIAL *pMat;															// Xファイルから取り出したマテリアル情報を入れる

		// Xファイルからマテリアル情報を取得
		pMat = (D3DXMATERIAL*)g_LoadTutoModel[nCntModel].pBuffMatTutoModel->GetBufferPointer();

		// テクスチャのポインタをマテリアル情報の数分配列化
		g_LoadTutoModel[nCntModel].pTextureTutoModel = new LPDIRECT3DTEXTURE9[(int)g_LoadTutoModel[nCntModel].NumMatTutoModel];	// int型に直す

		// 取得したファイル名を入力
		for (int nCntNumMat = 0; nCntNumMat < (int)g_LoadTutoModel[nCntModel].NumMatTutoModel; nCntNumMat++)	// DWORD型からint型に変換する
		{
			// テクスチャのポインタ初期化
			g_LoadTutoModel[nCntModel].pTextureTutoModel[nCntNumMat] = NULL;

			// テクスチャファイル名が入っている場合、読み込む
			if (pMat[nCntNumMat].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFile(pDevice, pMat[nCntNumMat].pTextureFilename,
				&g_LoadTutoModel[nCntModel].pTextureTutoModel[nCntNumMat]);
			}
		}
	}

	//Xファイルから最大値と最小値の設定
	int nNumVertices;						//頂点数
	DWORD sizeFVF;							//頂点フォーマットのサイズ
	BYTE *pVertexBuffer;					//頂点バッファのポインタ

	for (nCntModel = 0; nCntModel < g_TutoModel[nCntModel].nMaxModel; nCntModel++)
	{
		//頂点数を取得
		nNumVertices = g_LoadTutoModel[g_TutoModel[nCntModel].nTypeModel].pMeshTutoModel->GetNumVertices();

		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_LoadTutoModel[g_TutoModel[nCntModel].nTypeModel].pMeshTutoModel->GetFVF());

		//頂点バッファをロック
		g_LoadTutoModel[g_TutoModel[nCntModel].nTypeModel].pMeshTutoModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertexBuffer);

		for (int nCntvtx = 0; nCntvtx < nNumVertices; nCntvtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVertexBuffer;

			//すべての変数を比較して最小・最大値を決める
			if (g_TutoModel[nCntModel].vtxMinModel.x > vtx.x)
			{
				g_TutoModel[nCntModel].vtxMinModel.x = vtx.x;
			}
			if (g_TutoModel[nCntModel].vtxMaxModel.x < vtx.x)
			{
				g_TutoModel[nCntModel].vtxMaxModel.x = vtx.x;
			}
			if (g_TutoModel[nCntModel].vtxMinModel.y > vtx.y)
			{
				g_TutoModel[nCntModel].vtxMinModel.y = vtx.y;
			}
			if (g_TutoModel[nCntModel].vtxMaxModel.y < vtx.y)
			{
				g_TutoModel[nCntModel].vtxMaxModel.y = vtx.y;
			}
			if (g_TutoModel[nCntModel].vtxMinModel.z > vtx.z)
			{
				g_TutoModel[nCntModel].vtxMinModel.z = vtx.z;
			}
			if (g_TutoModel[nCntModel].vtxMaxModel.z < vtx.z)
			{
				g_TutoModel[nCntModel].vtxMaxModel.z = vtx.z;
			}

			pVertexBuffer += sizeFVF;		//サイズ分ポインタを進める
		}
		//頂点バッファのアンロック
		g_LoadTutoModel[g_TutoModel[nCntModel].nTypeModel].pMeshTutoModel->UnlockVertexBuffer();
	}
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitTutoModel(void)
{
		for (int nCntModel = 0; nCntModel < g_TutoModel[nCntModel].nMaxModel; nCntModel++)
		{
			// メッシュの開放
			if (g_LoadTutoModel[g_TutoModel[nCntModel].nTypeModel].pMeshTutoModel != NULL)
			{
				g_LoadTutoModel[g_TutoModel[nCntModel].nTypeModel].pMeshTutoModel->Release();
				g_LoadTutoModel[g_TutoModel[nCntModel].nTypeModel].pMeshTutoModel = NULL;
			}

			// マテリアルの開放
			if (g_LoadTutoModel[g_TutoModel[nCntModel].nTypeModel].pBuffMatTutoModel != NULL)
			{
				g_LoadTutoModel[g_TutoModel[nCntModel].nTypeModel].pBuffMatTutoModel->Release();
				g_LoadTutoModel[g_TutoModel[nCntModel].nTypeModel].pBuffMatTutoModel = NULL;
			}
		}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTutoModel(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTutoModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxSize, mtxRot, mtxTrans;				//計算用
	D3DXMATERIAL*pMat;
	D3DMATERIAL9 matDef;

	for (int nCntModel = 0; nCntModel < g_TutoModel[nCntModel].nMaxModel; nCntModel++)
	{
		if (g_TutoModel[nCntModel].bUse)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_TutoModel[nCntModel].mtxWorldModel);

			// スケールを反映
			D3DXMatrixScaling(&mtxSize, g_TutoModel[nCntModel].scale.x, g_TutoModel[nCntModel].scale.y, g_TutoModel[nCntModel].scale.z);
			D3DXMatrixMultiply(&g_TutoModel[nCntModel].mtxWorldModel, &g_TutoModel[nCntModel].mtxWorldModel, &mtxSize);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_TutoModel[nCntModel].rot.y, g_TutoModel[nCntModel].rot.x, g_TutoModel[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_TutoModel[nCntModel].mtxWorldModel, &g_TutoModel[nCntModel].mtxWorldModel, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_TutoModel[nCntModel].Pos.x, g_TutoModel[nCntModel].Pos.y, g_TutoModel[nCntModel].Pos.z);
			D3DXMatrixMultiply(&g_TutoModel[nCntModel].mtxWorldModel, &g_TutoModel[nCntModel].mtxWorldModel, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_TutoModel[nCntModel].mtxWorldModel);

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			// マテリアル情報に対するポインタを取得
			pMat = (D3DXMATERIAL*)g_LoadTutoModel[g_TutoModel[nCntModel].nTypeModel].pBuffMatTutoModel->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_LoadTutoModel[g_TutoModel[nCntModel].nTypeModel].NumMatTutoModel; nCntMat++)
			{
				// テクスチャの設定
				pDevice->SetTexture(0, g_LoadTutoModel[g_TutoModel[nCntModel].nTypeModel].pTextureTutoModel[nCntMat]);

				// マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// 描画
				g_LoadTutoModel[g_TutoModel[nCntModel].nTypeModel].pMeshTutoModel->DrawSubset(nCntMat);
			}
		}

		// マテリアルをデフォルトに戻す
		pDevice->SetMaterial(&matDef);
	}

}

//============================================================================
// モデルの取得
//=============================================================================
TUTOMODEL *GetTutoModel(void)
{
	return &g_TutoModel[0];
}

//=======================================================================================
// モデルの当たり判定
//=======================================================================================
bool ColisionTutoModel(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * move, TUTOMODEL**ppTutoModelRet)
{
	bool bLand = false;
	int nCntModel;
	PLAYER * pPlayer;

	//プレイヤーの取得
	pPlayer = GetPlayer();

	if (*ppTutoModelRet != NULL)
	{
		*ppTutoModelRet = NULL;
	}

	for (nCntModel = 0; nCntModel < g_TutoModel[nCntModel].nMaxModel; nCntModel++)
	{
		if (g_TutoModel[nCntModel].bUse)
		{
			if (pPos->y + pPlayer->size.y <g_TutoModel[nCntModel].vtxMaxModel.y + g_TutoModel[nCntModel].Pos.y &&
				pPos->y - pPlayer->size.y >g_TutoModel[nCntModel].vtxMinModel.y + g_TutoModel[nCntModel].Pos.y)
			{
				if (pPos->z + pPlayer->size.z <g_TutoModel[nCntModel].vtxMaxModel.z + g_TutoModel[nCntModel].Pos.z &&
					pPos->z - pPlayer->size.z >g_TutoModel[nCntModel].vtxMinModel.z + g_TutoModel[nCntModel].Pos.z)
				{
					//左
					if (pPos->x + pPlayer->size.x > g_TutoModel[nCntModel].vtxMinModel.x + g_TutoModel[nCntModel].Pos.x&&
						pPosOld->x - pPlayer->size.x < g_TutoModel[nCntModel].vtxMinModel.x + g_TutoModel[nCntModel].Pos.x)
					{
						pPos->x = g_TutoModel[nCntModel].vtxMinModel.x + g_TutoModel[nCntModel].Pos.x - pPlayer->size.x;
					}
					//右
					else if (pPos->x + pPlayer->size.x < g_TutoModel[nCntModel].vtxMaxModel.x + g_TutoModel[nCntModel].Pos.x &&
						pPosOld->x + pPlayer->size.x > g_TutoModel[nCntModel].vtxMaxModel.x + g_TutoModel[nCntModel].Pos.x)
					{
						pPos->x = g_TutoModel[nCntModel].vtxMaxModel.x + g_TutoModel[nCntModel].Pos.x + pPlayer->size.x;
					}
				}
			}
			if (pPos->y + pPlayer->size.y <g_TutoModel[nCntModel].vtxMaxModel.y + g_TutoModel[nCntModel].Pos.y &&
				pPos->y - pPlayer->size.y >g_TutoModel[nCntModel].vtxMinModel.y + g_TutoModel[nCntModel].Pos.y)
			{
				if (pPos->x + pPlayer->size.x <g_TutoModel[nCntModel].vtxMaxModel.x + g_TutoModel[nCntModel].Pos.x&&
					pPos->x + pPlayer->size.x >g_TutoModel[nCntModel].vtxMinModel.x + g_TutoModel[nCntModel].Pos.x)
				{
					//下
					if (pPos->z - pPlayer->size.z > g_TutoModel[nCntModel].vtxMinModel.z + g_TutoModel[nCntModel].Pos.z &&
						pPosOld->z - pPlayer->size.z < g_TutoModel[nCntModel].vtxMinModel.z + g_TutoModel[nCntModel].Pos.z)
					{
						pPos->z = g_TutoModel[nCntModel].vtxMinModel.z + g_TutoModel[nCntModel].Pos.z - pPlayer->size.z;
					}
					//上
					else if (pPos->z + pPlayer->size.z < g_TutoModel[nCntModel].vtxMaxModel.z + g_TutoModel[nCntModel].Pos.z&&
						pPosOld->z + pPlayer->size.z > g_TutoModel[nCntModel].vtxMaxModel.z + g_TutoModel[nCntModel].Pos.z)
					{
						pPos->z = g_TutoModel[nCntModel].vtxMaxModel.z + g_TutoModel[nCntModel].Pos.z + pPlayer->size.z;

					}
				}
			}
			if (pPos->z + pPlayer->size.z <g_TutoModel[nCntModel].vtxMaxModel.z + g_TutoModel[nCntModel].Pos.z &&
				pPos->z - pPlayer->size.z >g_TutoModel[nCntModel].vtxMinModel.z + g_TutoModel[nCntModel].Pos.z)
			{
				if (pPos->x + pPlayer->size.x <g_TutoModel[nCntModel].vtxMaxModel.x + g_TutoModel[nCntModel].Pos.x&&
					pPos->x + pPlayer->size.x >g_TutoModel[nCntModel].vtxMinModel.x + g_TutoModel[nCntModel].Pos.x)
				{
					//上の当たり判定処理
					if (pPosOld->y + pPlayer->size.y > g_TutoModel[nCntModel].vtxMinModel.y + g_TutoModel[nCntModel].Pos.y &&
						pPos->y + pPlayer->size.y < g_TutoModel[nCntModel].vtxMaxModel.y + g_TutoModel[nCntModel].Pos.y)
					{
						bLand = true;
						*ppTutoModelRet = &g_TutoModel[nCntModel];
						pPos->y = g_TutoModel[nCntModel].Pos.y - pPlayer->size.y + g_TutoModel[nCntModel].vtxMaxModel.y;
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
bool ColisionTutoShadow(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * move, TUTOMODEL**ppTutoModelRet)
{
	bool bLand = false;

	//プレイヤーの取得
	PLAYER * pPlayer;
	pPlayer = GetPlayer();

	if (*ppTutoModelRet != NULL)
	{
		*ppTutoModelRet = NULL;
	}

	for (int nCntModel = 0; nCntModel < g_TutoModel[nCntModel].nMaxModel; nCntModel++)
	{
		if (g_TutoModel[nCntModel].bUse)
		{
			if (pPos->z + pPlayer->size.z <g_TutoModel[nCntModel].vtxMaxModel.z + g_TutoModel[nCntModel].Pos.z &&
				pPos->z + pPlayer->size.z >g_TutoModel[nCntModel].vtxMinModel.z + g_TutoModel[nCntModel].Pos.z&&
				pPos->x + pPlayer->size.x <g_TutoModel[nCntModel].vtxMaxModel.x + g_TutoModel[nCntModel].Pos.x&&
				pPos->x + pPlayer->size.x >g_TutoModel[nCntModel].vtxMinModel.x + g_TutoModel[nCntModel].Pos.x)
			{
				bLand = true;
				*ppTutoModelRet = &g_TutoModel[nCntModel];
			}
		}
	}

	for (int nCntModel = 0; nCntModel < g_TutoModel[nCntModel].nMaxModel; nCntModel += 2)
	{
		if (g_TutoModel[nCntModel].bUse)
		{
			if (pPos->z + pPlayer->size.z <g_TutoModel[nCntModel].vtxMaxModel.z + g_TutoModel[nCntModel].Pos.z &&
				pPos->z + pPlayer->size.z >g_TutoModel[nCntModel].vtxMinModel.z + g_TutoModel[nCntModel].Pos.z&&
				pPos->x + pPlayer->size.x <g_TutoModel[nCntModel].vtxMaxModel.x + g_TutoModel[nCntModel].Pos.x&&
				pPos->x + pPlayer->size.x >g_TutoModel[nCntModel].vtxMinModel.x + g_TutoModel[nCntModel].Pos.x)
			{
				bLand = true;
				*ppTutoModelRet = &g_TutoModel[nCntModel];
			}
		}
	}
	return bLand;
}
//===============================================================================
// プレイヤーの読み込み
//===============================================================================
void LoadTutoModelText(void)
{
	//読み込んだモデルの情報の初期化
	for (int nCntPlayer = 0; nCntPlayer < g_TutoModel[nCntPlayer].nMaxModel; nCntPlayer++)
	{
		for (int nText = 0; nText < MAX_CHARMODEL; nText++)
		{
			g_LoadTutoModel[nCntPlayer].pXFileTutoName[nText] = NULL;		//ファイル名
		}
		g_LoadTutoModel[nCntPlayer].pMeshTutoModel = NULL;						//メッシュ情報へのポインタ
		g_LoadTutoModel[nCntPlayer].pBuffMatTutoModel = NULL;					//マテリアル情報へのポインタ
		g_LoadTutoModel[nCntPlayer].NumMatTutoModel = 0;						//マテリアルの数
		g_LoadTutoModel[nCntPlayer].pTextureTutoModel = NULL;					//テクスチャへのポインタ
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
	pFile = fopen(TUTOMODEL_FILE, "r");		// ファイルを開く[読み込み型]

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
					sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &g_TutoModel[nCntModel].nLoad);
				}
				else if (strcmp(HeadText, "MODEL_FILENAME") == 0)
				{// モデルファイル名
					if (g_TutoModel[nCntModel].nLoad > nCntText)
					{// 最大数以上処理しない
						sscanf(ReadText, "%s %c %s", &DustBox, &DustBox, &g_LoadTutoModel[nCntText].pXFileTutoName[0]);
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
							sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &g_TutoModel[nCntModel].nMaxModel);
						}

						if (strcmp(HeadText, "PARTSSET") == 0)
						{
							if (g_TutoModel[nCntModel].nMaxModel > nCntModel)
							{
								while (strcmp(HeadText, "END_PARTSSET") != 0)
								{// "END_PARTSSET" が読み取れるまで繰り返し文字列を読み取る
									fgets(ReadText, sizeof(ReadText), pFile);
									sscanf(ReadText, "%s", &HeadText);

									if (strcmp(HeadText, "POS") == 0)
									{// 位置
										sscanf(ReadText, "%s %c %f %f %f", &DustBox, &DustBox,
											&g_TutoModel[nCntModel].Pos.x,
											&g_TutoModel[nCntModel].Pos.y,
											&g_TutoModel[nCntModel].Pos.z);
									}
									else if (strcmp(HeadText, "ROT") == 0)
									{// 向き
										sscanf(ReadText, "%s %c %f %f %f", &DustBox, &DustBox,
											&g_TutoModel[nCntModel].rot.x,
											&g_TutoModel[nCntModel].rot.y,
											&g_TutoModel[nCntModel].rot.z);
									}
									else if (strcmp(HeadText, "TYPE") == 0)
									{// 部位
										sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &g_TutoModel[nCntModel].nTypeModel);
									}
									g_TutoModel[nCntModel].bUse = true;
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