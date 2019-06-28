//=============================================================================
//
// �Z�[�u���� [save.h]
// Author :  Kimura Kouta
//
//=============================================================================
#ifndef _SAVE_H_
#define _SAVE_H_

//=============================================================================
//
// �C���N���[�h�t�@�C��
//
//=============================================================================
#include "main.h"

//=============================================================================
//
// �\���̒�`
//
//=============================================================================
typedef struct
{
	char aName[128];
	int nPoint;
} SAVE;

//=============================================================================
//
// �v���g�^�C�v�錾
//
//=============================================================================
void InitSave(void);
void SaveData(int nPoint);   // �Z�[�u�֐�

//�Z�[�u���f��
void SaveModel(void);
SAVE *GetSave(void);
#endif