//=============================================================================
//
// �X�R�A���� [Time.cpp]
// Author : KIMURA KOUTA
//
//=============================================================================
#include "Time.h"
#include "Game.h"
#include "fade.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define	TEXTURE_Time		"DATA/TEX/number001.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define MAX_Time   (3)
#define Time_POS_X	(0)			    //�|���S���̕\���ʒu(����X)
#define Time_POS_Y	(0)			    //�|���S���̕\���ʒu(����Y)
#define Time_SIZE_X	(40)			//�|���S���̃T�C�Y(����)
#define Time_SIZE_Y	(60)			//�|���S���̃T�C�Y(����)
#define TimeCOLOR_TEX   (255)

#define MAX_TIMER   (300)

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void MakeVertexTime(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;				// �ʒu
	bool bUse;						// ���񂾂��ǂ���
	int Time;
} TIME;


//=============================================================================
// �O���[�o���ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureTime = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;	// ���_�o�b�t�@�ւ̃|�C���^

int						g_nTime;				// �X�R�A
TIME					g_aTime[8];
int g_TimerState;
int g_nCntTime;
//=============================================================================
// ����������
//=============================================================================
void InitTime(void)
{
	int g_TimerState = 0;
	int nCntTime = 0;
	int g_nTime = 0;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
								TEXTURE_Time,		// �t�@�C���̖��O
								&g_pTextureTime);	// �ǂݍ��ރ������[

	// ���_���̍쐬
	MakeVertexTime(pDevice);

}

//=============================================================================
// �I������
//=============================================================================
void UninitTime(void)
{
	// �e�N�X�`���̊J��
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();
		g_pVtxBuffTime = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();
		g_pVtxBuffTime = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTime(void)
{
	if (g_TimerState < MAX_TIMER)
	{
		g_nCntTime++;
	}
	if (g_nCntTime >= 60)
	{
		AddTime(-1);
		g_nCntTime = 0;
		g_TimerState++;

		if (g_TimerState >= MAX_TIMER)
		{
			SetGameState(GAMESTATE_END2);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTime(void)
{
	int nCntTime = 0;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffTime, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTime);

	for (nCntTime = 0; nCntTime < MAX_Time; nCntTime++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntTime, 2);
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
void MakeVertexTime(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;
	int nCntTime=0;


	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_Time,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime,
		NULL);

	// ���_���̐ݒ�
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTime = 0; nCntTime < MAX_Time; nCntTime++)
	{
		//���_���W�̐ݒ�(�E���Őݒ肷��j
		pVtx[0].pos = D3DXVECTOR3(Time_POS_X + 60 * nCntTime + 30 * 1.0f, Time_POS_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(Time_POS_X + 60 * nCntTime + 30 + Time_SIZE_X * 1.0f, Time_POS_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(Time_POS_X + 60 * nCntTime + 30 * 1.0f, Time_POS_Y + Time_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(Time_POS_X + 60 * nCntTime + 30 + Time_SIZE_X * 1.0f, Time_POS_Y + Time_SIZE_Y, 0.0f);

		//rhw�̐ݒ�i�l��1.0�ŌŒ�j�F2D�Ƃ��ē������̂ɕK�v�Ȃ���
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�(0�`255�̒l�Őݒ�j
		pVtx[0].col = D3DCOLOR_RGBA(TimeCOLOR_TEX, TimeCOLOR_TEX, TimeCOLOR_TEX, TimeCOLOR_TEX);
		pVtx[1].col = D3DCOLOR_RGBA(TimeCOLOR_TEX, TimeCOLOR_TEX, TimeCOLOR_TEX, TimeCOLOR_TEX);
		pVtx[2].col = D3DCOLOR_RGBA(TimeCOLOR_TEX, TimeCOLOR_TEX, TimeCOLOR_TEX, TimeCOLOR_TEX);
		pVtx[3].col = D3DCOLOR_RGBA(TimeCOLOR_TEX, TimeCOLOR_TEX, TimeCOLOR_TEX, TimeCOLOR_TEX);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4 ;
	}
	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffTime->Unlock();
}
	
//=============================================================================
// �X�R�A�̕ύX
//=============================================================================
void AddTime(int nValue)
{
	int nCntTime;
	int nTime;
	VERTEX_2D *pVtx;

	g_nTime += nValue;

	if (g_nTime > 300)
	{
		g_nTime = 300;
	}
	if (g_nTime < 0)
	{
		g_nTime = 0;
	}

	// ���_���̐ݒ�
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTime = 0; nCntTime < MAX_Time; nCntTime++)
	{
		nTime = g_nTime / (int)powf(10.0f, MAX_Time - nCntTime - 1.0f * 1.0f) % 10;

		//�e�N�X�`���摜�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2((nTime*0.1f) + 0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((nTime*0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((nTime*0.1f) + 0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((nTime*0.1f) + 0.1f, 1.0f);

		pVtx += 4;
	}
	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffTime->Unlock();
}
//==================================================================================================
// �X�R�A�̎擾
//==================================================================================================
int GetTime(void)
{
	return g_nTime;
}
