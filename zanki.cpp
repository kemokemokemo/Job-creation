//=============================================================================
//
// �X�R�A���� [zanki.cpp]
// Author : KIMURA KOUTA
//
//=============================================================================
#include "zanki.h"
#include "player.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define	TEXTURE_ZANKI		"DATA/TEX/number002.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define MAX_ZANKI   (1)
#define ZANKI_POS_X	(1150)			    //�|���S���̕\���ʒu(����X)
#define ZANKI_POS_Y	(10)			    //�|���S���̕\���ʒu(����Y)
#define ZANKI_SIZE_X	(60)			//�|���S���̃T�C�Y(����)
#define ZANKI_SIZE_Y	(100)			//�|���S���̃T�C�Y(����)
#define ZANKICOLOR_TEX   (255)

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void MakeVertexZanki(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;				// �ʒu
	bool bUse;						// ���񂾂��ǂ���
	int zanki;
} ZANKI;

//=============================================================================
// �O���[�o���ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTexturezanki = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffzanki = NULL;	// ���_�o�b�t�@�ւ̃|�C���^

int						g_nzanki;				// �X�R�A
ZANKI					g_azanki[MAX_ZANKI];
int g_zankirState;
int g_nCntzanki;

//=============================================================================
// ����������
//=============================================================================
void InitZanki(void)
{
	int g_zankirState = 0;
	int nCntzanki = 0;
	int g_nzanki = 0;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
							TEXTURE_ZANKI,		// �t�@�C���̖��O
							&g_pTexturezanki);	// �ǂݍ��ރ������[

	// ���_���̍쐬
	MakeVertexZanki(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitZanki(void)
{
	// �e�N�X�`���̊J��
	if (g_pVtxBuffzanki != NULL)
	{
		g_pVtxBuffzanki->Release();
		g_pVtxBuffzanki = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffzanki != NULL)
	{
		g_pVtxBuffzanki->Release();
		g_pVtxBuffzanki = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateZanki(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawZanki(void)
{
	int nCntzanki = 0;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffzanki, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturezanki);

	for (nCntzanki = 0; nCntzanki < MAX_ZANKI; nCntzanki++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntzanki, 2);
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
void MakeVertexZanki(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;
	int nCntzanki=0;

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ZANKI,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffzanki,
		NULL);

	// ���_���̐ݒ�
	g_pVtxBuffzanki->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntzanki = 0; nCntzanki < MAX_ZANKI; nCntzanki++)
	{
		//���_���W�̐ݒ�(�E���Őݒ肷��j
		pVtx[0].pos = D3DXVECTOR3(ZANKI_POS_X + 60 * nCntzanki + 30 * 1.0f, ZANKI_POS_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(ZANKI_POS_X + 60 * nCntzanki + 30 + ZANKI_SIZE_X * 1.0f, ZANKI_POS_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(ZANKI_POS_X + 60 * nCntzanki + 30 * 1.0f, ZANKI_POS_Y + ZANKI_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(ZANKI_POS_X + 60 * nCntzanki + 30 + ZANKI_SIZE_X * 1.0f, ZANKI_POS_Y + ZANKI_SIZE_Y, 0.0f);

		//rhw�̐ݒ�i�l��1.0�ŌŒ�j�F2D�Ƃ��ē������̂ɕK�v�Ȃ���
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�(0�`255�̒l�Őݒ�j
		pVtx[0].col = D3DCOLOR_RGBA(ZANKICOLOR_TEX, ZANKICOLOR_TEX, ZANKICOLOR_TEX, ZANKICOLOR_TEX);
		pVtx[1].col = D3DCOLOR_RGBA(ZANKICOLOR_TEX, ZANKICOLOR_TEX, ZANKICOLOR_TEX, ZANKICOLOR_TEX);
		pVtx[2].col = D3DCOLOR_RGBA(ZANKICOLOR_TEX, ZANKICOLOR_TEX, ZANKICOLOR_TEX, ZANKICOLOR_TEX);
		pVtx[3].col = D3DCOLOR_RGBA(ZANKICOLOR_TEX, ZANKICOLOR_TEX, ZANKICOLOR_TEX, ZANKICOLOR_TEX);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4 ;
	}
	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffzanki->Unlock();
}
//=============================================================================
// �X�R�A�̕ύX
//=============================================================================
void AddZanki(int nValue)
{
	int nCntzanki;
	int nzanki;
	VERTEX_2D *pVtx;

	g_nzanki += nValue;

	if (g_nzanki < 0)
	{
		g_nzanki = 0;
	}

	// ���_���̐ݒ�
	g_pVtxBuffzanki->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntzanki = 0; nCntzanki < MAX_ZANKI; nCntzanki++)
	{
		nzanki = g_nzanki / (int)powf(10.0f, MAX_ZANKI - nCntzanki - 1.0f * 1.0f) % 10;

		//�e�N�X�`���摜�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2((nzanki*0.1f) + 0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((nzanki*0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((nzanki*0.1f) + 0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((nzanki*0.1f) + 0.1f, 1.0f);

		pVtx += 4;
	}
	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffzanki->Unlock();
}

//==================================================================================================
// �X�R�A�̎擾
//==================================================================================================
int GetZanki(void)
{
	return g_nzanki;
}