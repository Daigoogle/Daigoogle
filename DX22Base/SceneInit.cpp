#include "SceneInit.h"
#include "BaseObject.h"
#include "BaseObjectManager.h"
#include "Transform.h"
#include "SceneManager.h"
#include "SceneTitle.h"
#include "easing.h"
#include "InputDeviceManager.h"
#include "CameraDebug.h"
#include "CameraManager.h"

SceneInit::SceneInit()
	: m_FrameCount(0)
	, m_EnginRogo(nullptr)
	, m_FromRogo(nullptr)
	, m_TeamRogo(nullptr)
{
}

SceneInit::~SceneInit()
{
}

void SceneInit::Init()
{
	BaseObject Camera = ObjectManager::Make(this);
	CameraManager::GetInstance().SetCamera(Camera.AddComponent<CameraDebug>());

	BaseObject From = ObjectManager::Make(this);
	m_FromRogo = From.AddComponent<Sprite2DComponent>();
	Transform* tfFrom = From.GetComponent<Transform>();
	m_FromRogo->LoadTexture("Assets/Texture/Init_FROM.png");
	m_FromRogo->SetColor({ 0.0f,0.0f,0.0f,0.0f });
	tfFrom->SetLocalScale({1.0f,1.0f,1.0f});
	tfFrom->SetLocalPosition({0.0f,0.0f,2.0f});
	
	BaseObject Engin = ObjectManager::Make(this);
	m_EnginRogo = Engin.AddComponent<Sprite2DComponent>();
	Transform* tfEngin = Engin.GetComponent<Transform>();
	m_EnginRogo->LoadTexture("Assets/Texture/dx11.png");
	m_EnginRogo->SetColor({0.0f,0.0f,0.0f,0.0f});
	tfEngin->SetLocalScale({1.0f,1.0f,1.0f});
	tfEngin->SetLocalPosition({0.0f,0.0f,1.0f});

	BaseObject Team = ObjectManager::Make(this);
	m_TeamRogo = Team.AddComponent<Sprite2DComponent>();
	Transform* tfTeam = Team.GetComponent<Transform>();
	m_TeamRogo->LoadTexture("Assets/Texture/Team.png");
	m_TeamRogo->SetColor({ 0.0f,0.0f,0.0f,1.0f });
	tfTeam->SetLocalScale({1.0f,1.0f,1.0f});
	tfTeam->SetLocalPosition({ 0.0f,0.0f,0.0f });
}

void SceneInit::Update()
{
	if (m_FrameCount < 70)
	{
		float col = Easing::InOutSine(m_FrameCount / 70.0f);
		m_FromRogo->SetColor({col,col,col,1.0f});
	}
	else if (m_FrameCount < 190)
	{
		m_FromRogo->SetColor({1.0f,1.0f,1.0f,1.0f});
	}
	else if (m_FrameCount < 250)
	{
		m_FromRogo->SetColor({ 1.0f, 1.0f, 1.0f, Easing::InOutSine((250 - m_FrameCount) / 30.0f)});
	}
	else  if (m_FrameCount < 310)
	{
		m_FromRogo->SetColor({ 1.0f,1.0f,1.0f,0.0f });
		float col = Easing::InOutSine((m_FrameCount - 250) / 30.0f);
		m_EnginRogo->SetColor({col,col,col,1.0f});
	}
	else  if (m_FrameCount < 430)
	{
		m_EnginRogo->SetColor({ 1.0f,1.0f,1.0f,1.0f });
	}
	else  if (m_FrameCount < 490)
	{
		m_EnginRogo->SetColor({ 1.0f,1.0f,1.0f,Easing::InOutSine((490 - m_FrameCount) / 30.0f) });
	}
	else  if (m_FrameCount < 550)
	{
		m_EnginRogo->SetColor({1.0f,1.0f,1.0f,0.0f});
		float col = Easing::InOutSine((m_FrameCount - 490) / 30.0f);
		m_TeamRogo->SetColor({col,col,col,1.0f});
	}
	else  if (m_FrameCount < 670)
	{
		m_TeamRogo->SetColor({1.0f,1.0f,1.0f,1.0f});
	}
	else  if (m_FrameCount < 730)
	{
		float col = Easing::InOutSine((730 - m_FrameCount) / 30.0f);
		m_TeamRogo->SetColor({col,col,col,1.0f});
	}
	else
		SceneManager::GetInstance().ChangeScene<SceneTitle>();

	if (InputDevice::IsTrigger(KeyCodes::Space))
		m_FrameCount += 5;

	m_FrameCount++;
}

void SceneInit::UnInit()
{
	
}
