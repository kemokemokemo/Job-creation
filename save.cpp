// ====================================================================================================
//
// �Z�[�u���� [save.cpp]
// Author : Kimura kouta
//
// ====================================================================================================
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>              // ��ʓI�ȃw�b�_�[
#include "save.h"
#include "road.h"
#include "model.h"

// ====================================================================================================
//
// �}�N����`
//
// ====================================================================================================
#define	TEXTURE_SAVE		"DATA/TEX/number001.png"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define SAVE_SIZE (20)										// �Z�[�u�{�[�h�̑傫��
#define SAVE_MAX (10)										// ���l
#define SAVE_DATE (5)										// �Z�[�u��
#define SAVE_FILE_NAME ("text.txt")							// �Z�[�u�t�@�C��

// ====================================================================================================
//
// �v���g�^�C�v�錾
//
// ====================================================================================================

// ====================================================================================================
//
// �O���[�o���ϐ��錾
//
// ====================================================================================================
SAVE					g_aSave[5];				// �Z�[�u�ϐ�

char g_cComment1[8];
char g_cComment2[64];
char g_cComment3[8];

// ====================================================================================================
//
// ����������
//
// ====================================================================================================
void InitSave(void)
{
	int nCntSave;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (nCntSave = 0; nCntSave < SAVE_DATE; nCntSave++)
	{
		g_aSave[nCntSave].aName[nCntSave];
		g_aSave[nCntSave].nPoint = 0;
	}

	strcpy(g_cComment1, "#\n");
	strcpy(g_cComment2, "#=========================================================\n");
	strcpy(g_cComment3, "\n");
}

// ====================================================================================================
//
// �Z�[�u�֐�
//
// ====================================================================================================
void SaveData(int nPoint)
{
	// �t�@�C���|�C���g
	FILE *pFile;
	int aDate[6] = {};
	int nDate;
	int nCntSave;
	int nCntNum;

	ROAD *pLoad;

	pLoad = GetLoad();

	for (nCntSave = 0; nCntSave < SAVE_DATE; nCntSave++, pLoad++)
	{
		g_aSave[nCntSave].nPoint = pLoad->nPoint;
		aDate[nCntSave] = g_aSave[nCntSave].nPoint;
	}
	aDate[5] = nPoint;

	for (nCntSave = 0; nCntSave < SAVE_DATE + 1; nCntSave++)
	{
		for (nCntNum = nCntSave + 1; nCntNum < SAVE_DATE + 1; nCntNum++)
		{
			if (aDate[nCntSave] < aDate[nCntNum])
			{
				nDate = aDate[nCntNum];
				aDate[nCntNum] = aDate[nCntSave];
				aDate[nCntSave] = nDate;
			}
		}
	}

	// �t�@�C��
	pFile = fopen(SAVE_FILE_NAME, "w");

	// �J����
	if (pFile != NULL)
	{
		for (nCntSave = 0; nCntSave < SAVE_DATE; nCntSave++)
		{
			fprintf(pFile, "%d\n\n", aDate[nCntSave]);	// �|�C���g
		}
		// �t�@�C����
		fclose(pFile);
	}

	// �J���Ȃ�
	else
	{
		printf("�J���܂���ł���\n");
	}
}
// ====================================================================================================
//
// �Z�[�u�f�[�^�擾�֐�
//
// ====================================================================================================
void SaveModel(void)
{
	//�t�@�C���|�C���g
	FILE *pFile;

	//�ϐ��錾
	int nCntLoad = 0;			//���[�h�J�E���g
	char cHeadText[128];		//����p
	char cWriteText[128];		//�����Ƃ��Ă̏������ݗp
	char cEqual[8] = { "=" };	//�C�R�[���p

	//���f���̃|�C���^
	MODEL *pModel;
	pModel = GetModel();

	//�t�@�C���J��
	pFile = fopen("DATA/road/road.txt", " w");
	
	//�J����
	if (pFile != NULL)
	{
		//�u���b�N�R�����g
		fputs(g_cComment2, pFile);
		//�R�����g���s
		fputs(g_cComment1, pFile);

		strcpy(cHeadText, "# ���[�h���f��\n");
		fputs(cHeadText, pFile);

		strcpy(cHeadText, "# Author : Kimura Kouta\n");
		fputs(cHeadText, pFile);

		//�R�����g���s
		fputs(g_cComment1, pFile);

		//�u���b�N�R�����g
		fputs(g_cComment2, pFile);

		//���s
		fputs(g_cComment3, pFile);

		//���f���̏��//

		//�X�N���v�g
		strcpy(cHeadText, "SCRIPT");

		fputs(cHeadText, pFile);

		//���s
		fputs(g_cComment3, pFile);

		//�X�N���v�g
		if (strcmp(cHeadText, "SCRIPT") == 0)
		{
			//�G���h�X�N���v�g���ʂ�܂Ń��[�v
			while (strcmp(cHeadText, "END_SCRIPT") != 0)
			{
				if (pModel->bUse)
				{
					//���f���Z�b�g
					strcpy(cHeadText, "MODELSET\n");
					sprintf(cWriteText, "    %s", &cHeadText);
					fputs(cWriteText, pFile);

					//�G���h���f�����ł���܂Ń��[�v
					while (strcmp(cHeadText, "END_MODELSET") != 0)
					{
						//�J�E���g
						switch (nCntLoad)
						{
							//�|�W�V����
						case 0:
							strcpy(cHeadText, "pos");
							sprintf(cWriteText, "        %s %s %0.1f %0.1f %0.1f", &cHeadText, &cEqual, pModel->Pos.x, pModel->Pos.y, pModel->Pos.z);
							fputs(cWriteText, pFile);
							fputs(g_cComment3, pFile);

							//�J�E���g�A�b�v
							nCntLoad++;
							break;

							//��]��
						case 1:
							strcpy(cHeadText, "rot");
							sprintf(cWriteText, "        %s %s %0.1f %0.1f %0.1f", &cHeadText, &cEqual, pModel->rot.x, pModel->rot.y, pModel->rot.z);
							fputs(cWriteText, pFile);
							fputs(g_cComment3, pFile);

							//�J�E���g�A�b�v
							nCntLoad++;
							break;

						case 2:
							strcpy(cHeadText, "nType");
							sprintf(cWriteText, "        %s %s %d", &cHeadText, &cEqual, pModel->nTypeModel);
							fputs(cWriteText, pFile);
							fputs(g_cComment3, pFile);

							//�G���h���f���Z�b�g
							strcpy(cHeadText, "END_MODELSET");
							sprintf(cWriteText, "    %s", &cHeadText);
							fputs(cWriteText, pFile);
							fputs(g_cComment3, pFile);

							//�J�E���g�̏�����
							nCntLoad = 0;
							break;
						}
					}
				}
				//�G���h�X�N���v�g
				else
				{
					strcpy(cHeadText, "END_SCRIPT");
					fputs(cHeadText, pFile);
				}
				//���f���̍X�V
				pModel++;
			}
		}
		//���f���̏��I��
		fclose(pFile);
	}
	//�t�@�C�����J���Ȃ�����
	else
	{
		printf("�J���܂���ł���");
	}
}

// ====================================================================================================
//
// �Z�[�u�f�[�^�擾�֐�
//
// ====================================================================================================
SAVE *GetSave(void)
{
	return &g_aSave[0];
}
