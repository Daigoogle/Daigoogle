#include "SingletonsMng.hxx"

// =-=-= �C���N���[�h�� =-=-=
#include "DebugRestriction.hxx"
#include "Window.h"
#include "DirectX11SetUp.h"
#include "InputDeviceManager.h"
#include "SceneMng.hxx"
#include "RenderMng.hxx"
#include "ThreadPool.hxx"
#include "CameraManager.h"

#include "testScene.hxx"

/// @brief �������������s��
/// @return ����������true
bool Supervision::Initialize()
{
	bool Sucsses = true;

	// �����������͂��̒���
	Sucsses &= FalseCheck(Window			::CreateInstance().Init()	);
	Sucsses &= FalseCheck(DirectX11SetUp	::CreateInstance().Init()	);
	Sucsses &= FalseCheck(InputDeviceManager::CreateInstance().Init()	);
	//Sucsses &= FalseCheck(GameObjectMng	::CreateInstance().Init()	);
	Sucsses &= FalseCheck(SceneManager		::CreateInstance().Init()	);
	Sucsses &= FalseCheck(CameraManager		::CreateInstance().Init()	);
	Sucsses &= FalseCheck(RenderMng			::CreateInstance().Init()	);
	Sucsses &= FalseCheck(ThreadPool		::CreateInstance().Init()	);

	SceneManager::GetInstance().ChangeScene<testScene>();

	if(Sucsses)
		return true;
	return false;
}