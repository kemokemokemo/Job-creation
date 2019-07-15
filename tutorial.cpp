//====================================================================================================
//
// �w�i���� (Tutorial.cpp)
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
// �}�N����`
//==================================================================================================== 
#define TUTORIAL_TEX "DATA/TEX/tutorial.jpg"//�ǂݍ��ރe�N�X�`���t�@�C����
#define TUTORIAL_POS_X	(0)			    //�|���S���̕\���ʒu(����X)
#define TUTORIAL_POS_Y	(0)			    //�|���S���̕\���ʒu(����Y)
#define TUTORIAL_SIZE_X	(1280)			//�|���S���̃T�C�Y(����)
#define TUTORIAL_SIZE_Y	(720)			//�|���S���̃T�C�Y(����)
#define TUTORIALCOLOR_TEX (255)

//=====================================================================================================
// �O���[�o���ϐ�
//=====================================================================================================
VERTEX_2D g_pVertexTutorial[4];
LPDIRECT3DTEXTURE9 g_pTextureTutorial = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;
float postuto;
int g_cCount;

//================================================================================================
// �w�i�̏�����
//=================================================================================================
void InitTutorial(void)
{
	// �J�����̏���������
	InitCamera();

	// ���C�g�̏���������
	InitLight();

	//�e�̏���������
	InitShadow();

	//���f���̏���������
	InitTutoModel();

	//�v���C���[�̏���������
	InitPlayer();

	//�X�̏���������
	InitIce();

	//�t�B�[���h�̏���������
	InitMeshField();

	//�ǂ̏���������
	InitMeshWall();
	SetMeshWall(D3DXVECTOR3(1700.0f, 45.0f, 0.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-1700.0f, 45.0f, 0.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetMeshWall(D3DXVECTOR3(0.0f, 45.0f, -1700.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetMeshWall(D3DXVECTOR3(0.0f, 45.0f, 1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//�G�t�F�N�g�̏���������
	InitEffect();

	//�e�L�X�g�̏���������
	InitGameText();
	SetGameText(D3DXVECTOR3(1000.0f, 600.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 210, 180, 4);
}

//================================================================================================
// �w�i�̊J������
//=================================================================================================
void UninitTutorial(void)
{
	// �J�����̏I������
	UninitCamera();

	// ���C�g�̏I������
	UninitLight();

	//�e�̏I������
	UninitShadow();

	//���f���̏I������
	UninitTutoModel();

	//�v���C���[�̏I������
	UninitPlayer();

	//�X�̏I������
	UninitIce();

	//�t�B�[���h�̏I������
	UninitMeshField();

	//�ǂ̏I������
	UninitMeshWall();

	//�G�t�F�N�g�̏I������
	UninitEffect();

	//�e�L�X�g�̏I������
	UninitGameText();
}

//================================================================================================
// �w�i�̍X�V����
//=================================================================================================
void UpdateTutorial(void)
{
	//���[�h�̐؂�ւ�
	if (GetFade() == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_SPACE) || GetJoypadTrigger(0, JOYPADKEY_START))
		{
			PlaySound(SOUND_LABEL_SE_ENTER);
			SetFade(MODE_GAME);
		}
	}

	// �J�����̍X�V����
	UpdateCamera();

	// ���C�g�̍X�V����
	UpdateLight();

	//�e�̍X�V����
	UpdateShadow();

	//���f���̍X�V����
	UpdateTutoModel();

	//�v���C���[�̍X�V����
	UpdatePlayer();

	//�X�̍X�V����
	UpdateIce();

	//�t�B�[���h�̍X�V����
	UpdateMeshField();

	//�ǂ̍X�V����
	UpdateMeshWall();

	//�G�t�F�N�g�̍X�V����
	UpdateEffect();

	//�e�L�X�g�̍X�V����
	UpdateGameText();

}

//================================================================================================
// �w�i�̕`�揈��
//=================================================================================================
void DrawTutorial(void)
{

	//�J�����̐ݒ�
	SetCamera();

	//�t�B�[���h�̕`�揈��
	DrawMeshField();

	//�ǂ̕`�揈��
	DrawMeshWall();

	//�G�t�F�N�g�̕`�揈��
	DrawEffect();

	//���f���̕`�揈��
	DrawTutoModel();

	//�v���C���[�̕`�揈��
	DrawPlayer();

	//�X�̕`�揈��
	DrawIce();

	//�e�̕`�揈��
	DrawShadow();

	//�e�L�X�g�̕`�揈��
	DrawGameText();
}

