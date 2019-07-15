//====================================================================================================
//
// �w�i���� (Gameover.cpp)
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
// �}�N����`
//==================================================================================================== 
#define GAMEOVER_TEX "DATA/TEX/GAMEOVER.jpg"//�ǂݍ��ރe�N�X�`���t�@�C����
#define GAMEOVER_POS_X	(0)			    //�|���S���̕\���ʒu(����X)
#define GAMEOVER_POS_Y	(0)			    //�|���S���̕\���ʒu(����Y)
#define GAMEOVER_SIZE_X	(1280)			//�|���S���̃T�C�Y(����)
#define GAMEOVER_SIZE_Y	(720)			//�|���S���̃T�C�Y(����)
#define GAMEOVERCOLOR_TEX (255)

//=====================================================================================================
// �O���[�o���ϐ�
//=====================================================================================================
VERTEX_3D g_pVertexGameover[4];
LPDIRECT3DTEXTURE9 g_pTextureGameover = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGameover = NULL;


//================================================================================================
// �w�i�̏�����
//=================================================================================================
void InitGameover(void)
{
	//	�f�o�C�X���擾����
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	InitLight();
	InitCamera();
	InitMeshField();
	InitGameText();
	InitMeshWall();

	//�e�L�X�g�̐ݒ�
	SetGameText(D3DXVECTOR3(670.0f, 250.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 280, 180, 1);
	SetGameText(D3DXVECTOR3(1000.0f, 600.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 210, 180, 3);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		GAMEOVER_TEX,
		&g_pTextureGameover);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGameover,
		NULL);

	VERTEX_3D *pVtx;

	g_pVtxBuffGameover->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�(�E���Őݒ肷��j
	pVtx[0].Pos = D3DXVECTOR3(GAMEOVER_POS_X, GAMEOVER_POS_Y, 0.0f);
	pVtx[1].Pos = D3DXVECTOR3(GAMEOVER_POS_X + GAMEOVER_SIZE_X, GAMEOVER_POS_Y, 0.0f);
	pVtx[2].Pos = D3DXVECTOR3(GAMEOVER_POS_X, GAMEOVER_POS_Y + GAMEOVER_SIZE_Y, 0.0f);
	pVtx[3].Pos = D3DXVECTOR3(GAMEOVER_POS_X + GAMEOVER_SIZE_X, GAMEOVER_POS_Y + GAMEOVER_SIZE_Y, 0.0f);

	//���_�x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[�̐ݒ�(0�`255�̒l�Őݒ�j
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
// �w�i�̊J������
//=================================================================================================
void UninitGameover(void)
{

	UninitLight();
	UninitCamera();
	UninitMeshField();
	UninitGameText();
	UninitMeshWall();

	//�e�N�X�`���̊֐�
	if (g_pTextureGameover != NULL)
	{
		g_pTextureGameover->Release();
		g_pTextureGameover = NULL;
	}
	if (g_pVtxBuffGameover != NULL)
		//���_�o�b�t�@�̊J��
	{
		g_pVtxBuffGameover->Release();
		g_pVtxBuffGameover = NULL;
	}
}

//================================================================================================
// �w�i�̍X�V����
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
// �w�i�̕`�揈��
//=================================================================================================
void DrawGameover(void)
{

	SetCamera();
	DrawMeshField();
	DrawMeshWall();
	DrawGameText();

	//	�f�o�C�X���擾����
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�f�[�^�̃f�o�C�X�Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffGameover, 0, sizeof(VERTEX_3D));

	pDevice->SetFVF(FVF_VERTEX_3D);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetTexture(0, g_pTextureGameover);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}