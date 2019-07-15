//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : KIMURA KOUTA
//
//=============================================================================
#include "player.h"
#include "input.h"
#include "camera.h"
#include "Shadow.h"
#include "effect.h"
#include "model.h"
#include "Game.h"
#include "fade.h"
#include "effect.h"
#include "ice.h"
#include "zanki.h"
#include "Controlar.h"
#include "GameText.h"
#include "sound.h"
#include "TutoModel.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define PLAYER_FILE					"DATA/road/player.txt"			// ファイル名
#define PLAY_MOTION					(true)							// モーション [On,Off]
#define MOTIONBREADFRAME			(10)							// モーションブレンドのフレーム数
#define SPEED						(0.15f)

//=============================================================================
// グローバル変数
//=============================================================================
LoadModel				g_LoadPlayer[MAX_PARTS];		// 読み込んだモデルの情報
LoadMotion				g_Motion;						// 読み込んだモーション情報
PLAYER					g_Player;						// プレイヤーの情報
int						g_nCounterKeySet;				// キーセットのカウンター
int						g_nCounterFrame;				// フレーム数のカウンター
int						g_nMotionBlendFrame;			// モーションブレンド用のフレーム数
D3DXVECTOR3				g_posDiff[MAX_PARTS];			// １フレームあたりの差分 [pos]
D3DXVECTOR3				g_RotDiff[MAX_PARTS];			// １フレームあたりの差分 [Rot]

D3DXVECTOR3				g_fDistanceP;
float g_nCnt;

//=============================================================================
// 初期化処理
//=============================================================================
void InitPlayer(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//構造体の初期化
	g_Player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.Diffrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.rotDestPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.rotDestPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.fMoveSpeed = 0.0f;
	g_Player.fRadius = 100.0f;
	g_Player.fHeight = 0.0f;
	g_Player.nIdxLine = 0;
	g_Player.fDestAngle = D3DX_PI;
	g_Player.bJump = false;
	g_Player.bPlayerDeth = false;
	g_Player.bPlayerCrear = false;
	g_Player.bNolmal = false;
	g_Player.bWalk = false;
	g_Player.bJumpMS = false;
	g_Player.bDeth = false;
	g_Player.bClearFlag1 = false;
	g_Player.bClearFlag2 = false;
	g_Player.nZanki = 3;

	g_Player.nCntDeth = 0;

	g_Player.hIdxShadow = SetShadow(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y, g_Player.pos.z), g_Player.rot);

	for (int nCntModel = 0; nCntModel < MAX_PLAYER; nCntModel++)
	{// モデルの情報
		g_Player.aPlayerModel[nCntModel].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// モデルの位置
		g_Player.aPlayerModel[nCntModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// モデルの向き
		g_Player.aPlayerModel[nCntModel].nType = 0;												// モデルの種類
		g_Player.aPlayerModel[nCntModel].nIdxModelParent = -1;									// 親モデルのインデックス
	}

	// モーション 
	g_Player.nMotionTypeOld = MOTION_MAX;			// 前モーションの種類
	g_Player.nMotionType = MOTION_NEUTRAL;			// モーションの種類
	g_Player.nFrameALL = 0;							// モーションの最大フレーム数
	g_Player.nNowFrame = 0;							// モーションの現在のフレーム数

	g_nCounterKeySet = 0;							// キーセットのカウンター
	g_nCounterFrame = 0;							// フレーム数のカウンター
	g_nMotionBlendFrame = 0;						// モーションブレンド用のフレーム数

	g_Player.nMaxParts = 0;							// 使用するするモデルの数

	for (int nCntModel = 0; nCntModel < MAX_PLAYER; nCntModel++)
	{// モデルの最大数
		g_posDiff[nCntModel] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// １フレームあたりの差分 [pos]
		g_RotDiff[nCntModel] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// １フレームあたりの差分 [Rot]
	}

	//==============================
	// ファイル読み込み
	//==============================
	LoadPlayer();

	//#if 1
	//==============================
	// Xファイル読み込み
	//==============================

	for (int nCntModel = 0; nCntModel < g_Player.nLoadParts; nCntModel++)
	{// 読み込むモデルの最大数
		D3DXLoadMeshFromX(g_LoadPlayer[nCntModel].pXFileName,		// 読み込むXファイル名
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_LoadPlayer[nCntModel].pBuffMat,		// マテリアル情報ポインタ
			NULL,
			&g_LoadPlayer[nCntModel].NumMat,		// マテリアル情報の数
			&g_LoadPlayer[nCntModel].pMesh);		// メッシュ情報ポインタ

		//テクスチャの読み込み
		D3DXMATERIAL *pMat;							// Xファイルから取り出したマテリアル情報を入れる

		// Xファイルからマテリアル情報を取得
		pMat = (D3DXMATERIAL*)g_LoadPlayer[nCntModel].pBuffMat->GetBufferPointer();

		// テクスチャのポインタをマテリアル情報の数分配列化
		g_LoadPlayer[nCntModel].pTexture = new LPDIRECT3DTEXTURE9[(int)g_LoadPlayer[nCntModel].NumMat];	// int型に直す

		// 取得したファイル名を入力
		for (int nCntNumMat = 0; nCntNumMat < (int)g_LoadPlayer[nCntModel].NumMat; nCntNumMat++)	// DWORD型からint型に変換する
		{
			// テクスチャのポインタ初期化
			g_LoadPlayer[nCntModel].pTexture[nCntNumMat] = NULL;

			// テクスチャファイル名が入っている場合、読み込む
			if (pMat[nCntNumMat].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFile(pDevice, pMat[nCntNumMat].pTextureFilename,
				&g_LoadPlayer[nCntModel].pTexture[nCntNumMat]);
			}
		}
	}

	//Xファイルから最大値と最小値の設定
	int nNumVertices;						//頂点数
	DWORD sizeFVF;							//頂点フォーマットのサイズ
	BYTE *pVertexBuffer;					//頂点バッファのポインタ

	g_Player.vtxMinPlayer = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
	g_Player.vtxMaxPlayer = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		//頂点数を取得
		nNumVertices = g_LoadPlayer[nCntPlayer].pMesh->GetNumVertices();

		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_LoadPlayer[nCntPlayer].pMesh->GetFVF());

		//頂点バッファをロック
		g_LoadPlayer[nCntPlayer].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertexBuffer);

		for (int nCntvtx = 0; nCntvtx < nNumVertices; nCntvtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVertexBuffer;
			//すべての変数を比較して最小・最大値を決める
			if (g_Player.vtxMinPlayer.x > vtx.x)
			{
				g_Player.vtxMinPlayer.x = vtx.x;
			}
			if (g_Player.vtxMaxPlayer.x < vtx.x)
			{
				g_Player.vtxMaxPlayer.x = vtx.x;
			}
			if (g_Player.vtxMinPlayer.y > vtx.y)
			{
				g_Player.vtxMinPlayer.y = vtx.y;
			}
			if (g_Player.vtxMaxPlayer.y < vtx.y)
			{
				g_Player.vtxMaxPlayer.y = vtx.y;
			}
			if (g_Player.vtxMinPlayer.z > vtx.z)
			{
				g_Player.vtxMinPlayer.z = vtx.z;
			}
			if (g_Player.vtxMaxPlayer.z < vtx.z)
			{
				g_Player.vtxMaxPlayer.z = vtx.z;
			}
			pVertexBuffer += sizeFVF;		//サイズ分ポインタを進める
		}

		//差分の計算
		g_Player.size = (g_Player.vtxMaxPlayer - g_Player.vtxMinPlayer) * 0.01f;

		//頂点バッファのアンロック
		g_LoadPlayer[nCntPlayer].pMesh->UnlockVertexBuffer();
	}

}
//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		// メッシュの開放
		if (g_LoadPlayer[nCntPlayer].pMesh != NULL)
		{
			g_LoadPlayer[nCntPlayer].pMesh->Release();
			g_LoadPlayer[nCntPlayer].pMesh = NULL;
		}

		// マテリアルの開放
		if (g_LoadPlayer[nCntPlayer].pBuffMat != NULL)
		{
			g_LoadPlayer[nCntPlayer].pBuffMat->Release();
			g_LoadPlayer[nCntPlayer].pBuffMat = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{

	//モデルの取得
	MODEL *pModel;
	pModel = GetModel();

	// 前回のモーションを記憶
	g_Player.nMotionTypeOld = g_Player.nMotionType;

	//重力処理
	g_Player.move.y -= 0.05f;

	// 前回のポジションを記憶
	g_Player.posOld = g_Player.pos;

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{

		//慣性処理
		g_Player.move.x += (0 - g_Player.move.x) * 1 / 5;
		g_Player.move.z += (0 - g_Player.move.z) * 1 / 5;

		//モデルを動かす
		g_Player.pos += g_Player.move;

		//移動処理
		PlayerMove();

		//当たり判定
		PlayerCollision();

		//動くブロックの処理
		if (g_Player.pModel != NULL)
		{
			g_Player.pos.x += g_Player.pModel->move.x;
			g_Player.pos.z += g_Player.pModel->move.z;
		}
	}

	//プレイヤーの死亡処理
	if (g_Player.pos.y < 0.0f)
	{
		g_Player.pos.y = 0.0f;

		PlayerDeth();		
	}

	//風の処理
	if (g_Player.pos.x <= -2000 && g_Player.pos.x >= -4000)
	{
		g_Player.move.z += 0.2f;
		PlaySound(SOUND_LABEL_SE_BLIZZARD);
	}

	//=============//
	// エフェクト  //
	//=============//
	EffectRound();

	//=============//
	// モーション  //
	//=============//
	PlayerMotionPlay();

#if PLAY_MOTION
	PlayerMotion();
#endif
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9	pDevice = GetDevice();		// デバイスの取得
	D3DXMATRIX			mtxRot, mtxTrans;			// 計算用マトリックス
	D3DMATERIAL9		matDef;						// 現在のマテリアル保存用
	D3DXMATERIAL		*pMat;						// マテリアルへのポインタ
	D3DXMATRIX			mtxParent;					// 親のマトリックス

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_Player.mtxWorld);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		g_Player.rot.y,
		g_Player.rot.x,
		g_Player.rot.z);

	D3DXMatrixMultiply(&g_Player.mtxWorld,
	&g_Player.mtxWorld, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTrans,
		g_Player.pos.x,
		g_Player.pos.y,
		g_Player.pos.z);

	D3DXMatrixMultiply(&g_Player.mtxWorld,
	&g_Player.mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorld);

	// かけ合わせるマトリックスの設定
	for (int nCntModel = 0; nCntModel < g_Player.nMaxParts; nCntModel++)
	{
		if (g_Player.aPlayerModel[nCntModel].nIdxModelParent == -1)
		{
			mtxParent = g_Player.mtxWorld;
		}
		else
		{
			mtxParent = g_Player.aPlayerModel[g_Player.aPlayerModel[nCntModel].nIdxModelParent].mtxWorld;
		}

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Player.aPlayerModel[nCntModel].mtxWorld);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_Player.aPlayerModel[nCntModel].rot.y, g_Player.aPlayerModel[nCntModel].rot.x, g_Player.aPlayerModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_Player.aPlayerModel[nCntModel].mtxWorld,
			&g_Player.aPlayerModel[nCntModel].mtxWorld, &mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTrans,
			g_Player.aPlayerModel[nCntModel].pos.x, g_Player.aPlayerModel[nCntModel].pos.y, g_Player.aPlayerModel[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_Player.aPlayerModel[nCntModel].mtxWorld,
			&g_Player.aPlayerModel[nCntModel].mtxWorld, &mtxTrans);

		// 親モデルのマトリックスをかけ合わせる
		D3DXMatrixMultiply(&g_Player.aPlayerModel[nCntModel].mtxWorld,
			&g_Player.aPlayerModel[nCntModel].mtxWorld, &mtxParent);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Player.aPlayerModel[nCntModel].mtxWorld);

		// 現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_LoadPlayer[g_Player.aPlayerModel[nCntModel].nType].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_LoadPlayer[g_Player.aPlayerModel[nCntModel].nType].NumMat; nCntMat++)
		{
			// マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			// テクスチャの反映
			pDevice->SetTexture(0, 0);

			// モデル(パーツ)の描画
			g_LoadPlayer[g_Player.aPlayerModel[nCntModel].nType].pMesh->DrawSubset(nCntMat);
		}

		// マテリアルをデフォルトに戻す
		pDevice->SetMaterial(&matDef);
	}

}

//===============================================================================
// プレイヤーの移動処理
//===============================================================================
void PlayerMove(void)
{
	//カメラの取得
	CAMERA *pCamera;
	pCamera = GetCamera();

	//変数宣言
	int nStickH, nStickV;

	//プレイヤーがCLEARしてない
	if (g_Player.bPlayerCrear == false)
	{
		//移動
		if (g_Player.bPlayerDeth == false)
		{
			// アナログスティック左の取得
			GetJoypadStickLeft(0, &nStickH, &nStickV);

			if (nStickH != 0 || nStickV != 0)
			{
				g_Player.move.x += sinf(pCamera->rot.y + (float)atan2(nStickH, nStickV))*SPEED;
				g_Player.move.z += cosf(pCamera->rot.y + (float)atan2(nStickH, nStickV))*SPEED;

				g_Player.Diffrot.y = pCamera->rot.y + (float)atan2(-nStickH, -nStickV);

				g_Player.bNolmal = false;
				g_Player.bWalk = true;
				g_Player.bJumpMS = false;
				g_Player.bDeth = false;
			}

			// 上方向移動
			if (GetKeyboardPress(DIK_W) || GetJoypadPress(0, JOYPADKEY_UP))
			{
				g_Player.bNolmal = false;
				g_Player.bWalk = true;
				g_Player.bJumpMS = false;
				g_Player.bDeth = false;

				if (GetKeyboardPress(DIK_D) || GetJoypadPress(0, JOYPADKEY_RIGHT))
				{
					g_Player.bNolmal = false;
					g_Player.bWalk = true;
					g_Player.bJumpMS = false;
					g_Player.bDeth = false;

					g_Player.move.x -= sinf(pCamera->rot.y - D3DX_PI*0.75f)*SPEED;
					g_Player.move.z -= cosf(pCamera->rot.y - D3DX_PI*0.75f)*SPEED;
					g_Player.Diffrot.y = pCamera->rot.y - D3DX_PI * 0.75f;
				}

				else if (GetKeyboardPress(DIK_A) || GetJoypadPress(0, JOYPADKEY_LEFT))
				{
					g_Player.bNolmal = false;
					g_Player.bWalk = true;
					g_Player.bJumpMS = false;
					g_Player.bDeth = false;

					g_Player.move.x -= sinf(pCamera->rot.y + D3DX_PI*0.75f)*SPEED;
					g_Player.move.z -= cosf(pCamera->rot.y + D3DX_PI*0.75f)*SPEED;
					g_Player.Diffrot.y = pCamera->rot.y + D3DX_PI * 0.75f;
				}
				else
				{
					g_Player.bNolmal = false;
					g_Player.bWalk = true;
					g_Player.bJumpMS = false;
					g_Player.bDeth = false;
					g_Player.move.x -= sinf(pCamera->rot.y + D3DX_PI*-1.0f)*SPEED;
					g_Player.move.z -= cosf(pCamera->rot.y + D3DX_PI*-1.0f)*SPEED;
					g_Player.Diffrot.y = pCamera->rot.y - D3DX_PI*1.0f;
				}
			}

			// 下方向移動
			else if (GetKeyboardPress(DIK_S) || GetJoypadPress(0, JOYPADKEY_DOWN))
			{
				g_Player.bNolmal = false;
				g_Player.bWalk = true;
				g_Player.bJumpMS = false;
				g_Player.bDeth = false;
				if (GetKeyboardPress(DIK_D) || GetJoypadPress(0, JOYPADKEY_RIGHT))
				{
					g_Player.bNolmal = false;
					g_Player.bWalk = true;
					g_Player.bJumpMS = false;
					g_Player.bDeth = false;
					g_Player.move.x -= sinf(pCamera->rot.y + D3DX_PI*-0.25f)*SPEED;
					g_Player.move.z -= cosf(pCamera->rot.y + D3DX_PI*-0.25f)*SPEED;
					g_Player.Diffrot.y = pCamera->rot.y + D3DX_PI * -0.25f;
				}

				else if (GetKeyboardPress(DIK_A) || GetJoypadPress(0, JOYPADKEY_LEFT))
				{
					g_Player.bNolmal = false;
					g_Player.bWalk = true;
					g_Player.bJumpMS = false;
					g_Player.bDeth = false;
					g_Player.move.x -= sinf(pCamera->rot.y + D3DX_PI*0.25f)*SPEED;
					g_Player.move.z -= cosf(pCamera->rot.y + D3DX_PI*0.25f)*SPEED;
					g_Player.Diffrot.y = pCamera->rot.y - D3DX_PI * -0.25f;
				}

				else
				{
					g_Player.bNolmal = false;
					g_Player.bWalk = true;
					g_Player.bJumpMS = false;
					g_Player.bDeth = false;
					g_Player.move.x -= sinf(pCamera->rot.y + D3DX_PI*0.0f)*SPEED;
					g_Player.move.z -= cosf(pCamera->rot.y + D3DX_PI*0.0f)*SPEED;
					g_Player.Diffrot.y = pCamera->rot.y + D3DX_PI*0.0f;
				}
			}

			// 右
			else if (GetKeyboardPress(DIK_D) || GetJoypadPress(0, JOYPADKEY_RIGHT))
			{
				g_Player.bNolmal = false;
				g_Player.bWalk = true;
				g_Player.bJumpMS = false;
				g_Player.bDeth = false;
				g_Player.move.x -= sinf(pCamera->rot.y - D3DX_PI*0.5f)*SPEED;
				g_Player.move.z -= cosf(pCamera->rot.y - D3DX_PI*0.5f)*SPEED;
				g_Player.Diffrot.y = pCamera->rot.y + D3DX_PI*-0.5f;
			}

			else if (GetKeyboardPress(DIK_A) || GetJoypadPress(0, JOYPADKEY_LEFT))
			{
				g_Player.bNolmal = false;
				g_Player.bWalk = true;
				g_Player.bJumpMS = false;
				g_Player.bDeth = false;
				g_Player.move.x -= sinf(pCamera->rot.y + D3DX_PI*0.5f)*SPEED;
				g_Player.move.z -= cosf(pCamera->rot.y + D3DX_PI*0.5f)*SPEED;
				g_Player.Diffrot.y = pCamera->rot.y + D3DX_PI*0.5f;
			}

			if (GetKeyboardTrigger(DIK_RETURN) || GetJoypadTrigger(0, JOYPADKEY_B))
			{
				if (g_Player.bJump == false)
				{
					g_Player.move.y = 1.0f;
					g_Player.bJump = true;
					g_Player.bJumpMS = true;
					g_Player.bWalk = false;
					g_Player.bNolmal = false;
					g_Player.bDeth = false;
				}
			}

			// 差分
			if (g_fDistanceP.y = g_Player.Diffrot.y - g_Player.rot.y)
			{
				if (D3DX_PI < g_fDistanceP.y)
				{
					g_fDistanceP.y -= D3DX_PI * 2;
				}
				else if (-D3DX_PI > g_fDistanceP.y)
				{
					g_fDistanceP.y += D3DX_PI * 2;
				}
			}

			g_Player.rot.y += g_fDistanceP.y * 0.2f;
		}
	}
}

//===============================================================================
// プレイヤーの当たり判定処理
//===============================================================================
void PlayerCollision(void)
{
	if (GetMode() == MODE_GAME)
	{
		// 影の当たり判定
		if (ColisionShadow
		(&g_Player.pos,
			&g_Player.posOld,
			&g_Player.move,
			&g_Player.pModel))
		{
			g_nCnt = g_Player.pModel->vtxMaxModel.y + g_Player.pModel->Pos.y;

			//影のセット
			SetPositionShadow(g_Player.hIdxShadow, D3DXVECTOR3(g_Player.pos.x, g_nCnt, g_Player.pos.z));
		}
		else
		{
			g_nCnt = 20;
			SetPositionShadow(g_Player.hIdxShadow, D3DXVECTOR3(g_Player.pos.x, g_nCnt, g_Player.pos.z));
		}

		// 当たり判定
		if (ColisionModel
		(&g_Player.pos,
			&g_Player.posOld,
			&g_Player.move,
			&g_Player.pModel) == true)
		{
			//ジャンプを使用可能にする
			g_Player.bJump = false;

			//重力のリセット
			g_Player.move.y = 0;

		}
	}

	if (GetMode() == MODE_TUTORIAL)
	{
		if (ColisionTutoModel
		(&g_Player.pos,
			&g_Player.posOld,
			&g_Player.move,
			&g_Player.pTutoModel))
		{
			//ジャンプを使用可能にする
			g_Player.bJump = false;

			//重力のリセット
			g_Player.move.y = 0;
		}
		else
		{

		}
		// 影の当たり判定
		if (ColisionTutoShadow
		(&g_Player.pos,
			&g_Player.posOld,
			&g_Player.move,
			&g_Player.pTutoModel))
		{
			g_nCnt = g_Player.pTutoModel->vtxMaxModel.y + g_Player.pTutoModel->Pos.y;

			//影のセット
			SetPositionShadow(g_Player.hIdxShadow, D3DXVECTOR3(g_Player.pos.x, g_nCnt, g_Player.pos.z));
		}
		else
		{
			g_nCnt = 20;
			SetPositionShadow(g_Player.hIdxShadow, D3DXVECTOR3(g_Player.pos.x, g_nCnt, g_Player.pos.z));
		}
	}
}

//===============================================================================
// エフェクトの設定処理
//===============================================================================
void EffectRound(void)
{
	//吹雪のエフェクト//

	if (g_Player.pos.x <= -2000 && g_Player.pos.x >= -6000)
	{
		for (int nCntParticle = 0; nCntParticle < 50; nCntParticle++)
		{
			SetParticle(D3DXVECTOR3(rand() % (-2000) + (-4000.0f), 1000.0f, rand() % 4000 + (-2000.0f)), D3DXVECTOR3(0.0f, -10.0f, 12.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 20, 2000, 0);
		}
	}

	//魔法陣のエフェクト//

	if (g_Player.pos.x <= 1350 && g_Player.pos.x >= 1060 && g_Player.pos.z <= 150 && g_Player.pos.z >= -150)
	{
		SetParticle(D3DXVECTOR3(rand() % 170 + 1130.0f, rand() % 100 + 200.0f, rand() % 200 + (-100.0f)), D3DXVECTOR3(0.0f, 0.1f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 20, 40, 1);
		SetParticle(D3DXVECTOR3(rand() % 170 + 1130.0f, rand() % 100 + 200.0f, rand() % 200 + (-100.0f)), D3DXVECTOR3(0.0f, 0.1f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 20, 40, 2);
	}

	if (g_Player.pos.x >= -1350 && g_Player.pos.x <= -1060 && g_Player.pos.z <= 150 && g_Player.pos.z >= -150)
	{
		SetParticle(D3DXVECTOR3(rand() % -170 + -1280.0f, rand() % 100 + 200.0f, rand() % 200 + (-100.0f)), D3DXVECTOR3(0.0f, 0.1f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 20, 40, 1);
		SetParticle(D3DXVECTOR3(rand() % -170 + -1280.0f, rand() % 100 + 200.0f, rand() % 200 + (-100.0f)), D3DXVECTOR3(0.0f, 0.1f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 20, 40, 2);
	}
}

//===============================================================================
// プレイヤーの死亡処理
//===============================================================================
void PlayerDeth(void)
{
	//氷の取得
	ICE * pIce;
	pIce = GetIce();

	SetIce(g_Player.pos, D3DXVECTOR3(0.0f, g_Player.move.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	g_Player.bPlayerDeth = true;
	pIce->bUse = true;

	DeleteShadow(g_Player.hIdxShadow);

	if (g_Player.bPlayerDeth == true)
	{
		g_Player.bDeth = true;
		g_Player.bNolmal = false;
		g_Player.bWalk = false;
		g_Player.bJumpMS = false;

		g_Player.nCntDeth++;

		if (g_Player.nCntDeth == 30)
		{
			if (GetMode() == MODE_GAME)
			{
				g_Player.nZanki -= 1;
				AddZanki(-1);
			}
			g_Player.move.y += 4;
			g_Player.rot.x += 1;
		}
		if (g_Player.nCntDeth >= 31)
		{
			g_Player.move.x--;
		}

		if (g_Player.nCntDeth >= 90)
		{

			if (g_Player.nZanki == 3 || g_Player.nZanki == 2 || g_Player.nZanki == 1)
			{

				if (g_Player.pos.x <= -2000 && g_Player.pos.x >= -6000)
				{
					g_Player.pos = D3DXVECTOR3(-4400.0f, 1000.0f, 0.0f);

				}
				if (g_Player.pos.x >= -2000 && g_Player.pos.x <= 1800)
				{
					g_Player.pos = D3DXVECTOR3(0.0f, 1000.0f, 0.0f);
				}

				if (g_Player.pos.x >= 1900 && g_Player.pos.x <= 6000)
				{

					g_Player.pos = D3DXVECTOR3(4200.0f, 1000.0f, 0.0f);
				}
				//プレイヤーの動きを止める
				g_Player.bPlayerDeth = false;
				//プレイヤーの使用をしない
				pIce->bUse = false;
				//プレイヤーの回転量を戻す
				g_Player.rot.x = 0;
				//カウントの初期化
				g_Player.nCntDeth = 0;
				//影の再配置
				g_Player.hIdxShadow = SetShadow(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y, g_Player.pos.z), g_Player.rot);
			}
			else
			{
				if (GetMode() == MODE_GAME)
				{
					SetGameState(GAMESTATE_END2);
					//プレイヤーの初期化処理
					InitPlayer();
				}
				else
				{
					SetFade(MODE_TUTORIAL);
					//プレイヤーの初期化処理
					InitPlayer();
				}
			}
		}
	}
}
//===============================================================================
// プレイヤーのモーション
//===============================================================================
void PlayerMotionPlay(void)
{
	// 待機
	if (!g_Player.bWalk || !g_Player.bJumpMS || !g_Player.bDeth)
	{
		g_Player.nMotionType = MOTION_NEUTRAL;
	}

	//　歩き
	if (g_Player.bWalk)
	{
		g_Player.nMotionType = A;
		if (g_Player.nMotionType != g_Player.nMotionTypeOld)
		{
			CulFrame();
		}
		if (g_Player.nNowFrame == g_Player.nFrameALL)
		{// 最後まで再生された場合
			g_Player.bWalk = false;
		}
	}

	//　ジャンプ
	if (g_Player.bJumpMS)
	{
		g_Player.nMotionType = B;
		if (g_Player.nMotionType != g_Player.nMotionTypeOld)
		{
			CulFrame();
		}
		if (g_Player.nNowFrame == g_Player.nFrameALL)
		{// 最後まで再生された場合
			g_Player.bJumpMS = false;
		}
	}

	//　死亡
	if (g_Player.bDeth)
	{
		g_Player.nMotionType = C;
		if (g_Player.nMotionType != g_Player.nMotionTypeOld)
		{
			CulFrame();
		}
		if (g_Player.nNowFrame == g_Player.nFrameALL)
		{// 最後まで再生された場合
			g_Player.bDeth = false;
		}
	}

}

//===============================================================================
// プレイヤーのモーション
//===============================================================================
void PlayerMotion(void)
{
	// モーションの初期化

	if (g_Player.nMotionTypeOld != g_Player.nMotionType)
	{// モーションが前回と異なる
	 // キーフレーム
		g_nCounterKeySet = 0;
		// フレーム数
		g_nCounterFrame = 0;
		// モーションブレンドのフレーム数を決める
		g_nMotionBlendFrame = MOTIONBREADFRAME;
		// フレーム数の計算
		CulFrame();
	}
	// キーの切替

	switch (g_Motion.Motion[g_Player.nMotionType].nLoop)
	{// モーションの種類のループ別
	case 0:		// ループしない
		if (g_nCounterFrame == g_nMotionBlendFrame && g_Motion.Motion[g_Player.nMotionType].nNumKey == g_nCounterKeySet + 1)
		{// 最終フレーム　&& 最終キーになった
		 // フレーム数初期化
			g_nCounterFrame = 0;
			// キーセットを進める
			g_nCounterKeySet = g_Motion.Motion[g_Player.nMotionType].nNumKey - 1;		// 最後のキーセットを設定する

			// 分割フレーム数を決める
			g_nMotionBlendFrame = g_Motion.Motion[g_Player.nMotionType].nKey[g_nCounterKeySet].nframe;
		}
		else if (g_nCounterFrame == g_nMotionBlendFrame && g_Motion.Motion[g_Player.nMotionType].nNumKey != g_nCounterKeySet)
		{// 最後のフレーム && 最終キーではない
		 // フレーム数初期化
			g_nCounterFrame = 0;
			// キーセットを進める
			g_nCounterKeySet = (g_nCounterKeySet + 1) % g_Motion.Motion[g_Player.nMotionType].nNumKey;
			// 分割フレーム数を決める
			g_nMotionBlendFrame = g_Motion.Motion[g_Player.nMotionType].nKey[g_nCounterKeySet].nframe;
		}
		break;

	case 1:		// ループする
		if (g_nCounterFrame == g_nMotionBlendFrame)
		{// 最後のフレーム
		 // フレーム数初期化
			g_nCounterFrame = 0;
			// キーセットを進める
			g_nCounterKeySet = (g_nCounterKeySet + 1) % g_Motion.Motion[g_Player.nMotionType].nNumKey;
			// 分割フレーム数を決める
			g_nMotionBlendFrame = g_Motion.Motion[g_Player.nMotionType].nKey[g_nCounterKeySet].nframe;
		}
		break;
	}

	if (g_nCounterFrame == 0)
	{// 最初のフレームになったら、次のキーセットとの差分計算
		for (int nCntParts = 0; nCntParts < MAX_PLAYER; nCntParts++)
		{
			// 各パーツの位置の差分 = ([次]のキーセットの各パーツの位置 + 各パーツの初期オフセット[位置]) - [現在]の各パーツの位置
			g_posDiff[nCntParts] = (g_Motion.Motion[g_Player.nMotionType].nKey[g_nCounterKeySet].pos[nCntParts] +
				g_Motion.Offset[nCntParts].pos) - g_Player.aPlayerModel[nCntParts].pos;

			// 各パーツの向きの差分 = [次]のキーセットの各パーツの向き + 各パーツの初期オフセット[向き] - [現在]の各パーツの向き
			g_RotDiff[nCntParts] = g_Motion.Motion[g_Player.nMotionType].nKey[g_nCounterKeySet].rot[nCntParts] +
				g_Motion.Offset[nCntParts].rot - g_Player.aPlayerModel[nCntParts].rot;

			// 差分をフレーム数で割る
			/* １フレームあたりの差分 = (各パーツの位置[x]の差分 / [次]のキーセットのフレーム数,
			各パーツの位置[y]の差分 / [次]のキーセットのフレーム数,
			各パーツの位置[z]の差分 / [次]のキーセットのフレーム数)*/
			g_posDiff[nCntParts] = D3DXVECTOR3(g_posDiff[nCntParts].x / g_nMotionBlendFrame,
				g_posDiff[nCntParts].y / g_nMotionBlendFrame,
				g_posDiff[nCntParts].z / g_nMotionBlendFrame);

			g_RotDiff[nCntParts] = D3DXVECTOR3(g_RotDiff[nCntParts].x / g_nMotionBlendFrame,
				g_RotDiff[nCntParts].y / g_nMotionBlendFrame,
				g_RotDiff[nCntParts].z / g_nMotionBlendFrame);
		}
	}

	// モーション更新
	for (int nCntParts = 0; nCntParts < MAX_PLAYER; nCntParts++)
	{
		g_Player.aPlayerModel[nCntParts].pos += g_posDiff[nCntParts];
		g_Player.aPlayerModel[nCntParts].rot += g_RotDiff[nCntParts];

		if (g_Player.aPlayerModel[nCntParts].rot.x > D3DX_PI)
		{
			g_Player.aPlayerModel[nCntParts].rot.x -= D3DX_PI * 2;
		}
		else if (g_Player.aPlayerModel[nCntParts].rot.x < -D3DX_PI)
		{
			g_Player.aPlayerModel[nCntParts].rot.x += D3DX_PI * 2;
		}
		if (g_Player.aPlayerModel[nCntParts].rot.y > D3DX_PI)
		{
			g_Player.aPlayerModel[nCntParts].rot.y -= D3DX_PI * 2;
		}
		else if (g_Player.aPlayerModel[nCntParts].rot.y < -D3DX_PI)
		{
			g_Player.aPlayerModel[nCntParts].rot.y += D3DX_PI * 2;
		}
		if (g_Player.aPlayerModel[nCntParts].rot.y > D3DX_PI)
		{
			g_Player.aPlayerModel[nCntParts].rot.z -= D3DX_PI * 2;
		}
		else if (g_Player.aPlayerModel[nCntParts].rot.z < -D3DX_PI)
		{
			g_Player.aPlayerModel[nCntParts].rot.z += D3DX_PI * 2;
		}
	}
	// フレーム数の加算
	g_nCounterFrame++;

	if (g_Player.nNowFrame < g_Player.nFrameALL)
	{
		// 現在のフレーム数を加算
		g_Player.nNowFrame++;
	}
}

//===============================================================================
// モーションのフレーム数の計算
//===============================================================================
void CulFrame(void)
{
	// 現在のフレーム数をリセット
	g_Player.nNowFrame = 0;

	// モーションの総フレーム数をリセット
	g_Player.nFrameALL = 0;

	// モーションの総フレーム数を計算
	for (int nCntKey = 0; nCntKey < g_Motion.Motion[g_Player.nMotionType].nNumKey; nCntKey++)
	{
		g_Player.nFrameALL += g_Motion.Motion[g_Player.nMotionType].nKey[nCntKey].nframe;
	}
}

//===============================================================================
// プレイヤーの読み込み
//===============================================================================
void LoadPlayer(void)
{
	//読み込んだモデルの情報の初期化
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		for (int nText = 0; nText < MAX_CHAR; nText++)
		{
			g_LoadPlayer[nCntPlayer].pXFileName[nText] = NULL;		//ファイル名
		}
		g_LoadPlayer[nCntPlayer].pMesh = NULL;						//メッシュ情報へのポインタ
		g_LoadPlayer[nCntPlayer].pBuffMat = NULL;					//マテリアル情報へのポインタ
		g_LoadPlayer[nCntPlayer].NumMat = 0;						//マテリアルの数
		g_LoadPlayer[nCntPlayer].pTexture = NULL;					//テクスチャへのポインタ
	}

	for (int nCntModel = 0; nCntModel < MAX_PLAYER; nCntModel++)
	{// モデルの最大数
		g_Motion.Offset[nCntModel].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// オフセット[位置]
		g_Motion.Offset[nCntModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// オフセット[向き]
	}

	for (int nCntMotion = 0; nCntMotion < MOTION_MAX; nCntMotion++)
	{// モーションの種類
		g_Motion.Motion[nCntMotion].nLoop;				// ループ情報 [0 : ループしない, 1 : ループする]
		g_Motion.Motion[nCntMotion].nNumKey = 0;		// キー数

		// キー情報
		for (int nNumKeySet = 0; nNumKeySet < MAX_KEYSET; nNumKeySet++)
		{// キーセットの最大数
			g_Motion.Motion[nCntMotion].nKey[nNumKeySet].nframe = 0;				// フレーム数
			for (int nCntModel = 0; nCntModel < MAX_PLAYER; nCntModel++)
			{// モデルの最大数
				g_Motion.Motion[nCntMotion].nKey[nNumKeySet].pos[nCntModel] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
				g_Motion.Motion[nCntMotion].nKey[nNumKeySet].rot[nCntModel] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 向き
			}
		}
	}

	//#if 1
	// ローカル変数宣言
	FILE *pFile;				// ファイルのポインタ
	char ReadText[256];			// 読み込んだ文字列を入れておく
	char HeadText[256];			// 比較用
	char DustBox[256];			// 使用しないものを入れておく
	int nCntText = 0;			// モデルファイル名
	int nCntModel = 0;			// モデル数
	int nCntMotion = 0;			// モーション数
	int nCntKeySet = 0;			// キーセット数

	// ファイルオープン
	pFile = fopen(PLAYER_FILE, "r");		// ファイルを開く[読み込み型]

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
				 //int nCnt = 0;
				}
				if (strcmp(HeadText, "NUM_MODEL") == 0)
				{// 読み込むモデルの最大数
					sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &g_Player.nLoadParts);
				}
				else if (strcmp(HeadText, "MODEL_FILENAME") == 0)
				{// モデルファイル名
					if (g_Player.nLoadParts > nCntText)
					{// 最大数以上処理しない
						sscanf(ReadText, "%s %c %s", &DustBox, &DustBox, &g_LoadPlayer[nCntText].pXFileName[0]);
						nCntText++;
					}
				}
				else if (strcmp(HeadText, "CHARACTERSET") == 0)
				{//--- キャラクター情報 ---//
					while (strcmp(HeadText, "END_CHARACTERSET") != 0)
					{// "END_CHARACTERSET" が読み取れるまで繰り返し文字列を読み取る
						fgets(ReadText, sizeof(ReadText), pFile);
						sscanf(ReadText, "%s", &HeadText);

						if (strcmp(HeadText, "\n") == 0)
						{// 文字列の先頭が [\n](改行) の場合処理しない
							int nCnt = 0;
						}

						else if (strcmp(HeadText, "MOVE") == 0)
						{// 移動量
							sscanf(ReadText, "%s %c %f", &DustBox, &DustBox, &g_Player.fMoveSpeed);
						}
						else if (strcmp(HeadText, "pos") == 0)
						{// 場所
							sscanf(ReadText, "%s %c %f %f %f", &DustBox, &DustBox, &g_Player.pos.x, &g_Player.pos.y, &g_Player.pos.z);
						}
						else if (strcmp(HeadText, "RADIUS") == 0)
						{// 半径
							sscanf(ReadText, "%s %c %f", &DustBox, &DustBox, &g_Player.fRadius);
						}
						else if (strcmp(HeadText, "HEIGHT") == 0)
						{// 高さ
							sscanf(ReadText, "%s %c %f", &DustBox, &DustBox, &g_Player.fHeight);
						}
						else if (strcmp(HeadText, "NUM_PARTS") == 0)
						{// プレイヤー１体に対するモデルの使用数
							sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &g_Player.nMaxParts);
						}

						g_Player.nMaxParts = 10;

						// モデルの配置情報
						if (strcmp(HeadText, "PARTSSET") == 0)
						{
							if (g_Player.nMaxParts > nCntModel)
							{
								while (strcmp(HeadText, "END_PARTSSET") != 0)
								{// "END_PARTSSET" が読み取れるまで繰り返し文字列を読み取る
									fgets(ReadText, sizeof(ReadText), pFile);
									sscanf(ReadText, "%s", &HeadText);

									if (strcmp(HeadText, "INDEX") == 0)
									{// 部位
										sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &g_Player.aPlayerModel[nCntModel].nType);
									}
									else if (strcmp(HeadText, "PARENT") == 0)
									{// 親のインデックス
										sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &g_Player.aPlayerModel[nCntModel].nIdxModelParent);
									}
									else if (strcmp(HeadText, "pos") == 0)
									{// 位置
										sscanf(ReadText, "%s %c %f %f %f", &DustBox, &DustBox,
											&g_Player.aPlayerModel[nCntModel].pos.x,
											&g_Player.aPlayerModel[nCntModel].pos.y,
											&g_Player.aPlayerModel[nCntModel].pos.z);

										sscanf(ReadText, "%s %c %f %f %f", &DustBox, &DustBox,
											&g_Motion.Offset[nCntModel].pos.x,
											&g_Motion.Offset[nCntModel].pos.y,
											&g_Motion.Offset[nCntModel].pos.z);
									}
									else if (strcmp(HeadText, "ROT") == 0)
									{// 向き
										sscanf(ReadText, "%s %c %f %f %f", &DustBox, &DustBox,
											&g_Player.aPlayerModel[nCntModel].rot.x,
											&g_Player.aPlayerModel[nCntModel].rot.y,
											&g_Player.aPlayerModel[nCntModel].rot.z);
									}
								}
								nCntModel++;		// モデル数を進める
							}
						}
					}
				}

				// モーション情報
				else if (strcmp(HeadText, "MOTIONSET") == 0)
				{
					nCntModel = 0;		// モデル数のリセット

					while (strcmp(HeadText, "END_MOTIONSET") != 0)
					{// "END_MOTIONSET" が読み取れるまで繰り返し文字列を読み取る
						fgets(ReadText, sizeof(ReadText), pFile);
						sscanf(ReadText, "%s", &HeadText);

						if (strcmp(HeadText, "LOOP") == 0)
						{// ループ情報
							sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &g_Motion.Motion[nCntMotion].nLoop);
						}
						else if (strcmp(HeadText, "NUM_KEY") == 0)
						{// キー数
							sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &g_Motion.Motion[nCntMotion].nNumKey);
						}
						else if (strcmp(HeadText, "KEYSET") == 0)
						{// キーセット
							while (strcmp(HeadText, "END_KEYSET") != 0)
							{// "END_KEYSET" が読み取れるまで繰り返し文字列を読み取る
								fgets(ReadText, sizeof(ReadText), pFile);
								sscanf(ReadText, "%s", &HeadText);

								if (strcmp(HeadText, "FRAME") == 0)
								{// フレーム数
									sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &g_Motion.Motion[nCntMotion].nKey[nCntKeySet].nframe);
								}
								else if (strcmp(HeadText, "KEY") == 0)
								{// キー
									while (strcmp(HeadText, "END_KEY") != 0)
									{// "END_KEY" が読み取れるまで繰り返し文字列を読み取る
										fgets(ReadText, sizeof(ReadText), pFile);
										sscanf(ReadText, "%s", &HeadText);

										if (strcmp(HeadText, "pos") == 0)
										{// 位置
											sscanf(ReadText, "%s %c %f %f %f", &DustBox, &DustBox,
												&g_Motion.Motion[nCntMotion].nKey[nCntKeySet].pos[nCntModel].x,
												&g_Motion.Motion[nCntMotion].nKey[nCntKeySet].pos[nCntModel].y,
												&g_Motion.Motion[nCntMotion].nKey[nCntKeySet].pos[nCntModel].z);
										}
										else if (strcmp(HeadText, "ROT") == 0)
										{// 向き
											sscanf(ReadText, "%s %c %f %f %f", &DustBox, &DustBox,
												&g_Motion.Motion[nCntMotion].nKey[nCntKeySet].rot[nCntModel].x,
												&g_Motion.Motion[nCntMotion].nKey[nCntKeySet].rot[nCntModel].y,
												&g_Motion.Motion[nCntMotion].nKey[nCntKeySet].rot[nCntModel].z);
										}
									}
									nCntModel++;		// モデル数を進める
								}
							}
							nCntKeySet++;		// キーセット数を進める
							nCntModel = 0;		// モデル数のリセット
						}
					}
					nCntMotion++;			// モーションの種類を進める
					nCntKeySet = 0;			// キーセット数のリセット
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
// プレイヤーの破棄
//===============================================================================
void UpdateTitlePlayer(void)
{
	// カメラの取得
	CAMERA *pCamera = GetCamera();

	// 前回の位置を記憶
	g_Player.posOld = g_Player.pos;

	// 前回のモーションを記憶
	g_Player.nMotionTypeOld = g_Player.nMotionType;

	// 待機
	if (!g_Player.bWalk)
	{
		g_Player.nMotionType = MOTION_NEUTRAL;
	}

	 //モーション
#if PLAY_MOTION
	PlayerMotion();
#endif
}

//===============================================================================
// プレイヤーの取得
//===============================================================================
PLAYER * GetPlayer(void)
{
	return & g_Player;
}