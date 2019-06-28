//=============================================================================
//
// �X�R�A���� [score.cpp]
// Author : KIMURA KOUTA
//
//=============================================================================
#include "score.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define	TEXTURE_SCORE		"DATA/TEX/number001.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define MAX_SCORE   (8)
#define SCORE_POS_X	(0)			    //�|���S���̕\���ʒu(����X)
#define SCORE_POS_Y	(0)			    //�|���S���̕\���ʒu(����Y)
#define SCORE_SIZE_X	(40)			//�|���S���̃T�C�Y(����)
#define SCORE_SIZE_Y	(60)			//�|���S���̃T�C�Y(����)
#define SCORECOLOR_TEX   (255)

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;				// �ʒu
	bool bUse;						// ���񂾂��ǂ���
	int score;
} SCORE;


//=============================================================================
// �O���[�o���ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureScore = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;	// ���_�o�b�t�@�ւ̃|�C���^

int						g_nScore;				// �X�R�A
SCORE                   g_aScore[8];

//=============================================================================
// ����������
//=============================================================================
void InitScore(void)
{

	int nCntScore = 0;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_nScore = 0;


	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
								TEXTURE_SCORE,		// �t�@�C���̖��O
								&g_pTextureScore);	// �ǂݍ��ރ������[

	// ���_���̍쐬
	MakeVertexScore(pDevice);

}

//=============================================================================
// �I������
//=============================================================================
void UninitScore(void)
{
	// �e�N�X�`���̊J��
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateScore(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawScore(void)
{
	int nCntScore = 0;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureScore);

	for (nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntScore, 2);
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;
	int nCntScore=0;


	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

	// ���_���̐ݒ�
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		//���_���W�̐ݒ�(�E���Őݒ肷��j
		pVtx[0].pos = D3DXVECTOR3(SCORE_POS_X + 60 * nCntScore + 30 * 1.0f, SCORE_POS_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCORE_POS_X + 60 * nCntScore + 30 + SCORE_SIZE_X * 1.0f, SCORE_POS_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(SCORE_POS_X + 60 * nCntScore + 30 * 1.0f, SCORE_POS_Y + SCORE_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCORE_POS_X + 60 * nCntScore + 30 + SCORE_SIZE_X * 1.0f, SCORE_POS_Y + SCORE_SIZE_Y, 0.0f);

		//rhw�̐ݒ�i�l��1.0�ŌŒ�j�F2D�Ƃ��ē������̂ɕK�v�Ȃ���
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�(0�`255�̒l�Őݒ�j
		pVtx[0].col = D3DCOLOR_RGBA(SCORECOLOR_TEX, SCORECOLOR_TEX, SCORECOLOR_TEX, SCORECOLOR_TEX);
		pVtx[1].col = D3DCOLOR_RGBA(SCORECOLOR_TEX, SCORECOLOR_TEX, SCORECOLOR_TEX, SCORECOLOR_TEX);
		pVtx[2].col = D3DCOLOR_RGBA(SCORECOLOR_TEX, SCORECOLOR_TEX, SCORECOLOR_TEX, SCORECOLOR_TEX);
		pVtx[3].col = D3DCOLOR_RGBA(SCORECOLOR_TEX, SCORECOLOR_TEX, SCORECOLOR_TEX, SCORECOLOR_TEX);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4 ;
	}
	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffScore->Unlock();
}
	
//=============================================================================
// �X�R�A�̕ύX
//=============================================================================
void AddScore(int nValue)
{
	int nCntScore;
	int nScore;
	VERTEX_2D *pVtx;

	g_nScore += nValue;

	if (g_nScore < 0)
	{
		g_nScore = 0;
	}

	// ���_���̐ݒ�
  	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		nScore = g_nScore % (int)powf(10.0f, 8.0f - nCntScore) / (int)powf(10.0f, 8.0f - 1.0f - nCntScore);

		//�e�N�X�`���摜�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2((nScore*0.1f) + 0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((nScore*0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((nScore*0.1f) + 0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((nScore*0.1f) + 0.1f, 1.0f);

		pVtx += 4;
	}
	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffScore->Unlock();
}
//==================================================================================================
// �X�R�A�̎擾
//==================================================================================================
int GetScore(void)
{
	return g_nScore;
}
