//=============================================================================
//
// �������� [Explosion.cpp]
// Author : Kimura Kouta
//
//=============================================================================
#include "Explosion.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_EXPLOSION (128)								// ���˂ł���e�̍ő吔
#define EXPLOSION_TEX "DATA/TEX/explosion000.png"		//�ǂݍ��ރe�N�X�`���t�@�C����
#define EXPLOSION_SIZE_X	 (100)						//�|���S���̃T�C�Y(����)
#define EXPLOSION_SIZE_Y	 (100)						//�|���S���̃T�C�Y(����)
#define EXPLOSIONCOLOR_TEX   (255)
#define EXPLOSIONALPA_TEX    (255)

//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;				// �ʒu
	D3DXCOLOR   col;				// �F
	D3DXMATRIX  mtxWorldWall;			//���[���h�}�g���b�N�X
	bool bUse;						// �g�p���Ă��邩�ǂ���
	int nCounteAnim;
	int nPatternAnim;
	
}EXPLOSION;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureExplosion = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;	// ���_�o�b�t�@�ւ̃|�C���^

EXPLOSION g_aExplosion[MAX_EXPLOSION];

//=============================================================================
// �e�̏���������
//=============================================================================
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_3D *pVtx;
	int nCntExplosion;

	// �����̏��̏�����
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].col = D3DXCOLOR  (1.0f, 1.0f, 1.0f,1.0f);
		g_aExplosion[nCntExplosion].bUse = false;
		g_aExplosion[nCntExplosion].nCounteAnim = 0;	// �A�j���[�V�����J�E���^
		g_aExplosion[nCntExplosion].nPatternAnim = 0;   // �p�^�[���i���o�[�̏�����
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		EXPLOSION_TEX,
		&g_pTextureExplosion);

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		//���_���W�̐ݒ�(�E���Őݒ肷��j
		pVtx[0].Pos = D3DXVECTOR3(-10.0f, 10.0f, 0.0f);
		pVtx[1].Pos = D3DXVECTOR3(10.0f, 10.0f, 0.0f);
		pVtx[2].Pos = D3DXVECTOR3(-10.0f, -10.0f, 0.0f);
		pVtx[3].Pos = D3DXVECTOR3(10.0f, -10.0f, 0.0f);

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
	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffExplosion->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitExplosion(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateExplosion(void)
{
	VERTEX_3D *pVtx;
	// �e�J�E���^�[�̏�����
	int nCntExplosion;

	//���_�o�b�t�@�̃��b�N
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);		
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		// �e���g�p����Ă���
		if (g_aExplosion[nCntExplosion].bUse == true)
		{
			g_aExplosion[nCntExplosion].nCounteAnim++;

			// ���Ԋu���o��
			if (g_aExplosion[nCntExplosion].nCounteAnim % 3 == 0)
			{
				// �p�^�[���̏�����
				g_aExplosion[nCntExplosion].nPatternAnim = (g_aExplosion[nCntExplosion].nPatternAnim + 1) % 8;
				// �e�N�X�`�����W�̎w��
				pVtx[0].tex = D3DXVECTOR2(0.0f + (g_aExplosion[nCntExplosion].nPatternAnim * 0.125f), 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.125f + (g_aExplosion[nCntExplosion].nPatternAnim * 0.125f), 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f + (g_aExplosion[nCntExplosion].nPatternAnim * 0.125f), 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.125f + (g_aExplosion[nCntExplosion].nPatternAnim * 0.125f), 1.0f);

				// ���Ԋu���o��
				if (g_aExplosion[nCntExplosion].nPatternAnim % 8 == 0)
				{
					g_aExplosion[nCntExplosion].bUse = false;
				}
			}

			//���_���W�̐ݒ�(�E���Őݒ肷��j
			pVtx[0].Pos = D3DXVECTOR3(-15.0f, 15.0f, 15.0f);
			pVtx[1].Pos = D3DXVECTOR3(15.0, 15.0f, 15.0f);
			pVtx[2].Pos = D3DXVECTOR3(-15.0f, -15.0f, 15.0f);
			pVtx[3].Pos = D3DXVECTOR3(15.0f, -15.0f, 15.0f);
		}
		pVtx += 4; // �e�A��
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffExplosion->Unlock();		
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			// �f�o�C�X�̎擾

	D3DXMATRIX mtxrot, mtxTrans, mtxView;				//�v�Z�p�}�g���b�N�X

	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aExplosion[nCntExplosion].mtxWorldWall);

			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			g_aExplosion[nCntExplosion].mtxWorldWall._11 = mtxView._11;//X��
			g_aExplosion[nCntExplosion].mtxWorldWall._12 = mtxView._21;//X��
			g_aExplosion[nCntExplosion].mtxWorldWall._13 = mtxView._31;//X��
			g_aExplosion[nCntExplosion].mtxWorldWall._21 = mtxView._12;//Y��
			g_aExplosion[nCntExplosion].mtxWorldWall._22 = mtxView._22;//Y��
			g_aExplosion[nCntExplosion].mtxWorldWall._23 = mtxView._32;//Y��

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxrot,
				rot.y,
				rot.x,
				rot.z);
			D3DXMatrixMultiply(&g_aExplosion[nCntExplosion].mtxWorldWall,
				&g_aExplosion[nCntExplosion].mtxWorldWall,
				&mtxrot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans,
				g_aExplosion[nCntExplosion].pos.x,
				g_aExplosion[nCntExplosion].pos.y,
				g_aExplosion[nCntExplosion].pos.z);
			D3DXMatrixMultiply(&g_aExplosion[nCntExplosion].mtxWorldWall,
				&g_aExplosion[nCntExplosion].mtxWorldWall,
				&mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aExplosion[nCntExplosion].mtxWorldWall);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureExplosion);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntExplosion, 2);
		}
	}
	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
}


//============================================================================
// �����̐ݒ�
//=============================================================================
void SetExplotion(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	// �ϐ��錾
	VERTEX_3D *pVtx;
	int nCntExplosion;

	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);		//���_�o�b�t�@�̃��b�N

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)
		{
			g_aExplosion[nCntExplosion].pos = pos;
			g_aExplosion[nCntExplosion].col = col;
			g_aExplosion[nCntExplosion].bUse = true;
			break;
		}
		pVtx += 4;
	}
	g_pVtxBuffExplosion->Unlock();		//���_�o�b�t�@�̃A�����b�N
}