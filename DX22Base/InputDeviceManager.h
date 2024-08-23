//	�t�@�C�����FInputDeviceManager.h
//	�T�v		 �F���͏��̊Ǘ�
//	�쐬��	 �F�ɓ����
//	�X�V�L�^	 �F2024/02/17	21:40	�R�����g�ǉ�
//������������������������������������������������������������������������������������������������������

// =-=-= �C���N���[�h�K�[�h�� =-=-=
#ifndef _____INPUT_DEVICE_MANAGER_H_____
#define _____INPUT_DEVICE_MANAGER_H_____

// =-=-= �C���N���[�h�� =-=-=
#include <Windows.h>
#include <Xinput.h>
#include "Vectors.hxx"
#include "SingletonsMng.hxx"

#pragma comment(lib, "Xinput.lib")

//�L�[�{�[�h����
enum class KeyCodes
{
	Mouse_L = 0x01,
	Mouse_R = 0x02,
	Cancel = 0x03,
	Mouse_Wheel = 0x04,
	XButton1 = 0x05,
	XButton2 = 0x06,
	Back = 0x08,
	Tab = 0x09,
	Clear = 0x0C,
	Return = 0x0D,
	Shift = 0x10,
	Control = 0x11,
	Menu = 0x12,
	Pause = 0x13,
	Capital = 0x14,
	Kana = 0x15,
	IME_On = 0x16,
	Junja = 0x17,
	Final = 0x18,
	Kanji = 0x19,
	IME_Off = 0x1A,
	Escape = 0x1B,
	Convert = 0x1C,
	NonConvert = 0x1D,
	Accept = 0x1E,
	ModeChange = 0x1F,
	Space = 0x20,
	Prior = 0x21,
	Next = 0x22,
	End = 0x23,
	Home = 0x24,
	Left = 0x25,
	Up = 0x26,
	Right = 0x27,
	Down = 0x28,
	Select = 0x29,
	Print = 0x2A,
	Execute = 0x2B,
	SnapShot = 0x2C,
	Insert = 0x2D,
	Delete = 0x2E,
	Help = 0x2F,
	LWin = 0x5B,
	RWin = 0x5C,
	Apps = 0x5D,
	Sleep = 0x5F,
	NumPad_0 = 0x60,
	NumPad_1 = 0x61,
	NumPad_2 = 0x62,
	NumPad_3 = 0x63,
	NumPad_4 = 0x64,
	NumPad_5 = 0x65,
	NumPad_6 = 0x66,
	NumPad_7 = 0x67,
	NumPad_8 = 0x68,
	NumPad_9 = 0x69,
	MultiPly = 0x6A,
	Add = 0x6B,
	Separator = 0x6C,
	Subtract = 0x6D,
	Decimal = 0x6E,
	Devide = 0x6F,
	F1 = 0x70,
	F2 = 0x71,
	F3 = 0x72,
	F4 = 0x73,
	F5 = 0x74,
	F6 = 0x75,
	F7 = 0x76,
	F8 = 0x77,
	F9 = 0x78,
	F10 = 0x79,
	F11 = 0x7A,
	F12 = 0x7B,
	F13 = 0x7C,
	F14 = 0x7D,
	F15 = 0x7E,
	F16 = 0x7F,
	F17 = 0x80,
	F18 = 0x81,
	F19 = 0x82,
	F20 = 0x83,
	F21 = 0x84,
	F22 = 0x85,
	F23 = 0x86,
	F24 = 0x87,
	Navi_View = 0x88,
	Navi_Menu = 0x89,
	Navi_Up = 0x8A,
	Navi_Down = 0x8B,
	Navi_Left = 0x8C,
	Navi_Right = 0x8D,
	Navi_Accept = 0x8E,
	Navi_Cancel = 0x8F,
	NumLock = 0x90,
	Scroll = 0x91,
	NEC_Equal = 0x92,
	FJ_Jisho = 0x92,
	FJ_Masshou = 0x93,
	FJ_Touroku = 0x94,
	FJ_Loya = 0x95,
	FJ_Roya = 0x96,
	LShift = 0xA0,
	RShift = 0xA1,
	LControl = 0xA2,
	RControl = 0xA3,
	LMenu = 0xA4,
	RMenu = 0xA5,
	Browser_Back = 0xA6,
	Browser_Forward = 0xA7,
	Browser_Refresh = 0xA8,
	Browser_Stop = 0xA9,
	Browser_Search = 0xAA,
	Browser_Favorite = 0xAB,
	Browser_Home = 0xAC,
	Volume_Mute = 0xAD,
	Volume_Down = 0xAE,
	Volume_Up = 0xAF,
	Media_Next_Track = 0xB0,
	Media_Prev_Track = 0xB1,
	Media_Stop = 0xB2,
	Media_Play_Pause = 0xB3,
	Launch_Mail = 0xB4,
	Launch_Media_Select = 0xB5,
	Launch_App1 = 0xB6,
	Launch_App2 = 0xB7,
	OEM_1 = 0xBA,
	OEM_Plus = 0xBB,
	OEM_Comma = 0xBC,
	OEM_Minus = 0xBD,
	OEM_Period = 0xBE,
	OEM_2 = 0xBF,
	OEM_3 = 0xC0,
	OEM_4 = 0xDB,
	OEM_5 = 0xDC,
	OEM_6 = 0xDD,
	OEM_7 = 0xDE,
	OEM_8 = 0xDF,
	OEM_AX = 0xE1,
	OEM_102 = 0xE2,
	OEM_ICO_Help = 0xE3,
	OEM_ICO_00 = 0xE4,
	ProcessKey = 0xE5,
	ICO_Clear = 0xE6,
	Packet = 0xE7,
	OEM_Reset = 0xE9,
	OEM_Jump = 0xEA,
	OEM_PA1 = 0xEB,
	OEM_PA2 = 0xEC,
	OEM_PA3 = 0xED,
	OEM_WSCTRL = 0xEE,
	OEM_CUSEL = 0xEF,
	OEM_ATTN = 0xF0,
	OEM_Finish = 0xF1,
	OEM_Copy = 0xF2,
	OEM_Auto = 0xF3,
	OEM_Enlw = 0xF4,
	OEM_BackTab = 0xF5,
	ATTN = 0xF6,
	CRSEL = 0xF7,
	EXSEL = 0xF8,
	EREOF = 0xF9,
	Play = 0xFA,
	Zoom = 0xFB,
	NoName = 0xFC,
	PA1 = 0xFD,
	OEM_Clear = 0xFE,
	A = 0x41,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P,
	Q,
	R,
	S,
	T,
	U,
	V,
	W,
	X,
	Y,
	Z,
	Num_0 = 0x30,
	Num_1,
	Num_2,
	Num_3,
	Num_4,
	Num_5,
	Num_6,
	Num_7,
	Num_8,
	Num_9,
};

//�p�b�h����
enum class PadCodes
{
	Up = 0x0001,
	Down = 0x0002,
	Left = 0x0004,
	Right = 0x0008,
	Start = 0x0010,
	Back = 0x0020,
	LStick = 0x0040,
	RStick = 0x0080,
	LB = 0x0100,
	RB = 0x0200,
	A = 0x1000,
	B = 0x2000,
	X = 0x4000,
	Y = 0x8000,
	LT = 0xFFF0,
	RT = 0xFFF1,
};

/// @brief �L�[�{�[�h��R���g���[���[���̓X�e�[�^�X�̕ێ��Ƃ��̔���
/// @brief �e����ł͂�����ł͂Ȃ�InputDevice���g�p���Ă��������B
/// @brief ������������ �V���O���g���ł� ������������
class InputDeviceManager :public Singleton<InputDeviceManager>
{
	friend class Singleton<InputDeviceManager>;
public:
	bool Init();
	void Update();

	void SetHWND(HWND);

	//�g���K�[����
	bool	IsTrigger(KeyCodes);
	bool	IsTrigger(PadCodes, int);

	//�v���X����
	bool	IsPress(KeyCodes);
	bool	IsPress(PadCodes, int);

	//�����[�X����
	bool	IsRelease(KeyCodes);
	bool	IsRelease(PadCodes, int);

	//�X�e�B�b�N
	fVec2	GetLeftStick(int);
	fVec2	GetRightStick(int);

	//�^�b�`�\����
	typedef struct tTouchState
	{
		fVec2	touchPos[10];
		int			nCntTouch = 0;
	}tTouchState;

	//�^�b�`����
	tTouchState	GetTouch(void);

	//�U��
	void	SetLeftVibration(int, int);
	void	SetRightVibration(int, int);

	//�����x�Z���T
	fVec3	GetLeftAccel(fVec3);
	fVec3	GetRightAccel(fVec3);

	//�X���Z���T
	fVec3	GetLeftAngle(fVec3);
	fVec3	GetRightAngle(fVec3);

private:
	InputDeviceManager();
	~InputDeviceManager();
	//�֐�
	bool	XInputInit(void);
	bool	KeyInputInit(HWND);
	void	XInputUpdate(void);
	void	KeyInputUpdate(void);

	//�L�[���͗p�ϐ�
	static const int	KEY_MAX = 256;		//�L�[�̐�
	BYTE		m_keyState[KEY_MAX];	//�L�[���
	BYTE		m_keyOldState[KEY_MAX];	//�O�t���[���̃L�[���
	fVec2	m_mousePos;			//�}�E�X���W
	HWND		m_hWnd;				//�E�B���h�E�n���h��

	//XInput�p�ϐ�
	XINPUT_GAMEPAD	m_xInputPadState[XUSER_MAX_COUNT];		//XInput�̏��
	XINPUT_GAMEPAD	m_xInputPadOldState[XUSER_MAX_COUNT];	//�O�t���[����XInput�̏��
	int				m_nCntConnect;							//�ڑ��σR���g���[���̐�
	int				m_nLimitFrameVibration;		//�U������c��t���[��
	int				m_nVibrationUser;			//�U�����郆�[�U
	bool			m_bIsVibration;				//�U���t���O
	static const int VIBRATION_SPEED = 20000;	//�U�������]��
};

/// @brief ����͂����炩��
namespace InputDevice
{
	//�g���K�[����
	bool	IsTrigger(KeyCodes);
	bool	IsTrigger(PadCodes, int);

	//�v���X����
	bool	IsPress(KeyCodes);
	bool	IsPress(PadCodes, int);

	//�����[�X����
	bool	IsRelease(KeyCodes);
	bool	IsRelease(PadCodes, int);

	//�X�e�B�b�N
	fVec2	GetLeftStick(int);
	fVec2	GetRightStick(int);
	fVec2	GetLeftStick(void);
	fVec2	GetRightStick(void);

	//�^�b�`����
	InputDeviceManager::tTouchState	GetTouchs(void);

	//�U��
	void	SetLeftVibration(int, int);
	void	SetRightVibration(int, int);
	void	SetLeftVibration(int);
	void	SetRightVibration(int);


	//�����x�Z���T
	fVec3	GetLeftAccel(fVec3);
	fVec3	GetRightAccel(fVec3);
	fVec3	GetLeftAccel(void);
	fVec3	GetRightAccel(void);

	//�X���Z���T
	fVec3	GetLeftAngle(fVec3);
	fVec3	GetRightAngle(fVec3);
	fVec3	GetLeftAngle(void);
	fVec3	GetRightAngle(void);

}

#endif // !_____INPUT_DEVICE_MANAGER_H_____