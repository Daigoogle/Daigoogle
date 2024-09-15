#include "SingletonsMng.hxx"

// =-=-= �C���N���[�h�� =-=-=
#include "Window.h"
#include "DirectX11SetUp.h"
#include "InputDeviceManager.h"
#include "SceneMng.hxx"
#include "GameObjectMng.hxx"
#include "RenderMng.hxx"
#include "ThreadPoolMng.hxx"

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
	Sucsses &= RenderMng::GetInstance().Init();

	SceneMng::GetInstance().ChangeScene<testScene>();

	Sucsses &= ThreadPoolMng::GetInstance().Init();

	if(Sucsses)
		return true;
	return false;
}

/// @brief �`�揈�����s��
void Supervision::Drawing()
{
}