//=============================================================================
//
// �T�E���h���� [sound.h]
// Author :kimura kouta
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//=============================================================================
// �T�E���h�t�@�C��
//=============================================================================
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// BGM0
	SOUND_LABEL_BGM001,			// BGM1
	SOUND_LABEL_BGM002,			// BGM2
	SOUND_LABEL_BGM003,			// BGM3
	SOUND_LABEL_BGM004,			// BGM4
	SOUND_LABEL_BGM005,			// BGM5
	SOUND_LABEL_BGM006,			// BGM6
	SOUND_LABEL_SE_ENTER,		// ENTER�̌��艹
	SOUND_LABEL_SE_JUMP,		// �W�����v��
	SOUND_LABEL_SE_KEYGET,		// �A�C�e���Q�b�g��
	SOUND_LABEL_SE_CLEAR,		// �N���A��
	SOUND_LABEL_SE_BLIZZARD,	// ���ቹ
	SOUND_LABEL_MAX,

} SOUND_LABEL;
//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
HRESULT InitSound(HWND hWnd);
void UninitSound(void);

HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif