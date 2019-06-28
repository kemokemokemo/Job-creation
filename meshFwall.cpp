//=============================================================================
//
// �|���S������ [MeshWall.cpp]
// Author : KIM JOHNUN
//
//=============================================================================
#include "meshFwall.h"
#include "input.h"

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void MakeVertexMeshWall(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		 g_pTextureMeshWall = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshWall = NULL;		//���_�o�b�t�@�ւ̃|�C���^
PDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshWall = NULL;		//���_�o�b�t�@�ւ̃|�C���^

MESHWALL		g_MeshWall[MAX_WALL];

int nNumrertexMashWall;
int nNumIndexMashWall;
int nNumPolygonMashWall;

//=============================================================================
// ����������
//=============================================================================
void InitMeshWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// �ʒu�E��]�̏����ݒ�
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		g_MeshWall[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_MeshWall[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_MeshWall[nCntWall].bUse = false;
	}

	nNumrertexMashWall = (WIDTH + 1) * (HEIGHT + 1);
	nNumIndexMashWall = (WIDTH * 2 + 2)*HEIGHT + 2 * (HEIGHT - 1);
	nNumPolygonMashWall = WIDTH*HEIGHT * 2 + 4 * (HEIGHT - 1);

	// ���_���̍쐬
	MakeVertexMeshWall(pDevice);
}
//=============================================================================
// �I������
//=============================================================================
void UninitMeshWall(void)
{
	if (g_pTextureMeshWall!=NULL)
	{
		g_pTextureMeshWall->Release();
		g_pTextureMeshWall = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffMeshWall != NULL)
	{
		g_pVtxBuffMeshWall->Release();
		g_pVtxBuffMeshWall = NULL;
	}

	if (g_pIdxBuffMeshWall != NULL)
	{
		g_pIdxBuffMeshWall->Release();
		g_pIdxBuffMeshWall = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMeshWall(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMeshWall(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_MeshWall[nCntWall].bUse)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_MeshWall[nCntWall].mtxWorldWall);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_MeshWall[nCntWall].rot.y, g_MeshWall[nCntWall].rot.x, g_MeshWall[nCntWall].rot.z);
			D3DXMatrixMultiply(&g_MeshWall[nCntWall].mtxWorldWall, &g_MeshWall[nCntWall].mtxWorldWall, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_MeshWall[nCntWall].pos.x, g_MeshWall[nCntWall].pos.y, g_MeshWall[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_MeshWall[nCntWall].mtxWorldWall, &g_MeshWall[nCntWall].mtxWorldWall, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_MeshWall[nCntWall].mtxWorldWall);

			//�C���f�b�N�X�o�b�t�@�̐ݒ�
			pDevice->SetIndices(g_pIdxBuffMeshWall);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffMeshWall, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureMeshWall);

			// �|���S���̕`��
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, nNumrertexMashWall, 0, nNumIndexMashWall);
		}
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexMeshWall(LPDIRECT3DDEVICE9 pDevice)
{
	//�ϐ��錾
	int nCntIdx = 0;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		POLTGON0_TEX,
		&g_pTextureMeshWall);

	// ���_���̃|�C���^
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * nNumrertexMashWall,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshWall,
		NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(VERTEX_3D) * nNumIndexMashWall,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshWall,
		NULL);

	g_pVtxBuffMeshWall->Lock(0, 0, (void**)&pVtx, 0);

		for (float nCntH = 0; nCntH < HEIGHT + 1; nCntH++)
		{
			for (float nCntW = 0; nCntW < WIDTH + 1; nCntW++)
			{
				//���_���W�̐ݒ�(�E���Őݒ肷��j
				pVtx[0].Pos = D3DXVECTOR3((-SIZE_X * WIDTH / 2) + (nCntW * SIZE_X),(SIZE_Y * HEIGHT / 2) - (nCntH * SIZE_Y),  0.0f);

				//���_�x�N�g���̐ݒ�
				pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

				//���_�J���[�̐ݒ�(0�`255�̒l�Őݒ�j
				pVtx[0].Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				pVtx[0].tex = D3DXVECTOR2(0.5f * nCntW, 0.5f * nCntH);
				pVtx += 1; 
			}
		}

	g_pVtxBuffMeshWall->Unlock();

	//�C���f�b�N�X�f�[�^�ւ̃|�C���^
	WORD*pIdx;

	g_pIdxBuffMeshWall->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCnt = 0; nCnt < nNumIndexMashWall; nCntIdx += 2)
	{
		if ((nCntIdx + 2) % ((WIDTH + 1) * 2 + 2) == 0 && nCntIdx != 0)
		{
			pIdx[nCntIdx] = nCnt - 1;
			pIdx[nCntIdx + 1] = (WIDTH + 1 + nCnt);
		}
		else
		{
			pIdx[nCntIdx] = (WIDTH +1 + nCnt);
			pIdx[nCntIdx +1] = nCnt;
			nCnt++;
		}
	}
	g_pIdxBuffMeshWall->Unlock();
}
//=============================================================================
// �ǂ̎擾
//=============================================================================
int SetMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//�ϐ��錾
	int nCntWall;

	// ���_���̍쐬
	VERTEX_3D *pVtx;

	g_pVtxBuffMeshWall->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (!g_MeshWall[nCntWall].bUse)
		{
			g_MeshWall[nCntWall].pos = pos;
			g_MeshWall[nCntWall].rot = rot;
			g_MeshWall[nCntWall].bUse = true;
			break;
		}
	}
	g_pVtxBuffMeshWall->Unlock();
	return nCntWall;
}

//=======================================================================================================
// �ǂ̎擾
//=======================================================================================================
MESHWALL * GetMeshWall(void)
{
	return &g_MeshWall[0];
}

