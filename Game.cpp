//====================================================================================================
//
// ���C�� (Game.cpp)
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
// �}�N����`
//==================================================================================================== 

//=====================================================================================================
// �O���[�o���ϐ�
//=====================================================================================================
GAMESTATE g_gamestate = GAMESTATE_NONE;
int g_nCounterGameState = 0;

//================================================================================================
// �w�i�̏�����
//=================================================================================================
void InitGame(void)
{
	//�J�����̏���������
	InitCamera();

	// ���C�g�̏���������
	InitLight();

	//�e�̏���������
	InitShadow();

	//���f���̏���������
	InitModel();

	//�v���C���[�̏���������
	InitPlayer();

	//�t�B�[���h�̏���������
	InitMeshField();

	//�ǂ̏���������
	InitMeshWall();

	//�G�t�F�N�g�̏���������
	InitEffect();

	//���Ԃ̏���������
	InitTime();

	//��������
	AddTime(300);

	//���̂̏�����
	InitIce();

	//�Q�[���e�L�X�g�̏�����
	InitGameText();

	SetGameText(D3DXVECTOR3(1100.0f, 65.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 120, 100, 5);

	//�c�@�̏�����
	InitZanki();

	//�c�@�ݒ�
	AddZanki(3);

	//�X�e�[�W�P�̕ǂ̐���
	SetMeshWall(D3DXVECTOR3(1700.0f, 45.0f, 0.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-1700.0f, 45.0f, 0.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetMeshWall(D3DXVECTOR3(0.0f, 45.0f, -1700.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetMeshWall(D3DXVECTOR3(0.0f, 45.0f, 1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//�X�e�[�W2�̕ǂ̐���
	SetMeshWall(D3DXVECTOR3(5000.0f, 45.0f, 0.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetMeshWall(D3DXVECTOR3(2000.0f, 45.0f, 0.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetMeshWall(D3DXVECTOR3(3500.0f, 45.0f, -1700.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetMeshWall(D3DXVECTOR3(3500.0f, 45.0f, 1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//�X�e�[�W3�̕ǂ̐���
	SetMeshWall(D3DXVECTOR3(-1800.0f, 45.0f, 0.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-4800.0f, 45.0f, 0.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-3000.0f, 45.0f, -1700.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-3000.0f, 45.0f, 1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	g_gamestate = GAMESTATE_NORMAL;
	g_nCounterGameState = 0;

	return;
}

//================================================================================================
// �w�i�̊J������
//=================================================================================================
void UninitGame(void)
{
	//�J�����̏I������
	UninitCamera();

	//���C�g�̏I������
	UninitLight();

	//�e�̏I������
	UninitShadow();

	//���f���̏I������
	UninitModel();

	//�v���C���[�̏I������
	UninitPlayer();

	//�t�B�[���h�̏I������
	UninitMeshField();

	//�ǂ̏I������
	UninitMeshWall();

	//�����̏I������
	UninitEffect();

	//���Ԃ̏I������
	UninitTime();

	//���̂̏I������
	UninitIce();

	//�Q�[���e�L�X�g�̏I������
	UninitGameText();

	//�c�@�̏I������
	UninitZanki();

}

//================================================================================================
// �w�i�̍X�V����
//=================================================================================================
void UpdateGame(void)
{
	//�v���C���[�̎擾
	PLAYER *pPlayer;
	pPlayer = GetPlayer();

	switch (g_gamestate)
	{
	case 	GAMESTATE_NORMAL:

		//�J�����̍X�V����
		UpdateCamera();

		//���C�g�̍X�V����
		UpdateLight();

		//�e�̍X�V����
		UpdateShadow();

		//���f���̍X�V����
		UpdateModel();

		//�v���C���[�̍X�V����
		UpdatePlayer();

		//���̂̍X�V����
		UpdateIce();

		//�t�B�[���h�̍X�V����
		UpdateMeshField();

		//�ǂ̍X�V����
		UpdateMeshWall();

		//�G�t�F�N�g�̍X�V����
		UpdateEffect();

		//���Ԃ̍X�V����
		UpdateTime();

		//�Q�[���e�L�X�g�̍X�V����
		UpdateGameText();

		//�c�@�̍X�V����
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
// �w�i�̕`�揈��
//=================================================================================================
void DrawGame(void)
{
	//�J�����̐ݒ�
	SetCamera();

	//�t�B�[���h�̕`�揈��
	DrawMeshField();

	//�ǂ̕`�揈��
	DrawMeshWall();

	//���f���̕`�揈��
	DrawModel();

	//�v���C���[�̕`�揈��
	DrawPlayer();

	//�G�t�F�N�g�̕`�揈��
	DrawEffect();

	//���̂̕`�揈��
	DrawIce();

	//�^�C���̕`�揈��
	DrawTime();

	//�Q�[���e�L�X�g�̕`�揈��
	DrawGameText();

	//�c�@�̕`�揈��
	DrawZanki();

	//�e�̕`�揈��
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