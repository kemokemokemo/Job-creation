//====================================================================================================
//
// �w�i���� (Title.cpp)
// Author  Kimura Kouta
//
//====================================================================================================
#include "Title.h"//�C���N���[�h�t�@�C��
#include "input.h"
#include "fade.h"
#include "light.h"
#include "camera.h"
#include "meshField.h"
#include "GameText.h"
#include "model.h"
#include "meshFwall.h"
#include "player.h"
#include "Controlar.h"
#include "sound.h"
//====================================================================================================
// �}�N����`
//==================================================================================================== 

//=====================================================================================================
// �O���[�o���ϐ�
//=====================================================================================================

//================================================================================================
// �w�i�̏�����
//=================================================================================================
void InitTitle(void)
{

	InitLight();

	InitCamera();

	InitMeshField();

	InitGameText();

	InitModel();

	InitMeshWall();

	SetGameText(D3DXVECTOR3(670.0f, 250.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 510, 380, 0);

	SetGameText(D3DXVECTOR3(600.0f, 570.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 300, 280, 3);

	SetMeshWall(D3DXVECTOR3(600.0f, 45.0f, 0.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));

	SetMeshWall(D3DXVECTOR3(-600.0f, 45.0f, 0.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));

	SetMeshWall(D3DXVECTOR3(0.0f, 45.0f, -600.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));

	SetMeshWall(D3DXVECTOR3(0.0f, 45.0f, 600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}
//================================================================================================
// �w�i�̊J������
//=================================================================================================
void UninitTitle(void)
{
	UninitLight();

	UninitCamera();

	UninitMeshField();

	UninitGameText();

	UninitModel();

	UninitMeshWall();
}

//================================================================================================
// �w�i�̍X�V����
//=================================================================================================
void UpdateTitle(void)
{
	UpdateLight();

	UpdateCamera();

	UpdateMeshField();

	UpdateGameText();

	UpdateModel();

	UpdateMeshWall();

	if (GetKeyboardTrigger(DIK_RETURN) || GetJoypadTrigger(0, JOYPADKEY_START))
	{
		if (GetFade() == FADE_NONE)
		{
			PlaySound(SOUND_LABEL_SE_ENTER);
			SetFade(MODE_TUTORIAL);
		}
	}

	static int nCnt = 0;

	nCnt++;
	//if (GetFade() == FADE_NONE)
	//{
	//	if ( nCnt >= 300 && GetFade() == FADE_NONE)
	//	{
	//		SetFade(MODE_RANKING);
	//		nCnt = 0;
	//	}
	//}
}

//================================================================================================
// �w�i�̕`�揈��
//=================================================================================================
void DrawTitle(void)
{

	SetCamera();

	DrawMeshField();

	DrawModel();

	DrawMeshWall();

	DrawGameText();

}