//=============================================================================
//
// ���f������ [model.cpp]
// Author : KIMURA KOUTA
//
//=============================================================================
#include "TutoModel.h"
#include "input.h"
#include "camera.h"
#include "Shadow.h"
#include "bullet.h"
#include "effect.h"
#include "player.h"
#include "Game.h"
#include "fade.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TUTOMODEL_FILE		"DATA/road/TutoModel.txt"					//�t�@�C����

#define SPEED			(0.5f)									//�v���C���[�X�s�[�h

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
TUTOMODEL					 g_TutoModel[MAX_TUTOMODEL];					// �ǂݍ��񂾃��f���̏��
LOADTUTOMODEL				 g_LoadTutoModel[MAX_TUTOMODEL];					// �ǂݍ��񂾃��f���̏��

//=============================================================================
// ����������
//=============================================================================
void InitTutoModel(void)
{
	int nCntModel = 0;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (nCntModel = 0; nCntModel < MAX_TUTOMODEL; nCntModel++)
	{
		// �ʒu�E�����̏����ݒ�
		g_TutoModel[nCntModel].Pos = D3DXVECTOR3(100.0f, 0.0f, 0.0f);
		g_TutoModel[nCntModel].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_TutoModel[nCntModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_TutoModel[nCntModel].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_TutoModel[nCntModel].Diffrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_TutoModel[nCntModel].nTypeTex = 0;
		g_TutoModel[nCntModel].nTypeModel = 0;
		g_TutoModel[nCntModel].bUse = false;
		g_TutoModel[nCntModel].fRadius = 0;
		g_TutoModel[nCntModel].fHeight = 0;
		g_TutoModel[nCntModel].nLoad = MAX_TUTOMODELTYPE;
		g_TutoModel[nCntModel].nMaxModel = MAX_TUTOMODEL;
		g_TutoModel[nCntModel].vtxMinModel = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
		g_TutoModel[nCntModel].vtxMaxModel = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);
	}

	//==============================
	// �t�@�C���ǂݍ���
	//==============================
	LoadTutoModelText();

	for(nCntModel = 0; nCntModel < g_TutoModel[nCntModel].nLoad; nCntModel++)
	{
		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(g_LoadTutoModel[nCntModel].pXFileTutoName,					// �ǂݍ���X�t�@�C����
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_LoadTutoModel[nCntModel].pBuffMatTutoModel,								// �}�e���A�����|�C���^
			NULL,
			&g_LoadTutoModel[nCntModel].NumMatTutoModel,								// �}�e���A�����̐�
			&g_LoadTutoModel[nCntModel].pMeshTutoModel);								// ���b�V�����|�C���g

		//�e�N�X�`���̓ǂݍ���
		D3DXMATERIAL *pMat;															// X�t�@�C��������o�����}�e���A����������

		// X�t�@�C������}�e���A�������擾
		pMat = (D3DXMATERIAL*)g_LoadTutoModel[nCntModel].pBuffMatTutoModel->GetBufferPointer();

		// �e�N�X�`���̃|�C���^���}�e���A�����̐����z��
		g_LoadTutoModel[nCntModel].pTextureTutoModel = new LPDIRECT3DTEXTURE9[(int)g_LoadTutoModel[nCntModel].NumMatTutoModel];	// int�^�ɒ���

		// �擾�����t�@�C���������
		for (int nCntNumMat = 0; nCntNumMat < (int)g_LoadTutoModel[nCntModel].NumMatTutoModel; nCntNumMat++)	// DWORD�^����int�^�ɕϊ�����
		{
			// �e�N�X�`���̃|�C���^������
			g_LoadTutoModel[nCntModel].pTextureTutoModel[nCntNumMat] = NULL;

			// �e�N�X�`���t�@�C�����������Ă���ꍇ�A�ǂݍ���
			if (pMat[nCntNumMat].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFile(pDevice, pMat[nCntNumMat].pTextureFilename,
				&g_LoadTutoModel[nCntModel].pTextureTutoModel[nCntNumMat]);
			}
		}
	}

	//X�t�@�C������ő�l�ƍŏ��l�̐ݒ�
	int nNumVertices;						//���_��
	DWORD sizeFVF;							//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVertexBuffer;					//���_�o�b�t�@�̃|�C���^

	for (nCntModel = 0; nCntModel < g_TutoModel[nCntModel].nMaxModel; nCntModel++)
	{
		//���_�����擾
		nNumVertices = g_LoadTutoModel[g_TutoModel[nCntModel].nTypeModel].pMeshTutoModel->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_LoadTutoModel[g_TutoModel[nCntModel].nTypeModel].pMeshTutoModel->GetFVF());

		//���_�o�b�t�@�����b�N
		g_LoadTutoModel[g_TutoModel[nCntModel].nTypeModel].pMeshTutoModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertexBuffer);

		for (int nCntvtx = 0; nCntvtx < nNumVertices; nCntvtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVertexBuffer;

			//���ׂĂ̕ϐ����r���čŏ��E�ő�l�����߂�
			if (g_TutoModel[nCntModel].vtxMinModel.x > vtx.x)
			{
				g_TutoModel[nCntModel].vtxMinModel.x = vtx.x;
			}
			if (g_TutoModel[nCntModel].vtxMaxModel.x < vtx.x)
			{
				g_TutoModel[nCntModel].vtxMaxModel.x = vtx.x;
			}
			if (g_TutoModel[nCntModel].vtxMinModel.y > vtx.y)
			{
				g_TutoModel[nCntModel].vtxMinModel.y = vtx.y;
			}
			if (g_TutoModel[nCntModel].vtxMaxModel.y < vtx.y)
			{
				g_TutoModel[nCntModel].vtxMaxModel.y = vtx.y;
			}
			if (g_TutoModel[nCntModel].vtxMinModel.z > vtx.z)
			{
				g_TutoModel[nCntModel].vtxMinModel.z = vtx.z;
			}
			if (g_TutoModel[nCntModel].vtxMaxModel.z < vtx.z)
			{
				g_TutoModel[nCntModel].vtxMaxModel.z = vtx.z;
			}

			pVertexBuffer += sizeFVF;		//�T�C�Y���|�C���^��i�߂�
		}
		//���_�o�b�t�@�̃A�����b�N
		g_LoadTutoModel[g_TutoModel[nCntModel].nTypeModel].pMeshTutoModel->UnlockVertexBuffer();
	}
}
//=============================================================================
// �I������
//=============================================================================
void UninitTutoModel(void)
{
		for (int nCntModel = 0; nCntModel < g_TutoModel[nCntModel].nMaxModel; nCntModel++)
		{
			// ���b�V���̊J��
			if (g_LoadTutoModel[g_TutoModel[nCntModel].nTypeModel].pMeshTutoModel != NULL)
			{
				g_LoadTutoModel[g_TutoModel[nCntModel].nTypeModel].pMeshTutoModel->Release();
				g_LoadTutoModel[g_TutoModel[nCntModel].nTypeModel].pMeshTutoModel = NULL;
			}

			// �}�e���A���̊J��
			if (g_LoadTutoModel[g_TutoModel[nCntModel].nTypeModel].pBuffMatTutoModel != NULL)
			{
				g_LoadTutoModel[g_TutoModel[nCntModel].nTypeModel].pBuffMatTutoModel->Release();
				g_LoadTutoModel[g_TutoModel[nCntModel].nTypeModel].pBuffMatTutoModel = NULL;
			}
		}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTutoModel(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTutoModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxSize, mtxRot, mtxTrans;				//�v�Z�p
	D3DXMATERIAL*pMat;
	D3DMATERIAL9 matDef;

	for (int nCntModel = 0; nCntModel < g_TutoModel[nCntModel].nMaxModel; nCntModel++)
	{
		if (g_TutoModel[nCntModel].bUse)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_TutoModel[nCntModel].mtxWorldModel);

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxSize, g_TutoModel[nCntModel].scale.x, g_TutoModel[nCntModel].scale.y, g_TutoModel[nCntModel].scale.z);
			D3DXMatrixMultiply(&g_TutoModel[nCntModel].mtxWorldModel, &g_TutoModel[nCntModel].mtxWorldModel, &mtxSize);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_TutoModel[nCntModel].rot.y, g_TutoModel[nCntModel].rot.x, g_TutoModel[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_TutoModel[nCntModel].mtxWorldModel, &g_TutoModel[nCntModel].mtxWorldModel, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_TutoModel[nCntModel].Pos.x, g_TutoModel[nCntModel].Pos.y, g_TutoModel[nCntModel].Pos.z);
			D3DXMatrixMultiply(&g_TutoModel[nCntModel].mtxWorldModel, &g_TutoModel[nCntModel].mtxWorldModel, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_TutoModel[nCntModel].mtxWorldModel);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A�����ɑ΂���|�C���^���擾
			pMat = (D3DXMATERIAL*)g_LoadTutoModel[g_TutoModel[nCntModel].nTypeModel].pBuffMatTutoModel->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_LoadTutoModel[g_TutoModel[nCntModel].nTypeModel].NumMatTutoModel; nCntMat++)
			{
				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_LoadTutoModel[g_TutoModel[nCntModel].nTypeModel].pTextureTutoModel[nCntMat]);

				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// �`��
				g_LoadTutoModel[g_TutoModel[nCntModel].nTypeModel].pMeshTutoModel->DrawSubset(nCntMat);
			}
		}

		// �}�e���A�����f�t�H���g�ɖ߂�
		pDevice->SetMaterial(&matDef);
	}

}

//============================================================================
// ���f���̎擾
//=============================================================================
TUTOMODEL *GetTutoModel(void)
{
	return &g_TutoModel[0];
}

//=======================================================================================
// ���f���̓����蔻��
//=======================================================================================
bool ColisionTutoModel(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * move, TUTOMODEL**ppTutoModelRet)
{
	bool bLand = false;
	int nCntModel;
	PLAYER * pPlayer;

	//�v���C���[�̎擾
	pPlayer = GetPlayer();

	if (*ppTutoModelRet != NULL)
	{
		*ppTutoModelRet = NULL;
	}

	for (nCntModel = 0; nCntModel < g_TutoModel[nCntModel].nMaxModel; nCntModel++)
	{
		if (g_TutoModel[nCntModel].bUse)
		{
			if (pPos->y + pPlayer->size.y <g_TutoModel[nCntModel].vtxMaxModel.y + g_TutoModel[nCntModel].Pos.y &&
				pPos->y - pPlayer->size.y >g_TutoModel[nCntModel].vtxMinModel.y + g_TutoModel[nCntModel].Pos.y)
			{
				if (pPos->z + pPlayer->size.z <g_TutoModel[nCntModel].vtxMaxModel.z + g_TutoModel[nCntModel].Pos.z &&
					pPos->z - pPlayer->size.z >g_TutoModel[nCntModel].vtxMinModel.z + g_TutoModel[nCntModel].Pos.z)
				{
					//��
					if (pPos->x + pPlayer->size.x > g_TutoModel[nCntModel].vtxMinModel.x + g_TutoModel[nCntModel].Pos.x&&
						pPosOld->x - pPlayer->size.x < g_TutoModel[nCntModel].vtxMinModel.x + g_TutoModel[nCntModel].Pos.x)
					{
						pPos->x = g_TutoModel[nCntModel].vtxMinModel.x + g_TutoModel[nCntModel].Pos.x - pPlayer->size.x;
					}
					//�E
					else if (pPos->x + pPlayer->size.x < g_TutoModel[nCntModel].vtxMaxModel.x + g_TutoModel[nCntModel].Pos.x &&
						pPosOld->x + pPlayer->size.x > g_TutoModel[nCntModel].vtxMaxModel.x + g_TutoModel[nCntModel].Pos.x)
					{
						pPos->x = g_TutoModel[nCntModel].vtxMaxModel.x + g_TutoModel[nCntModel].Pos.x + pPlayer->size.x;
					}
				}
			}
			if (pPos->y + pPlayer->size.y <g_TutoModel[nCntModel].vtxMaxModel.y + g_TutoModel[nCntModel].Pos.y &&
				pPos->y - pPlayer->size.y >g_TutoModel[nCntModel].vtxMinModel.y + g_TutoModel[nCntModel].Pos.y)
			{
				if (pPos->x + pPlayer->size.x <g_TutoModel[nCntModel].vtxMaxModel.x + g_TutoModel[nCntModel].Pos.x&&
					pPos->x + pPlayer->size.x >g_TutoModel[nCntModel].vtxMinModel.x + g_TutoModel[nCntModel].Pos.x)
				{
					//��
					if (pPos->z - pPlayer->size.z > g_TutoModel[nCntModel].vtxMinModel.z + g_TutoModel[nCntModel].Pos.z &&
						pPosOld->z - pPlayer->size.z < g_TutoModel[nCntModel].vtxMinModel.z + g_TutoModel[nCntModel].Pos.z)
					{
						pPos->z = g_TutoModel[nCntModel].vtxMinModel.z + g_TutoModel[nCntModel].Pos.z - pPlayer->size.z;
					}
					//��
					else if (pPos->z + pPlayer->size.z < g_TutoModel[nCntModel].vtxMaxModel.z + g_TutoModel[nCntModel].Pos.z&&
						pPosOld->z + pPlayer->size.z > g_TutoModel[nCntModel].vtxMaxModel.z + g_TutoModel[nCntModel].Pos.z)
					{
						pPos->z = g_TutoModel[nCntModel].vtxMaxModel.z + g_TutoModel[nCntModel].Pos.z + pPlayer->size.z;

					}
				}
			}
			if (pPos->z + pPlayer->size.z <g_TutoModel[nCntModel].vtxMaxModel.z + g_TutoModel[nCntModel].Pos.z &&
				pPos->z - pPlayer->size.z >g_TutoModel[nCntModel].vtxMinModel.z + g_TutoModel[nCntModel].Pos.z)
			{
				if (pPos->x + pPlayer->size.x <g_TutoModel[nCntModel].vtxMaxModel.x + g_TutoModel[nCntModel].Pos.x&&
					pPos->x + pPlayer->size.x >g_TutoModel[nCntModel].vtxMinModel.x + g_TutoModel[nCntModel].Pos.x)
				{
					//��̓����蔻�菈��
					if (pPosOld->y + pPlayer->size.y > g_TutoModel[nCntModel].vtxMinModel.y + g_TutoModel[nCntModel].Pos.y &&
						pPos->y + pPlayer->size.y < g_TutoModel[nCntModel].vtxMaxModel.y + g_TutoModel[nCntModel].Pos.y)
					{
						bLand = true;
						*ppTutoModelRet = &g_TutoModel[nCntModel];
						pPos->y = g_TutoModel[nCntModel].Pos.y - pPlayer->size.y + g_TutoModel[nCntModel].vtxMaxModel.y;
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
bool ColisionTutoShadow(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * move, TUTOMODEL**ppTutoModelRet)
{
	bool bLand = false;

	//�v���C���[�̎擾
	PLAYER * pPlayer;
	pPlayer = GetPlayer();

	if (*ppTutoModelRet != NULL)
	{
		*ppTutoModelRet = NULL;
	}

	for (int nCntModel = 0; nCntModel < g_TutoModel[nCntModel].nMaxModel; nCntModel++)
	{
		if (g_TutoModel[nCntModel].bUse)
		{
			if (pPos->z + pPlayer->size.z <g_TutoModel[nCntModel].vtxMaxModel.z + g_TutoModel[nCntModel].Pos.z &&
				pPos->z + pPlayer->size.z >g_TutoModel[nCntModel].vtxMinModel.z + g_TutoModel[nCntModel].Pos.z&&
				pPos->x + pPlayer->size.x <g_TutoModel[nCntModel].vtxMaxModel.x + g_TutoModel[nCntModel].Pos.x&&
				pPos->x + pPlayer->size.x >g_TutoModel[nCntModel].vtxMinModel.x + g_TutoModel[nCntModel].Pos.x)
			{
				bLand = true;
				*ppTutoModelRet = &g_TutoModel[nCntModel];
			}
		}
	}

	for (int nCntModel = 0; nCntModel < g_TutoModel[nCntModel].nMaxModel; nCntModel += 2)
	{
		if (g_TutoModel[nCntModel].bUse)
		{
			if (pPos->z + pPlayer->size.z <g_TutoModel[nCntModel].vtxMaxModel.z + g_TutoModel[nCntModel].Pos.z &&
				pPos->z + pPlayer->size.z >g_TutoModel[nCntModel].vtxMinModel.z + g_TutoModel[nCntModel].Pos.z&&
				pPos->x + pPlayer->size.x <g_TutoModel[nCntModel].vtxMaxModel.x + g_TutoModel[nCntModel].Pos.x&&
				pPos->x + pPlayer->size.x >g_TutoModel[nCntModel].vtxMinModel.x + g_TutoModel[nCntModel].Pos.x)
			{
				bLand = true;
				*ppTutoModelRet = &g_TutoModel[nCntModel];
			}
		}
	}
	return bLand;
}
//===============================================================================
// �v���C���[�̓ǂݍ���
//===============================================================================
void LoadTutoModelText(void)
{
	//�ǂݍ��񂾃��f���̏��̏�����
	for (int nCntPlayer = 0; nCntPlayer < g_TutoModel[nCntPlayer].nMaxModel; nCntPlayer++)
	{
		for (int nText = 0; nText < MAX_CHARMODEL; nText++)
		{
			g_LoadTutoModel[nCntPlayer].pXFileTutoName[nText] = NULL;		//�t�@�C����
		}
		g_LoadTutoModel[nCntPlayer].pMeshTutoModel = NULL;						//���b�V�����ւ̃|�C���^
		g_LoadTutoModel[nCntPlayer].pBuffMatTutoModel = NULL;					//�}�e���A�����ւ̃|�C���^
		g_LoadTutoModel[nCntPlayer].NumMatTutoModel = 0;						//�}�e���A���̐�
		g_LoadTutoModel[nCntPlayer].pTextureTutoModel = NULL;					//�e�N�X�`���ւ̃|�C���^
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
	pFile = fopen(TUTOMODEL_FILE, "r");		// �t�@�C�����J��[�ǂݍ��݌^]

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
					sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &g_TutoModel[nCntModel].nLoad);
				}
				else if (strcmp(HeadText, "MODEL_FILENAME") == 0)
				{// ���f���t�@�C����
					if (g_TutoModel[nCntModel].nLoad > nCntText)
					{// �ő吔�ȏ㏈�����Ȃ�
						sscanf(ReadText, "%s %c %s", &DustBox, &DustBox, &g_LoadTutoModel[nCntText].pXFileTutoName[0]);
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
							sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &g_TutoModel[nCntModel].nMaxModel);
						}

						if (strcmp(HeadText, "PARTSSET") == 0)
						{
							if (g_TutoModel[nCntModel].nMaxModel > nCntModel)
							{
								while (strcmp(HeadText, "END_PARTSSET") != 0)
								{// "END_PARTSSET" ���ǂݎ���܂ŌJ��Ԃ��������ǂݎ��
									fgets(ReadText, sizeof(ReadText), pFile);
									sscanf(ReadText, "%s", &HeadText);

									if (strcmp(HeadText, "POS") == 0)
									{// �ʒu
										sscanf(ReadText, "%s %c %f %f %f", &DustBox, &DustBox,
											&g_TutoModel[nCntModel].Pos.x,
											&g_TutoModel[nCntModel].Pos.y,
											&g_TutoModel[nCntModel].Pos.z);
									}
									else if (strcmp(HeadText, "ROT") == 0)
									{// ����
										sscanf(ReadText, "%s %c %f %f %f", &DustBox, &DustBox,
											&g_TutoModel[nCntModel].rot.x,
											&g_TutoModel[nCntModel].rot.y,
											&g_TutoModel[nCntModel].rot.z);
									}
									else if (strcmp(HeadText, "TYPE") == 0)
									{// ����
										sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &g_TutoModel[nCntModel].nTypeModel);
									}
									g_TutoModel[nCntModel].bUse = true;
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