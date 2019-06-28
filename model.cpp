//=============================================================================
//
// ���f������ [model.cpp]
// Author : KIMURA KOUTA
//
//=============================================================================
#include "model.h"
#include "input.h"
#include "camera.h"
#include "Shadow.h"
#include "bullet.h"
#include "effect.h"
#include "player.h"
#include "Game.h"
#include "fade.h"
#include "Controlar.h"
#include "GameText.h"
#include "sound.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MODEL_FILE		"DATA/road/model.txt"					//�t�@�C����

#define SPEED			(0.5f)									//�v���C���[�X�s�[�h

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
MODEL					 g_Model[MAX_MODEL];					// �ǂݍ��񂾃��f���̏��
LOADMODEL				 g_LoadModel[MAX_MODEL];				// �ǂݍ��񂾃��f���̏��

D3DXVECTOR3				g_fDistance;
int g_nCntCrear;

//=============================================================================
// ����������
//=============================================================================
void InitModel(void)
{
	int nCntModel = 0;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		// �ʒu�E�����̏����ݒ�
		g_Model[nCntModel].Pos = D3DXVECTOR3(100.0f, 0.0f, 0.0f);
		g_Model[nCntModel].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Model[nCntModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Model[nCntModel].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_Model[nCntModel].Diffrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Model[nCntModel].nTypeTex = 0;
		g_Model[nCntModel].nTypeModel = 0;
		g_Model[nCntModel].bUse = false;
		g_Model[nCntModel].fRadius = 0;
		g_Model[nCntModel].fHeight = 0;
		g_Model[nCntModel].nLoad = MAX_MODELTYPE;
		g_Model[nCntModel].MaxModel = MAX_MODEL;
		g_Model[nCntModel].vtxMinModel = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
		g_Model[nCntModel].vtxMaxModel = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);
	}

	g_nCntCrear = 0;

	//==============================
	// �t�@�C���ǂݍ���
	//==============================
	LoadModelText();

	for(nCntModel = 0; nCntModel < g_Model[nCntModel].nLoad; nCntModel++)
	{
		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(g_LoadModel[nCntModel].pXFileName,					// �ǂݍ���X�t�@�C����
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_LoadModel[nCntModel].pBuffMatModel,								// �}�e���A�����|�C���^
			NULL,
			&g_LoadModel[nCntModel].NumMatModel,								// �}�e���A�����̐�
			&g_LoadModel[nCntModel].pMeshModel);								// ���b�V�����|�C���g

		//�e�N�X�`���̓ǂݍ���
		D3DXMATERIAL *pMat;														// X�t�@�C��������o�����}�e���A����������

		// X�t�@�C������}�e���A�������擾
		pMat = (D3DXMATERIAL*)g_LoadModel[nCntModel].pBuffMatModel->GetBufferPointer();

		// �e�N�X�`���̃|�C���^���}�e���A�����̐����z��
		g_LoadModel[nCntModel].pTextureModel = new LPDIRECT3DTEXTURE9[(int)g_LoadModel[nCntModel].NumMatModel];	// int�^�ɒ���

		// �擾�����t�@�C���������
		for (int nCntNumMat = 0; nCntNumMat < (int)g_LoadModel[nCntModel].NumMatModel; nCntNumMat++)	// DWORD�^����int�^�ɕϊ�����
		{
			// �e�N�X�`���̃|�C���^������
			g_LoadModel[nCntModel].pTextureModel[nCntNumMat] = NULL;

			// �e�N�X�`���t�@�C�����������Ă���ꍇ�A�ǂݍ���
			if (pMat[nCntNumMat].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFile(pDevice, pMat[nCntNumMat].pTextureFilename,
				&g_LoadModel[nCntModel].pTextureModel[nCntNumMat]);
			}
		}
	}

	//X�t�@�C������ő�l�ƍŏ��l�̐ݒ�
	int nNumVertices;						//���_��
	DWORD sizeFVF;							//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVertexBuffer;					//���_�o�b�t�@�̃|�C���^

	for (nCntModel = 0; nCntModel < g_Model[nCntModel].MaxModel; nCntModel++)
	{
		//���_�����擾
		nNumVertices = g_LoadModel[g_Model[nCntModel].nTypeModel].pMeshModel->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_LoadModel[g_Model[nCntModel].nTypeModel].pMeshModel->GetFVF());

		//���_�o�b�t�@�����b�N
		g_LoadModel[g_Model[nCntModel].nTypeModel].pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertexBuffer);

		for (int nCntvtx = 0; nCntvtx < nNumVertices; nCntvtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVertexBuffer;

			//���ׂĂ̕ϐ����r���čŏ��E�ő�l�����߂�
			if (g_Model[nCntModel].vtxMinModel.x > vtx.x)
			{
				g_Model[nCntModel].vtxMinModel.x = vtx.x;
			}
			if (g_Model[nCntModel].vtxMaxModel.x < vtx.x)
			{
				g_Model[nCntModel].vtxMaxModel.x = vtx.x;
			}
			if (g_Model[nCntModel].vtxMinModel.y > vtx.y)
			{
				g_Model[nCntModel].vtxMinModel.y = vtx.y;
			}
			if (g_Model[nCntModel].vtxMaxModel.y < vtx.y)
			{
				g_Model[nCntModel].vtxMaxModel.y = vtx.y;
			}
			if (g_Model[nCntModel].vtxMinModel.z > vtx.z)
			{
				g_Model[nCntModel].vtxMinModel.z = vtx.z;
			}
			if (g_Model[nCntModel].vtxMaxModel.z < vtx.z)
			{
				g_Model[nCntModel].vtxMaxModel.z = vtx.z;
			}

			pVertexBuffer += sizeFVF;		//�T�C�Y���|�C���^��i�߂�
		}
		//���_�o�b�t�@�̃A�����b�N
		g_LoadModel[g_Model[nCntModel].nTypeModel].pMeshModel->UnlockVertexBuffer();
	}
}
//=============================================================================
// �I������
//=============================================================================
void UninitModel(void)
{
		for (int nCntModel = 0; nCntModel < g_Model[nCntModel].MaxModel; nCntModel++)
		{
			// ���b�V���̊J��
			if (g_LoadModel[g_Model[nCntModel].nTypeModel].pMeshModel != NULL)
			{
				g_LoadModel[g_Model[nCntModel].nTypeModel].pMeshModel->Release();
				g_LoadModel[g_Model[nCntModel].nTypeModel].pMeshModel = NULL;
			}

			// �}�e���A���̊J��
			if (g_LoadModel[g_Model[nCntModel].nTypeModel].pBuffMatModel != NULL)
			{
				g_LoadModel[g_Model[nCntModel].nTypeModel].pBuffMatModel->Release();
				g_LoadModel[g_Model[nCntModel].nTypeModel].pBuffMatModel = NULL;
			}
		}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateModel(void)
{
	int nCntModel = 0;

	//�v���C���[�̎擾
	PLAYER * pPlayer;
	pPlayer = GetPlayer();

	for (nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		g_Model[nCntModel].Pos += g_Model[nCntModel].move;

		if (g_Model[nCntModel].nTypeModel == 7)
		{
			g_Model[nCntModel].move = D3DXVECTOR3(0.0f, 0.0f, -3.0f);

			if (g_Model[nCntModel].Pos.z <= -1000)
			{
				g_Model[nCntModel].Pos = D3DXVECTOR3(3800.0f, 0.0f, 1500.0f);
			}
		}
		if (g_Model[nCntModel].nTypeModel == 9)
		{
			g_Model[nCntModel].move = D3DXVECTOR3(0.0f, 0.0f, 3.0f);

			if (g_Model[nCntModel].Pos.z >= 1200)
			{
				g_Model[nCntModel].Pos = D3DXVECTOR3(2700.0f, 0.0f, -1500.0f);
			}
		}
		if (g_Model[nCntModel].nTypeModel == 10)
		{
			g_Model[nCntModel].rot.y -= 0.1f;
		}
		if (g_Model[nCntModel].nTypeModel == 19)
		{
			g_Model[nCntModel].rot.y -= 0.1f;
		}
		if (pPlayer->bClearFlag1 == true)
		{
			if (g_Model[nCntModel].nTypeModel == 22)
			{
				g_Model[nCntModel].bUse = false;
			}
		}
		if (pPlayer->bClearFlag2 == true)
		{
			if (g_Model[nCntModel].nTypeModel == 23)
			{
				g_Model[nCntModel].bUse = false;
			}
		}

		if (g_Model[nCntModel].nTypeModel == 24)
		{
			if (g_Model[nCntModel].bUse)
			{

			}
		}
		g_Model[nCntModel].Pos.y;
	}

	CrearModel();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxSize, mtxRot, mtxTrans;				//�v�Z�p
	D3DXMATERIAL*pMat;
	D3DMATERIAL9 matDef;

	for (int nCntModel = 0; nCntModel < g_Model[nCntModel].MaxModel; nCntModel++)
	{
		if (g_Model[nCntModel].bUse)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Model[nCntModel].mtxWorldModel);

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxSize, g_Model[nCntModel].scale.x, g_Model[nCntModel].scale.y, g_Model[nCntModel].scale.z);
			D3DXMatrixMultiply(&g_Model[nCntModel].mtxWorldModel, &g_Model[nCntModel].mtxWorldModel, &mtxSize);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Model[nCntModel].rot.y, g_Model[nCntModel].rot.x, g_Model[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_Model[nCntModel].mtxWorldModel, &g_Model[nCntModel].mtxWorldModel, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Model[nCntModel].Pos.x, g_Model[nCntModel].Pos.y, g_Model[nCntModel].Pos.z);
			D3DXMatrixMultiply(&g_Model[nCntModel].mtxWorldModel, &g_Model[nCntModel].mtxWorldModel, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Model[nCntModel].mtxWorldModel);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A�����ɑ΂���|�C���^���擾
			pMat = (D3DXMATERIAL*)g_LoadModel[g_Model[nCntModel].nTypeModel].pBuffMatModel->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_LoadModel[g_Model[nCntModel].nTypeModel].NumMatModel; nCntMat++)
			{
				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_LoadModel[g_Model[nCntModel].nTypeModel].pTextureModel[nCntMat]);

				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// �`��
				g_LoadModel[g_Model[nCntModel].nTypeModel].pMeshModel->DrawSubset(nCntMat);
			}
		}
		// �}�e���A�����f�t�H���g�ɖ߂�
		pDevice->SetMaterial(&matDef);
	}
}

//============================================================================
// ���f���̎擾
//=============================================================================
MODEL * GetModel(void)
{
	return &g_Model[0];
}

//=======================================================================================
// ���f���̓����蔻��
//=======================================================================================
bool ColisionModel(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * move, MODEL**ppModelRet)
{
	bool bLand = false;
	int nCntModel;

	//�v���C���[�̎擾
	PLAYER * pPlayer;
	pPlayer = GetPlayer();

	if (*ppModelRet != NULL)
	{
		*ppModelRet = NULL;
	}

		for (nCntModel = 0; nCntModel < g_Model[nCntModel].MaxModel; nCntModel++)
		{
			if (pPlayer->bPlayerDeth==false)
			{
				if (g_Model[nCntModel].bUse)
				{

					if (pPos->y + pPlayer->size.y <g_Model[nCntModel].vtxMaxModel.y + g_Model[nCntModel].Pos.y &&
						pPos->y - pPlayer->size.y >g_Model[nCntModel].vtxMinModel.y + g_Model[nCntModel].Pos.y)
					{
						if (pPos->z + pPlayer->size.z <g_Model[nCntModel].vtxMaxModel.z + g_Model[nCntModel].Pos.z &&
							pPos->z - pPlayer->size.z >g_Model[nCntModel].vtxMinModel.z + g_Model[nCntModel].Pos.z)
						{
							//��
							if (pPos->x + pPlayer->size.x > g_Model[nCntModel].vtxMinModel.x + g_Model[nCntModel].Pos.x&&
								pPosOld->x - pPlayer->size.x < g_Model[nCntModel].vtxMinModel.x + g_Model[nCntModel].Pos.x)
							{
								pPos->x = g_Model[nCntModel].vtxMinModel.x + g_Model[nCntModel].Pos.x - pPlayer->size.x;

								if (g_Model[nCntModel].nTypeModel == 10)
								{
									g_Model[nCntModel].bUse = false;
									pPlayer->bClearFlag1 = true;
									PlaySound(SOUND_LABEL_SE_KEYGET);
								}
								if (g_Model[nCntModel].nTypeModel == 19)
								{
									g_Model[nCntModel].bUse = false;
									pPlayer->bClearFlag2 = true;
									PlaySound(SOUND_LABEL_SE_KEYGET);
								}
								if (g_Model[nCntModel].nTypeModel == 20)
								{
									if (pPlayer->bClearFlag1 == true && pPlayer->bClearFlag2 == true)
									{
										pPlayer->bPlayerCrear = true;
									}
								}
								move->x = 0.0f;
							}
							//�E
							else if (pPos->x + pPlayer->size.x < g_Model[nCntModel].vtxMaxModel.x + g_Model[nCntModel].Pos.x &&
								pPosOld->x + pPlayer->size.x > g_Model[nCntModel].vtxMaxModel.x + g_Model[nCntModel].Pos.x)
							{
								pPos->x = g_Model[nCntModel].vtxMaxModel.x + g_Model[nCntModel].Pos.x + pPlayer->size.x;
								if (g_Model[nCntModel].nTypeModel == 10)
								{
									g_Model[nCntModel].bUse = false;
									pPlayer->bClearFlag1 = true;
									PlaySound(SOUND_LABEL_SE_KEYGET);
								}
								if (g_Model[nCntModel].nTypeModel == 19)
								{
									g_Model[nCntModel].bUse = false;
									pPlayer->bClearFlag2 = true;
									PlaySound(SOUND_LABEL_SE_KEYGET);
								}
								if (g_Model[nCntModel].nTypeModel == 20)
								{
									if (pPlayer->bClearFlag1 == true && pPlayer->bClearFlag2 == true)
									{
										pPlayer->bPlayerCrear = true;
									}
								}
								move->x = 0.0f;
							}
						}
					}
					if (pPos->y + pPlayer->size.y <g_Model[nCntModel].vtxMaxModel.y + g_Model[nCntModel].Pos.y &&
						pPos->y - pPlayer->size.y >g_Model[nCntModel].vtxMinModel.y + g_Model[nCntModel].Pos.y)
					{
						if (pPos->x + pPlayer->size.x <g_Model[nCntModel].vtxMaxModel.x + g_Model[nCntModel].Pos.x&&
							pPos->x + pPlayer->size.x >g_Model[nCntModel].vtxMinModel.x + g_Model[nCntModel].Pos.x)
						{
							//��
							if (pPos->z - pPlayer->size.z > g_Model[nCntModel].vtxMinModel.z + g_Model[nCntModel].Pos.z &&
								pPosOld->z - pPlayer->size.z < g_Model[nCntModel].vtxMinModel.z + g_Model[nCntModel].Pos.z)
							{
								pPos->z = g_Model[nCntModel].vtxMinModel.z + g_Model[nCntModel].Pos.z - pPlayer->size.z;
								if (g_Model[nCntModel].nTypeModel == 10)
								{
									g_Model[nCntModel].bUse = false;
									pPlayer->bClearFlag1 = true;
									PlaySound(SOUND_LABEL_SE_KEYGET);
								}
								if (g_Model[nCntModel].nTypeModel == 19)
								{
									g_Model[nCntModel].bUse = false;
									pPlayer->bClearFlag2 = true;
									PlaySound(SOUND_LABEL_SE_KEYGET);
								}
								if (g_Model[nCntModel].nTypeModel == 20)
								{
									if (pPlayer->bClearFlag1 == true && pPlayer->bClearFlag2 == true)
									{
										pPlayer->bPlayerCrear = true;
									}
								}
								move->z = 0.0f;
							}
							//��
							else if (pPos->z + pPlayer->size.z < g_Model[nCntModel].vtxMaxModel.z + g_Model[nCntModel].Pos.z&&
								pPosOld->z + pPlayer->size.z > g_Model[nCntModel].vtxMaxModel.z + g_Model[nCntModel].Pos.z)
							{
								pPos->z = g_Model[nCntModel].vtxMaxModel.z + g_Model[nCntModel].Pos.z + pPlayer->size.z;
								if (g_Model[nCntModel].nTypeModel == 10)
								{
									g_Model[nCntModel].bUse = false;
									pPlayer->bClearFlag1 = true;
									PlaySound(SOUND_LABEL_SE_KEYGET);
								}
								if (g_Model[nCntModel].nTypeModel == 19)
								{
									g_Model[nCntModel].bUse = false;
									pPlayer->bClearFlag2 = true;
									PlaySound(SOUND_LABEL_SE_KEYGET);
								}
								if (g_Model[nCntModel].nTypeModel == 20)
								{
									if (pPlayer->bClearFlag1 == true && pPlayer->bClearFlag2 == true)
									{
										pPlayer->bPlayerCrear = true;
									}
								}
								//�e�̃Z�b�g
								move->z = 0.0f;
							}
						}
					}
					if (pPos->z + pPlayer->size.z <g_Model[nCntModel].vtxMaxModel.z + g_Model[nCntModel].Pos.z &&
						pPos->z - pPlayer->size.z >g_Model[nCntModel].vtxMinModel.z + g_Model[nCntModel].Pos.z)
					{
						if (pPos->x + pPlayer->size.x <g_Model[nCntModel].vtxMaxModel.x + g_Model[nCntModel].Pos.x&&
							pPos->x + pPlayer->size.x >g_Model[nCntModel].vtxMinModel.x + g_Model[nCntModel].Pos.x)
						{
							//��̓����蔻�菈��
							if (pPosOld->y + pPlayer->size.y > g_Model[nCntModel].vtxMinModel.y + g_Model[nCntModel].Pos.y &&
								pPos->y + pPlayer->size.y < g_Model[nCntModel].vtxMaxModel.y + g_Model[nCntModel].Pos.y)
							{
								bLand = true;
								*ppModelRet = &g_Model[nCntModel];
								pPos->y = g_Model[nCntModel].Pos.y - pPlayer->size.y + g_Model[nCntModel].vtxMaxModel.y;

								if (g_Model[nCntModel].nTypeModel == 5)
								{
									if (GetKeyboardPress(DIK_J) || GetJoypadTrigger(0, JOYPADKEY_X))
									{
										pPlayer->pos = D3DXVECTOR3(4200.0f, 1000.0f, 0.0f);
									}
								}

								if (g_Model[nCntModel].nTypeModel == 6)
								{
									if (GetKeyboardPress(DIK_J) || GetJoypadTrigger(0, JOYPADKEY_X))
									{
										pPlayer->pos = D3DXVECTOR3(-4400.0f, 1000.0f, 0.0f);
									}
								}
								if (g_Model[nCntModel].nTypeModel == 11)
								{
									if (GetKeyboardPress(DIK_J) || GetJoypadTrigger(0, JOYPADKEY_X))
									{
										pPlayer->pos = D3DXVECTOR3(-1200, 1000.0f, 0.0f);
									}
								}

								if (g_Model[nCntModel].nTypeModel == 12)
								{
									if (GetKeyboardPress(DIK_J) || GetJoypadTrigger(0, JOYPADKEY_X))
									{
										pPlayer->pos = D3DXVECTOR3(1200, 1000.0f, 0.0f);
									}
								}
							}
						}
					}
				}
			}
		}
	return bLand;
}

//=======================================================================================
// ���f���̓����蔻��
//=======================================================================================
bool ColisionShadow(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * move, MODEL**ppModelRet)
{
	bool bLand = false;

	//�v���C���[�̎擾
	PLAYER * pPlayer;
	pPlayer = GetPlayer();

	for (int nCntModel = 0; nCntModel < g_Model[nCntModel].MaxModel; nCntModel++)
	{
		if (g_Model[nCntModel].bUse)
		{
			if (pPos->z + pPlayer->size.z <g_Model[nCntModel].vtxMaxModel.z + g_Model[nCntModel].Pos.z &&
				pPos->z + pPlayer->size.z >g_Model[nCntModel].vtxMinModel.z + g_Model[nCntModel].Pos.z&&
				pPos->x + pPlayer->size.x <g_Model[nCntModel].vtxMaxModel.x + g_Model[nCntModel].Pos.x&&
				pPos->x + pPlayer->size.x >g_Model[nCntModel].vtxMinModel.x + g_Model[nCntModel].Pos.x)
			{
					bLand = true;
					g_Model[nCntModel].fDistance = pPos->y - g_Model[nCntModel].vtxMaxModel.y;
					*ppModelRet = &g_Model[nCntModel];
		
			}
		}
	}
	
	for (int nCntModel = 0; nCntModel < g_Model[nCntModel].MaxModel; nCntModel+=2)
	{
		if (g_Model[nCntModel].bUse)
		{
			if (pPos->z + pPlayer->size.z <g_Model[nCntModel].vtxMaxModel.z + g_Model[nCntModel].Pos.z &&
				pPos->z + pPlayer->size.z >g_Model[nCntModel].vtxMinModel.z + g_Model[nCntModel].Pos.z&&
				pPos->x + pPlayer->size.x <g_Model[nCntModel].vtxMaxModel.x + g_Model[nCntModel].Pos.x&&
				pPos->x + pPlayer->size.x >g_Model[nCntModel].vtxMinModel.x + g_Model[nCntModel].Pos.x)
			{
				bLand = true;
				g_Model[nCntModel].fDistance = pPos->y - g_Model[nCntModel].vtxMaxModel.y;
				*ppModelRet = &g_Model[nCntModel];
			}
		}
	}
	return bLand;
}

//===============================================================================
// ���f���̓ǂݍ���
//===============================================================================
void LoadModelText(void)
{
	//�ǂݍ��񂾃��f���̏��̏�����
	for (int nCntPlayer = 0; nCntPlayer < g_Model[nCntPlayer].MaxModel; nCntPlayer++)
	{
		for (int nText = 0; nText < MAX_CHARMODEL; nText++)
		{
			g_LoadModel[nCntPlayer].pXFileName[nText] = NULL;		//�t�@�C����
		}
		g_LoadModel[nCntPlayer].pMeshModel = NULL;						//���b�V�����ւ̃|�C���^
		g_LoadModel[nCntPlayer].pBuffMatModel = NULL;					//�}�e���A�����ւ̃|�C���^
		g_LoadModel[nCntPlayer].NumMatModel = 0;						//�}�e���A���̐�
		g_LoadModel[nCntPlayer].pTextureModel = NULL;					//�e�N�X�`���ւ̃|�C���^
	}

	//#if 1
	// ���[�J���ϐ��錾
	FILE *pFile;				// �t�@�C���̃|�C���^
	char ReadText[256];			// �ǂݍ��񂾕���������Ă���
	char HeadText[256];			// ��r�p
	char DustBox[256];			// �g�p���Ȃ����̂����Ă���
	int nCntText = 0;			// ���f���t�@�C����
	int nCntModel = 0;			// ���f����

	// �t�@�C���I�[�v��
	pFile = fopen(MODEL_FILE, "r");		// �t�@�C�����J��[�ǂݍ��݌^]

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

				}
				if (strcmp(HeadText, "NUM_MODEL") == 0)
				{// �ǂݍ��ރ��f���̍ő吔
					sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &g_Model[nCntModel].nLoad);
				}
				else if (strcmp(HeadText, "MODEL_FILENAME") == 0)
				{// ���f���t�@�C����
					if (g_Model[nCntModel].nLoad > nCntText)
					{// �ő吔�ȏ㏈�����Ȃ�
						sscanf(ReadText, "%s %c %s", &DustBox, &DustBox, &g_LoadModel[nCntText].pXFileName[0]);
						nCntText++;
					}
				}
				else if (strcmp(HeadText, "MODELSET") == 0)
				{//--- �L�����N�^�[��� ---//
					while (strcmp(HeadText, "END_MODELSET") != 0)
					{// "END_CHARACTERSET" ���ǂݎ���܂ŌJ��Ԃ��������ǂݎ��
						// ���f���̔z�u���
						fgets(ReadText, sizeof(ReadText), pFile);
						sscanf(ReadText, "%s", &HeadText);

						if (strcmp(HeadText, "\n") == 0)
						{// ������̐擪�� [\n](���s) �̏ꍇ�������Ȃ�
							int nCnt = 0;
						}
						else if (strcmp(HeadText, "NUM_PARTS") == 0)
						{// �v���C���[�P�̂ɑ΂��郂�f���̎g�p��
							sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &g_Model[nCntModel].MaxModel);
						}

						if (strcmp(HeadText, "PARTSSET") == 0)
						{
							if (g_Model[nCntModel].MaxModel > nCntModel)
							{
								while (strcmp(HeadText, "END_PARTSSET") != 0)
								{// "END_PARTSSET" ���ǂݎ���܂ŌJ��Ԃ��������ǂݎ��
									fgets(ReadText, sizeof(ReadText), pFile);
									sscanf(ReadText, "%s", &HeadText);

									if (strcmp(HeadText, "POS") == 0)
									{// �ʒu
										sscanf(ReadText, "%s %c %f %f %f", &DustBox, &DustBox,
											&g_Model[nCntModel].Pos.x,
											&g_Model[nCntModel].Pos.y,
											&g_Model[nCntModel].Pos.z);
									}
									else if (strcmp(HeadText, "ROT") == 0)
									{// ����
										sscanf(ReadText, "%s %c %f %f %f", &DustBox, &DustBox,
											&g_Model[nCntModel].rot.x,
											&g_Model[nCntModel].rot.y,
											&g_Model[nCntModel].rot.z);
									}
									else if (strcmp(HeadText, "TYPE") == 0)
									{// ����
										sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &g_Model[nCntModel].nTypeModel);
									}

									g_Model[nCntModel].bUse = true;

									if (g_Model[nCntModel].nTypeModel == 24)
									{
										g_Model[nCntModel].bUse = false;
									}
								}
								nCntModel++;		// ���f������i�߂�
							}
						}
					}
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
// ���f���̓ǂݍ���
//===============================================================================
void CrearModel(void)
{
	//�v���C���[�̎擾
	PLAYER * pPlayer;
	pPlayer = GetPlayer();

	g_nCntCrear = 0;

	for (int nCntModel = 0; nCntModel < g_Model[nCntModel].MaxModel; nCntModel++)
	{
		if (pPlayer->bPlayerCrear == true)
		{
			PlaySound(SOUND_LABEL_SE_CLEAR);
			g_nCntCrear++;
			if (g_Model[nCntModel].nTypeModel == 21)
			{
				g_Model[nCntModel].rot.z = -0.8f;
			}

			if (g_Model[nCntModel].nTypeModel == 24)
			{
				g_Model[nCntModel].bUse = true;
			}

			if (GetMode() == MODE_GAME)
			{
				SetGameText(D3DXVECTOR3(670.0f, 600.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 400, 200, 6);
			}

			if (g_nCntCrear >= 30)
			{

					SetGameState(GAMESTATE_END);
					//�v���C���[�̏���������
					InitPlayer();

			}
		}
	}

}