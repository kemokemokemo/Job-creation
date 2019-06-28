//=============================================================================
//
// �G�t�F�N�g�̏��� [effect.h]
// Author : KIMURA KOUTA
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 move;		// �ړ�
	D3DXMATRIX  mtxWorldWall;			//���[���h�}�g���b�N�X
	D3DXCOLOR col;			// �F
	float fRadius;			// ���a
	int nLife;				// ���C�t
	int nType;
	int ParticlenType;
	bool bUse;				// �g�p���Ă��邩�ǂ���
} EFFECT;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);

void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, int nLife,int nType);
void SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, int nLife, int nType);

#endif
