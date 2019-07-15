//====================================================================================================
//
// 背景処理 (Tutorial.cpp)
// Author  Kimura Kouta
//
//====================================================================================================
#include "Tutorial.h"
#include "Game.h"
#include "camera.h"
#include "light.h"
#include "model.h"
#include "input.h"
#include "Shadow.h"
#include "meshField.h"
#include "meshFwall.h"
#include "effect.h"
#include "player.h"
#include "fade.h"
#include "save.h"
#include "road.h"
#include "GameText.h"
#include "TutoModel.h"
#include "Controlar.h"
#include "sound.h"
#include "ice.h"

//====================================================================================================
// マクロ定義
//==================================================================================================== 
#define TUTORIAL_TEX "DATA/TEX/tutorial.jpg"//読み込むテクスチャファイル名
#define TUTORIAL_POS_X	(0)			    //ポリゴンの表示位置(左上X)
#define TUTORIAL_POS_Y	(0)			    //ポリゴンの表示位置(左上Y)
#define TUTORIAL_SIZE_X	(1280)			//ポリゴンのサイズ(横幅)
#define TUTORIAL_SIZE_Y	(720)			//ポリゴンのサイズ(立幅)
#define TUTORIALCOLOR_TEX (255)

//=====================================================================================================
// グローバル変数
//=====================================================================================================
VERTEX_2D g_pVertexTutorial[4];
LPDIRECT3DTEXTURE9 g_pTextureTutorial = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;
float postuto;
int g_cCount;

//================================================================================================
// 背景の初期化
//=================================================================================================
void InitTutorial(void)
{
	// カメラの初期化処理
	InitCamera();

	// ライトの初期化処理
	InitLight();

	//影の初期化処理
	InitShadow();

	//モデルの初期化処理
	InitTutoModel();

	//プレイヤーの初期化処理
	InitPlayer();

	//氷の初期化処理
	InitIce();

	//フィールドの初期化処理
	InitMeshField();

	//壁の初期化処理
	InitMeshWall();
	SetMeshWall(D3DXVECTOR3(1700.0f, 45.0f, 0.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-1700.0f, 45.0f, 0.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetMeshWall(D3DXVECTOR3(0.0f, 45.0f, -1700.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetMeshWall(D3DXVECTOR3(0.0f, 45.0f, 1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//エフェクトの初期化処理
	InitEffect();

	//テキストの初期化処理
	InitGameText();
	SetGameText(D3DXVECTOR3(1000.0f, 600.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 210, 180, 4);
}

//================================================================================================
// 背景の開放処理
//=================================================================================================
void UninitTutorial(void)
{
	// カメラの終了処理
	UninitCamera();

	// ライトの終了処理
	UninitLight();

	//影の終了処理
	UninitShadow();

	//モデルの終了処理
	UninitTutoModel();

	//プレイヤーの終了処理
	UninitPlayer();

	//氷の終了処理
	UninitIce();

	//フィールドの終了処理
	UninitMeshField();

	//壁の終了処理
	UninitMeshWall();

	//エフェクトの終了処理
	UninitEffect();

	//テキストの終了処理
	UninitGameText();
}

//================================================================================================
// 背景の更新処理
//=================================================================================================
void UpdateTutorial(void)
{
	//モードの切り替え
	if (GetFade() == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_SPACE) || GetJoypadTrigger(0, JOYPADKEY_START))
		{
			PlaySound(SOUND_LABEL_SE_ENTER);
			SetFade(MODE_GAME);
		}
	}

	// カメラの更新処理
	UpdateCamera();

	// ライトの更新処理
	UpdateLight();

	//影の更新処理
	UpdateShadow();

	//モデルの更新処理
	UpdateTutoModel();

	//プレイヤーの更新処理
	UpdatePlayer();

	//氷の更新処理
	UpdateIce();

	//フィールドの更新処理
	UpdateMeshField();

	//壁の更新処理
	UpdateMeshWall();

	//エフェクトの更新処理
	UpdateEffect();

	//テキストの更新処理
	UpdateGameText();

}

//================================================================================================
// 背景の描画処理
//=================================================================================================
void DrawTutorial(void)
{

	//カメラの設定
	SetCamera();

	//フィールドの描画処理
	DrawMeshField();

	//壁の描画処理
	DrawMeshWall();

	//エフェクトの描画処理
	DrawEffect();

	//モデルの描画処理
	DrawTutoModel();

	//プレイヤーの描画処理
	DrawPlayer();

	//氷の描画処理
	DrawIce();

	//影の描画処理
	DrawShadow();

	//テキストの描画処理
	DrawGameText();
}

