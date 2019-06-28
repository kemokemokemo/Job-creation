//=============================================================================
//
// �e�L�X�g���� [Text.h]
// Author :  Kimura Kouta
//
//=============================================================================
#ifndef _GAMETEXT_H_
#define _GAMETEXT_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_GAMETEXT (20)


//=============================================================================
// �\���̒�`
//=============================================================================
typedef enum
{
	GAMETEXTTYPE_TITLELOG = 0,
	GAMETEXTTYPE_MAX,

} GAMETEXTTYPE;
typedef struct
{
	D3DXVECTOR3 pos;				// �ʒu
	D3DXVECTOR3 move;				// �ړ���
	D3DXCOLOR col;					//�F�̕ύX
	int nType;						// �G�̎��
	int sizex;
	int sizey;
	bool bUse;						// ���񂾂��ǂ���
	bool bAlfa;
}GAMETEXT;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitGameText(void);
void UninitGameText(void);
void UpdateGameText(void);
void DrawGameText(void);

void SetGameText(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col,int sizex,int sizey, int nType);
GAMETEXT *GetGameText(void);
#endif
