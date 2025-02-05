#include "SingletonsMng.hxx"

// =-=-= インクルード部 =-=-=
#include "DebugRestriction.hxx"
#include "Window.h"
#include "DirectX11SetUp.h"
#include "InputDeviceManager.h"
#include "SceneMng.hxx"
#include "RenderMng.hxx"
#include "ThreadPool.hxx"
#include "CameraManager.h"

#include "testScene.hxx"

/// @brief 初期化処理を行う
/// @return 成功したらtrue
bool Supervision::Initialize()
{
	bool Sucsses = true;

	// 初期化処理はこの中へ
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