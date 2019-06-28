//=============================================================================
//
// �o���b�g���� [bullet.cpp]
// Author : kimura kouta
//
//=============================================================================
#include "bullet.h"
#include "Shadow.h"
#include "input.h"
#include "player.h"
#include "meshFwall.h"
#include "Explosion.h"
#include "effect.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define BULLET_TEX		"DATA/TEX/bullet001.png"	//�ǂݍ��ރe�N�X�`���t�@�C����
#define MAX_BULLET		(128)						//
#define BULLET_SIZE		(10.0f)						//
#define BULLET_SPEED	(-5.0f)						//

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void MakeVertexBullet(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		 g_pTextureBullet = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;		//���_�o�b�t�@�ւ̃|�C���^

BULLET		g_Bullet[MAX_BULLET];

//=============================================================================
// ����������
//=============================================================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// �ʒu�E��]�̏����ݒ�
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_Bullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bullet[nCntBullet].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bullet[nCntBullet].bUse = false;
		g_Bullet[nCntBullet].Life = 0;
	}

	MakeVertexBullet(pDevice);

}

//=============================================================================
// �I������
//=============================================================================
void UninitBullet(void)
{
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBullet(void)
{
	// �ϐ��錾
	PLAYER *pPlayer = GetPlayer();
	MESHWALL *GetMeshWall();

	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	float fRadius = 20;
	int nLife = 200;
	float fAngle = 0;
	float fSpeed = 1;

	MESHWALL *pMeshWall = GetMeshWall();
	// �ʒu�E��]�̏����ݒ�
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_Bullet[nCntBullet].bUse)
		{
			SetEffect(g_Bullet[nCntBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), col, fRadius, 20, 0);
			g_Bullet[nCntBullet].pos.x += sinf(g_Bullet[nCntBullet].rot.y) * BULLET_SPEED;
			g_Bullet[nCntBullet].pos.z += cosf(g_Bullet[nCntBullet].rot.y) * BULLET_SPEED;

			SetPositionShadow(g_Bullet[nCntBullet].hIdxShadow, g_Bullet[nCntBullet].pos);

			g_Bullet[nCntBullet].Life--;
			if (g_Bullet[nCntBullet].Life <= 0)
			{
				// �e���g��Ȃ�
				g_Bullet[nCntBullet].bUse = false;

				SetExplotion(g_Bullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

				DeleteShadow(g_Bullet[nCntBullet].hIdxShadow);

				for (int nCnt = 0; nCnt < 50; nCnt++)
				{
					D3DXVECTOR3 pos = g_Bullet[nCntBullet].pos;
					//fAngle = (rand() % 628 / 100.0f)*(rand() % 2)*-1;
					fAngle = 0.4f * nCnt; 
					D3DXVECTOR3 move = D3DXVECTOR3(sinf(fAngle)*fSpeed, cosf(fAngle)*fSpeed,0.0f);
					SetEffect(pos, move, col, fRadius, nLife,1);
					D3DXVECTOR3 move2 = D3DXVECTOR3(sinf(fAngle)*fSpeed, cosf(fAngle)*fSpeed, sinf(fAngle)*fSpeed);
					SetEffect(pos, move2, col, fRadius, nLife,1);
					D3DXVECTOR3 move3 = D3DXVECTOR3(sinf(fAngle)*fSpeed, cosf(fAngle)*fSpeed, -sinf(fAngle)*fSpeed);
					SetEffect(pos, move3, col, fRadius, nLife,1);
					D3DXVECTOR3 move4 = D3DXVECTOR3(sinf(fAngle)*fSpeed, cosf(fAngle)*fSpeed, sinf(fAngle*2)*fSpeed);
					SetEffect(pos, move4, col, fRadius, nLife,1);
				}
			}
			if (pMeshWall->bUse == true)
			{
				if (g_Bullet[nCntBullet].pos.x > 600.0f)
				{
					SetExplotion(g_Bullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
					g_Bullet[nCntBullet].bUse = false;
					DeleteShadow(g_Bullet[nCntBullet].hIdxShadow);
				}
				else if (g_Bullet[nCntBullet].pos.x < -600.0f)
				{
					SetExplotion(g_Bullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
					g_Bullet[nCntBullet].bUse = false;
					DeleteShadow(g_Bullet[nCntBullet].hIdxShadow);
				}
				else if (g_Bullet[nCntBullet].pos.z > 600.0f)
				{
					SetExplotion(g_Bullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
					g_Bullet[nCntBullet].bUse = false;
					DeleteShadow(g_Bullet[nCntBullet].hIdxShadow);
				}
				else if (g_Bullet[nCntBullet].pos.z < -600.0f)
				{
					SetExplotion(g_Bullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
					g_Bullet[nCntBullet].bUse = false;
					DeleteShadow(g_Bullet[nCntBullet].hIdxShadow);
				}
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			// �f�o�C�X�̎擾

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, D3DZB_TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 128);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	D3DXMATRIX mtxrot, mtxTrans, mtxView;				//�v�Z�p�}�g���b�N�X

	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);



	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_Bullet[nCntBullet].bUse)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Bullet[nCntBullet].mtxWorldWall);

			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			g_Bullet[nCntBullet].mtxWorldWall._11 = mtxView._11;//X��
			g_Bullet[nCntBullet].mtxWorldWall._12 = mtxView._21;//X��
			g_Bullet[nCntBullet].mtxWorldWall._13 = mtxView._31;//X��
			g_Bullet[nCntBullet].mtxWorldWall._21 = mtxView._12;//Y��
			g_Bullet[nCntBullet].mtxWorldWall._22 = mtxView._22;//Y��
			g_Bullet[nCntBullet].mtxWorldWall._23 = mtxView._32;//Y��

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxrot,
				rot.y,
				rot.x,
				rot.z);
			D3DXMatrixMultiply(&g_Bullet[nCntBullet].mtxWorldWall,
				&g_Bullet[nCntBullet].mtxWorldWall,
				&mtxrot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans,
				g_Bullet[nCntBullet].pos.x,
				g_Bullet[nCntBullet].pos.y,
				g_Bullet[nCntBullet].pos.z);
			D3DXMatrixMultiply(&g_Bullet[nCntBullet].mtxWorldWall,
				&g_Bullet[nCntBullet].mtxWorldWall,
				&mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Bullet[nCntBullet].mtxWorldWall);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBullet);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntBullet, 2);
		}
	}
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, D3DZB_FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_LESSEQUAL);
}

//=============================================================================
// �ǂ̎擾
//=============================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//�ϐ��錾
	int nCntBullet;

	// ���_���̍쐬
	VERTEX_3D *pVtx;

	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (!g_Bullet[nCntBullet].bUse)
		{
			g_Bullet[nCntBullet].Life = 50;
			g_Bullet[nCntBullet].pos = pos;
			g_Bullet[nCntBullet].rot = rot;
			g_Bullet[nCntBullet].hIdxShadow = SetShadow(g_Bullet[nCntBullet].pos, g_Bullet[nCntBullet].rot);
			g_Bullet[nCntBullet].bUse = true;
			break;
		}
		pVtx += 4;
	}
	g_pVtxBuffBullet->Unlock();
}

//=============================================================================z
// �e�̎擾
//=============================================================================
BULLET * GetBullet(void)
{
	return &g_Bullet[MAX_BULLET];
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexBullet(LPDIRECT3DDEVICE9 pDevice)
{

	D3DXCreateTextureFromFile(
		pDevice,
		BULLET_TEX,
		&g_pTextureBullet);

	// ���_���̍쐬
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//���_���W�̐ݒ�(�E���Őݒ肷��j
		pVtx[0].Pos = D3DXVECTOR3(-BULLET_SIZE, BULLET_SIZE, 0.0f);
		pVtx[1].Pos = D3DXVECTOR3(BULLET_SIZE, BULLET_SIZE, 0.0f);
		pVtx[2].Pos = D3DXVECTOR3(-BULLET_SIZE, -BULLET_SIZE, 0.0f);
		pVtx[3].Pos = D3DXVECTOR3(BULLET_SIZE, -BULLET_SIZE, 0.0f);

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
	g_pVtxBuffBullet->Unlock();

}

