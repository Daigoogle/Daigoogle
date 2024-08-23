#include "SingletonsMng.hxx"

// =-=-= �C���N���[�h�� =-=-=
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

/// @brief �������������s��
/// @return ����������true
bool Supervision::Initialize()
{
	bool Sucsses = true;

	// �����������͂��̒���
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

/// @brief �`�揈�����s��
void Supervision::Drawing()
{
	// �`�揈���͂��̒���

	//BeginDrawDirectX();
	DirectX11SetUp& Dx11 = DirectX11SetUp::GetInstance();
	Dx11.BeginDraw();

	RenderTarget* pRT = Dx11.GetDefaultRTV();//�f�t�H���g�Ŏg�p���Ă���RenderTargetView�̎擾
	DepthStencil* pDS = Dx11.GetDefaultDSV();//DeapthStencilView�̎擾

	Dx11.SetRenderTargets(1, &pRT, nullptr);
	SkyBoxManager::GetInstance().Draw();

	Dx11.SetRenderTargets(1, &pRT, pDS);

	Sprite3DManager::GetInstance().Draw();
	CubeManager::GetInstance().Draw();
	ModelManager::GetInstance().Draw();
	SceneManager::GetInstance().Draw();

	Dx11.SetRenderTargets(1, &pRT, nullptr);//�[�x�o�b�t�@������

	Sprite2DManager::GetInstance().Draw();
	Fade::GetInstance().Draw();

	Dx11.EndDraw();
}