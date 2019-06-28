//=============================================================================
//
// サウンド処理 [sound.h]
// Author :kimura kouta
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//=============================================================================
// サウンドファイル
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
	SOUND_LABEL_SE_ENTER,		// ENTERの決定音
	SOUND_LABEL_SE_JUMP,		// ジャンプ音
	SOUND_LABEL_SE_KEYGET,		// アイテムゲット音
	SOUND_LABEL_SE_CLEAR,		// クリア音
	SOUND_LABEL_SE_BLIZZARD,	// 吹雪音
	SOUND_LABEL_MAX,

} SOUND_LABEL;
//=============================================================================
// プロトタイプ宣言
//=============================================================================
HRESULT InitSound(HWND hWnd);
void UninitSound(void);

HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
