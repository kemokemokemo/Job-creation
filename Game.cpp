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

	//�e�̏���������
	InitBullet();

	//�t�B�[���h�̏���������
	InitMeshField();

	//�ǂ̏���������
	InitMeshWall();

	//�����̏���������
	InitExplosion();

	//�G�t�F�N�g�̏���������
	InitEffect();

	//���Ԃ̏���������
	InitTime();

	//��������
	AddTime(300);

	//�|�[�Y�̏�����
	InitPause();

	//���̂̏�����
	InitIce();

	//�Q�[���e�L�X�g�̏�����
	InitGameText();

	SetGameText(D3DXVECTOR3(1100.0f, 65.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 120, 100, 5);

	//�c�@�̏�����
	InitZanki();

	//�c�@�ݒ�
	AddZanki(3);

	//���f���̏���������
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

	//�o���b�g�̏I������
	UninitBullet();

	//�t�B�[���h�̏I������
	UninitMeshField();

	//�ǂ̏I������
	UninitMeshWall();

	//�����̏I������
	UninitExplosion();

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

	//�|�[�Y�̏I������
	UninitPause();

	// �G�I������
	//UninitEnemy();

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

		//�o���b�g�̍X�V����
		UpdateBullet();

		//�t�B�[���h�̍X�V����
		UpdateMeshField();

		//�ǂ̍X�V����
		UpdateMeshWall();

		//�����̍X�V����
		UpdateExplosion();

		//�G�t�F�N�g�̍X�V����
		UpdateEffect();

		//���Ԃ̍X�V����
		UpdateTime();

		//�Q�[���e�L�X�g�̍X�V����
		UpdateGameText();

		//�c�@�̍X�V����
		UpdateZanki();

		//�|�[�Y�̍X�V����
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

	//�o���b�g�̕`�揈��
	DrawBullet();

	//�����̕`�揈��
	DrawExplosion();

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

	//�|�[�Y�̕`�揈��
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