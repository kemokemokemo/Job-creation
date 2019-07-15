//=============================================================================
//
// ���C�g���� [light.cpp]
// Author : 
//
//=============================================================================
#include "light.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_LIGHT	(3)

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
D3DLIGHT9 g_Light[MAX_LIGHT];

//=============================================================================
// ���C�g�̏���������
//=============================================================================
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXVECTOR3 vecDir;
	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		// ���C�g���N���A����
		ZeroMemory(&g_Light[nCntLight], sizeof(D3DLIGHT9));

		// ���C�g�̎�ނ�ݒ�
		g_Light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;
		
		// ���C�g�̊g�U����ݒ�
		g_Light[nCntLight].Diffuse = D3DXCOLOR(1.0f - nCntLight * 0.3f, 1.0f - nCntLight * 0.3f, 1.0f - nCntLight * 0.3f, 1.0f);

	}

		// 1�ڂ̃��C�g�̕����̐ݒ�
		vecDir = D3DXVECTOR3(0.20f, -0.80f, 0.40f);
		D3DXVec3Normalize(&vecDir, &vecDir);
		g_Light[0].Direction = vecDir;

		// 2�ڂ̃��C�g�̕����̐ݒ�
		vecDir = D3DXVECTOR3(-0.20f, 0.80f, -0.40f);
		D3DXVec3Normalize(&vecDir, &vecDir);
		g_Light[1].Direction = vecDir;

		// 3�ڂ̃��C�g�̕����̐ݒ�
		vecDir = D3DXVECTOR3(0.90f, -0.10f, 0.40f);
		D3DXVec3Normalize(&vecDir, &vecDir);
		g_Light[2].Direction = vecDir;

		for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
		{
			// ���C�g��ݒ肷��
			pDevice->SetLight(nCntLight, &g_Light[nCntLight]);

			// ���C�g��L���ɂ���
			pDevice->LightEnable(nCntLight, TRUE);
		}
}

//=============================================================================
// ���C�g�̏I������
//=============================================================================
void UninitLight(void)
{
}

//=============================================================================
// ���C�g�̍X�V����
//=============================================================================
void UpdateLight(void)
{
}

