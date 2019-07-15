//=============================================================================
//
// �G�t�F�N�g�̏��� [effect.cpp]
// Author : KIMURA KOUTA
//
//=============================================================================
#include "effect.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define	TEXTURE_EFFECT		"DATA/TEX/effect000.jpg"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_EFFECT2		"DATA/TEX/effect001.jpg"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_EFFECT3		"DATA/TEX/efect002.jpg"			// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_EFFECT4		"DATA/TEX/effect003.jpg"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_EFFECT5		"DATA/TEX/effect004.jpg"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_EFFECT6		"DATA/TEX/effect005.jpg"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	MAX_EFFECT			(5000)							// �G�t�F�N�g�̍ő吔

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureEffect[MAX_EFFECT] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;	// ���_�o�b�t�@�ւ̃|�C���^

EFFECT					g_aEffect[MAX_EFFECT];		// �G�t�F�N�g���

//=============================================================================
// ����������
//=============================================================================
void InitEffect(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�ϐ��̏�����
	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		g_aEffect[nCntEffect].fRadius = 50.0f;
		g_aEffect[nCntEffect].nType = 0;
		g_aEffect[nCntEffect].ParticlenType = 0;
		g_aEffect[nCntEffect].nLife = 0;
		g_aEffect[nCntEffect].bUse = false;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_EFFECT,		// �t�@�C���̖��O
		&g_pTextureEffect[0]);	// �ǂݍ��ރ������[

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_EFFECT2,		// �t�@�C���̖��O
		&g_pTextureEffect[1]);	// �ǂݍ��ރ������[

	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_EFFECT3,		// �t�@�C���̖��O
		&g_pTextureEffect[2]);	// �ǂݍ��ރ������[

	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_EFFECT4,		// �t�@�C���̖��O
		&g_pTextureEffect[3]);	// �ǂݍ��ރ������[

	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_EFFECT5,		// �t�@�C���̖��O
		&g_pTextureEffect[4]);	// �ǂݍ��ރ������[

	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_EFFECT5,		// �t�@�C���̖��O
		&g_pTextureEffect[5]);	// �ǂݍ��ރ������[

	// ���_���̍쐬
	MakeVertexEffect(pDevice);

}

//=============================================================================
// �I������
//=============================================================================
void UninitEffect(void)
{
	// �e�N�X�`���̊J��
	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_pTextureEffect[nCntEffect] != NULL)
		{
			g_pTextureEffect[nCntEffect]->Release();
			g_pTextureEffect[nCntEffect] = NULL;
		}
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEffect(void)
{
	//�ϐ��錾
	int nCntEffect = 0;
	int nLife = 0;
	VERTEX_3D *pVtx;


	// ���_���̐ݒ�
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)					 
		{
			g_aEffect[nCntEffect].nLife--;
			g_aEffect[nCntEffect].fRadius -= 3.0f;
			if (g_aEffect[nCntEffect].fRadius <= 0)
			{
				g_aEffect[nCntEffect].fRadius = 0;
			}

			g_aEffect[nCntEffect].pos += g_aEffect[nCntEffect].move;

			if (g_aEffect[nCntEffect].nType == 0)
			{
				//���_���W�̐ݒ�(�E���Őݒ肷��j
				pVtx[0].Pos = D3DXVECTOR3(-2.5f, 2.5f, 0.0f);
				pVtx[1].Pos = D3DXVECTOR3(2.5f, 2.5f, 0.0f);
				pVtx[2].Pos = D3DXVECTOR3(-2.5f, -2.5f, 0.0f);
				pVtx[3].Pos = D3DXVECTOR3(2.5f, -2.5f, 0.0f);
			}

			if (g_aEffect[nCntEffect].nType == 1)
			{
				//���_���W�̐ݒ�(�E���Őݒ肷��j
				pVtx[0].Pos = D3DXVECTOR3(-2.5f, 100.5f, 0.0f);
				pVtx[1].Pos = D3DXVECTOR3(2.5f, 100.5f, 0.0f);
				pVtx[2].Pos = D3DXVECTOR3(-2.5f, -100.5f, 0.0f);
				pVtx[3].Pos = D3DXVECTOR3(2.5f, -100.5f, 0.0f);
			}

			//���_�J���[�̐ݒ�(0�`255�̒l�Őݒ�j
			pVtx[0].Col = g_aEffect[nCntEffect].col, g_aEffect[nCntEffect].col,g_aEffect[nCntEffect].col,g_aEffect[nCntEffect].col;
			pVtx[1].Col = g_aEffect[nCntEffect].col, g_aEffect[nCntEffect].col,g_aEffect[nCntEffect].col,g_aEffect[nCntEffect].col;
			pVtx[2].Col = g_aEffect[nCntEffect].col, g_aEffect[nCntEffect].col,g_aEffect[nCntEffect].col,g_aEffect[nCntEffect].col;
			pVtx[3].Col = g_aEffect[nCntEffect].col, g_aEffect[nCntEffect].col,g_aEffect[nCntEffect].col,g_aEffect[nCntEffect].col;

			if (g_aEffect[nCntEffect].nLife == 0)
			{
				g_aEffect[nCntEffect].bUse = false;
			}

			if (g_aEffect[nCntEffect].pos.y <= 0)
			{
				g_aEffect[nCntEffect].bUse = false;
			}

		}
		pVtx += 4;
	}
	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntEffect = 0;

	D3DXMATRIX mtxrot, mtxTrans, mtxView;				//�v�Z�p�}�g���b�N�X

	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �����_�[�X�e�[�g(���Z��������)
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);				//�A���t�@�u�����h���s��
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	// �|���S���̕`��
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aEffect[nCntEffect].mtxWorldWall);

			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			g_aEffect[nCntEffect].mtxWorldWall._11 = mtxView._11;//X��
			g_aEffect[nCntEffect].mtxWorldWall._12 = mtxView._21;//X��
			g_aEffect[nCntEffect].mtxWorldWall._13 = mtxView._31;//X��
			g_aEffect[nCntEffect].mtxWorldWall._21 = mtxView._12;//Y��
			g_aEffect[nCntEffect].mtxWorldWall._22 = mtxView._22;//Y��
			g_aEffect[nCntEffect].mtxWorldWall._23 = mtxView._32;//Y��

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxrot,
				rot.y,
				rot.x,
				rot.z);
			D3DXMatrixMultiply(&g_aEffect[nCntEffect].mtxWorldWall,
				&g_aEffect[nCntEffect].mtxWorldWall,
				&mtxrot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans,
				g_aEffect[nCntEffect].pos.x,
				g_aEffect[nCntEffect].pos.y,
				g_aEffect[nCntEffect].pos.z);
			D3DXMatrixMultiply(&g_aEffect[nCntEffect].mtxWorldWall,
				&g_aEffect[nCntEffect].mtxWorldWall,
				&mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aEffect[nCntEffect].mtxWorldWall);

			// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureEffect[g_aEffect[nCntEffect].nType]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntEffect, 2);

		}
	}

	// �����_�[�X�e�[�g(�ʏ�u�����h����)
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);				//�A���t�@�u�����h���s��
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

}

//=============================================================================
// ���_�̍쐬
//=============================================================================
void MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D *pVtx;
	int nCntEffect = 0;

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	// ���_���̐ݒ�
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		//���_���W�̐ݒ�(�E���Őݒ肷��j
		pVtx[0].Pos = D3DXVECTOR3(-15.0f, 15.0f, 0.0f);
		pVtx[1].Pos = D3DXVECTOR3(15.0f, 15.0f, 0.0f);
		pVtx[2].Pos = D3DXVECTOR3(-15.0f, -15.0f, 0.0f);
		pVtx[3].Pos = D3DXVECTOR3(15.0f, -15.0f, 0.0f);

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

		//�e�N�X�`���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}

//=============================================================================
// �G�t�F�N�g�ݒ�
//=============================================================================
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, int nLife,int nType)
{
	//�ϐ��錾
	int nCntEffect;
	VERTEX_3D *pVtx;

	// ���_���̐ݒ�
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == false)
		{
			g_aEffect[nCntEffect].pos = pos;
			g_aEffect[nCntEffect].move = move;
			g_aEffect[nCntEffect].col = col;
			g_aEffect[nCntEffect].nType = nType;
			g_aEffect[nCntEffect].fRadius = fRadius;
			g_aEffect[nCntEffect].nLife = nLife;
			g_aEffect[nCntEffect].bUse = true;
			break;
		}
		pVtx += 4;
	}
	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}

//=============================================================================
// �p�[�e�B�N���ݒ�
//=============================================================================
void SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, int nLife, int nType)
{
	int nCntParticle;
	VERTEX_3D *pVtx;

	// ���_���̐ݒ�
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntParticle = 0; nCntParticle < MAX_EFFECT; nCntParticle++)
	{
		if (g_aEffect[nCntParticle].bUse == false)
		{
			g_aEffect[nCntParticle].pos = pos;
			g_aEffect[nCntParticle].move = move;
			g_aEffect[nCntParticle].col = col;
			g_aEffect[nCntParticle].nType = nType;
			g_aEffect[nCntParticle].fRadius = fRadius;
			g_aEffect[nCntParticle].nLife = nLife;
			g_aEffect[nCntParticle].bUse = true;
			break;
		}
		pVtx += 4;
	}
	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}
