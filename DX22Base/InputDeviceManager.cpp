#include "InputDeviceManager.h"

//=================================
//	�R���X�g���N�^
//	�֐��T�v�F�R���X�g���N�^(DirectX�p)
//	�N���X�FInputDeviceManager
//	���@���F�Ȃ�
//	�Ԃ�l�F�Ȃ�
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
	//-----������-----
	ZeroMemory(m_xInputPadOldState, sizeof(m_xInputPadOldState));
	ZeroMemory(m_xInputPadState, sizeof(m_xInputPadState));


}


//=================================
//	�f�X�g���N�^
//	�֐��T�v�F�f�X�g���N�^
//	�N���X�FInputDeviceManager
//	���@���F�Ȃ�
//	�Ԃ�l�F�Ȃ�
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
//	�֐��T�v�F������(DirectX�p)
//	�N���X�FInputDeviceManager
//	���@���FhWnd	HWND�^	�E�B���h�E�n���h��
//	�Ԃ�l�F����	bool�^
//=================================
bool InputDeviceManager::Init()
{
	//-----�ϐ��錾-----
	bool bResult;

	//-----DirectX���͏�����-----
	bResult = KeyInputInit(m_hWnd);
	if (!bResult)
	{
		MessageBox(NULL, "�L�[�{�[�h���͏��������s", "Error", MB_OK);
		return false;
	}

	bResult = XInputInit();
	if (!bResult)
	{
		MessageBox(NULL, "XInput���͏��������s", "Error", MB_OK);
		return false;
	}

	return true;
}

//=================================
//	KeyInputInit
//	�֐��T�v�F�L�[�{�[�h���͏�����
//	�N���X�FInputDeviceManager
//	���@���FhWnd	HWND�^	�E�B���h�E�n���h��
//	�Ԃ�l�F����	bool�^
//=================================
bool InputDeviceManager::KeyInputInit(HWND hWnd)
{
	//�E�B���h�E�n���h����ݒ�
	m_hWnd = hWnd;

	//�}�E�X���W��������
	m_mousePos = {0.0f,0.0f};

	//�L�[���͔z���������
	for (int i = 0; i < KEY_MAX; i++)
	{
		m_keyState[i] = 0;
		m_keyOldState[i] = 0;
	}

	return true;
}

//=================================
//	XInputInit
//	�֐��T�v�FXInput���͏�����
//	�N���X�FInputDeviceManager
//	���@���F�Ȃ�
//	�Ԃ�l�F����	bool�^
//=================================
bool InputDeviceManager::XInputInit(void)
{
	//-----������-----
	//�Q�[���p�b�h��Ԃ̏�����
	ZeroMemory(m_xInputPadState, sizeof(m_xInputPadState));
	ZeroMemory(m_xInputPadOldState, sizeof(m_xInputPadOldState));
	m_nCntConnect = 0;

	//�U���p�����[�^�̏�����
	m_bIsVibration = false;
	m_nLimitFrameVibration = 0;
	m_nVibrationUser = 0;

	return true;
}

//=================================
//	Update
//	�֐��T�v�F�X�V
//	�N���X�FInputDeviceManager
//	���@���F�Ȃ�
//	�Ԃ�l�F�Ȃ�
//=================================
void InputDeviceManager::Update(void)
{
	//-----DirectX���͍X�V-----
	KeyInputUpdate();
	XInputUpdate();
}

//=================================
//	KeyInputUpdate
//	�֐��T�v�F�L�[�{�[�h���͍X�V
//	�N���X�FInputDeviceManager
//	���@���F�Ȃ�
//	�Ԃ�l�F�Ȃ�
//=================================
void InputDeviceManager::KeyInputUpdate(void)
{
	//------�L�[�z����X�V-----
	memcpy(m_keyOldState, m_keyState, sizeof(m_keyOldState));
	GetKeyboardState(m_keyState);

	//------�}�E�X���W���X�V------
	POINT cursorPos;
	GetCursorPos(&cursorPos);			//��ʍ��W�擾
	ScreenToClient(m_hWnd, &cursorPos);	//�N���C�A���g���W�ɕϊ�

	//CMultiBuildManager& manager = CMultiBuildManager::GetInstance();
	//int width = manager.GetWindowWidth();	//��ʉ���
	//int height = manager.GetWindowHeight();	//��ʏc��

	RECT clientRect;
	GetClientRect(m_hWnd, &clientRect);

	int height = clientRect.bottom - clientRect.top;
	int width = clientRect.right - clientRect.left;

	//float posX = ((float)cursorPos.x - (float)width / 2.0f)  / (float)width;	//X���W�̌��_�𒆉��ɕ␳
	//float rateY = ((float)cursorPos.y - (float)height / 2.0f) / (float)height;	//Y���W�̌��_�𒆉��ɕ␳
	//float posY = (float)height * rateY / (float)width;	//������̍��W�ɕ␳

	float posX = ((float)width / 2.0f - (float)cursorPos.x) * -1.0f / (float)width;
	float rateY = ((float)height / 2.0f - (float)cursorPos.y) * -1.0f / (float)height;
	float posY = rateY * (float)height / (float)width;


	//�}�E�X���W�m��
	m_mousePos.x = posX;
	m_mousePos.y = posY;


}

//=================================
//	XInputUpdate
//	�֐��T�v�FXInput���͍X�V
//	�N���X�FInputDeviceManager
//	���@���F�Ȃ�
//	�Ԃ�l�F�Ȃ�
//=================================
void InputDeviceManager::XInputUpdate(void)
{
	//------XInput���͂��X�V------
	memcpy(m_xInputPadOldState, m_xInputPadState, sizeof(m_xInputPadOldState));	//�ߋ�����ޔ�

	m_nCntConnect = 0;

	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));

		DWORD dwResult = XInputGetState(i, &state);

		if (dwResult != ERROR_SUCCESS)
		{
			//�ڑ��G���[
			break;
		}

		m_xInputPadState[i] = state.Gamepad;//�Q�[���p�b�h�̏�Ԃ��擾

		m_nCntConnect++;	//�ڑ����𑝉�
	}

	//-----�U���p�����[�^���X�V-----
	if (m_bIsVibration)
	{
		//�U����
		m_nLimitFrameVibration--;	//�U���c��t���[�����X�V

		if (m_nLimitFrameVibration < 1)
		{
			//�U���I��
			XINPUT_VIBRATION vibe;
			ZeroMemory(&vibe, sizeof(XINPUT_VIBRATION));
			vibe.wLeftMotorSpeed = 0;
			vibe.wRightMotorSpeed = 0;
			XInputSetState(m_nVibrationUser, &vibe);	//�U����0��

			m_bIsVibration = false;	//�U���I��
		}
	}
}


//=================================
//	IsTrigger
//	�֐��T�v�F�g���K�[����
//	�N���X�FInputDeviceManager
//	���@���Fcode	KeyCodes�^	�L�[�R�[�h
//	�Ԃ�l�F����	bool�^
//=================================
bool InputDeviceManager::IsTrigger(KeyCodes code)
{
	//�L�[�𔻒�
	int index = static_cast<int>(code);
	return ((~m_keyOldState[index]) & m_keyState[index]) & 0x80;

	return false;

}

//=================================
//	IsTrigger
//	�֐��T�v�F�g���K�[����
//	�N���X�FInputDeviceManager
//	���@���F
//		code	PadCodes�^	�L�[�R�[�h
//		user	int�^			�R���g���[���̔ԍ�(0�`3)
//	�Ԃ�l�F����	bool�^
//=================================
bool InputDeviceManager::IsTrigger(PadCodes code, int user)
{
	//�L�[�𔻒�
	if (user > m_nCntConnect - 1)
	{
		//���ڑ����[�U
		return false;
	}

	if (code == PadCodes::LT)
	{
		//L�g���K�[
		bool now = (m_xInputPadState[user].bLeftTrigger > 0);
		bool old = (m_xInputPadOldState[user].bLeftTrigger > 0);

		return (!old && now);
	}

	if (code == PadCodes::RT)
	{
		//R�g���K�[
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
//	�֐��T�v�F�����[�X����
//	�N���X�FInputDeviceManager
//	���@���Fcode	KeyCodes�^	�L�[�R�[�h
//	�Ԃ�l�F����	bool�^
//=================================
bool InputDeviceManager::IsRelease(KeyCodes code)
{
	//�L�[�𔻒�
	int index = static_cast<int>(code);
	return (m_keyOldState[index] & (~m_keyState[index])) & 0x80;

}

//=================================
//	IsRelease
//	�֐��T�v�F�����[�X����
//	�N���X�FInputDeviceManager
//	���@���F
//		code	PadCodes�^	�L�[�R�[�h
//		user	int�^			�R���g���[���̔ԍ�(0�`3)
//	�Ԃ�l�F����	bool�^
//=================================
bool InputDeviceManager::IsRelease(PadCodes code, int user)
{
	//�L�[�𔻒�
	if (user > m_nCntConnect - 1)
	{
		//���ڑ����[�U
		return false;
	}

	if (code == PadCodes::LT)
	{
		//L�g���K�[
		bool now = (m_xInputPadState[user].bLeftTrigger > 0);
		bool old = (m_xInputPadOldState[user].bLeftTrigger > 0);

		return (old && !now);
	}

	if (code == PadCodes::RT)
	{
		//R�g���K�[
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
//	�֐��T�v�F�v���X����
//	�N���X�FInputDeviceManager
//	���@���Fcode	KeyCodes�^	�L�[�R�[�h
//	�Ԃ�l�F����	bool�^
//=================================
bool InputDeviceManager::IsPress(KeyCodes code)
{
	//�L�[�𔻒�
	int index = static_cast<int>(code);
	return m_keyState[index] & 0x80;

}

//=================================
//	IsPress
//	�֐��T�v�F�v���X����
//	�N���X�FInputDeviceManager
//	���@���F
//		code	PadCodes�^	�L�[�R�[�h
//		user	int�^			�R���g���[���̔ԍ�(0�`3)
//	�Ԃ�l�F����	bool�^
//=================================
bool InputDeviceManager::IsPress(PadCodes code, int user)
{
	//�L�[�𔻒�
	if (user > m_nCntConnect - 1)
	{
		//���ڑ����[�U
		return false;
	}

	if (code == PadCodes::LT)
	{
		//L�g���K�[
		bool now = (m_xInputPadState[user].bLeftTrigger > 0);

		return now;
	}

	if (code == PadCodes::RT)
	{
		//R�g���K�[
		bool now = (m_xInputPadState[user].bRightTrigger > 0);

		return now;
	}


	int index = static_cast<int>(code);
	WORD now = m_xInputPadState[user].wButtons & index;

	return now;

}


//=================================
//	GetLeftStick
//	�֐��T�v�F���X�e�B�b�N���擾
//	�N���X�FInputDeviceManager
//	���@���Fuser	int�^		�R���g���[���̔ԍ�(0�`3)
//	�Ԃ�l�F����	fVec2�^
//=================================
fVec2 InputDeviceManager::GetLeftStick(int user)
{
	//-----DirectX����------
	if (user > m_nCntConnect - 1)
	{
		//���ڑ����[�U
		return {0.0f,0.0f};
	}

	int stickX = m_xInputPadState[user].sThumbLX;
	int stickY = -m_xInputPadState[user].sThumbLY;	//Switch�p�ɏ㉺���]

	float rateX = (float)stickX / 32768.0f;
	float rateY = (float)stickY / 32768.0f;

	return { rateX, rateY };

}

//=================================
//	GetRightStick
//	�֐��T�v�F�E�X�e�B�b�N���擾
//	�N���X�FInputDeviceManager
//	���@���Fuser	int�^		�R���g���[���̔ԍ�(0�`3)
//	�Ԃ�l�F����	fVec2�^
//=================================
fVec2 InputDeviceManager::GetRightStick(int user)
{
	//-----DirectX����------
	if (user > m_nCntConnect - 1)
	{
		//���ڑ����[�U
		return {0.0f,0.0f};
	}

	int stickX = m_xInputPadState[user].sThumbRX;
	int stickY = -m_xInputPadState[user].sThumbRY;	//Switch�p�ɏ㉺���]

	float rateX = (float)stickX / 32768.0f;
	float rateY = (float)stickY / 32768.0f;

	return { rateX, rateY };

}

//=================================
//	GetTouch
//	�֐��T�v�F�^�b�`������擾
//	�N���X�FInputDeviceManager
//	���@���F�Ȃ�
//	�Ԃ�l�F����	tTouchState�^
//=================================
InputDeviceManager::tTouchState	InputDeviceManager::GetTouch(void)
{
	//-----�ϐ��錾-----
	tTouchState ans;	//�v�Z����

	//-----DirectX����------
	if (InputDeviceManager::IsPress(KeyCodes::Mouse_L))
	{
		//�N���b�N����
		ans.nCntTouch = 1;
		ans.touchPos[0] = m_mousePos;

	}
	else
	{
		//�N���b�N�Ȃ�
		ans.nCntTouch = 0;
	}


	return ans;
}

//=================================
//	GetLeftAccel
//	�֐��T�v�F���R���g���[���[�̉����x(Switch�p)
//	�N���X�FInputDeviceManager
//	���@���FdxVec	fVec3�^	DX�ғ����̕Ԃ�l	
//	�Ԃ�l�F����	fVec3�^
//=================================
fVec3 InputDeviceManager::GetLeftAccel(fVec3 dxVec)
{
	//-----DirectX����------
	return dxVec;
}

//=================================
//	GetRightAccel
//	�֐��T�v�F�E�R���g���[���[�̉����x(Switch�p)
//	�N���X�FInputDeviceManager
//	��  ���FdxVec	fVec3�^	DX�ғ����̕Ԃ�l	
//	�Ԃ�l�F����	fVec3�^
//=================================
fVec3 InputDeviceManager::GetRightAccel(fVec3 dxVec)
{
	//-----DirectX����------
	return dxVec;
}

//=================================
//	GetLeftAngle
//	�֐��T�v�F���R���g���[���[�̃W���C��(Switch�p)
//	�N���X�FInputDeviceManager
//	���@���FdxVec	fVec3�^	DX�ғ����̕Ԃ�l	
//	�Ԃ�l�F����	fVec3�^
//=================================
fVec3 InputDeviceManager::GetLeftAngle(fVec3 dxVec)
{
	//-----DirectX����------
	return dxVec;
}

//=================================
//	GetRightAngle
//	�֐��T�v�F�E�R���g���[���[�̃W���C��(Switch�p)
//	�N���X�FInputDeviceManager
//	���@���FdxVec	fVec3�^	DX�ғ����̕Ԃ�l	
//	�Ԃ�l�F����	fVec3�^
//=================================
fVec3 InputDeviceManager::GetRightAngle(fVec3 dxVec)
{
	//-----DirectX����------
	return dxVec;
}

//=================================
//	SetLeftVibration
//	�֐��T�v�F���R���g���[���[�̃W���C��(Switch�p)
//	�N���X�FInputDeviceManager
//	���@���F
//		frame	int�^	�U������t���[��	
//		user	int�^	�R���g���[���ԍ�
//	�Ԃ�l�F�Ȃ�
//=================================
void InputDeviceManager::SetLeftVibration(int frame, int user)
{
	//-----�U����ݒ�-----
	//-----DirectX����------
	m_bIsVibration = true;
	m_nLimitFrameVibration = frame;
	m_nVibrationUser = user;

	XINPUT_VIBRATION vibe;
	ZeroMemory(&vibe, sizeof(XINPUT_VIBRATION));
	vibe.wLeftMotorSpeed = VIBRATION_SPEED;
	vibe.wRightMotorSpeed = 0;
	XInputSetState(m_nVibrationUser, &vibe);	//�U����0��

}

//=================================
//	SetRightVibration
//	�֐��T�v�F�E�R���g���[���[�̃W���C��(Switch�p)
//	�N���X�FInputDeviceManager
//	���@���F
//		frame	int�^	�U������t���[��	
//		user	int�^	�R���g���[���ԍ�
//	�Ԃ�l�F�Ȃ�
//=================================
void InputDeviceManager::SetRightVibration(int frame, int user)
{
	//-----�U����ݒ�-----
	//-----DirectX����------
	m_bIsVibration = true;
	m_nLimitFrameVibration = frame;
	m_nVibrationUser = user;

	XINPUT_VIBRATION vibe;
	ZeroMemory(&vibe, sizeof(XINPUT_VIBRATION));
	vibe.wLeftMotorSpeed = 0;
	vibe.wRightMotorSpeed = VIBRATION_SPEED;
	XInputSetState(m_nVibrationUser, &vibe);	//�U����0��

}

//=================================
//	IsTrigger
//	�֐��T�v�F�g���K�[����
//	���O��ԁFInputDevice
//	���@���Fcode	KeyCodes�^	�L�[�R�[�h
//	�Ԃ�l�F����	bool�^
//=================================
bool	InputDevice::IsTrigger(KeyCodes code)
{
	InputDeviceManager& controller = InputDeviceManager::GetInstance();
	return controller.IsTrigger(code);
}

//=================================
//	IsPress
//	�֐��T�v�F�v���X����
//	���O��ԁFInputDevice
//	���@���Fcode	KeyCodes�^	�L�[�R�[�h
//	�Ԃ�l�F����	bool�^
//=================================
bool	InputDevice::IsPress(KeyCodes code)
{
	InputDeviceManager& controller = InputDeviceManager::GetInstance();
	return controller.IsPress(code);
}

//=================================
//	IsRelease
//	�֐��T�v�F�����[�X����
//	���O��ԁFInputDevice
//	���@���Fcode	KeyCodes�^	�L�[�R�[�h
//	�Ԃ�l�F����	bool�^
//=================================
bool	InputDevice::IsRelease(KeyCodes code)
{
	InputDeviceManager& controller = InputDeviceManager::GetInstance();
	return controller.IsRelease(code);
}

//=================================
//	IsTrigger
//	�֐��T�v�F�g���K�[����
//	���O��ԁFInputDevice
//	���@���F
//		code	PadCodes�^	�L�[�R�[�h
//		user	int�^			�R���g���[���̔ԍ�(0�`3)
//	�Ԃ�l�F����	bool�^
//=================================
bool	InputDevice::IsTrigger(PadCodes code, int user)
{
	InputDeviceManager& controller = InputDeviceManager::GetInstance();
	return controller.IsTrigger(code, user);
}

//=================================
//	IsPress
//	�֐��T�v�F�v���X����
//	���O��ԁFInputDevice
//	���@���F
//		code	PadCodes�^	�L�[�R�[�h
//		user	int�^			�R���g���[���̔ԍ�(0�`3)
//	�Ԃ�l�F����	bool�^
//=================================
bool	InputDevice::IsPress(PadCodes code, int user)
{
	InputDeviceManager& controller = InputDeviceManager::GetInstance();
	return controller.IsPress(code, user);
}

//=================================
//	IsRelease
//	�֐��T�v�F�����[�X����
//	���O��ԁFInputDevice
//	���@���F
//		code	PadCodes�^	�L�[�R�[�h
//		user	int�^			�R���g���[���̔ԍ�(0�`3)
//	�Ԃ�l�F����	bool�^
//=================================
bool	InputDevice::IsRelease(PadCodes code, int user)
{
	InputDeviceManager& controller = InputDeviceManager::GetInstance();
	return controller.IsRelease(code, user);
}


//=================================
//	GetLeftStick
//	�֐��T�v�F���X�e�B�b�N����
//	���O��ԁFInputDevice
//	���@���Fuser	int�^	�R���g���[���̔ԍ�(0�`3)
//	�Ԃ�l�F����	fVec2�^
//=================================
fVec2	InputDevice::GetLeftStick(int user)
{
	InputDeviceManager& controller = InputDeviceManager::GetInstance();
	return controller.GetLeftStick(user);
}

//=================================
//	GetLeftStick
//	�֐��T�v�F���X�e�B�b�N����
//	���O��ԁFInputDevice
//	���@���F�Ȃ�
//	�Ԃ�l�F����	fVec2�^
//=================================
fVec2	InputDevice::GetLeftStick(void)
{
	InputDeviceManager& controller = InputDeviceManager::GetInstance();
	return controller.GetLeftStick(0);
}

//=================================
//	GetRightStick
//	�֐��T�v�F�E�X�e�B�b�N����
//	���O��ԁFInputDevice
//	���@���Fuser	int�^	�R���g���[���̔ԍ�(0�`3)
//	�Ԃ�l�F����	fVec2�^
//=================================
fVec2	InputDevice::GetRightStick(int user)
{
	InputDeviceManager& controller = InputDeviceManager::GetInstance();
	return controller.GetRightStick(user);
}

//=================================
//	GetRightStick
//	�֐��T�v�F�E�X�e�B�b�N����
//	���O��ԁFInputDevice
//	���@���F�Ȃ�
//	�Ԃ�l�F����	fVec2�^
//=================================
fVec2	InputDevice::GetRightStick(void)
{
	InputDeviceManager& controller = InputDeviceManager::GetInstance();
	return controller.GetRightStick(0);
}

//=================================
//	GetTouchs
//	�֐��T�v�F�^�b�`������擾
//	���O��ԁFInputDevice
//	���@���F�Ȃ�
//	�Ԃ�l�F����	tTouchState�^
//=================================
InputDeviceManager::tTouchState	InputDevice::GetTouchs(void)
{
	InputDeviceManager& controller = InputDeviceManager::GetInstance();
	return controller.GetTouch();
}

//=================================
//	SetLeftVibration
//	�֐��T�v�F���R���g���[���[�̃W���C��(Switch�p)
//	���O��ԁFInputDevice
//	���@���F
//		frame	int�^	�U������t���[��	
//		user	int�^	�R���g���[���ԍ�
//	�Ԃ�l�F�Ȃ�
//=================================
void	InputDevice::SetLeftVibration(int frame, int user)
{
	InputDeviceManager& controller = InputDeviceManager::GetInstance();
	controller.SetLeftVibration(frame, user);
}

//=================================
//	SetLeftVibration
//	�֐��T�v�F���R���g���[���[�̃W���C��(Switch�p)
//	���O��ԁFInputDevice
//	���@���Fframe	int�^	�U������t���[��	
//	�Ԃ�l�F�Ȃ�
//=================================
void	InputDevice::SetLeftVibration(int frame)
{
	InputDeviceManager& controller = InputDeviceManager::GetInstance();
	controller.SetLeftVibration(frame, 0);
}

//=================================
//	SetRightVibration
//	�֐��T�v�F�E�R���g���[���[�̃W���C��(Switch�p)
//	���O��ԁFInputDevice
//	���@���F
//		frame	int�^	�U������t���[��	
//		user	int�^	�R���g���[���ԍ�
//	�Ԃ�l�F�Ȃ�
//=================================
void	InputDevice::SetRightVibration(int frame, int user)
{
	InputDeviceManager& controller = InputDeviceManager::GetInstance();
	controller.SetRightVibration(frame, user);
}

//=================================
//	SetRightVibration
//	�֐��T�v�F�E�R���g���[���[�̃W���C��(Switch�p)
//	���O��ԁFInputDevice
//	���@���Fframe	int�^	�U������t���[��	
//	�Ԃ�l�F�Ȃ�
//=================================
void	InputDevice::SetRightVibration(int frame)
{
	InputDeviceManager& controller = InputDeviceManager::GetInstance();
	controller.SetRightVibration(frame, 0);
}

//=================================
//	GetLeftAccel
//	�֐��T�v�F���R���g���[���[�̉����x(Switch�p)
//	���O��ԁFInputDevice
//	���@���FdxVec	fVec3�^	DX�ғ����̕Ԃ�l	
//	�Ԃ�l�F����	fVec3�^
//=================================
fVec3	InputDevice::GetLeftAccel(fVec3 dxVec)
{
	InputDeviceManager& controller = InputDeviceManager::GetInstance();
	return controller.GetLeftAccel(dxVec);
}

//=================================
//	GetLeftAccel
//	�֐��T�v�F���R���g���[���[�̉����x(Switch�p)
//	���O��ԁFInputDevice
//	���@���F�Ȃ�	
//	�Ԃ�l�F����	fVec3�^
//=================================
fVec3	InputDevice::GetLeftAccel(void)
{
	InputDeviceManager& controller = InputDeviceManager::GetInstance();
	return controller.GetLeftAccel({0.0f,0.0f,0.0f});
}

//=================================
//	GetRightAccel
//	�֐��T�v�F�E�R���g���[���[�̉����x(Switch�p)
//	���O��ԁFInputDevice
//	���@���FdxVec	fVec3�^	DX�ғ����̕Ԃ�l	
//	�Ԃ�l�F����	fVec3�^
//=================================
fVec3	InputDevice::GetRightAccel(fVec3 dxVec)
{
	InputDeviceManager& controller = InputDeviceManager::GetInstance();
	return controller.GetRightAccel(dxVec);
}

//=================================
//	GetRightAccel
//	�֐��T�v�F�E�R���g���[���[�̉����x(Switch�p)
//	���O��ԁFInputDevice
//	���@���F�Ȃ�	
//	�Ԃ�l�F����	fVec3�^
//=================================
fVec3	InputDevice::GetRightAccel(void)
{
	InputDeviceManager& controller = InputDeviceManager::GetInstance();
	return controller.GetRightAccel({0.0f,0.0f,0.0f});
}

//=================================
//	GetLeftAngle
//	�֐��T�v�F���R���g���[���[�̃W���C��(Switch�p)
//	���O��ԁFInputDevice
//	���@���FdxVec	fVec3�^	DX�ғ����̕Ԃ�l	
//	�Ԃ�l�F����	fVec3�^
//=================================
fVec3	InputDevice::GetLeftAngle(fVec3 dxVec)
{
	InputDeviceManager& controller = InputDeviceManager::GetInstance();
	return controller.GetLeftAngle(dxVec);
}

//=================================
//	GetLeftAngle
//	�֐��T�v�F���R���g���[���[�̃W���C��(Switch�p)
//	���O��ԁFInputDevice
//	���@���F�Ȃ�	
//	�Ԃ�l�F����	fVec3�^
//=================================
fVec3	InputDevice::GetLeftAngle(void)
{
	InputDeviceManager& controller = InputDeviceManager::GetInstance();
	return controller.GetLeftAngle({0.0f,0.0f,0.0f});
}

//=================================
//	GetRightAngle
//	�֐��T�v�F�E�R���g���[���[�̃W���C��(Switch�p)
//	���O��ԁFInputDevice
//	���@���FdxVec	fVec3�^	DX�ғ����̕Ԃ�l	
//	�Ԃ�l�F����	fVec3�^
//=================================
fVec3	InputDevice::GetRightAngle(fVec3 dxVec)
{
	InputDeviceManager& controller = InputDeviceManager::GetInstance();
	return controller.GetRightAngle(dxVec);
}

//=================================
//	GetRightAngle
//	�֐��T�v�F�E�R���g���[���[�̃W���C��(Switch�p)
//	���O��ԁFInputDevice
//	���@���F�Ȃ�	
//	�Ԃ�l�F����	fVec3�^
//=================================
fVec3	InputDevice::GetRightAngle(void)
{
	InputDeviceManager& controller = InputDeviceManager::GetInstance();
	return controller.GetRightAngle({0.0f,0.0f,0.0f});
}

