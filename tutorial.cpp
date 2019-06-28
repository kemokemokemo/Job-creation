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
#include "bullet.h"
#include "meshField.h"
#include "meshFwall.h"
#include "Explosion.h"
#include "effect.h"
#include "player.h"
#include "fade.h"
#include "save.h"
#include "road.h"
#include "GameText.h"
#include "TutoModel.h"
#include "Controlar.h"
#include "sound.h"

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

	//弾の初期化処理
	InitBullet();

	//フィールドの初期化処理
	InitMeshField();

	//壁の初期化処理
	InitMeshWall();

	//爆発の初期化処理
	InitExplosion();

	//エフェクトの初期化処理
	InitEffect();

	LoadObject();

	InitGameText();

	SetGameText(D3DXVECTOR3(1000.0f, 600.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 210, 180, 4);

	//SetGameText(D3DXVECTOR3(1100.0f, 550.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 180, 180, 4);

	SetMeshWall(D3DXVECTOR3(1700.0f, 45.0f, 0.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-1700.0f, 45.0f, 0.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetMeshWall(D3DXVECTOR3(0.0f, 45.0f, -1700.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetMeshWall(D3DXVECTOR3(0.0f, 45.0f, 1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
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


	//バレットの終了処理
	UninitBullet();

	//フィールドの終了処理
	UninitMeshField();

	//壁の終了処理
	UninitMeshWall();

	//爆発の終了処理
	UninitExplosion();

	//爆発の終了処理
	UninitEffect();

	UninitGameText();

}

//================================================================================================
// 背景の更新処理
//=================================================================================================
void UpdateTutorial(void)
{
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

	UpdateBullet();

	UpdateMeshField();

	UpdateMeshWall();

	UpdateExplosion();

	UpdateEffect();

	UpdateGameText();

}

//================================================================================================
// 背景の描画処理
//=================================================================================================
void DrawTutorial(void)
{

	// カメラの設定
	SetCamera();

	DrawMeshField();

	DrawMeshWall();

	DrawEffect();

	// 影の描画処理
	DrawShadow();

	// モデルの描画処理
	DrawTutoModel();

	DrawBullet();

	DrawExplosion();

	DrawPlayer();

	DrawGameText();

}

