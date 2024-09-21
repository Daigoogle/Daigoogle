#include "SingletonsMng.hxx"

// =-=-= �C���N���[�h�� =-=-=
#include "DebugRestriction.hxx"
#include "Window.h"
#include "DirectX11SetUp.h"
#include "InputDeviceManager.h"
#include "SceneMng.hxx"
#include "GameObjectMng.hxx"
#include "RenderMng.hxx"
#include "ThreadPoolMng.hxx"
#include "CameraManager.h"

#include "testScene.hxx"

/// @brief �������������s��
/// @return ����������true
bool Supervision::Initialize()
{
	bool Sucsses = true;

	// �����������͂��̒���
	Sucsses &= FalseCheck(Window::GetInstance().Init()				);
	Sucsses &= FalseCheck(DirectX11SetUp::GetInstance().Init()		);
	Sucsses &= FalseCheck(InputDeviceManager::GetInstance().Init()	);
	Sucsses &= FalseCheck(GameObjectMng::GetInstance().Init()		);
	Sucsses &= FalseCheck(SceneMng::GetInstance().Init()			);
	Sucsses &= FalseCheck(CameraManager::GetInstance().Init()		);
	Sucsses &= FalseCheck(RenderMng::GetInstance().Init()			);

	SceneMng::GetInstance().ChangeScene<testScene>();

	if(Sucsses)
		return true;
	return false;
}