//=============================================================================
//
// ���f������ [model.h]
// Author : 
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_MODEL		(46)//�\�����郂�f���̍ő吔
#define MAX_MODELTYPE	(26)//�ǂݍ��ރ��f���̍ő吔
#define MAX_CHARMODEL	(40)

//=============================================================================
// �\���̒�`
//=============================================================================
//�ǂݍ��񂾃��f���̍\����
typedef struct
{
	char				pXFileName[MAX_CHARMODEL];	// �t�@�C����
	LPD3DXMESH			pMeshModel;					// ���b�V�����
	LPD3DXBUFFER		pBuffMatModel;				// �}�e���A�����ւ̃|�C���g
	DWORD				NumMatModel;				// �}�e���A���̐�
	LPDIRECT3DTEXTURE9	*pTextureModel;				// �e�N�X�`���ւ̃|�C���g
}LOADMODEL;

typedef struct
{
	D3DXVECTOR3 Pos;								//�|���S���̈ʒu
	D3DXVECTOR3 Posold;								//�O��ʒu
	D3DXVECTOR3 move;								//�|���S���̈ړ�
	D3DXVECTOR3 scale;								//�|���S���̊g��,�k��
	D3DXVECTOR3 rot;								//�|���S���̌���
	D3DXVECTOR3 Diffrot;							//�|���S���̌���
	D3DXMATRIX mtxWorldModel;						//���[���h�}�g���b�N
	D3DXVECTOR3 vtxMaxModel;						//X�t�@�C���̍ő�l�擾
	D3DXVECTOR3 vtxMinModel;						//X�t�@�C���̍ŏ��l�擾
	float fRadius;									// ���a
	float fHeight;									// ����
	float fDistance;
	int hIdxShadow;									//�e�̐ݒ�
	int bUse;										//�g���Ă��邩�ǂ���
	int nTypeTex;									//�e�N�X�`��
	int nTypeModel;									//���f��
	int nLoad;										// �ǂݍ��ރ��f���̐�
	int MaxModel;									// �g�p���郂�f���̐�
}MODEL;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
MODEL *GetModel(void);

bool ColisionModel(
	D3DXVECTOR3 * pPos,
	D3DXVECTOR3 * pPosOld,
	D3DXVECTOR3 * move,
	MODEL**ppModelRet);

bool ColisionShadow(
	D3DXVECTOR3 * pPos,
	D3DXVECTOR3 * pPosOld,
	D3DXVECTOR3 * move,
	MODEL**ppModelRet);

void LoadModelText(void);
void CrearModel(void);
#endif