//=============================================================================
//
// �X���� [ice.cpp]
// Author : KIMURA KOUTA
//
//=============================================================================
#include"ice.h"
#include"player.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_ICE	(1)

//=============================================================================
// �}�N����`
//=============================================================================
ICE g_Ice[MAX_ICE];

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPD3DXMESH g_pMeshIce = NULL;							//���b�V�����ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatIce = NULL;						//�}�e���A�����ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureIce = NULL;
DWORD g_nNumMatIce = 0;									//�}�e���A�����̐�

//=============================================================================
// ����������
//=============================================================================
void InitIce(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nCntIce = 0; nCntIce < MAX_ICE; nCntIce++)
	{
		//�����ݒ�
		g_Ice[nCntIce].pos = D3DXVECTOR3(-1200.0f, 300.0f, 800.0f);
		g_Ice[nCntIce].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Ice[nCntIce].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Ice[nCntIce].fDistance = sqrtf(100.0f)*sqrtf(100.0f);
		g_Ice[nCntIce].nLife = 1;
		g_Ice[nCntIce].bUse = false;

		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX("DATA/MODEL/ice.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatIce,
			NULL,
			&g_nNumMatIce,
			&g_pMeshIce);

		//���f���̒��_���W�̍ő�l�E�ŏ��l�̐ݒ�
		int nNumVertices;				//���_��
		DWORD sizeFVF;					//���_�t�H�[�}�b�g�̃T�C�Y
		BYTE *pVertexBuffer;			//���_�o�b�t�@�ւ̃|�C���^

		g_Ice[nCntIce].vtxMin = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);
		g_Ice[nCntIce].vtxMax = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);

		//���_�����擾
		nNumVertices = g_pMeshIce->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_pMeshIce->GetFVF());

		//���_�o�b�t�@�����b�N
		g_pMeshIce->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertexBuffer);

		for (int nCntVtx = 0; nCntVtx < nNumVertices; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVertexBuffer;

			//���ׂĂ̒��_�����r���čő�l�E�ŏ��l�𔲂��o��
			if (g_Ice[nCntIce].vtxMin.x > vtx.x)
			{
				g_Ice[nCntIce].vtxMin.x = vtx.x;
			}
			if (g_Ice[nCntIce].vtxMin.y > vtx.y)
			{
				g_Ice[nCntIce].vtxMin.y = vtx.y;
			}
			if (g_Ice[nCntIce].vtxMin.z > vtx.z)
			{
				g_Ice[nCntIce].vtxMin.z = vtx.z;
			}
			if (g_Ice[nCntIce].vtxMax.x < vtx.x)
			{
				g_Ice[nCntIce].vtxMax.x = vtx.x;
			}
			if (g_Ice[nCntIce].vtxMax.y < vtx.y)
			{
				g_Ice[nCntIce].vtxMax.y = vtx.y;
			}
			if (g_Ice[nCntIce].vtxMax.z < vtx.z)
			{
				g_Ice[nCntIce].vtxMax.z = vtx.z;
			}

			pVertexBuffer += sizeFVF;
		}
	}
	//���_�o�b�t�@���A�����b�N
	g_pMeshIce->UnlockVertexBuffer();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEX/thEIAMVSCA.jpg", &g_pTextureIce);

	/*if (g_Ice.bUse == true)
	{
		g_Ice.IdxShadow = SetShadow(g_Ice.pos, g_Ice.rot);
	}*/
}

//=============================================================================
// �I������
//=============================================================================
void UninitIce(void)
{
	//���b�V���̊J��
	if (g_pMeshIce != NULL)
	{
		g_pMeshIce->Release();
		g_pMeshIce = NULL;
	}

	//�}�e���A���̊J��
	if (g_pBuffMatIce != NULL)
	{
		g_pBuffMatIce->Release();
		g_pBuffMatIce = NULL;
	}

	if (g_pTextureIce != NULL)
	{
		g_pTextureIce->Release();
		g_pTextureIce = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateIce(void)
{

	//�v���C���[�̎擾
	PLAYER * pPlayer;
	pPlayer = GetPlayer();
	int nCntIce = 0;

		//�d�͏���

		g_Ice[nCntIce].move.y -= 0.1f;


		g_Ice[nCntIce].posOld = g_Ice[nCntIce].pos;

		g_Ice[nCntIce].pos += g_Ice[nCntIce].move;

		g_Ice[nCntIce].pos = pPlayer->pos;

		g_Ice[nCntIce].rot = pPlayer->rot;

		/*if (g_Ice.bUse == true)
		{
			SetPositionShadow(g_Ice.IdxShadow, g_Ice.pos);
		}*/

		if (g_Ice[nCntIce].nLife <= 0)
		{
			g_Ice[nCntIce].bUse = false;
		}



		if (g_Ice[nCntIce].pos.y < 0.0f)
		{
			g_Ice[nCntIce].pos.y = 0.0f;
		}

		//if (pPlayer->nCntDeth == 30)
		//{
		//	g_Ice[nCntIce].move.y += 1;
		//}
	
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawIce(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	D3DXMATERIAL *pMat;
	D3DMATERIAL9 matDef;
	for (int nCntIce = 0; nCntIce < MAX_ICE; nCntIce++)
	{
		if (g_Ice[nCntIce].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Ice[nCntIce].mtxWorldObject);

			// �X�P�[���𔽉f


			//��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Ice[nCntIce].rot.y, g_Ice[nCntIce].rot.x, g_Ice[nCntIce].rot.z);
			D3DXMatrixMultiply(&g_Ice[nCntIce].mtxWorldObject, &g_Ice[nCntIce].mtxWorldObject, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Ice[nCntIce].pos.x, g_Ice[nCntIce].pos.y, g_Ice[nCntIce].pos.z);
			D3DXMatrixMultiply(&g_Ice[nCntIce].mtxWorldObject, &g_Ice[nCntIce].mtxWorldObject, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Ice[nCntIce].mtxWorldObject);

			//���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			//�}�e���A�����ɑ΂���|�C���^���擾
			pMat = (D3DXMATERIAL*)g_pBuffMatIce->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_nNumMatIce; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureIce);

				//�`��
				g_pMeshIce->DrawSubset(nCntMat);
			}

			//�}�e���A�����f�t�H���g�ɖ߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//=============================================================================
// �v���C���[�̎擾
//=============================================================================
ICE *GetIce(void)
{
	return &g_Ice[0];
}

//=============================================================================
// �X
//=============================================================================
void SetIce(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot)
{
	for (int nCntIce = 0; nCntIce < MAX_ICE; nCntIce++)
	{
		if (g_Ice[nCntIce].bUse == false)
		{
			g_Ice[nCntIce].pos = pos;
			g_Ice[nCntIce].rot = rot;
			g_Ice[nCntIce].move = move;
			g_Ice[nCntIce].bUse = true;
			break;
		}
	}
}