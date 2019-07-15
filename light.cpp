//=============================================================================
//
// ライト処理 [light.cpp]
// Author : 
//
//=============================================================================
#include "light.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_LIGHT	(3)

//=============================================================================
// グローバル変数
//=============================================================================
D3DLIGHT9 g_Light[MAX_LIGHT];

//=============================================================================
// ライトの初期化処理
//=============================================================================
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXVECTOR3 vecDir;
	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		// ライトをクリアする
		ZeroMemory(&g_Light[nCntLight], sizeof(D3DLIGHT9));

		// ライトの種類を設定
		g_Light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;
		
		// ライトの拡散光を設定
		g_Light[nCntLight].Diffuse = D3DXCOLOR(1.0f - nCntLight * 0.3f, 1.0f - nCntLight * 0.3f, 1.0f - nCntLight * 0.3f, 1.0f);

	}

		// 1つ目のライトの方向の設定
		vecDir = D3DXVECTOR3(0.20f, -0.80f, 0.40f);
		D3DXVec3Normalize(&vecDir, &vecDir);
		g_Light[0].Direction = vecDir;

		// 2つ目のライトの方向の設定
		vecDir = D3DXVECTOR3(-0.20f, 0.80f, -0.40f);
		D3DXVec3Normalize(&vecDir, &vecDir);
		g_Light[1].Direction = vecDir;

		// 3つ目のライトの方向の設定
		vecDir = D3DXVECTOR3(0.90f, -0.10f, 0.40f);
		D3DXVec3Normalize(&vecDir, &vecDir);
		g_Light[2].Direction = vecDir;

		for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
		{
			// ライトを設定する
			pDevice->SetLight(nCntLight, &g_Light[nCntLight]);

			// ライトを有効にする
			pDevice->LightEnable(nCntLight, TRUE);
		}
}

//=============================================================================
// ライトの終了処理
//=============================================================================
void UninitLight(void)
{
}

//=============================================================================
// ライトの更新処理
//=============================================================================
void UpdateLight(void)
{
}

