//=============================================================================
//
// 入力処理 [controlar.cpp]
// Author :  Kimura Kouta
//
//=============================================================================
#include "Controlar.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define	COUNT_WAIT_REPEAT	(20)	// リピート開始までの待ち時間
#define	INTERVAL_REPEAT		(1)		// リピート間隔

#define NUM_JOYPAD_MAX		(4)		// パッド最大数
#define JOY_MAX_RANGE		(1024)	// パッド有効範囲
#define	NUM_KEY_MAX			(256)	// キーの最大数
//=============================================================================
// グローバル変数宣言
//=============================================================================
LPDIRECTINPUT8 g_apInput = NULL;// IDirectInput8インターフェースへのポインタ
LPDIRECTINPUTDEVICE8 g_pDevJoypad = NULL;

BYTE g_aJoyKeyState[NUM_KEY_MAX];
int						g_nCountWaitRepeat = 0;				// リピート待ち時間
int						g_nIntervalRepeat = 0;				// リピート間隔

LPDIRECTINPUTDEVICE8	g_apDIDevJoypad[NUM_JOYPAD_MAX] = {};						// IDirectInputDevice8へのポインタ(ジョイパッド)
DIJOYSTATE2				g_aJoypadState[NUM_JOYPAD_MAX];								// ジョイパッド状態を受け取るワーク
bool					g_aKeyStateJoypad[NUM_JOYPAD_MAX][NUM_KEY_MAX];				// ジョイパッドの押下状態を保持するワーク
bool					g_aKeyStateTriggerJoypad[NUM_JOYPAD_MAX][NUM_KEY_MAX];		// ジョイパッドのトリガー状態を保持するワーク
bool					g_aKeyStateReleaseJoypad[NUM_JOYPAD_MAX][NUM_KEY_MAX];		// ジョイパッドのリリース状態を保持するワーク
bool					g_aKeyStateRepeatJoypad[NUM_JOYPAD_MAX][NUM_KEY_MAX];		// ジョイパッドのリピート状態を保持するワーク
int						g_aKeyStateRepeatCntJoypad[NUM_JOYPAD_MAX][NUM_KEY_MAX];	// ジョイパッドのリピートカウンタ
D3DXVECTOR3             g_aKeyStateAxis[NUM_JOYPAD_MAX];
int						g_nCntPad = 0;

//=============================================================================
// 入力処理の初期化
//=============================================================================
HRESULT InitInput(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT hr;

	if (g_apInput == NULL)
	{
		// DirectInputオブジェクトの作成
		hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
			IID_IDirectInput8, (void**)&g_apInput, NULL);

		g_nCountWaitRepeat = COUNT_WAIT_REPEAT;
		g_nIntervalRepeat = INTERVAL_REPEAT;
	}

	for (g_nCntPad = 0; g_nCntPad < NUM_JOYPAD_MAX; g_nCntPad++)
	{
		hr = g_apInput->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoyCallbackJoypad, NULL, DIEDFL_ATTACHEDONLY);
		if (FAILED(hr) || g_apDIDevJoypad[g_nCntPad] == NULL)
		{
			//MessageBox(hWnd, "ジョイパッドがありません", "警告", MB_ICONWARNING);
			return hr;
		}

		// データフォーマットを設定
		hr = g_apDIDevJoypad[g_nCntPad]->SetDataFormat(&c_dfDIJoystick2);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "ジョイパッドのデータフォーマットを設定できませんでした。", "警告", MB_ICONWARNING);
			return hr;
		}

		// 協調モードを設定（フォアグラウンド＆非排他モード）
		hr = g_apDIDevJoypad[g_nCntPad]->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
		if (FAILED(hr))
		{
			MessageBox(hWnd, "ジョイパッドの協調モードを設定できませんでした。", "警告", MB_ICONWARNING);
			return hr;
		}

		hr = g_apDIDevJoypad[g_nCntPad]->EnumObjects(EnumAxesCallbackJoypad, NULL, DIDFT_AXIS);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "ジョイパッドが見つかりませんでした", "警告", MB_ICONWARNING);
			return hr;
		}

		// デバイスの設定
		{
			DIPROPRANGE diprg;

			ZeroMemory(&diprg, sizeof(diprg));
			diprg.diph.dwSize       = sizeof(diprg);
			diprg.diph.dwHeaderSize = sizeof(diprg.diph);

			diprg.diph.dwObj = DIJOFS_X;
			diprg.diph.dwHow = DIPH_BYOFFSET;
			diprg.lMin       = -JOY_MAX_RANGE;
			diprg.lMax       = JOY_MAX_RANGE;
            // Ｘ方向の範囲を指定
			g_apDIDevJoypad[g_nCntPad]->SetProperty(DIPROP_RANGE, &diprg.diph);	

			diprg.diph.dwObj = DIJOFS_Y;
			diprg.diph.dwHow = DIPH_BYOFFSET;
			diprg.lMin       = -JOY_MAX_RANGE;
			diprg.lMax       = JOY_MAX_RANGE;
			// Ｙ方向の範囲を指定
			g_apDIDevJoypad[g_nCntPad]->SetProperty(DIPROP_RANGE, &diprg.diph);	

			diprg.diph.dwObj = DIJOFS_Z;
			diprg.diph.dwHow = DIPH_BYOFFSET;
			diprg.lMin       = -JOY_MAX_RANGE;
			diprg.lMax       = JOY_MAX_RANGE;
            // Ｚ方向の範囲を指定
			g_apDIDevJoypad[g_nCntPad]->SetProperty(DIPROP_RANGE, &diprg.diph);	

			diprg.diph.dwObj = DIJOFS_RZ;
			diprg.diph.dwHow = DIPH_BYOFFSET;
			diprg.lMin = -JOY_MAX_RANGE;
			diprg.lMax = JOY_MAX_RANGE;
			// ＲＺ方向の範囲を指定
			g_apDIDevJoypad[g_nCntPad]->SetProperty(DIPROP_RANGE, &diprg.diph);	
		}

		// キーボードへのアクセス権を獲得(入力制御開始)
		g_apDIDevJoypad[g_nCntPad]->Acquire();

		// ワーククリア
		memset(&g_aJoypadState[g_nCntPad], 0, sizeof g_aJoypadState[g_nCntPad]);
		memset(g_aKeyStateJoypad[g_nCntPad], 0, sizeof g_aKeyStateJoypad[g_nCntPad]);
		memset(g_aKeyStateTriggerJoypad[g_nCntPad], 0, sizeof g_aKeyStateTriggerJoypad[g_nCntPad]);
		memset(g_aKeyStateReleaseJoypad[g_nCntPad], 0, sizeof g_aKeyStateReleaseJoypad[g_nCntPad]);
		memset(g_aKeyStateRepeatJoypad[g_nCntPad], 0, sizeof g_aKeyStateRepeatJoypad[g_nCntPad]);
	}

	return hr;
}

//=============================================================================
// 入力処理の終了処理
//=============================================================================
void UninitInput(void)
{

	// ジョイパッドの終了処理
	for (int nCntPad = 0; nCntPad < 2; nCntPad++)
	{
		if (g_apDIDevJoypad[nCntPad] != NULL)
		{// デバイスオブジェクトの開放
			g_apDIDevJoypad[nCntPad]->Release();
			g_apDIDevJoypad[nCntPad] = NULL;
		}
	}

	if (g_apInput != NULL)
	{
		g_apInput->Release();
		g_apInput = NULL;
	}
}

//=============================================================================
// 入力処理の更新処理
//=============================================================================
void UpdateInput(void)
{
	HRESULT hr;
	bool aKeyStateOld[JOYPADKEY_MAX];

	for (int nCntPad = 0; nCntPad < NUM_JOYPAD_MAX; nCntPad++)
	{
		if (g_apDIDevJoypad[nCntPad] == NULL)
		{
			return;
		}

		// 前回のデータを保存
		for (int nCntKey = 0; nCntKey < JOYPADKEY_MAX; nCntKey++)
		{
			aKeyStateOld[nCntKey] = g_aKeyStateJoypad[nCntPad][nCntKey];
		}

		// デバイスからデータを取得
		hr = g_apDIDevJoypad[nCntPad]->GetDeviceState(sizeof(g_aJoypadState[nCntPad]), &g_aJoypadState[nCntPad]);
		if (SUCCEEDED(hr))
		{
			// キー情報設定
			SetKeyStateJoypad(nCntPad);
			//	軸位置を記録
			g_aKeyStateAxis[nCntPad].x = (float)g_aJoypadState[nCntPad].lX / JOY_MAX_RANGE;
			g_aKeyStateAxis[nCntPad].y = (float)g_aJoypadState[nCntPad].lY / JOY_MAX_RANGE;
			g_aKeyStateAxis[nCntPad].z = (float)g_aJoypadState[nCntPad].lZ / JOY_MAX_RANGE;

			for (int nCntKey = 0; nCntKey < JOYPADKEY_MAX; nCntKey++)
			{
				// トリガー・リリース情報の作成
				g_aKeyStateTriggerJoypad[nCntPad][nCntKey] = (aKeyStateOld[nCntKey] ^ g_aKeyStateJoypad[nCntPad][nCntKey]) & g_aKeyStateJoypad[nCntPad][nCntKey];
				g_aKeyStateReleaseJoypad[nCntPad][nCntKey] = (aKeyStateOld[nCntKey] ^ g_aKeyStateJoypad[nCntPad][nCntKey]) & !g_aKeyStateJoypad[nCntPad][nCntKey];

				// リピート情報の作成
				g_aKeyStateRepeatJoypad[nCntPad][nCntKey] = g_aKeyStateTriggerJoypad[nCntPad][nCntKey];
				if (g_aKeyStateJoypad[nCntPad][nCntKey])
				{
					g_aKeyStateRepeatCntJoypad[nCntPad][nCntKey]++;
					if (g_aKeyStateRepeatCntJoypad[nCntPad][nCntKey] < g_nCountWaitRepeat)
					{
						if (g_aKeyStateRepeatCntJoypad[nCntPad][nCntKey] == 1
							|| g_aKeyStateRepeatCntJoypad[nCntPad][nCntKey] >= g_nCountWaitRepeat)
						{
							g_aKeyStateRepeatJoypad[nCntPad][nCntKey] = g_aKeyStateJoypad[nCntPad][nCntKey];
						}
						else
						{
							g_aKeyStateRepeatJoypad[nCntPad][nCntKey] = 0;
						}
					}
					else
					{
						if (((g_aKeyStateRepeatCntJoypad[nCntPad][nCntKey] - g_nCountWaitRepeat) % g_nIntervalRepeat) == 0)
						{
							g_aKeyStateRepeatJoypad[nCntPad][nCntKey] = g_aKeyStateJoypad[nCntPad][nCntKey];
						}
						else
						{
							g_aKeyStateRepeatJoypad[nCntPad][nCntKey] = 0;
						}
					}
				}
				else
				{
					g_aKeyStateRepeatCntJoypad[nCntPad][nCntKey] = 0;
					g_aKeyStateRepeatJoypad[nCntPad][nCntKey] = 0;
				}
			}
		}
		else
		{
			g_apDIDevJoypad[nCntPad]->Acquire();
		}
	}
}
//=============================================================================
// ジョイスティックコールバック関数
//=============================================================================
BOOL CALLBACK EnumJoyCallbackJoypad(const DIDEVICEINSTANCE* lpddi, VOID* pvRef)
{
	static GUID pad_discrimination[2];	// 各デバイスの識別子を格納
	DIDEVCAPS	diDevCaps;				// デバイス情報
	HRESULT		hRes;


	// ジョイスティック用デバイスオブジェクトを作成
	hRes = g_apInput->CreateDevice(lpddi->guidInstance, &g_apDIDevJoypad[g_nCntPad], NULL);
	if (FAILED(hRes))
	{
		return DIENUM_CONTINUE;		// 列挙を続ける
	}

	// ジョイスティックの能力を調べる
	diDevCaps.dwSize = sizeof(DIDEVCAPS);
	hRes = g_apDIDevJoypad[g_nCntPad]->GetCapabilities(&diDevCaps);
	if (FAILED(hRes))
	{
		if (g_apDIDevJoypad[g_nCntPad])
		{
			g_apDIDevJoypad[g_nCntPad]->Release();
			g_apDIDevJoypad[g_nCntPad] = NULL;
		}
		// 列挙を続ける
		return DIENUM_CONTINUE;		
	}

	// デバイスの識別子を保存
	pad_discrimination[g_nCntPad] = lpddi->guidInstance;

	// このデバイスを使うので列挙を終了する
	return DIENUM_STOP;		
}

BOOL CALLBACK EnumAxesCallbackJoypad(const LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef)
{
	HRESULT hr;

	for (int nCntPad = 0; nCntPad < 2; nCntPad++)
	{
		DIPROPRANGE diprg;

		// スティック軸の値の範囲を設定（-32768〜32767）
		ZeroMemory(&diprg, sizeof(diprg));
		diprg.diph.dwSize = sizeof(diprg);
		diprg.diph.dwHeaderSize = sizeof(diprg.diph);
		diprg.diph.dwObj = lpddoi->dwType;
		diprg.diph.dwHow = DIPH_BYID;
		diprg.lMin = -32768;
		diprg.lMax = 32767;

		if (g_apDIDevJoypad[nCntPad] != NULL)
		{
			hr = g_apDIDevJoypad[nCntPad]->SetProperty(DIPROP_RANGE, &diprg.diph);
			if (FAILED(hr))
			{
				return DIENUM_STOP;
			}
		}
	}

	return DIENUM_CONTINUE;
}

//=============================================================================
// ジョイパッドのキー情報設定
//=============================================================================
void SetKeyStateJoypad(int nIDPad)
{
	if (g_aJoypadState[nIDPad].rgdwPOV[0] >= 225 * 100 && g_aJoypadState[nIDPad].rgdwPOV[0] <= 315 * 100)
	{// 十字キー[左]が押されている
		g_aKeyStateJoypad[nIDPad][JOYPADKEY_LEFT] = true;
	}
	else
	{
		g_aKeyStateJoypad[nIDPad][JOYPADKEY_LEFT] = false;
	}

	if (g_aJoypadState[nIDPad].rgdwPOV[0] >= 45 * 100 && g_aJoypadState[nIDPad].rgdwPOV[0] <= 135 * 100)
	{// 十字キー[右]が押されている
		g_aKeyStateJoypad[nIDPad][JOYPADKEY_RIGHT] = true;
	}
	else
	{
		g_aKeyStateJoypad[nIDPad][JOYPADKEY_RIGHT] = false;
	}

	if ((g_aJoypadState[nIDPad].rgdwPOV[0] >= 315 * 100 && g_aJoypadState[nIDPad].rgdwPOV[0] <= 360 * 100)
		|| (g_aJoypadState[nIDPad].rgdwPOV[0] >= 0 * 100 && g_aJoypadState[nIDPad].rgdwPOV[0] <= 45 * 100))
	{// 十字キー[上]が押されている
		g_aKeyStateJoypad[nIDPad][JOYPADKEY_UP] = true;
	}
	else
	{
		g_aKeyStateJoypad[nIDPad][JOYPADKEY_UP] = false;
	}

	if (g_aJoypadState[nIDPad].rgdwPOV[0] >= 135 * 100 && g_aJoypadState[nIDPad].rgdwPOV[0] <= 225 * 100)
	{// 十字キー[下]が押されている
		g_aKeyStateJoypad[nIDPad][JOYPADKEY_DOWN] = true;
	}
	else
	{
		g_aKeyStateJoypad[nIDPad][JOYPADKEY_DOWN] = false;
	}

	for (int nKey = JOYPADKEY_X; nKey <= JOYPADKEY_START; nKey++)
	{
		if (g_aJoypadState[nIDPad].rgbButtons[nKey])
		{// ボタンが押されている
			g_aKeyStateJoypad[nIDPad][nKey] = true;
		}
		else
		{
			g_aKeyStateJoypad[nIDPad][nKey] = false;
		}
	}
}

//=============================================================================
// ジョイパッド情報取得
//=============================================================================
bool GetJoypadPress(int nIDPad, JOYPADKEY key)
{
	return g_aKeyStateJoypad[nIDPad][key];
}

//=============================================================================
// ジョイパッド情報取得
//=============================================================================
bool GetJoypadTrigger(int nIDPad, JOYPADKEY key)
{
	return g_aKeyStateTriggerJoypad[nIDPad][key];
}

//=============================================================================
// ジョイパッド情報取得
//=============================================================================
bool GetJoypadRelease(int nIDPad, JOYPADKEY key)
{
	return g_aKeyStateReleaseJoypad[nIDPad][key];
}

//=============================================================================
// ジョイパッド情報取得
//=============================================================================
bool GetJoypadRepeat(int nIDPad, JOYPADKEY key)
{
	return g_aKeyStateRepeatJoypad[nIDPad][key];
}

//=============================================================================
// ジョイパッドのトリガー(左)の値取得
//=============================================================================
int GetJoypadTriggerLeft(int nIDPad)
{
	return g_aJoypadState[nIDPad].rgbButtons[JOYPADKEY_LEFT_TRIGGER];
}

//=============================================================================
// ジョイパッドのトリガー(右)の値取得
//=============================================================================
int GetJoypadTriggerRight(int nIDPad)
{
	return g_aJoypadState[nIDPad].rgbButtons[JOYPADKEY_RIGHT_TRIGGER];
}

//=============================================================================
// ジョイパッドのアナログスティック(左)の値取得
//=============================================================================
void GetJoypadStickLeft(int nIDPad, int *pValueH, int *pValueV)
{
	*pValueH = g_aJoypadState[nIDPad].lX;
	*pValueV = -g_aJoypadState[nIDPad].lY;
}

//=============================================================================
// ジョイパッドのアナログスティック(右)の値取得
//=============================================================================
void GetJoypadStickRight(int nIDPad, int *pValueH, int *pValueV)
{
	*pValueH = g_aJoypadState[nIDPad].lZ;
	*pValueV = -g_aJoypadState[nIDPad].lRz;
}
