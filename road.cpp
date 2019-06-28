// ====================================================================================================
//
// ロード処理 [road.cpp]
// Author : Kimura kouta
//
// ====================================================================================================
#include "road.h"
#include <stdio.h>              // 一般的なヘッダー
#include "model.h"

// ====================================================================================================
//
// マクロ定義
//
// ====================================================================================================
#define	TEXTURE_ROAD		"DATA/TEX/number001.png"	// 読み込むテクスチャファイル名
#define ROAD_SIZE (20)								// ロードボードの大きさ
#define ROAD_MAX (10)								// 数値
#define ROAD_DATE (5)										// ロード数
#define SAVE_FILE_NAME ("text.txt") // セーブファイル

// ====================================================================================================
//
// プロトタイプ宣言
//
// ====================================================================================================

// ====================================================================================================
//
// グローバル変数宣言
//
// ====================================================================================================
ROAD					g_aLoad[5];				// ロード変数

// ====================================================================================================
//
// 初期化処理
//
// ====================================================================================================
void InitLoad(void)
{
	int nCntLoad;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (nCntLoad = 0; nCntLoad < ROAD_DATE; nCntLoad++)
	{
		g_aLoad[nCntLoad].aName[nCntLoad];
		g_aLoad[nCntLoad].nPoint = 0;
	}

	LoadData();
}

// ====================================================================================================
//
// ロードデータ取得関数
//
// ====================================================================================================
ROAD *GetLoad(void)
{
	return &g_aLoad[0];
}

// ====================================================================================================
//
// ロード関数
//
// ====================================================================================================
void LoadData(void)
{
	// ファイルポイント
	FILE *pFile;

	int nCntLoad;

	// ファイル開
	pFile = fopen(SAVE_FILE_NAME, "r");

	// 開けた
	if (pFile != NULL)
	{
		for (nCntLoad = 0; nCntLoad < ROAD_DATE; nCntLoad++)
		{
			fscanf(pFile, "%d", &g_aLoad[nCntLoad].nPoint); // 名前
		}
		// ファイル
		fclose(pFile);
	}

	// 開けない
	else
	{
		printf("開けれませんでした\n");
	}
}

// ====================================================================================================
//
// ロード関数
//
// ====================================================================================================
void LoadObject(void)
{
	//FILE *pFile;

	//char cReadText[128];
	//char cHeadText[128];
	//char cDieText[128];

	//MODEL *pModel;
	//pModel = GetModel();

	//pFile = fopen("DATA/road/road.txt", " r");

	//if (pFile !=NULL)
	//{
	//	//スクリプトがくるまで
	//	/*strcmpは読み込んだ文字と指定されている文字を比較*/
	//	while (strcmp(cHeadText,"SCRIPT")!=0)
	//	{
	//		//fgetsは一文だけを読み取る
	//		fgets(cReadText, sizeof(cReadText), pFile);
	//		//cReadを読み込み,cHeadに代入
	//		//sscanfは文字を入力
	//		sscanf(cReadText, "%s", &cHeadText);
	//	}
	//	if (strcmp(cHeadText,"SCRIPT")==0)
	//	{
	//		while (strcmp(cHeadText, "END_SCRIPT") != 0)
	//		{
	//			fgets(cReadText, sizeof(cReadText), pFile);
	//			sscanf(cReadText, "%s", &cHeadText);
	//			//改行
	//			if (strcmp(cHeadText, "\n") == 0)
	//			{
	//			}
	//				//モデルセットだったら
	//				if (strcmp(cHeadText, "MODELSET") == 0)
	//				{			
	//					while (strcmp(cHeadText, "END_MODELSET")!=0)
	//					{
	//						fgets(cReadText, sizeof(cReadText), pFile);
	//						sscanf(cReadText, "%s", cHeadText);

	//						if (strcmp(cHeadText, "pos") == 0)
	//						{
	//							sscanf(cReadText, "%s %s %f %f %f", &cDieText, &cDieText, &pModel->Pos.x, &pModel->Pos.y, &pModel->Pos.z);
	//						}
	//						if (strcmp(cHeadText, "rot") == 0)
	//						{
	//							sscanf(cReadText, "%s %s %f %f %f", &cDieText, &cDieText, &pModel->rot.x, &pModel->rot.y, &pModel->rot.z);
	//						}
	//						if (strcmp(cHeadText, "nType") == 0)
	//						{
	//							sscanf(cReadText, "%s %s %d", &cDieText, &cDieText, &pModel->nTypeModel);

	//							//使用状態
	//							pModel->bUse = true;
	//							//モデル
	//							pModel++;
	//						}
	//					}
	//				}
	//			}
	//		}
	//	//ファイルを開く
	//	fclose(pFile);
	//}
	////開けない
	//else
	//{
	//	printf("開けませんでした");
	//}
}