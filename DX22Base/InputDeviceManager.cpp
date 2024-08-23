#include "InputDeviceManager.h"

//=================================
//	コンストラクタ
//	関数概要：コンストラクタ(DirectX用)
//	クラス：InputDeviceManager
//	引　数：なし
//	返り値：なし
//=================================
InputDeviceManager::InputDeviceManager()
	: Singleton(UPDATE_ORDER::FIRST_UPDATE)
	, m_bIsVibration(false)
	, m_hWnd(NULL)
	, m_keyOldState{ 0 }
	, m_keyState{ 0 }
	, m_nCntConnect(0)
	, m_nLimitFrameVibration(0)
	, m_nVibrationUser(0)
{
	//-----初期化-----
	ZeroMemory(m_xInputPadOldState, sizeof(m_xInputPadOldState));
	ZeroMemory(m_xInputPadState, sizeof(m_xInputPadState));


}


//=================================
//	デストラクタ
//	関数概要：デストラクタ
//	クラス：InputDeviceManager
//	引　数：なし
//	返り値：なし
//=================================
InputDeviceManager::~InputDeviceManager()
{

}

void InputDeviceManager::SetHWND(HWND hWnd)
{
	m_hWnd = hWnd;
}

//=================================
//	Init
//	関数概要：初期化(DirectX用)
//	クラス：InputDeviceManager
//	引　数：hWnd	HWND型	ウィンドウハンドル
//	返り値：成否	bool型
//=================================
bool InputDeviceManager::Init()
{
	//-----変数宣言-----
	bool bResult;

	//-----DirectX入力初期化-----
	bResult = KeyInputInit(m_hWnd);
	if (!bResult)
	{
		MessageBox(NULL, "キーボード入力初期化失敗", "Error", MB_OK);
		return false;
	}

	bResult = XInputInit();
	if (!bResult)
	{
		MessageBox(NULL, "XInput入力初期化失敗", "Error", MB_OK);
		return false;
	}

	return true;
}

//=================================
//	KeyInputInit
//	関数概要：キーボード入力初期化
//	クラス：InputDeviceManager
//	引　数：hWnd	HWND型	ウィンドウハンドル
//	返り値：成否	bool型
//=================================
bool InputDeviceManager::KeyInputInit(HWND hWnd)
{
	//ウィンドウハンドルを設定
	m_hWnd = hWnd;

	//マウス座標を初期化
	m_mousePos = {0.0f,0.0f};

	//キー入力配列を初期化
	for (int i = 0; i < KEY_MAX; i++)
	{
		m_keyState[i] = 0;
		m_keyOldState[i] = 0;
	}

	return true;
}

//=================================
//	XInputInit
//	関数概要：XInput入力初期化
//	クラス：InputDeviceManager
//	引　数：なし
//	返り値：成否	bool型
//=================================
bool InputDeviceManager::XInputInit(void)
{
	//-----初期化-----
	//ゲームパッド状態の初期化
	ZeroMemory(m_xInputPadState, sizeof(m_xInputPadState));
	ZeroMemory(m_xInputPadOldState, sizeof(m_xInputPadOldState));
	m_nCntConnect = 0;

	//振動パラメータの初期化
	m_bIsVibration = false;
	m_nLimitFrameVibration = 0;
	m_nVibrationUser = 0;

	return true;
}

//=================================
//	Update
//	関数概要：更新
//	クラス：InputDeviceManager
//	引　数：なし
//	返り値：なし
//=================================
void InputDeviceManager::Update(void)
{
	//-----DirectX入力更新-----
	KeyInputUpdate();
	XInputUpdate();
}

//=================================
//	KeyInputUpdate
//	関数概要：キーボード入力更新
//	クラス：InputDeviceManager
//	引　数：なし
//	返り値：なし
//=================================
void InputDeviceManager::KeyInputUpdate(void)
{
	//------キー配列を更新-----
	memcpy(m_keyOldState, m_keyState, sizeof(m_keyOldState));
	GetKeyboardState(m_keyState);

	//------マウス座標を更新------
	POINT cursorPos;
	GetCursorPos(&cursorPos);			//画面座標取得
	ScreenToClient(m_hWnd, &cursorPos);	//クライアント座標に変換

	//CMultiBuildManager& manager = CMultiBuildManager::GetInstance();
	//int width = manager.GetWindowWidth();	//画面横幅
	//int height = manager.GetWindowHeight();	//画面縦幅

	RECT clientRect;
	GetClientRect(m_hWnd, &clientRect);

	int height = clientRect.bottom - clientRect.top;
	int width = clientRect.right - clientRect.left;

	//float posX = ((float)cursorPos.x - (float)width / 2.0f)  / (float)width;	//X座標の原点を中央に補正
	//float rateY = ((float)cursorPos.y - (float)height / 2.0f) / (float)height;	//Y座標の原点を中央に補正
	//float posY = (float)height * rateY / (float)width;	//横幅基準の座標に補正

	float posX = ((float)width / 2.0f - (float)cursorPos.x) * -1.0f / (float)width;
	float rateY = ((float)height / 2.0f - (float)cursorPos.y) * -1.0f / (float)height;
	float posY = rateY * (float)height / (float)width;


	//マウス座標確定
	m_mousePos.x = posX;
	m_mousePos.y = posY;


}

//=================================
//	XInputUpdate
//	関数概要：XInput入力更新
//	クラス：InputDeviceManager
//	引　数：なし
//	返り値：なし
//=================================
void InputDeviceManager::XInputUpdate(void)
{
	//------XInput入力を更新------
	memcpy(m_xInputPadOldState, m_xInputPadState, sizeof(m_xInputPadOldState));	//過去情報を退避

	m_nCntConnect = 0;

	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));

		DWORD dwResult = XInputGetState(i, &state);

		if (dwResult != ERROR_SUCCESS)
		{
			//接続エラー
			break;
		}

		m_xInputPadState[i] = state.Gamepad;//ゲームパッドの状態を取得

		m_nCntConnect++;	//接続数を増加
	}

	//-----振動パラメータを更新-----
	if (m_bIsVibration)
	{
		//振動中
		m_nLimitFrameVibration--;	//振動残りフレームを更新

		if (m_nLimitFrameVibration < 1)
		{
			//振動終了
			XINPUT_VIBRATION vibe;
			ZeroMemory(&vibe, sizeof(XINPUT_VIBRATION));
			vibe.wLeftMotorSpeed = 0;
			vibe.wRightMotorSpeed = 0;
			XInputSetState(m_nVibrationUser, &vibe);	//振動を0に

			m_bIsVibration = false;	//振動終了
		}
	}
}


//=================================
//	IsTrigger
//	関数概要：トリガー入力
//	クラス：InputDeviceManager
//	引　数：code	KeyCodes型	キーコード
//	返り値：判定	bool型
//=================================
bool InputDeviceManager::IsTrigger(KeyCodes code)
{
	//キーを判定
	int index = static_cast<int>(code);
	return ((~m_keyOldState[index]) & m_keyState[index]) & 0x80;

	return false;

}

//=================================
//	IsTrigger
//	関数概要：トリガー入力
//	クラス：InputDeviceManager
//	引　数：
//		code	PadCodes型	キーコード
//		user	int型			コントローラの番号(0～3)
//	返り値：判定	bool型
//=================================
bool InputDeviceManager::IsTrigger(PadCodes code, int user)
{
	//キーを判定
	if (user > m_nCntConnect - 1)
	{
		//未接続ユーザ
		return false;
	}

	if (code == PadCodes::LT)
	{
		//Lトリガー
		bool now = (m_xInputPadState[user].bLeftTrigger > 0);
		bool old = (m_xInputPadOldState[user].bLeftTrigger > 0);

		return (!old && now);
	}

	if (code == PadCodes::RT)
	{
		//Rトリガー
		bool now = (m_xInputPadState[user].bRightTrigger > 0);
		bool old = (m_xInputPadOldState[user].bRightTrigger > 0);

		return (!old && now);
	}

	int index = static_cast<int>(code);
	WORD old = m_xInputPadOldState[user].wButtons & index;
	WORD now = m_xInputPadState[user].wButtons & index;

	return (~old) & now;

}


//=================================
//	IsRelease
//	関数概要：リリース入力
//	クラス：InputDeviceManager
//	引　数：code	KeyCodes型	キーコード
//	返り値：判定	bool型
//=================================
bool InputDeviceManager::IsRelease(KeyCodes code)
{
	//キーを判定
	int index = static_cast<int>(code);
	return (m_keyOldState[index] & (~m_keyState[index])) & 0x80;

}

//=================================
//	IsRelease
//	関数概要：リリース入力
//	クラス：InputDeviceManager
//	引　数：
//		code	PadCodes型	キーコード
//		user	int型			コントローラの番号(0～3)
//	返り値：判定	bool型
//=================================
bool InputDeviceManager::IsRelease(PadCodes code, int user)
{
	//キーを判定
	if (user > m_nCntConnect - 1)
	{
		//未接続ユーザ
		return false;
	}

	if (code == PadCodes::LT)
	{
		//Lトリガー
		bool now = (m_xInputPadState[user].bLeftTrigger > 0);
		bool old = (m_xInputPadOldState[user].bLeftTrigger > 0);

		return (old && !now);
	}

	if (code == PadCodes::RT)
	{
		//Rトリガー
		bool now = (m_xInputPadState[user].bRightTrigger > 0);
		bool old = (m_xInputPadOldState[user].bRightTrigger > 0);

		return (old && !now);
	}

	int index = static_cast<int>(code);
	WORD old = m_xInputPadOldState[user].wButtons & index;
	WORD now = m_xInputPadState[user].wButtons & index;

	return old & (~now);


}


//=================================
//	IsPress
//	関数概要：プレス入力
//	クラス：InputDeviceManager
//	引　数：code	KeyCodes型	キーコード
//	返り値：判定	bool型
//=================================
bool InputDeviceManager::IsPress(KeyCodes code)
{
	//キーを判定
	int index = static_cast<int>(code);
	return m_keyState[index] & 0x80;

}

//=================================
//	IsPress
//	関数概要：プレス入力
//	クラス：InputDeviceManager
//	引　数：
//		code	PadCodes型	キーコード
//		user	int型			コントローラの番号(0～3)
//	返り値：判定	bool型
//=================================
bool InputDeviceManager::IsPress(PadCodes code, int user)
{
	//キーを判定
	if (user > m_nCntConnect - 1)
	{
		//未接続ユーザ
		return false;
	}

	if (code == PadCodes::LT)
	{
		//Lトリガー
		bool now = (m_xInputPadState[user].bLeftTrigger > 0);

		return now;
	}

	if (code == PadCodes::RT)
	{
		//Rトリガー
		bool now = (m_xInputPadState[user].bRightTrigger > 0);

		return now;
	}


	int index = static_cast<int>(code);
	WORD now = m_xInputPadState[user].wButtons & index;

	return now;

}


//=================================
//	GetLeftStick
//	関数概要：左スティックを取得
//	クラス：InputDeviceManager
//	引　数：user	int型		コントローラの番号(0～3)
//	返り値：入力	fVec2型
//=================================
fVec2 InputDeviceManager::GetLeftStick(int user)
{
	//-----DirectX処理------
	if (user > m_nCntConnect - 1)
	{
		//未接続ユーザ
		return {0.0f,0.0f};
	}

	int stickX = m_xInputPadState[user].sThumbLX;
	int stickY = -m_xInputPadState[user].sThumbLY;	//Switch用に上下反転

	float rateX = (float)stickX / 32768.0f;
	float rateY = (float)stickY / 32768.0f;

	return { rateX, rateY };

}

//=================================
//	GetRightStick
//	関数概要：右スティックを取得
//	クラス：InputDeviceManager
//	引　数：user	int型		コントローラの番号(0～3)
//	返り値：入力	fVec2型
//=================================
fVec2 InputDeviceManager::GetRightStick(int user)
{
	//-----DirectX処理------
	if (user > m_nCntConnect - 1)
	{
		//未接続ユーザ
		return {0.0f,0.0f};
	}

	int stickX = m_xInputPadState[user].sThumbRX;
	int stickY = -m_xInputPadState[user].sThumbRY;	//Switch用に上下反転

	float rateX = (float)stickX / 32768.0f;
	float rateY = (float)stickY / 32768.0f;

	return { rateX, rateY };

}

//=================================
//	GetTouch
//	関数概要：タッチ判定を取得
//	クラス：InputDeviceManager
//	引　数：なし
//	返り値：入力	tTouchState型
//=================================
InputDeviceManager::tTouchState	InputDeviceManager::GetTouch(void)
{
	//-----変数宣言-----
	tTouchState ans;	//計算結果

	//-----DirectX処理------
	if (InputDeviceManager::IsPress(KeyCodes::Mouse_L))
	{
		//クリック判定
		ans.nCntTouch = 1;
		ans.touchPos[0] = m_mousePos;

	}
	else
	{
		//クリックなし
		ans.nCntTouch = 0;
	}


	return ans;
}

//=================================
//	GetLeftAccel
//	関数概要：左コントローラーの加速度(Switch用)
//	クラス：InputDeviceManager
//	引　数：dxVec	fVec3型	DX稼動時の返り値	
//	返り値：入力	fVec3型
//=================================
fVec3 InputDeviceManager::GetLeftAccel(fVec3 dxVec)
{
	//-----DirectX処理------
	return dxVec;
}

//=================================
//	GetRightAccel
//	関数概要：右コントローラーの加速度(Switch用)
//	クラス：InputDeviceManager
//	引  数：dxVec	fVec3型	DX稼動時の返り値	
//	返り値：入力	fVec3型
//=================================
fVec3 InputDeviceManager::GetRightAccel(fVec3 dxVec)
{
	//-----DirectX処理------
	return dxVec;
}

//=================================
//	GetLeftAngle
//	関数概要：左コントローラーのジャイロ(Switch用)
//	クラス：InputDeviceManager
//	引　数：dxVec	fVec3型	DX稼動時の返り値	
//	返り値：入力	fVec3型
//=================================
fVec3 InputDeviceManager::GetLeftAngle(fVec3 dxVec)
{
	//-----DirectX処理------
	return dxVec;
}

//=================================
//	GetRightAngle
//	関数概要：右コントローラーのジャイロ(Switch用)
//	クラス：InputDeviceManager
//	引　数：dxVec	fVec3型	DX稼動時の返り値	
//	返り値：入力	fVec3型
//=================================
fVec3 InputDeviceManager::GetRightAngle(fVec3 dxVec)
{
	//-----DirectX処理------
	return dxVec;
}

//=================================
//	SetLeftVibration
//	関数概要：左コントローラーのジャイロ(Switch用)
//	クラス：InputDeviceManager
//	引　数：
//		frame	int型	振動するフレーム	
//		user	int型	コントローラ番号
//	返り値：なし
//=================================
void InputDeviceManager::SetLeftVibration(int frame, int user)
{
	//-----振動を設定-----
	//-----DirectX処理------
	m_bIsVibration = true;
	m_nLimitFrameVibration = frame;
	m_nVibrationUser = user;

	XINPUT_VIBRATION vibe;
	ZeroMemory(&vibe, sizeof(XINPUT_VIBRATION));
	vibe.wLeftMotorSpeed = VIBRATION_SPEED;
	vibe.wRightMotorSpeed = 0;
	XInputSetState(m_nVibrationUser, &vibe);	//振動を0に

}

//=================================
//	SetRightVibration
//	関数概要：右コントローラーのジャイロ(Switch用)
//	クラス：InputDeviceManager
//	引　数：
//		frame	int型	振動するフレーム	
//		user	int型	コントローラ番号
//	返り値：なし
//=================================
void InputDeviceManager::SetRightVibration(int frame, int user)
{
	//-----振動を設定-----
	//-----DirectX処理------
	m_bIsVibration = true;
	m_nLimitFrameVibration = frame;
	m_nVibrationUser = user;

	XINPUT_VIBRATION vibe;
	ZeroMemory(&vibe, sizeof(XINPUT_VIBRATION));
	vibe.wLeftMotorSpeed = 0;
	vibe.wRightMotorSpeed = VIBRATION_SPEED;
	XInputSetState(m_nVibrationUser, &vibe);	//振動を0に

}

//=================================
//	IsTrigger
//	関数概要：トリガー入力
//	名前空間：InputDevice
//	引　数：code	KeyCodes型	キーコード
//	返り値：判定	bool型
//=================================
bool	InputDevice::IsTrigger(KeyCodes code)
{
	InputDeviceManager& controller = InputDeviceManager::GetInstance();
	return controller.IsTrigger(code);
}

//=================================
//	IsPress
//	関数概要：プレス入力
//	名前空間：InputDevice
//	引　数：code	KeyCodes型	キーコード
//	返り値：判定	bool型
//=================================
bool	InputDevice::IsPress(KeyCodes code)
{
	InputDeviceManager& controller = InputDeviceManager::GetInstance();
	return controller.IsPress(code);
}

//=================================
//	IsRelease
//	関数概要：リリース入力
//	名前空間：InputDevice
//	引　数：code	KeyCodes型	キーコード
//	返り値：判定	bool型
//=================================
bool	InputDevice::IsRelease(KeyCodes code)
{
	InputDeviceManager& controller = InputDeviceManager::GetInstance();
	return controller.IsRelease(code);
}

//=================================
//	IsTrigger
//	関数概要：トリガー入力
//	名前空間：InputDevice
//	引　数：
//		code	PadCodes型	キーコード
//		user	int型			コントローラの番号(0～3)
//	返り値：判定	bool型
//=================================
bool	InputDevice::IsTrigger(PadCodes code, int user)
{
	InputDeviceManager& controller = InputDeviceManager::GetInstance();
	return controller.IsTrigger(code, user);
}

//=================================
//	IsPress
//	関数概要：プレス入力
//	名前空間：InputDevice
//	引　数：
//		code	PadCodes型	キーコード
//		user	int型			コントローラの番号(0～3)
//	返り値：判定	bool型
//=================================
bool	InputDevice::IsPress(PadCodes code, int user)
{
	InputDeviceManager& controller = InputDeviceManager::GetInstance();
	return controller.IsPress(code, user);
}

//=================================
//	IsRelease
//	関数概要：リリース入力
//	名前空間：InputDevice
//	引　数：
//		code	PadCodes型	キーコード
//		user	int型			コントローラの番号(0～3)
//	返り値：判定	bool型
//=================================
bool	InputDevice::IsRelease(PadCodes code, int user)
{
	InputDeviceManager& controller = InputDeviceManager::GetInstance();
	return controller.IsRelease(code, user);
}


//=================================
//	GetLeftStick
//	関数概要：左スティック入力
//	名前空間：InputDevice
//	引　数：user	int型	コントローラの番号(0～3)
//	返り値：入力	fVec2型
//=================================
fVec2	InputDevice::GetLeftStick(int user)
{
	InputDeviceManager& controller = InputDeviceManager::GetInstance();
	return controller.GetLeftStick(user);
}

//=================================
//	GetLeftStick
//	関数概要：左スティック入力
//	名前空間：InputDevice
//	引　数：なし
//	返り値：入力	fVec2型
//=================================
fVec2	InputDevice::GetLeftStick(void)
{
	InputDeviceManager& controller = InputDeviceManager::GetInstance();
	return controller.GetLeftStick(0);
}

//=================================
//	GetRightStick
//	関数概要：右スティック入力
//	名前空間：InputDevice
//	引　数：user	int型	コントローラの番号(0～3)
//	返り値：入力	fVec2型
//=================================
fVec2	InputDevice::GetRightStick(int user)
{
	InputDeviceManager& controller = InputDeviceManager::GetInstance();
	return controller.GetRightStick(user);
}

//=================================
//	GetRightStick
//	関数概要：右スティック入力
//	名前空間：InputDevice
//	引　数：なし
//	返り値：入力	fVec2型
//=================================
fVec2	InputDevice::GetRightStick(void)
{
	InputDeviceManager& controller = InputDeviceManager::GetInstance();
	return controller.GetRightStick(0);
}

//=================================
//	GetTouchs
//	関数概要：タッチ判定を取得
//	名前空間：InputDevice
//	引　数：なし
//	返り値：入力	tTouchState型
//=================================
InputDeviceManager::tTouchState	InputDevice::GetTouchs(void)
{
	InputDeviceManager& controller = InputDeviceManager::GetInstance();
	return controller.GetTouch();
}

//=================================
//	SetLeftVibration
//	関数概要：左コントローラーのジャイロ(Switch用)
//	名前空間：InputDevice
//	引　数：
//		frame	int型	振動するフレーム	
//		user	int型	コントローラ番号
//	返り値：なし
//=================================
void	InputDevice::SetLeftVibration(int frame, int user)
{
	InputDeviceManager& controller = InputDeviceManager::GetInstance();
	controller.SetLeftVibration(frame, user);
}

//=================================
//	SetLeftVibration
//	関数概要：左コントローラーのジャイロ(Switch用)
//	名前空間：InputDevice
//	引　数：frame	int型	振動するフレーム	
//	返り値：なし
//=================================
void	InputDevice::SetLeftVibration(int frame)
{
	InputDeviceManager& controller = InputDeviceManager::GetInstance();
	controller.SetLeftVibration(frame, 0);
}

//=================================
//	SetRightVibration
//	関数概要：右コントローラーのジャイロ(Switch用)
//	名前空間：InputDevice
//	引　数：
//		frame	int型	振動するフレーム	
//		user	int型	コントローラ番号
//	返り値：なし
//=================================
void	InputDevice::SetRightVibration(int frame, int user)
{
	InputDeviceManager& controller = InputDeviceManager::GetInstance();
	controller.SetRightVibration(frame, user);
}

//=================================
//	SetRightVibration
//	関数概要：右コントローラーのジャイロ(Switch用)
//	名前空間：InputDevice
//	引　数：frame	int型	振動するフレーム	
//	返り値：なし
//=================================
void	InputDevice::SetRightVibration(int frame)
{
	InputDeviceManager& controller = InputDeviceManager::GetInstance();
	controller.SetRightVibration(frame, 0);
}

//=================================
//	GetLeftAccel
//	関数概要：左コントローラーの加速度(Switch用)
//	名前空間：InputDevice
//	引　数：dxVec	fVec3型	DX稼動時の返り値	
//	返り値：入力	fVec3型
//=================================
fVec3	InputDevice::GetLeftAccel(fVec3 dxVec)
{
	InputDeviceManager& controller = InputDeviceManager::GetInstance();
	return controller.GetLeftAccel(dxVec);
}

//=================================
//	GetLeftAccel
//	関数概要：左コントローラーの加速度(Switch用)
//	名前空間：InputDevice
//	引　数：なし	
//	返り値：入力	fVec3型
//=================================
fVec3	InputDevice::GetLeftAccel(void)
{
	InputDeviceManager& controller = InputDeviceManager::GetInstance();
	return controller.GetLeftAccel({0.0f,0.0f,0.0f});
}

//=================================
//	GetRightAccel
//	関数概要：右コントローラーの加速度(Switch用)
//	名前空間：InputDevice
//	引　数：dxVec	fVec3型	DX稼動時の返り値	
//	返り値：入力	fVec3型
//=================================
fVec3	InputDevice::GetRightAccel(fVec3 dxVec)
{
	InputDeviceManager& controller = InputDeviceManager::GetInstance();
	return controller.GetRightAccel(dxVec);
}

//=================================
//	GetRightAccel
//	関数概要：右コントローラーの加速度(Switch用)
//	名前空間：InputDevice
//	引　数：なし	
//	返り値：入力	fVec3型
//=================================
fVec3	InputDevice::GetRightAccel(void)
{
	InputDeviceManager& controller = InputDeviceManager::GetInstance();
	return controller.GetRightAccel({0.0f,0.0f,0.0f});
}

//=================================
//	GetLeftAngle
//	関数概要：左コントローラーのジャイロ(Switch用)
//	名前空間：InputDevice
//	引　数：dxVec	fVec3型	DX稼動時の返り値	
//	返り値：入力	fVec3型
//=================================
fVec3	InputDevice::GetLeftAngle(fVec3 dxVec)
{
	InputDeviceManager& controller = InputDeviceManager::GetInstance();
	return controller.GetLeftAngle(dxVec);
}

//=================================
//	GetLeftAngle
//	関数概要：左コントローラーのジャイロ(Switch用)
//	名前空間：InputDevice
//	引　数：なし	
//	返り値：入力	fVec3型
//=================================
fVec3	InputDevice::GetLeftAngle(void)
{
	InputDeviceManager& controller = InputDeviceManager::GetInstance();
	return controller.GetLeftAngle({0.0f,0.0f,0.0f});
}

//=================================
//	GetRightAngle
//	関数概要：右コントローラーのジャイロ(Switch用)
//	名前空間：InputDevice
//	引　数：dxVec	fVec3型	DX稼動時の返り値	
//	返り値：入力	fVec3型
//=================================
fVec3	InputDevice::GetRightAngle(fVec3 dxVec)
{
	InputDeviceManager& controller = InputDeviceManager::GetInstance();
	return controller.GetRightAngle(dxVec);
}

//=================================
//	GetRightAngle
//	関数概要：右コントローラーのジャイロ(Switch用)
//	名前空間：InputDevice
//	引　数：なし	
//	返り値：入力	fVec3型
//=================================
fVec3	InputDevice::GetRightAngle(void)
{
	InputDeviceManager& controller = InputDeviceManager::GetInstance();
	return controller.GetRightAngle({0.0f,0.0f,0.0f});
}

