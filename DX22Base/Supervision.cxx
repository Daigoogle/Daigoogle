#include "SingletonsMng.hxx"

// =-=-= インクルード部 =-=-=
#include "Window.h"
#include "DirectX11SetUp.h"
#include "InputDeviceManager.h"
#include "BaseObjectManager.h"
#include "Sprite2DManager.h"
#include "Sprite3DManager.h"
#include "CubeManager.h"
#include "ModelManager.h"
#include "SkyBoxManager.h"
#include "AudioManager.h"
#include "CubeCollisionToDirectManager.h"
#include "fade.h"
#include "SceneManager.h"

/// @brief 初期化処理を行う
/// @return 成功したらtrue
bool Supervision::Initialize()
{
	bool Sucsses = true;

	// 初期化処理はこの中へ
	Sucsses &= Window::GetInstance().Init();
	Sucsses &= DirectX11SetUp::GetInstance().Init();
	Sucsses &= InputDeviceManager::GetInstance().Init();
	Sucsses &= BaseObjectManager::GetInstance().Init();
	Sucsses &= Sprite2DManager::GetInstance().Init();
	Sucsses &= Sprite3DManager::GetInstance().Init();
	Sucsses &= CubeManager::GetInstance().Init();
	Sucsses &= ModelManager::GetInstance().Init();
	Sucsses &= SkyBoxManager::GetInstance().Init();
	Sucsses &= AudioManager::GetInstance().Init();
	Sucsses &= CubeCollisionToDirectManager::GetInstance().Init();
	Sucsses &= Fade::GetInstance().Init();
	Sucsses &= SceneManager::GetInstance().Init();

	if(Sucsses)
		return true;
	return false;
}

/// @brief 描画処理を行う
void Supervision::Drawing()
{
	// 描画処理はこの中へ

	//BeginDrawDirectX();
	DirectX11SetUp& Dx11 = DirectX11SetUp::GetInstance();
	Dx11.BeginDraw();

	RenderTarget* pRT = Dx11.GetDefaultRTV();//デフォルトで使用しているRenderTargetViewの取得
	DepthStencil* pDS = Dx11.GetDefaultDSV();//DeapthStencilViewの取得

	Dx11.SetRenderTargets(1, &pRT, nullptr);
	SkyBoxManager::GetInstance().Draw();

	Dx11.SetRenderTargets(1, &pRT, pDS);

	Sprite3DManager::GetInstance().Draw();
	CubeManager::GetInstance().Draw();
	ModelManager::GetInstance().Draw();
	SceneManager::GetInstance().Draw();

	Dx11.SetRenderTargets(1, &pRT, nullptr);//深度バッファおっふ

	Sprite2DManager::GetInstance().Draw();
	Fade::GetInstance().Draw();

	Dx11.EndDraw();
}