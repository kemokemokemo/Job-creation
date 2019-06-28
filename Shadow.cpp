//=============================================================================
//
// �e�̏��� [Shadow.cpp]
// Author : kimura kouta
//
//=============================================================================
#include "Shadow.h"
#include "model.h"
#include "player.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define SHADOW_TEX "DATA/TEX/shadow.jpg"	//�ǂݍ��ރe�N�X�`���t�@�C����
#define MAX_SHADOW	(256)

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void MakeVertexShadow(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// �e�̍\����
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;					//�|�W�V����
	D3DXVECTOR3 rot;					//��]
	D3DXMATRIX mtxWorldSadow;			//���[���h�}�g���b�N�X
	bool		bUse;					//�g�p���Ă��邩�ǂ���
} SHADOW;

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		 g_pTextureShadow = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;		//���_�o�b�t�@�ւ̃|�C���^

SHADOW    g_Shadow[MAX_SHADOW];

//=============================================================================
// ����������
//=============================================================================
void InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	//�ϐ��錾
	int nCntShadow;

	// �\���̂̏����ݒ�
	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		g_Shadow[nCntShadow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Shadow[nCntShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Shadow[nCntShadow].bUse = false;
	}

	MakeVertexShadow(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitShadow(void)
{
	if (g_pTextureShadow !=NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateShadow(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	SHADOW*pShadow;

	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	pShadow = &g_Shadow[0];

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++, pShadow++)
	{
		if (pShadow->bUse)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&pShadow->mtxWorldSadow);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, pShadow->rot.y, pShadow->rot.x, pShadow->rot.z);
			D3DXMatrixMultiply(&pShadow->mtxWorldSadow, &pShadow->mtxWorldSadow, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, pShadow->pos.x, pShadow->pos.y, pShadow->pos.z);
			D3DXMatrixMultiply(&pShadow->mtxWorldSadow, &pShadow->mtxWorldSadow, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &pShadow->mtxWorldSadow);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureShadow);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntShadow, 2);
		}
	}

	//�ʏ�u�����h
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
// �e�̍쐬
//=============================================================================
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//�ϐ��錾
	int nCntShadow;

	// ���_���̍쐬
	VERTEX_3D *pVtx;

	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (!g_Shadow[nCntShadow].bUse)
		{
			g_Shadow[nCntShadow].pos = pos;
			g_Shadow[nCntShadow].rot = rot;
			//�傫������ɒ��_��ݒ�_SIZE�����߂�
			pVtx[0].Pos = D3DXVECTOR3(-20.0f, 0.0f, 20.0f);
			pVtx[1].Pos = D3DXVECTOR3(20.0, 0.0f, 20.0f);
			pVtx[2].Pos = D3DXVECTOR3(-20.0f, 0.0f, -20.0f);
			pVtx[3].Pos = D3DXVECTOR3(20.0f, 0.0f, -20.0f);
			g_Shadow[nCntShadow].bUse = true;
			break;
		}
		pVtx += 4;
	}
	g_pVtxBuffShadow->Unlock();
	return nCntShadow;
}

//=============================================================================
// �e�̏���
//=============================================================================
void DeleteShadow(int hIdxShadow)
{
	g_Shadow[hIdxShadow].bUse = false;
}

//=============================================================================
// �e�̃|�W�V�����̐ݒ�
//=============================================================================
void SetPositionShadow(int hIdxShadow, D3DXVECTOR3 pos)
{
	MODEL *pModel;
	pModel = GetModel();

	PLAYER *pPlayer;
	pPlayer = GetPlayer();


	g_Shadow[hIdxShadow].pos = D3DXVECTOR3(pos.x, pos.y, pos.z);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexShadow(LPDIRECT3DDEVICE9 pDevice)
{

	D3DXCreateTextureFromFile(
		pDevice,
		SHADOW_TEX,
		&g_pTextureShadow);

	// ���_���̍쐬
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		//���_���W�̐ݒ�(�E���Őݒ肷��j
		pVtx[0].Pos = D3DXVECTOR3(-10.0f, 0.0f, 10.0f);
		pVtx[1].Pos = D3DXVECTOR3(10.0, 0.0f, 10.0f);
		pVtx[2].Pos = D3DXVECTOR3(-10.0f, 0.0f, -10.0f);
		pVtx[3].Pos = D3DXVECTOR3(10.0f, 0.0f, -10.0f);

		//���_�x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[�̐ݒ�(0�`255�̒l�Őݒ�j
		pVtx[0].Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	g_pVtxBuffShadow->Unlock();
}

