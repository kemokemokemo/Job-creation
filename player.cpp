//=============================================================================
//
// �v���C���[���� [player.cpp]
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
// �}�N����`
//=============================================================================
#define PLAYER_FILE					"DATA/road/player.txt"			// �t�@�C����
#define PLAY_MOTION					(true)							// ���[�V���� [On,Off]
#define MOTIONBREADFRAME			(10)							// ���[�V�����u�����h�̃t���[����
#define SPEED						(0.15f)

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LoadModel				g_LoadPlayer[MAX_PARTS];		// �ǂݍ��񂾃��f���̏��
LoadMotion				g_Motion;						// �ǂݍ��񂾃��[�V�������
PLAYER					g_Player;						// �v���C���[�̏��
int						g_nCounterKeySet;				// �L�[�Z�b�g�̃J�E���^�[
int						g_nCounterFrame;				// �t���[�����̃J�E���^�[
int						g_nMotionBlendFrame;			// ���[�V�����u�����h�p�̃t���[����
D3DXVECTOR3				g_posDiff[MAX_PARTS];			// �P�t���[��������̍��� [pos]
D3DXVECTOR3				g_RotDiff[MAX_PARTS];			// �P�t���[��������̍��� [Rot]

D3DXVECTOR3				g_fDistanceP;
float g_nCnt;

//=============================================================================
// ����������
//=============================================================================
void InitPlayer(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�\���̂̏�����
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
	{// ���f���̏��
		g_Player.aPlayerModel[nCntModel].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// ���f���̈ʒu
		g_Player.aPlayerModel[nCntModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// ���f���̌���
		g_Player.aPlayerModel[nCntModel].nType = 0;												// ���f���̎��
		g_Player.aPlayerModel[nCntModel].nIdxModelParent = -1;									// �e���f���̃C���f�b�N�X
	}

	// ���[�V���� 
	g_Player.nMotionTypeOld = MOTION_MAX;			// �O���[�V�����̎��
	g_Player.nMotionType = MOTION_NEUTRAL;			// ���[�V�����̎��
	g_Player.nFrameALL = 0;							// ���[�V�����̍ő�t���[����
	g_Player.nNowFrame = 0;							// ���[�V�����̌��݂̃t���[����

	g_nCounterKeySet = 0;							// �L�[�Z�b�g�̃J�E���^�[
	g_nCounterFrame = 0;							// �t���[�����̃J�E���^�[
	g_nMotionBlendFrame = 0;						// ���[�V�����u�����h�p�̃t���[����

	g_Player.nMaxParts = 0;							// �g�p���邷�郂�f���̐�

	for (int nCntModel = 0; nCntModel < MAX_PLAYER; nCntModel++)
	{// ���f���̍ő吔
		g_posDiff[nCntModel] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �P�t���[��������̍��� [pos]
		g_RotDiff[nCntModel] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �P�t���[��������̍��� [Rot]
	}

	//==============================
	// �t�@�C���ǂݍ���
	//==============================
	LoadPlayer();

	//#if 1
	//==============================
	// X�t�@�C���ǂݍ���
	//==============================

	for (int nCntModel = 0; nCntModel < g_Player.nLoadParts; nCntModel++)
	{// �ǂݍ��ރ��f���̍ő吔
		D3DXLoadMeshFromX(g_LoadPlayer[nCntModel].pXFileName,		// �ǂݍ���X�t�@�C����
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_LoadPlayer[nCntModel].pBuffMat,		// �}�e���A�����|�C���^
			NULL,
			&g_LoadPlayer[nCntModel].NumMat,		// �}�e���A�����̐�
			&g_LoadPlayer[nCntModel].pMesh);		// ���b�V�����|�C���^

		//�e�N�X�`���̓ǂݍ���
		D3DXMATERIAL *pMat;							// X�t�@�C��������o�����}�e���A����������

		// X�t�@�C������}�e���A�������擾
		pMat = (D3DXMATERIAL*)g_LoadPlayer[nCntModel].pBuffMat->GetBufferPointer();

		// �e�N�X�`���̃|�C���^���}�e���A�����̐����z��
		g_LoadPlayer[nCntModel].pTexture = new LPDIRECT3DTEXTURE9[(int)g_LoadPlayer[nCntModel].NumMat];	// int�^�ɒ���

		// �擾�����t�@�C���������
		for (int nCntNumMat = 0; nCntNumMat < (int)g_LoadPlayer[nCntModel].NumMat; nCntNumMat++)	// DWORD�^����int�^�ɕϊ�����
		{
			// �e�N�X�`���̃|�C���^������
			g_LoadPlayer[nCntModel].pTexture[nCntNumMat] = NULL;

			// �e�N�X�`���t�@�C�����������Ă���ꍇ�A�ǂݍ���
			if (pMat[nCntNumMat].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFile(pDevice, pMat[nCntNumMat].pTextureFilename,
				&g_LoadPlayer[nCntModel].pTexture[nCntNumMat]);
			}
		}
	}

	//X�t�@�C������ő�l�ƍŏ��l�̐ݒ�
	int nNumVertices;						//���_��
	DWORD sizeFVF;							//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVertexBuffer;					//���_�o�b�t�@�̃|�C���^

	g_Player.vtxMinPlayer = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
	g_Player.vtxMaxPlayer = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		//���_�����擾
		nNumVertices = g_LoadPlayer[nCntPlayer].pMesh->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_LoadPlayer[nCntPlayer].pMesh->GetFVF());

		//���_�o�b�t�@�����b�N
		g_LoadPlayer[nCntPlayer].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertexBuffer);

		for (int nCntvtx = 0; nCntvtx < nNumVertices; nCntvtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVertexBuffer;
			//���ׂĂ̕ϐ����r���čŏ��E�ő�l�����߂�
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
			pVertexBuffer += sizeFVF;		//�T�C�Y���|�C���^��i�߂�
		}

		//�����̌v�Z
		g_Player.size = (g_Player.vtxMaxPlayer - g_Player.vtxMinPlayer) * 0.01f;

		//���_�o�b�t�@�̃A�����b�N
		g_LoadPlayer[nCntPlayer].pMesh->UnlockVertexBuffer();
	}

}
//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		// ���b�V���̊J��
		if (g_LoadPlayer[nCntPlayer].pMesh != NULL)
		{
			g_LoadPlayer[nCntPlayer].pMesh->Release();
			g_LoadPlayer[nCntPlayer].pMesh = NULL;
		}

		// �}�e���A���̊J��
		if (g_LoadPlayer[nCntPlayer].pBuffMat != NULL)
		{
			g_LoadPlayer[nCntPlayer].pBuffMat->Release();
			g_LoadPlayer[nCntPlayer].pBuffMat = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{

	//���f���̎擾
	MODEL *pModel;
	pModel = GetModel();

	// �O��̃��[�V�������L��
	g_Player.nMotionTypeOld = g_Player.nMotionType;

	//�d�͏���
	g_Player.move.y -= 0.05f;

	// �O��̃|�W�V�������L��
	g_Player.posOld = g_Player.pos;

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{

		//��������
		g_Player.move.x += (0 - g_Player.move.x) * 1 / 5;
		g_Player.move.z += (0 - g_Player.move.z) * 1 / 5;

		//���f���𓮂���
		g_Player.pos += g_Player.move;

		//�ړ�����
		PlayerMove();

		//�����蔻��
		PlayerCollision();

		//�����u���b�N�̏���
		if (g_Player.pModel != NULL)
		{
			g_Player.pos.x += g_Player.pModel->move.x;
			g_Player.pos.z += g_Player.pModel->move.z;
		}
	}

	//�v���C���[�̎��S����
	if (g_Player.pos.y < 0.0f)
	{
		g_Player.pos.y = 0.0f;

		PlayerDeth();		
	}

	//���̏���
	if (g_Player.pos.x <= -2000 && g_Player.pos.x >= -4000)
	{
		g_Player.move.z += 0.2f;
		PlaySound(SOUND_LABEL_SE_BLIZZARD);
	}

	//=============//
	// �G�t�F�N�g  //
	//=============//
	EffectRound();

	//=============//
	// ���[�V����  //
	//=============//
	PlayerMotionPlay();

#if PLAY_MOTION
	PlayerMotion();
#endif
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9	pDevice = GetDevice();		// �f�o�C�X�̎擾
	D3DXMATRIX			mtxRot, mtxTrans;			// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9		matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL		*pMat;						// �}�e���A���ւ̃|�C���^
	D3DXMATRIX			mtxParent;					// �e�̃}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Player.mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		g_Player.rot.y,
		g_Player.rot.x,
		g_Player.rot.z);

	D3DXMatrixMultiply(&g_Player.mtxWorld,
	&g_Player.mtxWorld, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTrans,
		g_Player.pos.x,
		g_Player.pos.y,
		g_Player.pos.z);

	D3DXMatrixMultiply(&g_Player.mtxWorld,
	&g_Player.mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorld);

	// �������킹��}�g���b�N�X�̐ݒ�
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

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Player.aPlayerModel[nCntModel].mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_Player.aPlayerModel[nCntModel].rot.y, g_Player.aPlayerModel[nCntModel].rot.x, g_Player.aPlayerModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_Player.aPlayerModel[nCntModel].mtxWorld,
			&g_Player.aPlayerModel[nCntModel].mtxWorld, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTrans,
			g_Player.aPlayerModel[nCntModel].pos.x, g_Player.aPlayerModel[nCntModel].pos.y, g_Player.aPlayerModel[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_Player.aPlayerModel[nCntModel].mtxWorld,
			&g_Player.aPlayerModel[nCntModel].mtxWorld, &mtxTrans);

		// �e���f���̃}�g���b�N�X���������킹��
		D3DXMatrixMultiply(&g_Player.aPlayerModel[nCntModel].mtxWorld,
			&g_Player.aPlayerModel[nCntModel].mtxWorld, &mtxParent);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Player.aPlayerModel[nCntModel].mtxWorld);

		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_LoadPlayer[g_Player.aPlayerModel[nCntModel].nType].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_LoadPlayer[g_Player.aPlayerModel[nCntModel].nType].NumMat; nCntMat++)
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			// �e�N�X�`���̔��f
			pDevice->SetTexture(0, 0);

			// ���f��(�p�[�c)�̕`��
			g_LoadPlayer[g_Player.aPlayerModel[nCntModel].nType].pMesh->DrawSubset(nCntMat);
		}

		// �}�e���A�����f�t�H���g�ɖ߂�
		pDevice->SetMaterial(&matDef);
	}

}

//===============================================================================
// �v���C���[�̈ړ�����
//===============================================================================
void PlayerMove(void)
{
	//�J�����̎擾
	CAMERA *pCamera;
	pCamera = GetCamera();

	//�ϐ��錾
	int nStickH, nStickV;

	//�v���C���[��CLEAR���ĂȂ�
	if (g_Player.bPlayerCrear == false)
	{
		//�ړ�
		if (g_Player.bPlayerDeth == false)
		{
			// �A�i���O�X�e�B�b�N���̎擾
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

			// ������ړ�
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

			// �������ړ�
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

			// �E
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

			// ����
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
// �v���C���[�̓����蔻�菈��
//===============================================================================
void PlayerCollision(void)
{
	if (GetMode() == MODE_GAME)
	{
		// �e�̓����蔻��
		if (ColisionShadow
		(&g_Player.pos,
			&g_Player.posOld,
			&g_Player.move,
			&g_Player.pModel))
		{
			g_nCnt = g_Player.pModel->vtxMaxModel.y + g_Player.pModel->Pos.y;

			//�e�̃Z�b�g
			SetPositionShadow(g_Player.hIdxShadow, D3DXVECTOR3(g_Player.pos.x, g_nCnt, g_Player.pos.z));
		}
		else
		{
			g_nCnt = 20;
			SetPositionShadow(g_Player.hIdxShadow, D3DXVECTOR3(g_Player.pos.x, g_nCnt, g_Player.pos.z));
		}

		// �����蔻��
		if (ColisionModel
		(&g_Player.pos,
			&g_Player.posOld,
			&g_Player.move,
			&g_Player.pModel) == true)
		{
			//�W�����v���g�p�\�ɂ���
			g_Player.bJump = false;

			//�d�͂̃��Z�b�g
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
			//�W�����v���g�p�\�ɂ���
			g_Player.bJump = false;

			//�d�͂̃��Z�b�g
			g_Player.move.y = 0;
		}
		else
		{

		}
		// �e�̓����蔻��
		if (ColisionTutoShadow
		(&g_Player.pos,
			&g_Player.posOld,
			&g_Player.move,
			&g_Player.pTutoModel))
		{
			g_nCnt = g_Player.pTutoModel->vtxMaxModel.y + g_Player.pTutoModel->Pos.y;

			//�e�̃Z�b�g
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
// �G�t�F�N�g�̐ݒ菈��
//===============================================================================
void EffectRound(void)
{
	//����̃G�t�F�N�g//

	if (g_Player.pos.x <= -2000 && g_Player.pos.x >= -6000)
	{
		for (int nCntParticle = 0; nCntParticle < 50; nCntParticle++)
		{
			SetParticle(D3DXVECTOR3(rand() % (-2000) + (-4000.0f), 1000.0f, rand() % 4000 + (-2000.0f)), D3DXVECTOR3(0.0f, -10.0f, 12.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 20, 2000, 0);
		}
	}

	//���@�w�̃G�t�F�N�g//

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
// �v���C���[�̎��S����
//===============================================================================
void PlayerDeth(void)
{
	//�X�̎擾
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
				//�v���C���[�̓������~�߂�
				g_Player.bPlayerDeth = false;
				//�v���C���[�̎g�p�����Ȃ�
				pIce->bUse = false;
				//�v���C���[�̉�]�ʂ�߂�
				g_Player.rot.x = 0;
				//�J�E���g�̏�����
				g_Player.nCntDeth = 0;
				//�e�̍Ĕz�u
				g_Player.hIdxShadow = SetShadow(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y, g_Player.pos.z), g_Player.rot);
			}
			else
			{
				if (GetMode() == MODE_GAME)
				{
					SetGameState(GAMESTATE_END2);
					//�v���C���[�̏���������
					InitPlayer();
				}
				else
				{
					SetFade(MODE_TUTORIAL);
					//�v���C���[�̏���������
					InitPlayer();
				}
			}
		}
	}
}
//===============================================================================
// �v���C���[�̃��[�V����
//===============================================================================
void PlayerMotionPlay(void)
{
	// �ҋ@
	if (!g_Player.bWalk || !g_Player.bJumpMS || !g_Player.bDeth)
	{
		g_Player.nMotionType = MOTION_NEUTRAL;
	}

	//�@����
	if (g_Player.bWalk)
	{
		g_Player.nMotionType = A;
		if (g_Player.nMotionType != g_Player.nMotionTypeOld)
		{
			CulFrame();
		}
		if (g_Player.nNowFrame == g_Player.nFrameALL)
		{// �Ō�܂ōĐ����ꂽ�ꍇ
			g_Player.bWalk = false;
		}
	}

	//�@�W�����v
	if (g_Player.bJumpMS)
	{
		g_Player.nMotionType = B;
		if (g_Player.nMotionType != g_Player.nMotionTypeOld)
		{
			CulFrame();
		}
		if (g_Player.nNowFrame == g_Player.nFrameALL)
		{// �Ō�܂ōĐ����ꂽ�ꍇ
			g_Player.bJumpMS = false;
		}
	}

	//�@���S
	if (g_Player.bDeth)
	{
		g_Player.nMotionType = C;
		if (g_Player.nMotionType != g_Player.nMotionTypeOld)
		{
			CulFrame();
		}
		if (g_Player.nNowFrame == g_Player.nFrameALL)
		{// �Ō�܂ōĐ����ꂽ�ꍇ
			g_Player.bDeth = false;
		}
	}

}

//===============================================================================
// �v���C���[�̃��[�V����
//===============================================================================
void PlayerMotion(void)
{
	// ���[�V�����̏�����

	if (g_Player.nMotionTypeOld != g_Player.nMotionType)
	{// ���[�V�������O��ƈقȂ�
	 // �L�[�t���[��
		g_nCounterKeySet = 0;
		// �t���[����
		g_nCounterFrame = 0;
		// ���[�V�����u�����h�̃t���[���������߂�
		g_nMotionBlendFrame = MOTIONBREADFRAME;
		// �t���[�����̌v�Z
		CulFrame();
	}
	// �L�[�̐ؑ�

	switch (g_Motion.Motion[g_Player.nMotionType].nLoop)
	{// ���[�V�����̎�ނ̃��[�v��
	case 0:		// ���[�v���Ȃ�
		if (g_nCounterFrame == g_nMotionBlendFrame && g_Motion.Motion[g_Player.nMotionType].nNumKey == g_nCounterKeySet + 1)
		{// �ŏI�t���[���@&& �ŏI�L�[�ɂȂ���
		 // �t���[����������
			g_nCounterFrame = 0;
			// �L�[�Z�b�g��i�߂�
			g_nCounterKeySet = g_Motion.Motion[g_Player.nMotionType].nNumKey - 1;		// �Ō�̃L�[�Z�b�g��ݒ肷��

			// �����t���[���������߂�
			g_nMotionBlendFrame = g_Motion.Motion[g_Player.nMotionType].nKey[g_nCounterKeySet].nframe;
		}
		else if (g_nCounterFrame == g_nMotionBlendFrame && g_Motion.Motion[g_Player.nMotionType].nNumKey != g_nCounterKeySet)
		{// �Ō�̃t���[�� && �ŏI�L�[�ł͂Ȃ�
		 // �t���[����������
			g_nCounterFrame = 0;
			// �L�[�Z�b�g��i�߂�
			g_nCounterKeySet = (g_nCounterKeySet + 1) % g_Motion.Motion[g_Player.nMotionType].nNumKey;
			// �����t���[���������߂�
			g_nMotionBlendFrame = g_Motion.Motion[g_Player.nMotionType].nKey[g_nCounterKeySet].nframe;
		}
		break;

	case 1:		// ���[�v����
		if (g_nCounterFrame == g_nMotionBlendFrame)
		{// �Ō�̃t���[��
		 // �t���[����������
			g_nCounterFrame = 0;
			// �L�[�Z�b�g��i�߂�
			g_nCounterKeySet = (g_nCounterKeySet + 1) % g_Motion.Motion[g_Player.nMotionType].nNumKey;
			// �����t���[���������߂�
			g_nMotionBlendFrame = g_Motion.Motion[g_Player.nMotionType].nKey[g_nCounterKeySet].nframe;
		}
		break;
	}

	if (g_nCounterFrame == 0)
	{// �ŏ��̃t���[���ɂȂ�����A���̃L�[�Z�b�g�Ƃ̍����v�Z
		for (int nCntParts = 0; nCntParts < MAX_PLAYER; nCntParts++)
		{
			// �e�p�[�c�̈ʒu�̍��� = ([��]�̃L�[�Z�b�g�̊e�p�[�c�̈ʒu + �e�p�[�c�̏����I�t�Z�b�g[�ʒu]) - [����]�̊e�p�[�c�̈ʒu
			g_posDiff[nCntParts] = (g_Motion.Motion[g_Player.nMotionType].nKey[g_nCounterKeySet].pos[nCntParts] +
				g_Motion.Offset[nCntParts].pos) - g_Player.aPlayerModel[nCntParts].pos;

			// �e�p�[�c�̌����̍��� = [��]�̃L�[�Z�b�g�̊e�p�[�c�̌��� + �e�p�[�c�̏����I�t�Z�b�g[����] - [����]�̊e�p�[�c�̌���
			g_RotDiff[nCntParts] = g_Motion.Motion[g_Player.nMotionType].nKey[g_nCounterKeySet].rot[nCntParts] +
				g_Motion.Offset[nCntParts].rot - g_Player.aPlayerModel[nCntParts].rot;

			// �������t���[�����Ŋ���
			/* �P�t���[��������̍��� = (�e�p�[�c�̈ʒu[x]�̍��� / [��]�̃L�[�Z�b�g�̃t���[����,
			�e�p�[�c�̈ʒu[y]�̍��� / [��]�̃L�[�Z�b�g�̃t���[����,
			�e�p�[�c�̈ʒu[z]�̍��� / [��]�̃L�[�Z�b�g�̃t���[����)*/
			g_posDiff[nCntParts] = D3DXVECTOR3(g_posDiff[nCntParts].x / g_nMotionBlendFrame,
				g_posDiff[nCntParts].y / g_nMotionBlendFrame,
				g_posDiff[nCntParts].z / g_nMotionBlendFrame);

			g_RotDiff[nCntParts] = D3DXVECTOR3(g_RotDiff[nCntParts].x / g_nMotionBlendFrame,
				g_RotDiff[nCntParts].y / g_nMotionBlendFrame,
				g_RotDiff[nCntParts].z / g_nMotionBlendFrame);
		}
	}

	// ���[�V�����X�V
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
	// �t���[�����̉��Z
	g_nCounterFrame++;

	if (g_Player.nNowFrame < g_Player.nFrameALL)
	{
		// ���݂̃t���[���������Z
		g_Player.nNowFrame++;
	}
}

//===============================================================================
// ���[�V�����̃t���[�����̌v�Z
//===============================================================================
void CulFrame(void)
{
	// ���݂̃t���[���������Z�b�g
	g_Player.nNowFrame = 0;

	// ���[�V�����̑��t���[���������Z�b�g
	g_Player.nFrameALL = 0;

	// ���[�V�����̑��t���[�������v�Z
	for (int nCntKey = 0; nCntKey < g_Motion.Motion[g_Player.nMotionType].nNumKey; nCntKey++)
	{
		g_Player.nFrameALL += g_Motion.Motion[g_Player.nMotionType].nKey[nCntKey].nframe;
	}
}

//===============================================================================
// �v���C���[�̓ǂݍ���
//===============================================================================
void LoadPlayer(void)
{
	//�ǂݍ��񂾃��f���̏��̏�����
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		for (int nText = 0; nText < MAX_CHAR; nText++)
		{
			g_LoadPlayer[nCntPlayer].pXFileName[nText] = NULL;		//�t�@�C����
		}
		g_LoadPlayer[nCntPlayer].pMesh = NULL;						//���b�V�����ւ̃|�C���^
		g_LoadPlayer[nCntPlayer].pBuffMat = NULL;					//�}�e���A�����ւ̃|�C���^
		g_LoadPlayer[nCntPlayer].NumMat = 0;						//�}�e���A���̐�
		g_LoadPlayer[nCntPlayer].pTexture = NULL;					//�e�N�X�`���ւ̃|�C���^
	}

	for (int nCntModel = 0; nCntModel < MAX_PLAYER; nCntModel++)
	{// ���f���̍ő吔
		g_Motion.Offset[nCntModel].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �I�t�Z�b�g[�ʒu]
		g_Motion.Offset[nCntModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �I�t�Z�b�g[����]
	}

	for (int nCntMotion = 0; nCntMotion < MOTION_MAX; nCntMotion++)
	{// ���[�V�����̎��
		g_Motion.Motion[nCntMotion].nLoop;				// ���[�v��� [0 : ���[�v���Ȃ�, 1 : ���[�v����]
		g_Motion.Motion[nCntMotion].nNumKey = 0;		// �L�[��

		// �L�[���
		for (int nNumKeySet = 0; nNumKeySet < MAX_KEYSET; nNumKeySet++)
		{// �L�[�Z�b�g�̍ő吔
			g_Motion.Motion[nCntMotion].nKey[nNumKeySet].nframe = 0;				// �t���[����
			for (int nCntModel = 0; nCntModel < MAX_PLAYER; nCntModel++)
			{// ���f���̍ő吔
				g_Motion.Motion[nCntMotion].nKey[nNumKeySet].pos[nCntModel] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
				g_Motion.Motion[nCntMotion].nKey[nNumKeySet].rot[nCntModel] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����
			}
		}
	}

	//#if 1
	// ���[�J���ϐ��錾
	FILE *pFile;				// �t�@�C���̃|�C���^
	char ReadText[256];			// �ǂݍ��񂾕���������Ă���
	char HeadText[256];			// ��r�p
	char DustBox[256];			// �g�p���Ȃ����̂����Ă���
	int nCntText = 0;			// ���f���t�@�C����
	int nCntModel = 0;			// ���f����
	int nCntMotion = 0;			// ���[�V������
	int nCntKeySet = 0;			// �L�[�Z�b�g��

	// �t�@�C���I�[�v��
	pFile = fopen(PLAYER_FILE, "r");		// �t�@�C�����J��[�ǂݍ��݌^]

	if (pFile != NULL)		// �t�@�C������ł͂Ȃ�
	{//�t�@�C�����J�����ꍇ
		while (strcmp(HeadText, "SCRIPT") != 0)
		{// "SCRIPT" ���ǂݍ��܂��܂ŌJ��Ԃ��������ǂݎ��
			fgets(ReadText, sizeof(ReadText), pFile);
			sscanf(ReadText, "%s", &HeadText);
		}

		if (strcmp(HeadText, "SCRIPT") == 0)
		{// "SCRIPT" ���ǂݎ�ꂽ�ꍇ�A�����J�n
			while (strcmp(HeadText, "END_SCRIPT") != 0)
			{// "END_SCRIPT" ���ǂݍ��܂��܂ŌJ��Ԃ��������ǂݎ��
				fgets(ReadText, sizeof(ReadText), pFile);
				sscanf(ReadText, "%s", &HeadText);

				if (strcmp(HeadText, "\n") == 0)
				{// ������̐擪�� [\n](���s) �̏ꍇ�������Ȃ�
				 //int nCnt = 0;
				}
				if (strcmp(HeadText, "NUM_MODEL") == 0)
				{// �ǂݍ��ރ��f���̍ő吔
					sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &g_Player.nLoadParts);
				}
				else if (strcmp(HeadText, "MODEL_FILENAME") == 0)
				{// ���f���t�@�C����
					if (g_Player.nLoadParts > nCntText)
					{// �ő吔�ȏ㏈�����Ȃ�
						sscanf(ReadText, "%s %c %s", &DustBox, &DustBox, &g_LoadPlayer[nCntText].pXFileName[0]);
						nCntText++;
					}
				}
				else if (strcmp(HeadText, "CHARACTERSET") == 0)
				{//--- �L�����N�^�[��� ---//
					while (strcmp(HeadText, "END_CHARACTERSET") != 0)
					{// "END_CHARACTERSET" ���ǂݎ���܂ŌJ��Ԃ��������ǂݎ��
						fgets(ReadText, sizeof(ReadText), pFile);
						sscanf(ReadText, "%s", &HeadText);

						if (strcmp(HeadText, "\n") == 0)
						{// ������̐擪�� [\n](���s) �̏ꍇ�������Ȃ�
							int nCnt = 0;
						}

						else if (strcmp(HeadText, "MOVE") == 0)
						{// �ړ���
							sscanf(ReadText, "%s %c %f", &DustBox, &DustBox, &g_Player.fMoveSpeed);
						}
						else if (strcmp(HeadText, "pos") == 0)
						{// �ꏊ
							sscanf(ReadText, "%s %c %f %f %f", &DustBox, &DustBox, &g_Player.pos.x, &g_Player.pos.y, &g_Player.pos.z);
						}
						else if (strcmp(HeadText, "RADIUS") == 0)
						{// ���a
							sscanf(ReadText, "%s %c %f", &DustBox, &DustBox, &g_Player.fRadius);
						}
						else if (strcmp(HeadText, "HEIGHT") == 0)
						{// ����
							sscanf(ReadText, "%s %c %f", &DustBox, &DustBox, &g_Player.fHeight);
						}
						else if (strcmp(HeadText, "NUM_PARTS") == 0)
						{// �v���C���[�P�̂ɑ΂��郂�f���̎g�p��
							sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &g_Player.nMaxParts);
						}

						g_Player.nMaxParts = 10;

						// ���f���̔z�u���
						if (strcmp(HeadText, "PARTSSET") == 0)
						{
							if (g_Player.nMaxParts > nCntModel)
							{
								while (strcmp(HeadText, "END_PARTSSET") != 0)
								{// "END_PARTSSET" ���ǂݎ���܂ŌJ��Ԃ��������ǂݎ��
									fgets(ReadText, sizeof(ReadText), pFile);
									sscanf(ReadText, "%s", &HeadText);

									if (strcmp(HeadText, "INDEX") == 0)
									{// ����
										sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &g_Player.aPlayerModel[nCntModel].nType);
									}
									else if (strcmp(HeadText, "PARENT") == 0)
									{// �e�̃C���f�b�N�X
										sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &g_Player.aPlayerModel[nCntModel].nIdxModelParent);
									}
									else if (strcmp(HeadText, "pos") == 0)
									{// �ʒu
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
									{// ����
										sscanf(ReadText, "%s %c %f %f %f", &DustBox, &DustBox,
											&g_Player.aPlayerModel[nCntModel].rot.x,
											&g_Player.aPlayerModel[nCntModel].rot.y,
											&g_Player.aPlayerModel[nCntModel].rot.z);
									}
								}
								nCntModel++;		// ���f������i�߂�
							}
						}
					}
				}

				// ���[�V�������
				else if (strcmp(HeadText, "MOTIONSET") == 0)
				{
					nCntModel = 0;		// ���f�����̃��Z�b�g

					while (strcmp(HeadText, "END_MOTIONSET") != 0)
					{// "END_MOTIONSET" ���ǂݎ���܂ŌJ��Ԃ��������ǂݎ��
						fgets(ReadText, sizeof(ReadText), pFile);
						sscanf(ReadText, "%s", &HeadText);

						if (strcmp(HeadText, "LOOP") == 0)
						{// ���[�v���
							sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &g_Motion.Motion[nCntMotion].nLoop);
						}
						else if (strcmp(HeadText, "NUM_KEY") == 0)
						{// �L�[��
							sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &g_Motion.Motion[nCntMotion].nNumKey);
						}
						else if (strcmp(HeadText, "KEYSET") == 0)
						{// �L�[�Z�b�g
							while (strcmp(HeadText, "END_KEYSET") != 0)
							{// "END_KEYSET" ���ǂݎ���܂ŌJ��Ԃ��������ǂݎ��
								fgets(ReadText, sizeof(ReadText), pFile);
								sscanf(ReadText, "%s", &HeadText);

								if (strcmp(HeadText, "FRAME") == 0)
								{// �t���[����
									sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &g_Motion.Motion[nCntMotion].nKey[nCntKeySet].nframe);
								}
								else if (strcmp(HeadText, "KEY") == 0)
								{// �L�[
									while (strcmp(HeadText, "END_KEY") != 0)
									{// "END_KEY" ���ǂݎ���܂ŌJ��Ԃ��������ǂݎ��
										fgets(ReadText, sizeof(ReadText), pFile);
										sscanf(ReadText, "%s", &HeadText);

										if (strcmp(HeadText, "pos") == 0)
										{// �ʒu
											sscanf(ReadText, "%s %c %f %f %f", &DustBox, &DustBox,
												&g_Motion.Motion[nCntMotion].nKey[nCntKeySet].pos[nCntModel].x,
												&g_Motion.Motion[nCntMotion].nKey[nCntKeySet].pos[nCntModel].y,
												&g_Motion.Motion[nCntMotion].nKey[nCntKeySet].pos[nCntModel].z);
										}
										else if (strcmp(HeadText, "ROT") == 0)
										{// ����
											sscanf(ReadText, "%s %c %f %f %f", &DustBox, &DustBox,
												&g_Motion.Motion[nCntMotion].nKey[nCntKeySet].rot[nCntModel].x,
												&g_Motion.Motion[nCntMotion].nKey[nCntKeySet].rot[nCntModel].y,
												&g_Motion.Motion[nCntMotion].nKey[nCntKeySet].rot[nCntModel].z);
										}
									}
									nCntModel++;		// ���f������i�߂�
								}
							}
							nCntKeySet++;		// �L�[�Z�b�g����i�߂�
							nCntModel = 0;		// ���f�����̃��Z�b�g
						}
					}
					nCntMotion++;			// ���[�V�����̎�ނ�i�߂�
					nCntKeySet = 0;			// �L�[�Z�b�g���̃��Z�b�g
				}
			}
		}
		// �t�@�C�������
		fclose(pFile);
	}
	else
	{// �J���Ȃ������ꍇ
		MessageBox(NULL, "�L�����N�^�[���t�@�C�����J���܂���ł����B", NULL, MB_OK);
	}
}
//===============================================================================
// �v���C���[�̔j��
//===============================================================================
void UpdateTitlePlayer(void)
{
	// �J�����̎擾
	CAMERA *pCamera = GetCamera();

	// �O��̈ʒu���L��
	g_Player.posOld = g_Player.pos;

	// �O��̃��[�V�������L��
	g_Player.nMotionTypeOld = g_Player.nMotionType;

	// �ҋ@
	if (!g_Player.bWalk)
	{
		g_Player.nMotionType = MOTION_NEUTRAL;
	}

	 //���[�V����
#if PLAY_MOTION
	PlayerMotion();
#endif
}

//===============================================================================
// �v���C���[�̎擾
//===============================================================================
PLAYER * GetPlayer(void)
{
	return & g_Player;
}