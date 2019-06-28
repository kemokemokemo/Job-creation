//----------------------------------------------------------------------------
//
// �|�[�Y�̏���	[pause.cpp]
// Author:	Kimura kouta
//
//----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "pause.h"		//�C���N���[�h�t�@�C�� 
#include "input.h"
#include "fade.h"
#include "game.h"

//----------------------------------------------------------------------------
//�}�N����`
//----------------------------------------------------------------------------
#define MAX_PAUSE			(5)		//�|�[�Y�̎��
#define TEXTURE_NAME000	"DATA/TEX/pouse.jpg"
#define TEXTURE_NAME001	"DATA/TEX/P_GAME.png"
#define TEXTURE_NAME002	"DATA/TEX/P_RANKING.png"
#define TEXTURE_NAME003	"DATA/TEX/P_TITLE.png"
#define TEXTURE_NAME004	"DATA/TEX/P_Pause.png"

//----------------------------------------------------------------------------
//�\���̒�`
//----------------------------------------------------------------------------

typedef struct
{
	D3DXVECTOR3	pos;				//���W
	D3DXCOLOR	col;				//�F
	int			nType;				//���
	float		fWidth;				//�|�[�Y�̃T�C�Y(x)
	float		fHeight;			//�|�[�Y�̃T�C�Y(y)
	bool		bUse;				//�g���Ă邩�ǂ���
	bool		bDisp;				//��ʂɂ����Ă邩�ǂ���

} PAUSE;

//====================================================================================================
//
// �v���g�^�C�v�錾
//
//====================================================================================================

//====================================================================================================
// �O���[�o���錾
//====================================================================================================

LPDIRECT3DTEXTURE9		g_apTexturePause[MAX_PAUSE] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffPause = NULL;				//���_�o�b�t�@�ւ̃|�C���^
PAUSE					g_aPause[MAX_PAUSE];				//�|�[�Y
int						g_nCursor;							//�J�[�\���ʒu
bool					g_bPad;								//�X�e�B�b�N���

//============================================================================
// �|�[�Y�̏�����
//============================================================================
void InitPause(void)
{
	//�ϐ��錾
	int nCntPause;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++)
	{
		g_aPause[nCntPause].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//���W
		g_aPause[nCntPause].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//�F
		g_aPause[nCntPause].nType = 0;									//���
		g_aPause[nCntPause].fWidth = 0;									//�T�C�Y(X)
		g_aPause[nCntPause].fHeight = 0;								//�T�C�Y(Y)
		g_aPause[nCntPause].bUse = false;								//�g���Ă邩�ǂ���
		g_aPause[nCntPause].bDisp = false;								//�����Ă��邩�ǂ���
	}

	//�J�[�\���ʒu�̏�����
	g_nCursor = 1;
	//�X�e�B�b�N�̏�����
	g_bPad = false;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME000,
		&g_apTexturePause[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME001,
		&g_apTexturePause[1]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME002,
		&g_apTexturePause[2]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME003,
		&g_apTexturePause[3]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME004,
		&g_apTexturePause[4]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_PAUSE,	//�m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,			//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;
	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++)
	{
		//���_���W
		pVtx[0].pos = g_aPause[nCntPause].pos - D3DXVECTOR3((g_aPause[nCntPause].fWidth / 2.0f),
		(g_aPause[nCntPause].fHeight / 2.0f), 0.0f);
		pVtx[1].pos = g_aPause[nCntPause].pos - D3DXVECTOR3(-(g_aPause[nCntPause].fWidth / 2.0f),
		(g_aPause[nCntPause].fHeight / 2.0f), 0.0f);
		pVtx[2].pos = g_aPause[nCntPause].pos - D3DXVECTOR3((g_aPause[nCntPause].fWidth / 2.0f),
		-(g_aPause[nCntPause].fHeight / 2.0f), 0.0f);
		pVtx[3].pos = g_aPause[nCntPause].pos - D3DXVECTOR3(-(g_aPause[nCntPause].fWidth / 2.0f),
		-(g_aPause[nCntPause].fHeight / 2.0f), 0.0f);

		//���_�̓������W
		pVtx[0].rhw = 1.0f;									//1.0f�ŌŒ�
		pVtx[1].rhw = 1.0f;									//1.0f�ŌŒ�
		pVtx[2].rhw = 1.0f;									//1.0f�ŌŒ�
		pVtx[3].rhw = 1.0f;									//1.0f�ŌŒ�
		//���_�̐F
		pVtx[0].col = g_aPause[nCntPause].col;				//(��,��,��,�����x)
		pVtx[1].col = g_aPause[nCntPause].col;				//(��,��,��,�����x)
		pVtx[2].col = g_aPause[nCntPause].col;				//(��,��,��,�����x)
		pVtx[3].col = g_aPause[nCntPause].col;				//(��,��,��,�����x)
		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);				//(�e�N�X�`����UV���W)
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);				//(�e�N�X�`����UV���W)
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);				//(�e�N�X�`����UV���W)
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);				//(�e�N�X�`����UV���W)
		pVtx += 4;

	}

	//�|�[�Y��ݒu
	//SetPause(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 1280, 720);
	//SetPause(D3DXVECTOR3(SCREEN_WIDTH / 2, 450.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1, 600, 200);
	//SetPause(D3DXVECTOR3(SCREEN_WIDTH / 2, 550.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2, 600, 200);
	//SetPause(D3DXVECTOR3(SCREEN_WIDTH / 2, 650.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 3, 600, 200);
	//SetPause(D3DXVECTOR3(SCREEN_WIDTH / 2, 200.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 4, 600, 200);

	//���_�f�[�^���A�����b�N
	g_pVtxBuffPause->Unlock();
}

//============================================================================
//
//�|�[�Y�̊֐�����
//
//============================================================================
void UninitPause(void)
{
	int nCntPause;

	for (nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++)
	{
		//�e�N�X�`���̊J��
		if (g_apTexturePause[nCntPause] != NULL)
		{
			g_apTexturePause[nCntPause]->Release();
			g_apTexturePause[nCntPause] = NULL;
		}
	}
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}
}
//----------------------------------------------------------------------------
//
//�|�[�Y�̍X�V����
//
//----------------------------------------------------------------------------
void UpdatePause(void)
{
	//�ϐ��錾
	int nCntPause;
	bool bSwitch = false;

	//�ϐ��錾
//	int	joypadX, joypadY;

	//�W���C�p�b�h�̈ړ�����
	//GetJoypadStickLeft(0, &joypadX, &joypadY);

	/*if (joypadY == 0)
	{
		g_bPad = false;
	}*/

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//[D]�L�[����������
	if (GetKeyboardTrigger(DIK_W) || GetKeyboardTrigger(DIK_UP) /*|| GetJoypadTrigger(0, JOYPADKEY_UP) || (joypadY > 0 && g_bPad == false)*/)
	{
		g_nCursor--;		//�J�[�\��������
		g_bPad = true;		//�X�e�B�b�N����true��
		//PlaySound(SOUND_LABEL_SE_SHOT);
	}
	//[D]�L�[��������
	else if (GetKeyboardTrigger(DIK_S) || GetKeyboardTrigger(DIK_DOWN) /*|| GetJoypadTrigger(0, JOYPADKEY_DOWN) || (joypadY < 0 && g_bPad == false)*/)
	{
		g_nCursor++;		//�J�[�\��������
		g_bPad = true;		//�X�e�B�b�N����true��
		//PlaySound(SOUND_LABEL_SE_SHOT);
	}
	//�J�[�\����3��������1�ɂ���
	if (g_nCursor > 3)
	{
		g_nCursor = 1;
	}
	//�J�[�\����1��������3�ɂ���
	else if (g_nCursor < 1)
	{
		g_nCursor = 3;
	}

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

		for (nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++)
		{
			if (bSwitch == true)
			{
				//�J�[�\�������Ă���ڗ�������
				if (g_aPause[nCntPause].nType == g_nCursor)
				{
					g_aPause[nCntPause].col.a = 1.0f;
				}
				//����ȊO�̂�͏��������ɂ���
				else
				{
					g_aPause[nCntPause].col.a = 0.7f;
				}
				if (g_aPause[nCntPause].nType == 0)
				{
					g_aPause[nCntPause].col.a = 0.5f;
				}

				//���_�̐F
				pVtx[0].col = g_aPause[nCntPause].col;	//(��,��,��,�����x)
				pVtx[1].col = g_aPause[nCntPause].col;	//(��,��,��,�����x)
				pVtx[2].col = g_aPause[nCntPause].col;	//(��,��,��,�����x)
				pVtx[3].col = g_aPause[nCntPause].col;	//(��,��,��,�����x)

				pVtx += 4;
			}
			else
			{
				g_aPause[nCntPause].col.a = 0.0f;
			}
		}

	//���_�f�[�^���A�����b�N
	g_pVtxBuffPause->Unlock();

	//[Enter]���W���C�p�b�h�̃{�^������������
	if ((GetKeyboardTrigger(DIK_P) /*|| GetJoypadTrigger(0, JOYPADKEY_A) || GetJoypadTrigger(0, JOYPADKEY_B) || GetJoypadTrigger(0, JOYPADKEY_X) ||*/
		/*GetJoypadTrigger(0, JOYPADKEY_Y)*/) && GetFade() == FADE_NONE)
	{
		bSwitch = true;
		//�J�[�\���̈ʒu�ɉ����ď�����ς���
		switch (g_nCursor)
		{
		case 1:
			//�Q�[�����s
			SetGameState(GAMESTATE_NORMAL);
			//PlaySound(SOUND_LABEL_SE_ENTER);
			break;

		case 2:
			//�Q�[�����Z�b�g
			SetFade(MODE_RANKING);
			//PlaySound(SOUND_LABEL_SE_ENTER);
			break;

		case 3:
			//�^�C�g���ɖ߂�
			SetFade(MODE_TITLE);
			//PlaySound(SOUND_LABEL_SE_EXPLOSION);
			break;
		}
	}
}

//----------------------------------------------------------------------------
//
//�|�[�Y�̕`�揈��
//
//----------------------------------------------------------------------------
void DrawPause(void)
{
	//�ϐ��錾
	int nCntPause;
	LPDIRECT3DDEVICE9	pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);					// ���C�e�B���O����
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);			
	//pDevice->SetRenderState(D3DRS_ALPHAREF, 100);					// ��l

	//pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);			// Z��r�ݒ�

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++)
	{
		if (g_aPause[nCntPause].bDisp == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTexturePause[g_aPause[nCntPause].nType]);
			//�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
				nCntPause * 4,		//�J�n����C���f�b�N�X(���_)
				2);					//�|���S���̖���
		}
	}

	//pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);					// ���C�e�B���O����
	//pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);		
	//pDevice->SetRenderState(D3DRS_ALPHAREF, 0);						// ��l

	//pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);			// Z��r�ݒ�
}

//------------------------------------------------------------------------------
// �|�[�Y�̐ݒ�
//------------------------------------------------------------------------------
void SetPause(D3DXVECTOR3 pos, D3DXCOLOR col, int nType, float fWidth, float fHeight)
{
	VERTEX_2D *pVtx;

	int nCntPause;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++)
	{
		if (g_aPause[nCntPause].bUse == false)
		{
			g_aPause[nCntPause].pos = pos;				//���W
			g_aPause[nCntPause].col = col;				//�F
			g_aPause[nCntPause].nType = nType;			//���
			g_aPause[nCntPause].fWidth = fWidth;		//�T�C�Y(X)
			g_aPause[nCntPause].fHeight = fHeight;		//�T�C�Y(Y)
			g_aPause[nCntPause].bUse = true;			//�g���Ă邩�ǂ���
			g_aPause[nCntPause].bDisp = true;			//�����Ă��邩�ǂ���

			//���_���W
			pVtx[0].pos = g_aPause[nCntPause].pos - D3DXVECTOR3((g_aPause[nCntPause].fWidth / 2.0f),
				(g_aPause[nCntPause].fHeight / 2.0f), 0.0f);
			pVtx[1].pos = g_aPause[nCntPause].pos - D3DXVECTOR3(-(g_aPause[nCntPause].fWidth / 2.0f),
				(g_aPause[nCntPause].fHeight / 2.0f), 0.0f);
			pVtx[2].pos = g_aPause[nCntPause].pos - D3DXVECTOR3((g_aPause[nCntPause].fWidth / 2.0f),
				-(g_aPause[nCntPause].fHeight / 2.0f), 0.0f);
			pVtx[3].pos = g_aPause[nCntPause].pos - D3DXVECTOR3(-(g_aPause[nCntPause].fWidth / 2.0f),
				-(g_aPause[nCntPause].fHeight / 2.0f), 0.0f);

			//���_�̐F
			pVtx[0].col = g_aPause[nCntPause].col;	//(��,��,��,�����x)
			pVtx[1].col = g_aPause[nCntPause].col;	//(��,��,��,�����x)
			pVtx[2].col = g_aPause[nCntPause].col;	//(��,��,��,�����x)
			pVtx[3].col = g_aPause[nCntPause].col;	//(��,��,��,�����x)
			break;
		}
		pVtx += 4;
	}

	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffPause->Unlock();
}