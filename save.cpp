// ====================================================================================================
//
// セーブ処理 [save.cpp]
// Author : Kimura kouta
//
// ====================================================================================================
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>              // 一般的なヘッダー
#include "save.h"
#include "road.h"
#include "model.h"

// ====================================================================================================
//
// マクロ定義
//
// ====================================================================================================
#define	TEXTURE_SAVE		"DATA/TEX/number001.png"		// 読み込むテクスチャファイル名
#define SAVE_SIZE (20)										// セーブボードの大きさ
#define SAVE_MAX (10)										// 数値
#define SAVE_DATE (5)										// セーブ数
#define SAVE_FILE_NAME ("text.txt")							// セーブファイル

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
SAVE					g_aSave[5];				// セーブ変数

char g_cComment1[8];
char g_cComment2[64];
char g_cComment3[8];

// ====================================================================================================
//
// 初期化処理
//
// ====================================================================================================
void InitSave(void)
{
	int nCntSave;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (nCntSave = 0; nCntSave < SAVE_DATE; nCntSave++)
	{
		g_aSave[nCntSave].aName[nCntSave];
		g_aSave[nCntSave].nPoint = 0;
	}

	strcpy(g_cComment1, "#\n");
	strcpy(g_cComment2, "#=========================================================\n");
	strcpy(g_cComment3, "\n");
}

// ====================================================================================================
//
// セーブ関数
//
// ====================================================================================================
void SaveData(int nPoint)
{
	// ファイルポイント
	FILE *pFile;
	int aDate[6] = {};
	int nDate;
	int nCntSave;
	int nCntNum;

	ROAD *pLoad;

	pLoad = GetLoad();

	for (nCntSave = 0; nCntSave < SAVE_DATE; nCntSave++, pLoad++)
	{
		g_aSave[nCntSave].nPoint = pLoad->nPoint;
		aDate[nCntSave] = g_aSave[nCntSave].nPoint;
	}
	aDate[5] = nPoint;

	for (nCntSave = 0; nCntSave < SAVE_DATE + 1; nCntSave++)
	{
		for (nCntNum = nCntSave + 1; nCntNum < SAVE_DATE + 1; nCntNum++)
		{
			if (aDate[nCntSave] < aDate[nCntNum])
			{
				nDate = aDate[nCntNum];
				aDate[nCntNum] = aDate[nCntSave];
				aDate[nCntSave] = nDate;
			}
		}
	}

	// ファイル
	pFile = fopen(SAVE_FILE_NAME, "w");

	// 開けた
	if (pFile != NULL)
	{
		for (nCntSave = 0; nCntSave < SAVE_DATE; nCntSave++)
		{
			fprintf(pFile, "%d\n\n", aDate[nCntSave]);	// ポイント
		}
		// ファイル閉
		fclose(pFile);
	}

	// 開けない
	else
	{
		printf("開けませんでした\n");
	}
}
// ====================================================================================================
//
// セーブデータ取得関数
//
// ====================================================================================================
void SaveModel(void)
{
	//ファイルポイント
	FILE *pFile;

	//変数宣言
	int nCntLoad = 0;			//ロードカウント
	char cHeadText[128];		//代入用
	char cWriteText[128];		//文字としての書き込み用
	char cEqual[8] = { "=" };	//イコール用

	//モデルのポインタ
	MODEL *pModel;
	pModel = GetModel();

	//ファイル開く
	pFile = fopen("DATA/road/road.txt", " w");
	
	//開けた
	if (pFile != NULL)
	{
		//ブロックコメント
		fputs(g_cComment2, pFile);
		//コメント改行
		fputs(g_cComment1, pFile);

		strcpy(cHeadText, "# ロードモデル\n");
		fputs(cHeadText, pFile);

		strcpy(cHeadText, "# Author : Kimura Kouta\n");
		fputs(cHeadText, pFile);

		//コメント改行
		fputs(g_cComment1, pFile);

		//ブロックコメント
		fputs(g_cComment2, pFile);

		//改行
		fputs(g_cComment3, pFile);

		//モデルの情報//

		//スクリプト
		strcpy(cHeadText, "SCRIPT");

		fputs(cHeadText, pFile);

		//改行
		fputs(g_cComment3, pFile);

		//スクリプト
		if (strcmp(cHeadText, "SCRIPT") == 0)
		{
			//エンドスクリプトが通るまでループ
			while (strcmp(cHeadText, "END_SCRIPT") != 0)
			{
				if (pModel->bUse)
				{
					//モデルセット
					strcpy(cHeadText, "MODELSET\n");
					sprintf(cWriteText, "    %s", &cHeadText);
					fputs(cWriteText, pFile);

					//エンドモデルがでくるまでループ
					while (strcmp(cHeadText, "END_MODELSET") != 0)
					{
						//カウント
						switch (nCntLoad)
						{
							//ポジション
						case 0:
							strcpy(cHeadText, "pos");
							sprintf(cWriteText, "        %s %s %0.1f %0.1f %0.1f", &cHeadText, &cEqual, pModel->Pos.x, pModel->Pos.y, pModel->Pos.z);
							fputs(cWriteText, pFile);
							fputs(g_cComment3, pFile);

							//カウントアップ
							nCntLoad++;
							break;

							//回転量
						case 1:
							strcpy(cHeadText, "rot");
							sprintf(cWriteText, "        %s %s %0.1f %0.1f %0.1f", &cHeadText, &cEqual, pModel->rot.x, pModel->rot.y, pModel->rot.z);
							fputs(cWriteText, pFile);
							fputs(g_cComment3, pFile);

							//カウントアップ
							nCntLoad++;
							break;

						case 2:
							strcpy(cHeadText, "nType");
							sprintf(cWriteText, "        %s %s %d", &cHeadText, &cEqual, pModel->nTypeModel);
							fputs(cWriteText, pFile);
							fputs(g_cComment3, pFile);

							//エンドモデルセット
							strcpy(cHeadText, "END_MODELSET");
							sprintf(cWriteText, "    %s", &cHeadText);
							fputs(cWriteText, pFile);
							fputs(g_cComment3, pFile);

							//カウントの初期化
							nCntLoad = 0;
							break;
						}
					}
				}
				//エンドスクリプト
				else
				{
					strcpy(cHeadText, "END_SCRIPT");
					fputs(cHeadText, pFile);
				}
				//モデルの更新
				pModel++;
			}
		}
		//モデルの情報終了
		fclose(pFile);
	}
	//ファイルが開けなかった
	else
	{
		printf("開けませんでした");
	}
}

// ====================================================================================================
//
// セーブデータ取得関数
//
// ====================================================================================================
SAVE *GetSave(void)
{
	return &g_aSave[0];
}
