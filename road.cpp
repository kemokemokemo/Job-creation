// ====================================================================================================
//
// ���[�h���� [road.cpp]
// Author : Kimura kouta
//
// ====================================================================================================
#include "road.h"
#include <stdio.h>              // ��ʓI�ȃw�b�_�[
#include "model.h"

// ====================================================================================================
//
// �}�N����`
//
// ====================================================================================================
#define	TEXTURE_ROAD		"DATA/TEX/number001.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define ROAD_SIZE (20)								// ���[�h�{�[�h�̑傫��
#define ROAD_MAX (10)								// ���l
#define ROAD_DATE (5)										// ���[�h��
#define SAVE_FILE_NAME ("text.txt") // �Z�[�u�t�@�C��

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
ROAD					g_aLoad[5];				// ���[�h�ϐ�

// ====================================================================================================
//
// ����������
//
// ====================================================================================================
void InitLoad(void)
{
	int nCntLoad;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (nCntLoad = 0; nCntLoad < ROAD_DATE; nCntLoad++)
	{
		g_aLoad[nCntLoad].aName[nCntLoad];
		g_aLoad[nCntLoad].nPoint = 0;
	}

	LoadData();
}

// ====================================================================================================
//
// ���[�h�f�[�^�擾�֐�
//
// ====================================================================================================
ROAD *GetLoad(void)
{
	return &g_aLoad[0];
}

// ====================================================================================================
//
// ���[�h�֐�
//
// ====================================================================================================
void LoadData(void)
{
	// �t�@�C���|�C���g
	FILE *pFile;

	int nCntLoad;

	// �t�@�C���J
	pFile = fopen(SAVE_FILE_NAME, "r");

	// �J����
	if (pFile != NULL)
	{
		for (nCntLoad = 0; nCntLoad < ROAD_DATE; nCntLoad++)
		{
			fscanf(pFile, "%d", &g_aLoad[nCntLoad].nPoint); // ���O
		}
		// �t�@�C��
		fclose(pFile);
	}

	// �J���Ȃ�
	else
	{
		printf("�J����܂���ł���\n");
	}
}

// ====================================================================================================
//
// ���[�h�֐�
//
// ====================================================================================================
void LoadObject(void)
{
	//FILE *pFile;

	//char cReadText[128];
	//char cHeadText[128];
	//char cDieText[128];

	//MODEL *pModel;
	//pModel = GetModel();

	//pFile = fopen("DATA/road/road.txt", " r");

	//if (pFile !=NULL)
	//{
	//	//�X�N���v�g������܂�
	//	/*strcmp�͓ǂݍ��񂾕����Ǝw�肳��Ă��镶�����r*/
	//	while (strcmp(cHeadText,"SCRIPT")!=0)
	//	{
	//		//fgets�͈ꕶ������ǂݎ��
	//		fgets(cReadText, sizeof(cReadText), pFile);
	//		//cRead��ǂݍ���,cHead�ɑ��
	//		//sscanf�͕��������
	//		sscanf(cReadText, "%s", &cHeadText);
	//	}
	//	if (strcmp(cHeadText,"SCRIPT")==0)
	//	{
	//		while (strcmp(cHeadText, "END_SCRIPT") != 0)
	//		{
	//			fgets(cReadText, sizeof(cReadText), pFile);
	//			sscanf(cReadText, "%s", &cHeadText);
	//			//���s
	//			if (strcmp(cHeadText, "\n") == 0)
	//			{
	//			}
	//				//���f���Z�b�g��������
	//				if (strcmp(cHeadText, "MODELSET") == 0)
	//				{			
	//					while (strcmp(cHeadText, "END_MODELSET")!=0)
	//					{
	//						fgets(cReadText, sizeof(cReadText), pFile);
	//						sscanf(cReadText, "%s", cHeadText);

	//						if (strcmp(cHeadText, "pos") == 0)
	//						{
	//							sscanf(cReadText, "%s %s %f %f %f", &cDieText, &cDieText, &pModel->Pos.x, &pModel->Pos.y, &pModel->Pos.z);
	//						}
	//						if (strcmp(cHeadText, "rot") == 0)
	//						{
	//							sscanf(cReadText, "%s %s %f %f %f", &cDieText, &cDieText, &pModel->rot.x, &pModel->rot.y, &pModel->rot.z);
	//						}
	//						if (strcmp(cHeadText, "nType") == 0)
	//						{
	//							sscanf(cReadText, "%s %s %d", &cDieText, &cDieText, &pModel->nTypeModel);

	//							//�g�p���
	//							pModel->bUse = true;
	//							//���f��
	//							pModel++;
	//						}
	//					}
	//				}
	//			}
	//		}
	//	//�t�@�C�����J��
	//	fclose(pFile);
	//}
	////�J���Ȃ�
	//else
	//{
	//	printf("�J���܂���ł���");
	//}
}