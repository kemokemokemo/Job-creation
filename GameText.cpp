//=============================================================================
//
// �e�L�X�g���� [Text.cpp]
// Author : Kimura Kouta
//
//=============================================================================
#include "GameText.h"
#include "Title.h"//�C���N���[�h�t�@�C��
#include "input.h"
#include "fade.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TEXT_TEX01 "DATA/TEX/satan_rogo.png"		//�ǂݍ��ރe�N�X�`���t�@�C����
#define TEXT_TEX02 "DATA/TEX/GameOver000.png"		//�ǂݍ��ރe�N�X�`���t�@�C����
#define TEXT_TEX03 "DATA/TEX/text000.png"		//�ǂݍ��ރe�N�X�`���t�@�C����
#define TEXT_TEX04 "DATA/TEX/ENTER.png"		//�ǂݍ��ރe�N�X�`���t�@�C����
#define TEXT_TEX05 "DATA/TEX/tuto2.png"		//�ǂݍ��ރe�N�X�`���t�@�C����
#define TEXT_TEX06 "DATA/TEX/zannki.png"		//�ǂݍ��ރe�N�X�`���t�@�C����
#define TEXT_TEX07 "DATA/TEX/kuria.png"		//�ǂݍ��ރe�N�X�`���t�@�C����

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================

//=============================================================================
// �O���[�o���ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9		g_apTextureGameText[MAX_GAMETEXT] = {};	// �e�N�X�`���ւ̃|�C���^(�G�̐��̕������ǂݍ���)
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGameText = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
GAMETEXT g_aGameText[MAX_GAMETEXT];

float g_GameAlfha;

//=============================================================================
// ����������
//=============================================================================
void InitGameText(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D *pVtx;
	int nCntText= 0;
	g_GameAlfha = 0;

	// �G�̏���������
	for (nCntText = 0; nCntText < MAX_GAMETEXT; nCntText++)
	{
		g_aGameText[nCntText].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGameText[nCntText].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGameText[nCntText].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aGameText[nCntText].sizex = 0;
		g_aGameText[nCntText].sizey = 0;
		g_aGameText[nCntText].bUse = false;
		g_aGameText[nCntText].nType = 0;
		g_aGameText[nCntText].bAlfa = false;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		TEXT_TEX01,
		&g_apTextureGameText[0]);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		TEXT_TEX02,
		&g_apTextureGameText[1]);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		TEXT_TEX03,
		&g_apTextureGameText[2]);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		TEXT_TEX04,
		&g_apTextureGameText[3]);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		TEXT_TEX05,
		&g_apTextureGameText[4]);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		TEXT_TEX06,
		&g_apTextureGameText[5]);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		TEXT_TEX07,
		&g_apTextureGameText[6]);

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_GAMETEXT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGameText,
		NULL);

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffGameText->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntText = 0; nCntText < MAX_GAMETEXT; nCntText++)
	{
		//���_���W�̐ݒ�(�E���Őݒ肷��j
		pVtx[0].pos = D3DXVECTOR3(g_aGameText[nCntText].pos.x - g_aGameText[nCntText].sizex, g_aGameText[nCntText].pos.y - g_aGameText[nCntText].sizey , 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aGameText[nCntText].pos.x + g_aGameText[nCntText].sizex, g_aGameText[nCntText].pos.y - g_aGameText[nCntText].sizey , 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aGameText[nCntText].pos.x - g_aGameText[nCntText].sizex, g_aGameText[nCntText].pos.y + g_aGameText[nCntText].sizey , 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aGameText[nCntText].pos.x + g_aGameText[nCntText].sizex, g_aGameText[nCntText].pos.y + g_aGameText[nCntText].sizey , 0.0f);

		//rhw�̐ݒ�i�l��1.0�ŌŒ�j�F2D�Ƃ��ē������̂ɕK�v�Ȃ���
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�(0�`255�̒l�Őݒ�j
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffGameText->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitGameText(void)
{
	int nCntText = 0;
	for (nCntText = 0; nCntText < MAX_GAMETEXT; nCntText++)
	{
		// �e�N�X�`���̊J��
		if (g_apTextureGameText[nCntText] != NULL)
		{
			g_apTextureGameText[nCntText]->Release();
			g_apTextureGameText[nCntText] = NULL;
		}

		if (g_pVtxBuffGameText != NULL)
			// ���_�o�b�t�@�̊J��
		{
			g_pVtxBuffGameText->Release();
			g_pVtxBuffGameText = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateGameText(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawGameText(void)
{
	int nCntText = 0;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffGameText, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntText = 0; nCntText < MAX_GAMETEXT; nCntText++)
	{
		if (g_aGameText[nCntText].bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureGameText[g_aGameText[nCntText].nType]);
			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntText, 2);
		}
	}
}

//=============================================================================
// �G�̐ݒ�
//=============================================================================
void SetGameText(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, int sizex, int sizey, int nType)
{
	VERTEX_2D *pVtx;
	int nCntText = 0;

	g_pVtxBuffGameText->Lock(0, 0, (void**)&pVtx, 0);		//���_�o�b�t�@�̃��b�N
	for (nCntText = 0; nCntText < MAX_GAMETEXT; nCntText++)
	{
		if (g_aGameText[nCntText].bUse == false)
		{
			g_aGameText[nCntText].pos = pos;
			g_aGameText[nCntText].sizex = sizex;
			g_aGameText[nCntText].sizey = sizey;
			g_aGameText[nCntText].col = col;
			g_aGameText[nCntText].move = move;
			g_aGameText[nCntText].nType = nType;

			//���_���W�̐ݒ�(�E���Őݒ肷��j
			pVtx[0].pos = D3DXVECTOR3(g_aGameText[nCntText].pos.x - g_aGameText[nCntText].sizex , g_aGameText[nCntText].pos.y - g_aGameText[nCntText].sizey , 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aGameText[nCntText].pos.x + g_aGameText[nCntText].sizex , g_aGameText[nCntText].pos.y - g_aGameText[nCntText].sizey , 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aGameText[nCntText].pos.x - g_aGameText[nCntText].sizex , g_aGameText[nCntText].pos.y + g_aGameText[nCntText].sizey , 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aGameText[nCntText].pos.x + g_aGameText[nCntText].sizex , g_aGameText[nCntText].pos.y + g_aGameText[nCntText].sizey , 0.0f);

			g_aGameText[nCntText].bUse = true;
			break;

		}
		pVtx += 4;
	}
	g_pVtxBuffGameText->Unlock();		//���_�o�b�t�@�̃A�����b�N
}

//=============================================================================
// �G�̎擾
//=============================================================================
GAMETEXT *GetGameText(void)
{
	return &g_aGameText[0];
}