//====================================================================================================
//
// 背景処理 (Result.cpp)
// Author  Kimura Kouta
//
//====================================================================================================
#include "Result.h"//インクルードファイル
#include "input.h"
#include "fade.h"
#include "light.h"
#include "camera.h"
#include "meshField.h"
#include "GameText.h"
#include "Controlar.h"
#include "sound.h"
#include "meshFwall.h"

//====================================================================================================
// マクロ定義
//==================================================================================================== 
#define RESULT_TEX "DATA/TEX/RESULT.jpg"//読み込むテクスチャファイル名
#define RESULT_POS_X	(0)			    //ポリゴンの表示位置(左上X)
#define RESULT_POS_Y	(0)			    //ポリゴンの表示位置(左上Y)
#define RESULT_SIZE_X	(1280)			//ポリゴンのサイズ(横幅)
#define RESULT_SIZE_Y	(720)			//ポリゴンのサイズ(立幅)
#define RESULTCOLOR_TEX (255)

//=====================================================================================================
// グローバル変数
//=====================================================================================================
VERTEX_3D g_pVertexResult[4];
LPDIRECT3DTEXTURE9 g_pTextureResult = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;

//================================================================================================
// 背景の初期化
//=================================================================================================
void InitResult(void)
{

	InitLight();
	InitCamera();
	InitMeshField();
	InitGameText();
	InitMeshWall();

	SetGameText(D3DXVECTOR3(670.0f, 250.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 280, 180, 2);

	SetGameText(D3DXVECTOR3(1000.0f, 600.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 210, 180, 3);

	//	デバイスを取得する
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

	VERTEX_3D *pVtx;

	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定(右回りで設定する）
	pVtx[0].Pos = D3DXVECTOR3(RESULT_POS_X, RESULT_POS_Y, 0.0f);
	pVtx[1].Pos = D3DXVECTOR3(RESULT_POS_X + RESULT_SIZE_X, RESULT_POS_Y, 0.0f);
	pVtx[2].Pos = D3DXVECTOR3(RESULT_POS_X, RESULT_POS_Y + RESULT_SIZE_Y, 0.0f);
	pVtx[3].Pos = D3DXVECTOR3(RESULT_POS_X + RESULT_SIZE_X, RESULT_POS_Y + RESULT_SIZE_Y, 0.0f);

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

	g_pVtxBuffResult->Unlock();
}

//================================================================================================
// 背景の開放処理
//=================================================================================================
void UninitResult(void)
{
	UninitLight();
	UninitCamera();
	UninitMeshField();
	UninitGameText();
	UninitMeshWall();

	//テクスチャの関数
	if (g_pTextureResult != NULL)
	{
		g_pTextureResult->Release();
		g_pTextureResult = NULL;
	}
	if (g_pVtxBuffResult != NULL)
		//頂点バッファの開放
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
}

//================================================================================================
// 背景の更新処理
//=================================================================================================
void UpdateResult(void)
{
	UpdateLight();

	UpdateCamera();

	UpdateMeshField();

	UpdateGameText();

	UpdateMeshWall();

	if (GetFade() == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_RETURN) || GetJoypadTrigger(0, JOYPADKEY_START))
		{
			PlaySound(SOUND_LABEL_SE_ENTER);
			SetFade(MODE_RANKING);
		}
	}
}

//================================================================================================
// 背景の描画処理
//=================================================================================================
void DrawResult(void)
{
	SetCamera();

	DrawMeshField();

	DrawMeshWall();

	DrawGameText();

	//	デバイスを取得する
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//頂点バッファをデバイスデータのデバイスにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_3D));

	pDevice->SetFVF(FVF_VERTEX_3D);

	//頂点フォーマットの設定
	pDevice->SetTexture(0, g_pTextureResult);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}