//====================================================================================================
//
// 背景処理 (Gameover.cpp)
// Author  Kimura Kouta
//
//====================================================================================================
#include"Gameover.h"
#include"input.h"
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
#define GAMEOVER_TEX "DATA/TEX/GAMEOVER.jpg"//読み込むテクスチャファイル名
#define GAMEOVER_POS_X	(0)			    //ポリゴンの表示位置(左上X)
#define GAMEOVER_POS_Y	(0)			    //ポリゴンの表示位置(左上Y)
#define GAMEOVER_SIZE_X	(1280)			//ポリゴンのサイズ(横幅)
#define GAMEOVER_SIZE_Y	(720)			//ポリゴンのサイズ(立幅)
#define GAMEOVERCOLOR_TEX (255)

//=====================================================================================================
// グローバル変数
//=====================================================================================================
VERTEX_3D g_pVertexGameover[4];
LPDIRECT3DTEXTURE9 g_pTextureGameover = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGameover = NULL;


//================================================================================================
// 背景の初期化
//=================================================================================================
void InitGameover(void)
{
	//	デバイスを取得する
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	InitLight();
	InitCamera();
	InitMeshField();
	InitGameText();
	InitMeshWall();

	//テキストの設定
	SetGameText(D3DXVECTOR3(670.0f, 250.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 280, 180, 1);
	SetGameText(D3DXVECTOR3(1000.0f, 600.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 210, 180, 3);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		GAMEOVER_TEX,
		&g_pTextureGameover);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGameover,
		NULL);

	VERTEX_3D *pVtx;

	g_pVtxBuffGameover->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定(右回りで設定する）
	pVtx[0].Pos = D3DXVECTOR3(GAMEOVER_POS_X, GAMEOVER_POS_Y, 0.0f);
	pVtx[1].Pos = D3DXVECTOR3(GAMEOVER_POS_X + GAMEOVER_SIZE_X, GAMEOVER_POS_Y, 0.0f);
	pVtx[2].Pos = D3DXVECTOR3(GAMEOVER_POS_X, GAMEOVER_POS_Y + GAMEOVER_SIZE_Y, 0.0f);
	pVtx[3].Pos = D3DXVECTOR3(GAMEOVER_POS_X + GAMEOVER_SIZE_X, GAMEOVER_POS_Y + GAMEOVER_SIZE_Y, 0.0f);

	//頂点ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラーの設定(0～255の値で設定）
	pVtx[0].Col = D3DCOLOR_RGBA(GAMEOVERCOLOR_TEX, GAMEOVERCOLOR_TEX, GAMEOVERCOLOR_TEX, GAMEOVERCOLOR_TEX);
	pVtx[1].Col = D3DCOLOR_RGBA(GAMEOVERCOLOR_TEX, GAMEOVERCOLOR_TEX, GAMEOVERCOLOR_TEX, GAMEOVERCOLOR_TEX);
	pVtx[2].Col = D3DCOLOR_RGBA(GAMEOVERCOLOR_TEX, GAMEOVERCOLOR_TEX, GAMEOVERCOLOR_TEX, GAMEOVERCOLOR_TEX);
	pVtx[3].Col = D3DCOLOR_RGBA(GAMEOVERCOLOR_TEX, GAMEOVERCOLOR_TEX, GAMEOVERCOLOR_TEX, GAMEOVERCOLOR_TEX);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	g_pVtxBuffGameover->Unlock();
}

//================================================================================================
// 背景の開放処理
//=================================================================================================
void UninitGameover(void)
{

	UninitLight();
	UninitCamera();
	UninitMeshField();
	UninitGameText();
	UninitMeshWall();

	//テクスチャの関数
	if (g_pTextureGameover != NULL)
	{
		g_pTextureGameover->Release();
		g_pTextureGameover = NULL;
	}
	if (g_pVtxBuffGameover != NULL)
		//頂点バッファの開放
	{
		g_pVtxBuffGameover->Release();
		g_pVtxBuffGameover = NULL;
	}
}

//================================================================================================
// 背景の更新処理
//=================================================================================================
void UpdateGameover(void)
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
void DrawGameover(void)
{

	SetCamera();
	DrawMeshField();
	DrawMeshWall();
	DrawGameText();

	//	デバイスを取得する
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//頂点バッファをデバイスデータのデバイスにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffGameover, 0, sizeof(VERTEX_3D));

	pDevice->SetFVF(FVF_VERTEX_3D);

	//頂点フォーマットの設定
	pDevice->SetTexture(0, g_pTextureGameover);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}