//-----------------------------------------------------------------------------
//
// �|�[�Y
//
//-----------------------------------------------------------------------------
#ifndef _PAUSE_H_
#define _PAUSE_H_

#define _CRT_SECURE_NO_WARNINGS

//-----------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include	"main.h"	//�C���N���[�h�t�@�C�� 

//----------------------------------------------------------------------------
//�v���g�^�C�v�錾
//----------------------------------------------------------------------------
void InitPause(void);		//�|�[�Y�̏���������
void UninitPause(void);		//�|�[�Y�̏I������
void UpdatePause(void);		//�|�[�Y�̍X�V����
void DrawPause(void);		//�|�[�Y�̕`�揈��
void SetPause(D3DXVECTOR3 pos, D3DXCOLOR col, int nType, float fWidth, float fHeight);
#endif