//=============================================================================
//
// �|���S������ [MeshField.cpp]
// Author : 
//
//=============================================================================
#include "meshField.h"
#include "input.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define POLTGON0_TEX "DATA/TEX/umi.jpg"	//�ǂݍ��ރe�N�X�`���t�@�C����
#define WIDTH	(20)
#define HEIGHT	(20)
#define SIZE_X	(1200)
#define SIZE_Z	(1200)
#define WAVE_W	(0.003f)
#define WAVE_H	(3.0f)

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void MakeVertexMeshField(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		 g_pTextureMeshField = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField = NULL;		//���_�o�b�t�@�ւ̃|�C���^
PDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;		//���_�o�b�t�@�ւ̃|�C���^

D3DXVECTOR3 g_PosMeshField;								//�|���S���̈ʒu
D3DXVECTOR3 g_rotMeshField;								//�|���S���̌���

D3DXMATRIX  g_mtxWorldMeshField;							//���[���h�}�g���b�N�X

int nNumrertexMashField;
int nNumIndexMashField;
int nNumPolygonMashField;

int nCntNami;
float pos4;

bool bLUse;

//=============================================================================
// ����������
//=============================================================================
void InitMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	bLUse = false;
	nCntNami = 0;
	// �ʒu�E��]�̏����ݒ�
	g_PosMeshField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotMeshField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	nNumrertexMashField = (WIDTH + 1 ) * (HEIGHT + 1);
	nNumIndexMashField = (WIDTH * 2 + 2)*HEIGHT + 2 * (HEIGHT - 1);
	nNumPolygonMashField = WIDTH*HEIGHT * 2 + 4 * (HEIGHT - 1);

	// ���_���̍쐬
	MakeVertexMeshField(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitMeshField(void)
{
	if (g_pTextureMeshField!=NULL)
	{
		g_pTextureMeshField->Release();
		g_pTextureMeshField = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffMeshField != NULL)
	{
		g_pVtxBuffMeshField->Release();
		g_pVtxBuffMeshField = NULL;
	}

	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// ���_���̃|�C���^
	VERTEX_3D *pVtx;
	float move = WAVE_W;

	//�����_���[�X�e�[�g�̐ݒ�
	if (GetKeyboardTrigger(DIK_L))
	{
		if (bLUse == false)
		{
			bLUse = true;
		}
		else if(bLUse == true)
		{
			bLUse = false;
		}
	}

	if (bLUse == true)
	{
		pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}

	if (bLUse == false)
	{
		pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}

	//�g�̏㉺�^��
	nCntNami++;

	if (nCntNami<=200)
	{
		g_PosMeshField.y += sinf(3.0f);
	}
	if (nCntNami >= 200)
	{
		g_PosMeshField.y -= sinf(3.0f);
	}
	if (nCntNami >= 400)
	{
		nCntNami = 0;
	}

	//�g�̗���
	pos4 += move;

	g_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);

	for (float nCntH = 0; nCntH < HEIGHT + 1; nCntH++)
	{
		for (float nCntW = 0; nCntW < WIDTH + 1; nCntW++, pVtx++)
		{
			//���_���W�̐ݒ�(�E���Őݒ肷��j
			pVtx[0].Pos = D3DXVECTOR3((-SIZE_X * WIDTH / 2) + (nCntW * SIZE_X), 0.0f, (SIZE_Z * HEIGHT / 2) - (nCntH * SIZE_Z));

			pVtx[0].tex = D3DXVECTOR2(0.5f * nCntW + pos4 , 0.5f * nCntH);
		}
	}

	g_pVtxBuffMeshField->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMeshField(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldMeshField);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshField.y, g_rotMeshField.x, g_rotMeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_PosMeshField.x, g_PosMeshField.y, g_PosMeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshField);

	//�C���f�b�N�X�o�b�t�@�̐ݒ�
	pDevice->SetIndices(g_pIdxBuffMeshField);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshField, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMeshField);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0,0, nNumrertexMashField,0, nNumIndexMashField);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexMeshField(LPDIRECT3DDEVICE9 pDevice)
{
	//�ϐ��錾
	int nCntIdx = 0;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		POLTGON0_TEX,
		&g_pTextureMeshField);

	// ���_���̃|�C���^
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * nNumrertexMashField,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshField,
		NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(VERTEX_3D) * nNumIndexMashField,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField,
		NULL);

	g_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);

	for (float nCntH = 0; nCntH < HEIGHT + 1; nCntH++)
	{
		for (float nCntW = 0; nCntW < WIDTH + 1; nCntW++, pVtx++)
		{
			//���_���W�̐ݒ�(�E���Őݒ肷��j
			pVtx[0].Pos = D3DXVECTOR3((-SIZE_X * WIDTH / 2) + (nCntW * SIZE_X), 0.0f, (SIZE_Z * HEIGHT / 2) - (nCntH * SIZE_Z));

			//���_�x�N�g���̐ݒ�
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//���_�J���[�̐ݒ�(0�`255�̒l�Őݒ�j
			pVtx[0].Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);

			//���_�J���[�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.5f * nCntW + pos4, 0.5f * nCntH);
		}
	}

	g_pVtxBuffMeshField->Unlock();

	//�C���f�b�N�X�f�[�^�ւ̃|�C���^
	WORD*pIdx;

	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCnt = 0; nCnt < nNumIndexMashField; nCntIdx += 2)
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
	g_pIdxBuffMeshField->Unlock();
}