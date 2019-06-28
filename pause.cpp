//----------------------------------------------------------------------------
//
// ポーズの処理	[pause.cpp]
// Author:	Kimura kouta
//
//----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// インクルードファイル
//------------------------------------------------------------------------------
#include "pause.h"		//インクルードファイル 
#include "input.h"
#include "fade.h"
#include "game.h"

//----------------------------------------------------------------------------
//マクロ定義
//----------------------------------------------------------------------------
#define MAX_PAUSE			(5)		//ポーズの種類
#define TEXTURE_NAME000	"DATA/TEX/pouse.jpg"
#define TEXTURE_NAME001	"DATA/TEX/P_GAME.png"
#define TEXTURE_NAME002	"DATA/TEX/P_RANKING.png"
#define TEXTURE_NAME003	"DATA/TEX/P_TITLE.png"
#define TEXTURE_NAME004	"DATA/TEX/P_Pause.png"

//----------------------------------------------------------------------------
//構造体定義
//----------------------------------------------------------------------------

typedef struct
{
	D3DXVECTOR3	pos;				//座標
	D3DXCOLOR	col;				//色
	int			nType;				//種類
	float		fWidth;				//ポーズのサイズ(x)
	float		fHeight;			//ポーズのサイズ(y)
	bool		bUse;				//使ってるかどうか
	bool		bDisp;				//画面にうつしてるかどうか

} PAUSE;

//====================================================================================================
//
// プロトタイプ宣言
//
//====================================================================================================

//====================================================================================================
// グローバル宣言
//====================================================================================================

LPDIRECT3DTEXTURE9		g_apTexturePause[MAX_PAUSE] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffPause = NULL;				//頂点バッファへのポインタ
PAUSE					g_aPause[MAX_PAUSE];				//ポーズ
int						g_nCursor;							//カーソル位置
bool					g_bPad;								//スティック情報

//============================================================================
// ポーズの初期化
//============================================================================
void InitPause(void)
{
	//変数宣言
	int nCntPause;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++)
	{
		g_aPause[nCntPause].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//座標
		g_aPause[nCntPause].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//色
		g_aPause[nCntPause].nType = 0;									//種類
		g_aPause[nCntPause].fWidth = 0;									//サイズ(X)
		g_aPause[nCntPause].fHeight = 0;								//サイズ(Y)
		g_aPause[nCntPause].bUse = false;								//使ってるかどうか
		g_aPause[nCntPause].bDisp = false;								//うつっているかどうか
	}

	//カーソル位置の初期化
	g_nCursor = 1;
	//スティックの初期化
	g_bPad = false;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME000,
		&g_apTexturePause[0]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME001,
		&g_apTexturePause[1]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME002,
		&g_apTexturePause[2]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME003,
		&g_apTexturePause[3]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME004,
		&g_apTexturePause[4]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_PAUSE,	//確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,			//頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;
	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++)
	{
		//頂点座標
		pVtx[0].pos = g_aPause[nCntPause].pos - D3DXVECTOR3((g_aPause[nCntPause].fWidth / 2.0f),
		(g_aPause[nCntPause].fHeight / 2.0f), 0.0f);
		pVtx[1].pos = g_aPause[nCntPause].pos - D3DXVECTOR3(-(g_aPause[nCntPause].fWidth / 2.0f),
		(g_aPause[nCntPause].fHeight / 2.0f), 0.0f);
		pVtx[2].pos = g_aPause[nCntPause].pos - D3DXVECTOR3((g_aPause[nCntPause].fWidth / 2.0f),
		-(g_aPause[nCntPause].fHeight / 2.0f), 0.0f);
		pVtx[3].pos = g_aPause[nCntPause].pos - D3DXVECTOR3(-(g_aPause[nCntPause].fWidth / 2.0f),
		-(g_aPause[nCntPause].fHeight / 2.0f), 0.0f);

		//頂点の同次座標
		pVtx[0].rhw = 1.0f;									//1.0fで固定
		pVtx[1].rhw = 1.0f;									//1.0fで固定
		pVtx[2].rhw = 1.0f;									//1.0fで固定
		pVtx[3].rhw = 1.0f;									//1.0fで固定
		//頂点の色
		pVtx[0].col = g_aPause[nCntPause].col;				//(赤,緑,青,透明度)
		pVtx[1].col = g_aPause[nCntPause].col;				//(赤,緑,青,透明度)
		pVtx[2].col = g_aPause[nCntPause].col;				//(赤,緑,青,透明度)
		pVtx[3].col = g_aPause[nCntPause].col;				//(赤,緑,青,透明度)
		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);				//(テクスチャのUV座標)
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);				//(テクスチャのUV座標)
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);				//(テクスチャのUV座標)
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);				//(テクスチャのUV座標)
		pVtx += 4;

	}

	//ポーズを設置
	//SetPause(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 1280, 720);
	//SetPause(D3DXVECTOR3(SCREEN_WIDTH / 2, 450.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1, 600, 200);
	//SetPause(D3DXVECTOR3(SCREEN_WIDTH / 2, 550.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2, 600, 200);
	//SetPause(D3DXVECTOR3(SCREEN_WIDTH / 2, 650.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 3, 600, 200);
	//SetPause(D3DXVECTOR3(SCREEN_WIDTH / 2, 200.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 4, 600, 200);

	//頂点データをアンロック
	g_pVtxBuffPause->Unlock();
}

//============================================================================
//
//ポーズの関数処理
//
//============================================================================
void UninitPause(void)
{
	int nCntPause;

	for (nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++)
	{
		//テクスチャの開放
		if (g_apTexturePause[nCntPause] != NULL)
		{
			g_apTexturePause[nCntPause]->Release();
			g_apTexturePause[nCntPause] = NULL;
		}
	}
	//頂点バッファの開放
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}
}
//----------------------------------------------------------------------------
//
//ポーズの更新処理
//
//----------------------------------------------------------------------------
void UpdatePause(void)
{
	//変数宣言
	int nCntPause;
	bool bSwitch = false;

	//変数宣言
//	int	joypadX, joypadY;

	//ジョイパッドの移動処理
	//GetJoypadStickLeft(0, &joypadX, &joypadY);

	/*if (joypadY == 0)
	{
		g_bPad = false;
	}*/

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//[D]キーを押した時
	if (GetKeyboardTrigger(DIK_W) || GetKeyboardTrigger(DIK_UP) /*|| GetJoypadTrigger(0, JOYPADKEY_UP) || (joypadY > 0 && g_bPad == false)*/)
	{
		g_nCursor--;		//カーソル動かす
		g_bPad = true;		//スティック情報をtrueに
		//PlaySound(SOUND_LABEL_SE_SHOT);
	}
	//[D]キーを押した
	else if (GetKeyboardTrigger(DIK_S) || GetKeyboardTrigger(DIK_DOWN) /*|| GetJoypadTrigger(0, JOYPADKEY_DOWN) || (joypadY < 0 && g_bPad == false)*/)
	{
		g_nCursor++;		//カーソル動かす
		g_bPad = true;		//スティック情報をtrueに
		//PlaySound(SOUND_LABEL_SE_SHOT);
	}
	//カーソルが3こえたら1にする
	if (g_nCursor > 3)
	{
		g_nCursor = 1;
	}
	//カーソルが1こえたら3にする
	else if (g_nCursor < 1)
	{
		g_nCursor = 3;
	}

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

		for (nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++)
		{
			if (bSwitch == true)
			{
				//カーソル合ってるやつを目立たせる
				if (g_aPause[nCntPause].nType == g_nCursor)
				{
					g_aPause[nCntPause].col.a = 1.0f;
				}
				//それ以外のやつは少し透明にする
				else
				{
					g_aPause[nCntPause].col.a = 0.7f;
				}
				if (g_aPause[nCntPause].nType == 0)
				{
					g_aPause[nCntPause].col.a = 0.5f;
				}

				//頂点の色
				pVtx[0].col = g_aPause[nCntPause].col;	//(赤,緑,青,透明度)
				pVtx[1].col = g_aPause[nCntPause].col;	//(赤,緑,青,透明度)
				pVtx[2].col = g_aPause[nCntPause].col;	//(赤,緑,青,透明度)
				pVtx[3].col = g_aPause[nCntPause].col;	//(赤,緑,青,透明度)

				pVtx += 4;
			}
			else
			{
				g_aPause[nCntPause].col.a = 0.0f;
			}
		}

	//頂点データをアンロック
	g_pVtxBuffPause->Unlock();

	//[Enter]かジョイパッドのボタンを押した時
	if ((GetKeyboardTrigger(DIK_P) /*|| GetJoypadTrigger(0, JOYPADKEY_A) || GetJoypadTrigger(0, JOYPADKEY_B) || GetJoypadTrigger(0, JOYPADKEY_X) ||*/
		/*GetJoypadTrigger(0, JOYPADKEY_Y)*/) && GetFade() == FADE_NONE)
	{
		bSwitch = true;
		//カーソルの位置に応じて処理を変える
		switch (g_nCursor)
		{
		case 1:
			//ゲーム続行
			SetGameState(GAMESTATE_NORMAL);
			//PlaySound(SOUND_LABEL_SE_ENTER);
			break;

		case 2:
			//ゲームリセット
			SetFade(MODE_RANKING);
			//PlaySound(SOUND_LABEL_SE_ENTER);
			break;

		case 3:
			//タイトルに戻る
			SetFade(MODE_TITLE);
			//PlaySound(SOUND_LABEL_SE_EXPLOSION);
			break;
		}
	}
}

//----------------------------------------------------------------------------
//
//ポーズの描画処理
//
//----------------------------------------------------------------------------
void DrawPause(void)
{
	//変数宣言
	int nCntPause;
	LPDIRECT3DDEVICE9	pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);					// ライティング無効
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);			
	//pDevice->SetRenderState(D3DRS_ALPHAREF, 100);					// 基準値

	//pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);			// Z比較設定

	//頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++)
	{
		if (g_aPause[nCntPause].bDisp == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_apTexturePause[g_aPause[nCntPause].nType]);
			//ポリゴン描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
				nCntPause * 4,		//開始するインデックス(頂点)
				2);					//ポリゴンの枚数
		}
	}

	//pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);					// ライティング無効
	//pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);		
	//pDevice->SetRenderState(D3DRS_ALPHAREF, 0);						// 基準値

	//pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);			// Z比較設定
}

//------------------------------------------------------------------------------
// ポーズの設定
//------------------------------------------------------------------------------
void SetPause(D3DXVECTOR3 pos, D3DXCOLOR col, int nType, float fWidth, float fHeight)
{
	VERTEX_2D *pVtx;

	int nCntPause;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++)
	{
		if (g_aPause[nCntPause].bUse == false)
		{
			g_aPause[nCntPause].pos = pos;				//座標
			g_aPause[nCntPause].col = col;				//色
			g_aPause[nCntPause].nType = nType;			//種類
			g_aPause[nCntPause].fWidth = fWidth;		//サイズ(X)
			g_aPause[nCntPause].fHeight = fHeight;		//サイズ(Y)
			g_aPause[nCntPause].bUse = true;			//使ってるかどうか
			g_aPause[nCntPause].bDisp = true;			//うつっているかどうか

			//頂点座標
			pVtx[0].pos = g_aPause[nCntPause].pos - D3DXVECTOR3((g_aPause[nCntPause].fWidth / 2.0f),
				(g_aPause[nCntPause].fHeight / 2.0f), 0.0f);
			pVtx[1].pos = g_aPause[nCntPause].pos - D3DXVECTOR3(-(g_aPause[nCntPause].fWidth / 2.0f),
				(g_aPause[nCntPause].fHeight / 2.0f), 0.0f);
			pVtx[2].pos = g_aPause[nCntPause].pos - D3DXVECTOR3((g_aPause[nCntPause].fWidth / 2.0f),
				-(g_aPause[nCntPause].fHeight / 2.0f), 0.0f);
			pVtx[3].pos = g_aPause[nCntPause].pos - D3DXVECTOR3(-(g_aPause[nCntPause].fWidth / 2.0f),
				-(g_aPause[nCntPause].fHeight / 2.0f), 0.0f);

			//頂点の色
			pVtx[0].col = g_aPause[nCntPause].col;	//(赤,緑,青,透明度)
			pVtx[1].col = g_aPause[nCntPause].col;	//(赤,緑,青,透明度)
			pVtx[2].col = g_aPause[nCntPause].col;	//(赤,緑,青,透明度)
			pVtx[3].col = g_aPause[nCntPause].col;	//(赤,緑,青,透明度)
			break;
		}
		pVtx += 4;
	}

	// 頂点データをアンロックする
	g_pVtxBuffPause->Unlock();
}