#include "Main.h"
#include "DefaultSetting.hxx"

#include <memory>
//#include "DirectX.h"
#include "DirectX11SetUp.h"
#include "Geometory.h"
#include "Sprite.h"
#include "InputDeviceManager.h"
#include "BaseObjectManager.h"
#include "SceneManager.h"
#include "SceneGame.h"
#include "SceneTitle.h"
#include "SceneInit.h"
#include "SceneComponentTest.h"
#include "SceneResult.h"
#include "Defines.h"
#include "fade.h"
#include "Sprite2DManager.h"
#include "Sprite3DManager.h"
#include "CubeManager.h"
#include "SkyBoxManager.h"
#include "CubeCollisionToDirectManager.h"
#include "ModelManager.h"
#include "ModelRegister.h"
#include "TextureRegister.h"
#include "AudioManager.h"
#include "Window.h"

float g_tick;

HRESULT Init()
{
	//Window& wind = Window::GetInstance();

	//HWND hWnd = wind.GetHWnd();
	//UINT width = wind.GetScreenWidth();
	//UINT height = wind.GetScreenHeight();

	HRESULT hr = S_OK;

	//// DirectX初期化
	//DirectX11SetUp& Dx11 = DirectX11SetUp::GetInstance();
	//hr = Dx11.SettingData(hWnd, { (int)width,(int)height }, false);
	//if (FAILED(hr)) { return hr; }

	//InputDeviceManager::GetInstance().Init();

	//BaseObjectManager& basemanager = BaseObjectManager::GetInstance();
	//basemanager.Init();
	//basemanager.SetMode(BaseObjectManager::ProcessMode::MainScene);
	
	//Geometory::Init();
	Sprite::Init();



	// ジオメトリ用カメラ初期化
	//DirectX::XMFLOAT4X4 mat[2];
	//DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(
	//	DirectX::XMMatrixLookAtLH(
	//		DirectX::XMVectorSet(1.5f, 2.5f, -3.0f, 0.0f),
	//		DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),
	//		DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)
	//	)));
	//DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixTranspose(
	//	DirectX::XMMatrixPerspectiveFovLH(
	//		DirectX::XMConvertToRadians(60.0f), (float)width / height, 0.1f, 100.0f)
	//));
	//Geometory::SetView(mat[0]);
	//Geometory::SetProjection(mat[1]);

	Sprite3DManager& sprite3DManager = Sprite3DManager::GetInstance();
	Sprite2DManager& sprite2DManager = Sprite2DManager::GetInstance();
	CubeManager& cubeManager = CubeManager::GetInstance();
	ModelManager& modelManager = ModelManager::GetInstance();
	sprite3DManager.Init();
	sprite2DManager.Init();
	cubeManager.Init();
	modelManager.Init();
	SkyBoxManager::GetInstance().Init();

	AudioManager::GetInstance().Init();

	CubeCollisionToDirectManager::GetInstance().Init();

	Fade::GetInstance().Init();

	// シーン作成
	SceneManager& sceneManager = SceneManager::GetInstance();
	sceneManager.Init();


	//sceneManager.ChangeScene<SceneInit>();
	//sceneManager.ChangeScene<SceneTitle>();
	//sceneManager.ChangeScene<SceneComponentTest>();
	//sceneManager.ChangeScene<SceneGame>();	
	//sceneManager.ChangeScene<SceneResult>();	
	

	return hr;
}

void Uninit()
{
	//SceneManager>::GetInstance().UnInit();
	Sprite::Uninit();
	//Geometory::Uninit();
	//Sprite3DManager>::GetInstance().UnInit();
	//Sprite2DManager>::GetInstance().UnInit();
	//SingletonFinalizer::finalize();//シングルトン終了処理
	//UninitDirectX();
}

void Update(float tick)
{
	g_tick = tick;
	//UpdateInput();
	InputDeviceManager::GetInstance().Update();
	SceneManager::GetInstance().Update();

	BaseObjectManager::GetInstance().Update();
	ModelManager::GetInstance().Update();
	AudioManager::GetInstance().Update();
	Fade::GetInstance().Update();
}

void Draw()
{
	//BeginDrawDirectX();
	DirectX11SetUp& Dx11 = DirectX11SetUp::GetInstance();
	Dx11.BeginDraw();


	// 軸線の表示
#if 0
	// グリッド
	DirectX::XMFLOAT4 lineColor(0.5f, 0.5f, 0.5f, 1.0f);
	float size = DEBUG_GRID_NUM * DEBUG_GRID_MARGIN;
	for (int i = 1; i <= DEBUG_GRID_NUM; ++i)
	{
		float grid = i * DEBUG_GRID_MARGIN;
		DirectX::XMFLOAT3 pos[2] = {
			DirectX::XMFLOAT3(grid, 0.0f, size),
			DirectX::XMFLOAT3(grid, 0.0f,-size),
		};
		Geometory::AddLine(pos[0], pos[1], lineColor);
		pos[0].x = pos[1].x = -grid;
		Geometory::AddLine(pos[0], pos[1], lineColor);
		pos[0].x = size;
		pos[1].x = -size;
		pos[0].z = pos[1].z = grid;
		Geometory::AddLine(pos[0], pos[1], lineColor);
		pos[0].z = pos[1].z = -grid;
		Geometory::AddLine(pos[0], pos[1], lineColor);
	}
	// 軸
	Geometory::AddLine(DirectX::XMFLOAT3(0,0,0), DirectX::XMFLOAT3(size,0,0), DirectX::XMFLOAT4(1,0,0,1));
	Geometory::AddLine(DirectX::XMFLOAT3(0,0,0), DirectX::XMFLOAT3(0,size,0), DirectX::XMFLOAT4(0,1,0,1));
	Geometory::AddLine(DirectX::XMFLOAT3(0,0,0), DirectX::XMFLOAT3(0,0,size), DirectX::XMFLOAT4(0,0,1,1));
	Geometory::AddLine(DirectX::XMFLOAT3(0,0,0), DirectX::XMFLOAT3(-size,0,0),  DirectX::XMFLOAT4(0,0,0,1));
	Geometory::AddLine(DirectX::XMFLOAT3(0,0,0), DirectX::XMFLOAT3(0,0,-size),  DirectX::XMFLOAT4(0,0,0,1));

	Geometory::DrawLines();
#endif

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
	//EndDrawDirectX();
}

float GetTick()
{
	return g_tick;
}

// EOF