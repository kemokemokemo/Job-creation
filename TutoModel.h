//=============================================================================
//
// ���f������ [TutoModel.h]
// Author : kimura kouta
//
//=============================================================================
#ifndef _TUTOMODEL_H_
#define _TUTOMODEL_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_TUTOMODEL		(7)//�\�����郂�f���̍ő吔
#define MAX_TUTOMODELTYPE	(6)//�ǂݍ��ރ��f���̍ő吔
#define MAX_TUTOCHARMODEL	(40)

//=============================================================================
// �\���̒�`
//=============================================================================
//�ǂݍ��񂾃��f���̍\����
typedef struct
{
	char				pXFileTutoName[MAX_TUTOCHARMODEL];	// �t�@�C����
	LPD3DXMESH			pMeshTutoModel;					// ���b�V�����
	LPD3DXBUFFER		pBuffMatTutoModel;				// �}�e���A�����ւ̃|�C���g
	DWORD				NumMatTutoModel;				// �}�e���A���̐�
	LPDIRECT3DTEXTURE9	*pTextureTutoModel;				// �e�N�X�`���ւ̃|�C���g
}LOADTUTOMODEL;

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
	int hIdxShadow;									//�e�̐ݒ�
	int bUse;										//�g���Ă��邩�ǂ���
	int nTypeTex;									//�e�N�X�`��
	int nTypeModel;									//���f��
	int nLoad;										// �ǂݍ��ރ��f���̐�
	int nMaxModel;									// �g�p���郂�f���̐�
}TUTOMODEL;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitTutoModel(void);
void UninitTutoModel(void);
void UpdateTutoModel(void);
void DrawTutoModel(void);
TUTOMODEL *GetTutoModel(void);

bool ColisionTutoModel(
	D3DXVECTOR3 * pPos,
	D3DXVECTOR3 * pPosOld,
	D3DXVECTOR3 * move,
	TUTOMODEL**ppTutoModelRet);

bool ColisionTutoShadow(
	D3DXVECTOR3 * pPos,
	D3DXVECTOR3 * pPosOld,
	D3DXVECTOR3 * move,
	TUTOMODEL**ppTutoModelRet);


void LoadTutoModelText(void);
#endif