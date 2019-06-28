// ====================================================================================================
//
// �����L���O���� [ranking.cpp]
// Author : Kimura kouta
// ====================================================================================================
#include <stdio.h>              // ��ʓI�ȃw�b�_�[
#include "road.h"				// ���[�h�w�b�_�[
#include "ranking.h"			// �����L���O�w�b�_�[
#include "input.h"
#include "fade.h"
#include "score.h"
#include "rankbg.h"
#include "Controlar.h"
// ====================================================================================================
//
// �}�N����`
//
// ====================================================================================================
#define	TEXTURE_RANKING		"DATA/TEX/number001.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define RANKING_SIZE (20)									// �����L���O�{�[�h�̑傫��
#define RANKING_MAX (10)									// ���l
#define RANKING_DATE (5)									// �����L���O��
#define SAVE_FILE_NAME ("text.txt")							// �Z�[�u�t�@�C��

// ====================================================================================================
//
// �v���g�^�C�v�錾
//
// ====================================================================================================
void MakeVertexRanking(LPDIRECT3DDEVICE9 pDevice);

// ====================================================================================================
//
// �O���[�o���ϐ��錾
//
// ====================================================================================================
LPDIRECT3DTEXTURE9		g_pTextureRanking = NULL;				// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL;				// ���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3				g_RankingPos;							// �����L���O�{�[�h�̃|�W�V����
RANKING					g_aRankin[RANKING_DATE];				// �����L���O�ϐ�
int						g_nRanking;								// �����L���O
int g_nRNKData;

// ====================================================================================================
//
// ����������
//
// ====================================================================================================
void InitRanking(void)
{
	InitRankbg();

	int nCntRank;
	g_nRNKData = 0;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	g_RankingPos = D3DXVECTOR3(800.0f, 150.0f, 0.0f);
	g_nRanking = 0;
	
	for (nCntRank = 0; nCntRank < RANKING_DATE; nCntRank++)
	{
		g_aRankin[nCntRank].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRankin[nCntRank].aName[0];
		g_aRankin[nCntRank].nPoint = 0;
	}
	
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_RANKING,							// �t�@�C���̖��O
		&g_pTextureRanking);						// �ǂݍ��ރ������[

	// ���_���̍쐬
	MakeVertexRanking(pDevice);
}

// ====================================================================================================
//
// �I������
//
// ====================================================================================================
void UninitRanking(void)
{
	UninitRankbg();

	// �e�N�X�`���̊J��
	if (g_pTextureRanking != NULL)
	{
		g_pTextureRanking->Release();
		g_pTextureRanking = NULL;
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffRanking != NULL)
	{
		// ���_�o�b�t�@�̊J��
		g_pVtxBuffRanking->Release();
		g_pVtxBuffRanking = NULL;
	}
}

// ====================================================================================================
//
// �X�V����
//
// ====================================================================================================
void UpdateRanking(void)
{
	UpdateRankbg();
}

// ====================================================================================================
//
// �`�揈��
//
// ====================================================================================================
void DrawRanking(void)
{
	DrawRankbg();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntRanking;

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffRanking, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureRanking);

		for (nCntRanking = 0; nCntRanking < RANKING_MAX * RANKING_DATE; nCntRanking++)
		{
			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntRanking, 2);
		}
}

// ====================================================================================================
//
// ���_�̍쐬
//
// ====================================================================================================
void MakeVertexRanking(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;			// ���_���ւ̃|�C���g
	int nCntRanking;			// �����L���O�J�E���g
	int nCntRankingData;		// �����L���O�J�E���g

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * RANKING_MAX * RANKING_DATE, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffRanking, NULL);

	// ���_���̐ݒ�
	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^
	g_pVtxBuffRanking->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntRankingData = 0; nCntRankingData < RANKING_DATE; nCntRankingData++)
	{
		for (nCntRanking = 0; nCntRanking < RANKING_MAX; nCntRanking++)
		{
			pVtx[0].pos = D3DXVECTOR3(g_RankingPos.x + (-RANKING_SIZE / 2) - (RANKING_SIZE + 20) * nCntRanking,	
				g_RankingPos.y + (-RANKING_SIZE / 2) + (RANKING_SIZE + 50) * nCntRankingData, 0.0f);							// ��ڂ̒��_
			pVtx[1].pos = D3DXVECTOR3(g_RankingPos.x + (RANKING_SIZE / 2) - (RANKING_SIZE + 20) * nCntRanking + RANKING_SIZE,
				g_RankingPos.y + (-RANKING_SIZE / 2) + (RANKING_SIZE + 50) * nCntRankingData, 0.0f);							// ��ڂ̒��_
			pVtx[2].pos = D3DXVECTOR3(g_RankingPos.x + (-RANKING_SIZE / 2) - (RANKING_SIZE + 20) * nCntRanking,
				g_RankingPos.y + (RANKING_SIZE / 2) + (RANKING_SIZE + 50) * nCntRankingData + RANKING_SIZE, 0.0f);				// �O�ڂ̒��_
			pVtx[3].pos = D3DXVECTOR3(g_RankingPos.x + (RANKING_SIZE / 2) - (RANKING_SIZE + 20) * nCntRanking + RANKING_SIZE,
				g_RankingPos.y + (RANKING_SIZE / 2) + (RANKING_SIZE + 50) * nCntRankingData + RANKING_SIZE, 0.0f);				// �l�ڂ̒��_

			pVtx[0].rhw = 1.0f;	// ��ڂ̒��_�쐬
			pVtx[1].rhw = 1.0f;	// ��ڂ̒��_�쐬
			pVtx[2].rhw = 1.0f;	// �O�ڂ̒��_�쐬
			pVtx[3].rhw = 1.0f;	// �l�ڂ̒��_�쐬

			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// ��ڂ̐F�ݒ�
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// ��ڂ̐F�ݒ�
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �O�ڂ̐F�ݒ�
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �l�ڂ̐F�ݒ�

			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);		// ��ڂ̃e�N�X�`��
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);		// ��ڂ̃e�N�X�`��
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);		// �O�ڂ̃e�N�X�`��
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);		// �l�ڂ̃e�N�X�`��

			pVtx += 4;
		}
	}
	// �A�����b�N
	g_pVtxBuffRanking->Unlock();
}

// ====================================================================================================
//
// �����L���O�̕ύX
//
// ====================================================================================================
void AddRanking(int nPoint,int nRankingCnt)
{
	VERTEX_2D *pVtx;		// ���_���ւ̃|�C���g
	int nCntRanking;		// �����L���O�J�E���g
	int nCntRankingData;	// �����L���O�J�E���g
	int nRanking;			// �������L���O
	float fRanking;
	ROAD *pLoad;

	pLoad = GetLoad();

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^
	g_pVtxBuffRanking->Lock(0, 0, (void **)&pVtx, 0);


	for (nCntRankingData = 0; nCntRankingData < RANKING_DATE; nCntRankingData++, pLoad++)
	{
		g_aRankin[nCntRankingData].nPoint = pLoad->nPoint;

		for (nCntRanking = 0; nCntRanking < RANKING_MAX; nCntRanking++)
		{
			nRanking = g_aRankin[nCntRankingData].nPoint % (int)powf(10.0f, (float)nCntRanking + 1.0f) / (int)powf(10.0f, (float)nCntRanking);
			fRanking = (float)nRanking / 10.0f;

			pVtx[0].pos = D3DXVECTOR3(g_RankingPos.x + (-RANKING_SIZE / 2) - (RANKING_SIZE + 20) * nCntRanking,
				g_RankingPos.y + (-RANKING_SIZE / 2) + (RANKING_SIZE + 60) * nCntRankingData, 0.0f);							// ��ڂ̒��_
			pVtx[1].pos = D3DXVECTOR3(g_RankingPos.x + (RANKING_SIZE / 2) - (RANKING_SIZE + 20) * nCntRanking + RANKING_SIZE,
				g_RankingPos.y + (-RANKING_SIZE / 2) + (RANKING_SIZE + 60) * nCntRankingData, 0.0f);							// ��ڂ̒��_
			pVtx[2].pos = D3DXVECTOR3(g_RankingPos.x + (-RANKING_SIZE / 2) - (RANKING_SIZE + 20) * nCntRanking,
				g_RankingPos.y + (RANKING_SIZE / 2) + (RANKING_SIZE + 60) * nCntRankingData + RANKING_SIZE, 0.0f);				// �O�ڂ̒��_
			pVtx[3].pos = D3DXVECTOR3(g_RankingPos.x + (RANKING_SIZE / 2) - (RANKING_SIZE + 20) * nCntRanking + RANKING_SIZE,
				g_RankingPos.y + (RANKING_SIZE / 2) + (RANKING_SIZE + 60) * nCntRankingData + RANKING_SIZE, 0.0f);				// �l�ڂ̒��_

			pVtx[0].tex = D3DXVECTOR2(fRanking,  0.0f);				// ��ڂ̃e�N�X�`��
			pVtx[1].tex = D3DXVECTOR2(fRanking + 0.1f, 0.0f);		// ��ڂ̃e�N�X�`��
			pVtx[2].tex = D3DXVECTOR2(fRanking,  1.0f);				// �O�ڂ̃e�N�X�`��
			pVtx[3].tex = D3DXVECTOR2(fRanking + 0.1f, 1.0f);		// �l�ڂ̃e�N�X�`��

			pVtx += 4;
		}
	}
	// �A�����b�N
	g_pVtxBuffRanking->Unlock();
}