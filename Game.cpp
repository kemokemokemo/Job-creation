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
#include "bullet.h"
#include "meshField.h"
#include "meshFwall.h"
#include "Explosion.h"
#include "effect.h"
#include "player.h"
#include "fade.h"
#include "save.h"
#include "road.h"
#include "pause.h"
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

	//時間の初期化処理
	InitTime();

	//制限時間
	AddTime(300);

	//ポーズの初期化
	InitPause();

	//死体の初期化
	InitIce();

	//ゲームテキストの初期化
	InitGameText();

	SetGameText(D3DXVECTOR3(1100.0f, 65.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 120, 100, 5);

	//残機の初期化
	InitZanki();

	//残機設定
	AddZanki(3);

	//モデルの初期化処理
	LoadObject();

	SetMeshWall(D3DXVECTOR3(1700.0f, 45.0f, 0.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-1700.0f, 45.0f, 0.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetMeshWall(D3DXVECTOR3(0.0f, 45.0f, -1700.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetMeshWall(D3DXVECTOR3(0.0f, 45.0f, 1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetMeshWall(D3DXVECTOR3(5000.0f, 45.0f, 0.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetMeshWall(D3DXVECTOR3(2000.0f, 45.0f, 0.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetMeshWall(D3DXVECTOR3(3500.0f, 45.0f, -1700.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetMeshWall(D3DXVECTOR3(3500.0f, 45.0f, 1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

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

	//時間の終了処理
	UninitTime();

	//死体の終了処理
	UninitIce();

	//ゲームテキストの終了処理
	UninitGameText();

	//残機の終了処理
	UninitZanki();

	//ポーズの終了処理
	UninitPause();

	// 敵終了処理
	//UninitEnemy();

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

		//バレットの更新処理
		UpdateBullet();

		//フィールドの更新処理
		UpdateMeshField();

		//壁の更新処理
		UpdateMeshWall();

		//爆発の更新処理
		UpdateExplosion();

		//エフェクトの更新処理
		UpdateEffect();

		//時間の更新処理
		UpdateTime();

		//ゲームテキストの更新処理
		UpdateGameText();

		//残機の更新処理
		UpdateZanki();

		//ポーズの更新処理
		UpdatePause();

		//for (int nCntParticle = 0; nCntParticle < 1; nCntParticle++)
		//{
		//	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//	float fRadius = 20;
		//	int nLife = 20000;
		//	float fAngle = 0;
		//	float fSpeed = rand() % 100 / 1.0f;
		//	fAngle = 0.4f * nCntParticle;
		//	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, -2.0f, 0.0f);

		//	D3DXVECTOR3 pos = D3DXVECTOR3(rand() % 200 / 0.4f, 500, rand() % 200 / 0.4f);

		//	D3DXVECTOR3 pos2 = D3DXVECTOR3(rand() % 200 / -0.4f, 500, rand() % 200 / 0.4f);

		//	D3DXVECTOR3 pos3 = D3DXVECTOR3(rand() % 200 / 0.4f, 500, rand() % 200 / -0.4f);

		//	D3DXVECTOR3 pos4 = D3DXVECTOR3(rand() % 200 / -0.4f, 500, rand() % 200 / -0.4f);

		//	SetParticle(pos, move, col, fRadius, nLife, 0, 1);
		//	SetParticle(pos2, move, col, fRadius, nLife, 0, 1);
		//	SetParticle(pos3, move, col, fRadius, nLife, 0, 1);
		//	SetParticle(pos4, move, col, fRadius, nLife, 0, 1);
		//}
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

	//バレットの描画処理
	DrawBullet();

	//爆発の描画処理
	DrawExplosion();

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

	//ポーズの描画処理
	DrawPause();
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