#include "SingletonsMng.hxx"

// =-=-= インクルード部 =-=-=
#include "Window.h"
#include "DirectX11SetUp.h"
#include "InputDeviceManager.h"
#include "SceneMng.hxx"
#include "GameObjectMng.hxx"
#include "RenderMng.hxx"
#include "ThreadPoolMng.hxx"

#include "testScene.hxx"

/// @brief 初期化処理を行う
/// @return 成功したらtrue
bool Supervision::Initialize()
{
	bool Sucsses = true;

	// 初期化処理はこの中へ
	Sucsses &= Window::GetInstance().Init();
	Sucsses &= DirectX11SetUp::GetInstance().Init();
	Sucsses &= InputDeviceManager::GetInstance().Init();
	Sucsses &= GameObjectMng::GetInstance().Init();
	Sucsses &= SceneMng::GetInstance().Init();
	Sucsses &= RenderMng::GetInstance().Init();

	SceneMng::GetInstance().ChangeScene<testScene>();

	Sucsses &= ThreadPoolMng::GetInstance().Init();

	if(Sucsses)
		return true;
	return false;
}

/// @brief 描画処理を行う
void Supervision::Drawing()
{
}