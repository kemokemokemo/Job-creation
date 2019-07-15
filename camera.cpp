//=============================================================================
//
// �J�������� [camera.cpp]
// Author : �ؑ�����
//
//=============================================================================
#include "camera.h"
#include "input.h"
#include "player.h"
#include "Controlar.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define CSPEED		(1.0f)
#define CROT		(0.005f)
#define CFollow		(0.6f)

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
CAMERA g_Camera;
float fDistance;

//=============================================================================
// �J�����̏���������
//=============================================================================
void InitCamera(void)
{

	g_Camera.posV = D3DXVECTOR3(0.0f, 150.0f, -250.0f);
	g_Camera.posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.rot  = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_Camera.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ����
	D3DXVECTOR3 fDiffpos = g_Camera.posV- g_Camera.posR;

	// ����
	fDistance = sqrtf(fDiffpos.y * fDiffpos.y + fDiffpos.z* fDiffpos.z);
}
//=============================================================================
// �J�����̏I������
//=============================================================================
void UninitCamera(void)
{

}

//=============================================================================
// �J�����̍X�V����
//=============================================================================
void UpdateCamera(void)
{
	//�ϐ��錾
	PLAYER *pPlayer = GetPlayer();
	int nStickH, nStickV;

	//��ʂ̉�]
	if (GetMode()==MODE_TITLE || GetMode() == MODE_GAMEOVER || GetMode() == MODE_RANKING || GetMode() == MODE_RESULT)
	{
		g_Camera.rot.y -= CROT;
	}


	if (!pPlayer->bDeth && GetMode() == MODE_GAME || GetMode() == MODE_TUTORIAL)
	{
		//***
		//*joypad�̃J�����̉�]
		//***

		// �A�i���O�X�e�B�b�N���̎擾
		GetJoypadStickRight(0, &nStickH, &nStickV);

		if (nStickH != 0 || nStickV != 0)
		{
			g_Camera.rot.y += (float)atan2(nStickH, nStickV)*0.04f;
			g_Camera.posV.x = g_Camera.posR.x + sinf(D3DX_PI + g_Camera.rot.y) * fDistance;
			g_Camera.posV.z = g_Camera.posR.z + cosf(D3DX_PI + g_Camera.rot.y) * fDistance;
		}

		//***
		//*�L�[�{�[�h�̃J�����̉�]
		//***

		// ���]
		if (GetKeyboardPress(DIK_Q) || GetJoypadPress(0, JOYPADKEY_LEFT_SHOULDER))
		{
			g_Camera.rot.y -= 0.05f;
			g_Camera.posV.x = g_Camera.posR.x + sinf(D3DX_PI + g_Camera.rot.y) * fDistance;
			g_Camera.posV.z = g_Camera.posR.z + cosf(D3DX_PI + g_Camera.rot.y) * fDistance;
		}
		if (GetKeyboardPress(DIK_E) || GetJoypadPress(0, JOYPADKEY_RIGHT_SHOULDER))
		{
			g_Camera.rot.y += 0.05f;
			g_Camera.posV.x = g_Camera.posR.x + sinf(D3DX_PI + g_Camera.rot.y) * fDistance;
			g_Camera.posV.z = g_Camera.posR.z + cosf(D3DX_PI + g_Camera.rot.y) * fDistance;
		}

		//***
		//*�J�����̒Ǐ]����
		//***

		//�ړ�
		if (GetKeyboardPress(DIK_A))
		{
			if (GetKeyboardPress(DIK_S))
			{// ����
				g_Camera.posV.x += sinf(-D3DX_PI*0.75f + g_Camera.rot.y);
				g_Camera.posV.z += cosf(-D3DX_PI*0.75f + g_Camera.rot.y);
			}
			else if (GetKeyboardPress(DIK_W))
			{// ����
				g_Camera.posV.x += sinf(-D3DX_PI*0.25f + g_Camera.rot.y);
				g_Camera.posV.z += cosf(-D3DX_PI*0.25f + g_Camera.rot.y);
			}
			else
			{// ��
				g_Camera.posV.x += sinf(-D3DX_PI*0.5f + g_Camera.rot.y);
				g_Camera.posV.z += cosf(-D3DX_PI*0.5f + g_Camera.rot.y);
			}
		}

		else if (GetKeyboardPress(DIK_D))
		{
			if (GetKeyboardPress(DIK_S))
			{// �E��
				g_Camera.posV.x += sinf(D3DX_PI*0.75f + g_Camera.rot.y);
				g_Camera.posV.z += cosf(D3DX_PI*0.75f + g_Camera.rot.y);
			}
			else if (GetKeyboardPress(DIK_W))
			{// �E�� 
				g_Camera.posV.x += sinf(D3DX_PI*0.25f + g_Camera.rot.y);
				g_Camera.posV.z += cosf(D3DX_PI*0.25f + g_Camera.rot.y);
			}
			else
			{// �E
				g_Camera.posV.x += sinf(D3DX_PI*0.5f + g_Camera.rot.y);
				g_Camera.posV.z += cosf(D3DX_PI*0.5f + g_Camera.rot.y);
			}
		}
		else if (GetKeyboardPress(DIK_S))
		{
			g_Camera.posV.x += sinf(D3DX_PI + g_Camera.rot.y);
			g_Camera.posV.z += cosf(D3DX_PI + g_Camera.rot.y);
		}
		else if (GetKeyboardPress(DIK_W))
		{
			g_Camera.posV.x += sinf(0.0f + g_Camera.rot.y);
			g_Camera.posV.z += cosf(0.0f + g_Camera.rot.y);
		}
	}

	//�^�C�g����ʂ̃J����
	if (GetMode() == MODE_TITLE)
	{
		g_Camera.posRDest.x = pPlayer->pos.x - sinf(pPlayer->rot.y) * CSPEED;
		g_Camera.posRDest.y = pPlayer->pos.y + 0.0f;
		g_Camera.posRDest.z = pPlayer->pos.z - cosf(pPlayer->rot.y) * CSPEED;

		g_Camera.posVDest.x = pPlayer->pos.x - sinf(g_Camera.rot.y) * fDistance;
		g_Camera.posVDest.y = pPlayer->pos.y + 100;
		g_Camera.posVDest.z = pPlayer->pos.z - cosf(g_Camera.rot.y) * fDistance;

		g_Camera.posV.x += (g_Camera.posVDest.x - g_Camera.posV.x) * CFollow;
		g_Camera.posV.y += (g_Camera.posVDest.y - g_Camera.posV.y) * CFollow;
		g_Camera.posV.z += (g_Camera.posVDest.z - g_Camera.posV.z) * CFollow;
		g_Camera.posR.x += (g_Camera.posRDest.x - g_Camera.posR.x) * CFollow;
		g_Camera.posR.y += (g_Camera.posRDest.y - g_Camera.posR.y) * CFollow;
		g_Camera.posR.z += (g_Camera.posRDest.z - g_Camera.posR.z) * CFollow;
	}

	if (!pPlayer->bDeth && GetMode() != MODE_TITLE)
	{
		g_Camera.posRDest.x = pPlayer->pos.x - sinf(pPlayer->rot.y) * CSPEED;
		g_Camera.posRDest.y = pPlayer->pos.y + 0.0f;
		g_Camera.posRDest.z = pPlayer->pos.z - cosf(pPlayer->rot.y) * CSPEED;

		g_Camera.posVDest.x = pPlayer->pos.x - sinf(g_Camera.rot.y) * fDistance;
		g_Camera.posVDest.y = pPlayer->pos.y + 100;
		g_Camera.posVDest.z = pPlayer->pos.z - cosf(g_Camera.rot.y) * fDistance;

		g_Camera.posV.x += (g_Camera.posVDest.x - g_Camera.posV.x) * CFollow;
		g_Camera.posV.y += (g_Camera.posVDest.y - g_Camera.posV.y) * CFollow;
		g_Camera.posV.z += (g_Camera.posVDest.z - g_Camera.posV.z) * CFollow;
		g_Camera.posR.x += (g_Camera.posRDest.x - g_Camera.posR.x) * CFollow;
		g_Camera.posR.y += (g_Camera.posRDest.y - g_Camera.posR.y) * CFollow;
		g_Camera.posR.z += (g_Camera.posRDest.z - g_Camera.posR.z) * CFollow;
	}
}

//=============================================================================
// �J�����̐ݒ菈��
//=============================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Camera.mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&g_Camera.mtxProjection,
		D3DXToRadian(45.0f),(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		5000.0f);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_Camera.mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Camera.mtxView);

	// �r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH(
		&g_Camera.mtxView,
		&g_Camera.posV,
		&g_Camera.posR,
		&g_Camera.vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_Camera.mtxView);
}
//=========================================================================
// �J�����̎擾
//=========================================================================
CAMERA * GetCamera(void)
{
	return &g_Camera;
}