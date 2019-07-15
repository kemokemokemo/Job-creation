//====================================================================================================
//
// メイン (Game.cpp)
// Author  Kimura Kouta
//
//====================================================================================================
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
#include "time.h"
#include "ice.h"
#include "GameText.h"
#include "zanki.h"

//====================================================================================================
// マクロ定義
//==================================================================================================== 

//=====================================================================================================
// グローバル変数
//=====================================================================================================
GAMESTATE g_gamestate = GAMESTATE_NONE;
int g_nCounterGameState = 0;

//================================================================================================
// 背景の初期化
//=================================================================================================
void InitGame(void)
{
	//カメラの初期化処理
	InitCamera();

	// ライトの初期化処理
	InitLight();

	//影の初期化処理
	InitShadow();

	//モデルの初期化処理
	InitModel();

	//プレイヤーの初期化処理
	InitPlayer();

	//フィールドの初期化処理
	InitMeshField();

	//壁の初期化処理
	InitMeshWall();

	//エフェクトの初期化処理
	InitEffect();

	//時間の初期化処理
	InitTime();

	//制限時間
	AddTime(300);

	//死体の初期化
	InitIce();

	//ゲームテキストの初期化
	InitGameText();

	SetGameText(D3DXVECTOR3(1100.0f, 65.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 120, 100, 5);

	//残機の初期化
	InitZanki();

	//残機設定
	AddZanki(3);

	//ステージ１の壁の生成
	SetMeshWall(D3DXVECTOR3(1700.0f, 45.0f, 0.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-1700.0f, 45.0f, 0.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetMeshWall(D3DXVECTOR3(0.0f, 45.0f, -1700.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetMeshWall(D3DXVECTOR3(0.0f, 45.0f, 1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//ステージ2の壁の生成
	SetMeshWall(D3DXVECTOR3(5000.0f, 45.0f, 0.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetMeshWall(D3DXVECTOR3(2000.0f, 45.0f, 0.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetMeshWall(D3DXVECTOR3(3500.0f, 45.0f, -1700.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetMeshWall(D3DXVECTOR3(3500.0f, 45.0f, 1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//ステージ3の壁の生成
	SetMeshWall(D3DXVECTOR3(-1800.0f, 45.0f, 0.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-4800.0f, 45.0f, 0.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-3000.0f, 45.0f, -1700.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-3000.0f, 45.0f, 1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	g_gamestate = GAMESTATE_NORMAL;
	g_nCounterGameState = 0;

	return;
}

//================================================================================================
// 背景の開放処理
//=================================================================================================
void UninitGame(void)
{
	//カメラの終了処理
	UninitCamera();

	//ライトの終了処理
	UninitLight();

	//影の終了処理
	UninitShadow();

	//モデルの終了処理
	UninitModel();

	//プレイヤーの終了処理
	UninitPlayer();

	//フィールドの終了処理
	UninitMeshField();

	//壁の終了処理
	UninitMeshWall();

	//爆発の終了処理
	UninitEffect();

	//時間の終了処理
	UninitTime();

	//死体の終了処理
	UninitIce();

	//ゲームテキストの終了処理
	UninitGameText();

	//残機の終了処理
	UninitZanki();

}

//================================================================================================
// 背景の更新処理
//=================================================================================================
void UpdateGame(void)
{
	//プレイヤーの取得
	PLAYER *pPlayer;
	pPlayer = GetPlayer();

	switch (g_gamestate)
	{
	case 	GAMESTATE_NORMAL:

		//カメラの更新処理
		UpdateCamera();

		//ライトの更新処理
		UpdateLight();

		//影の更新処理
		UpdateShadow();

		//モデルの更新処理
		UpdateModel();

		//プレイヤーの更新処理
		UpdatePlayer();

		//死体の更新処理
		UpdateIce();

		//フィールドの更新処理
		UpdateMeshField();

		//壁の更新処理
		UpdateMeshWall();

		//エフェクトの更新処理
		UpdateEffect();

		//時間の更新処理
		UpdateTime();

		//ゲームテキストの更新処理
		UpdateGameText();

		//残機の更新処理
		UpdateZanki();

		break;

	case GAMESTATE_END:
		g_nCounterGameState++;
		if (g_nCounterGameState >= 60)
		{
			//SaveData(GetScore());
			//LoadData();

			AddTime(-300);
			AddZanki(-3);
			g_gamestate = GAMESTATE_NONE;
			SetFade(MODE_RESULT);
		}
		break;

	case GAMESTATE_END2:
		g_nCounterGameState++;
		if (g_nCounterGameState >= 60)
		{
			//SaveData(GetScore());
			//LoadData();
			AddTime(-300);
			AddZanki(-3);
			g_gamestate = GAMESTATE_NONE;
			SetFade(MODE_GAMEOVER);
		}
		break;
	}
}

//================================================================================================
// 背景の描画処理
//=================================================================================================
void DrawGame(void)
{
	//カメラの設定
	SetCamera();

	//フィールドの描画処理
	DrawMeshField();

	//壁の描画処理
	DrawMeshWall();

	//モデルの描画処理
	DrawModel();

	//プレイヤーの描画処理
	DrawPlayer();

	//エフェクトの描画処理
	DrawEffect();

	//死体の描画処理
	DrawIce();

	//タイムの描画処理
	DrawTime();

	//ゲームテキストの描画処理
	DrawGameText();

	//残機の描画処理
	DrawZanki();

	//影の描画処理
	DrawShadow();

}

void SetGameState(GAMESTATE state)
{
	g_gamestate = state;
	g_nCounterGameState = 0;
}

GAMESTATE GetGameState(void)
{
	return g_gamestate;
}