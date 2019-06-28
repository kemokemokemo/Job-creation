//=============================================================================
//
// �|���S������ [bullet.h]
// Author : 
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �e�̍\����
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;					//�|�W�V����
	D3DXVECTOR3 rot;					//�ړ�
	D3DXMATRIX  mtxWorldWall;			//���[���h�}�g���b�N�X
	bool		bUse;					//�g�p���Ă��邩�ǂ���
	int			hIdxShadow;				//
	int         Life;					//�e�̎���
} BULLET;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);

void SetBullet(D3DXVECTOR3 pos,D3DXVECTOR3 rot);
BULLET *GetBullet(void);
#endif