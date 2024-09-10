#include "SingletonsMng.hxx"

// =-=-= インクルード部 =-=-=
#include "Window.h"
#include "DirectX11SetUp.h"
#include "InputDeviceManager.h"
#include "SceneMng.hxx"
#include "GameObjectMng.hxx"

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

	SceneMng::GetInstance().ChangeScene<testScene>();

	if(Sucsses)
		return true;
	return false;
}

/// @brief 描画処理を行う
void Supervision::Drawing()
{
	//// 描画処理はこの中へ

	////BeginDrawDirectX();
	//DirectX11SetUp& Dx11 = DirectX11SetUp::GetInstance();
	//Dx11.BeginDraw();

	//RenderTarget* pRT = Dx11.GetDefaultRTV();//デフォルトで使用しているRenderTargetViewの取得
	//DepthStencil* pDS = Dx11.GetDefaultDSV();//DeapthStencilViewの取得

	//Dx11.SetRenderTargets(1, &pRT, nullptr);

	//Dx11.SetRenderTargets(1, &pRT, pDS);


	//Dx11.SetRenderTargets(1, &pRT, nullptr);//深度バッファおっふ

	//Dx11.EndDraw();
}