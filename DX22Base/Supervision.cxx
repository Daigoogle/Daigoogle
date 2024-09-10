#include "SingletonsMng.hxx"

// =-=-= �C���N���[�h�� =-=-=
#include "Window.h"
#include "DirectX11SetUp.h"
#include "InputDeviceManager.h"
#include "SceneMng.hxx"
#include "GameObjectMng.hxx"

#include "testScene.hxx"

/// @brief �������������s��
/// @return ����������true
bool Supervision::Initialize()
{
	bool Sucsses = true;

	// �����������͂��̒���
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

/// @brief �`�揈�����s��
void Supervision::Drawing()
{
	//// �`�揈���͂��̒���

	////BeginDrawDirectX();
	//DirectX11SetUp& Dx11 = DirectX11SetUp::GetInstance();
	//Dx11.BeginDraw();

	//RenderTarget* pRT = Dx11.GetDefaultRTV();//�f�t�H���g�Ŏg�p���Ă���RenderTargetView�̎擾
	//DepthStencil* pDS = Dx11.GetDefaultDSV();//DeapthStencilView�̎擾

	//Dx11.SetRenderTargets(1, &pRT, nullptr);

	//Dx11.SetRenderTargets(1, &pRT, pDS);


	//Dx11.SetRenderTargets(1, &pRT, nullptr);//�[�x�o�b�t�@������

	//Dx11.EndDraw();
}