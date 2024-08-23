#include "SceneResult.h"
#include "SceneManager.h"
#include "SceneTitle.h"
#include "ScoreManager.h"
#include "fade.h"
#include "NumSprite2D.h"
#include "InputDeviceManager.h"
#include "CameraDebug.h"
#include "CubeManager.h"
#include "Sprite3DManager.h"
#include "CameraManager.h"
#include "BaseObjectManager.h"
#include "SoundEffectComponent.h"




SceneResult::SceneResult()
	: m_Camera(nullptr)
	, m_Haikei(nullptr)
	, m_nFCntrr(0)
	, m_PressSpacerr(false)
{

}

SceneResult::~SceneResult()
{

}

void SceneResult::Init()
{
	BaseObject camera = ObjectManager::Make(this);
	m_Camera = camera.AddComponent<CameraDebug>();
	Singleton<CameraManager>::GetInstance().SetCamera(m_Camera);

	BaseObject haikei = ObjectManager::Make(this);
	m_Haikei = haikei.AddComponent<Sprite2DComponent>();
	m_SE = haikei.AddComponent<SoundEffectComponent>();
	m_Haikei->LoadTexture("Assets/Texture/Result.png");
	haikei.GetComponent<Transform>()->SetLocalScale({1.0f,1.0f,0.0f});

	BaseObject score = ObjectManager::Make(this);
	m_Score = score.AddComponent<NumSprite2D>();
	score.GetComponent<Transform>()->SetWorldPosition({ 0.45f,-0.38f,0.0f });

	m_Score->SetColor({1.0f,0.0f,1.0f,1.0f});

	Singleton<AudioManager>::GetInstance().PlayBGM(AudioManager::BGM_KIND::BGM_RESULT);
	Singleton<Fade>::GetInstance().InStart();
}

void SceneResult::Update()
{
	m_Score->SetNum(ScoreManager::GetInstance().GetScore());

	if (InputDevice::IsPress(KeyCodes::Space))
		m_PressSpacerr = true;
	if (m_PressSpacerr)
	{
		if (m_nFCntrr == 0)
		{
			Singleton<Fade>::GetInstance().OutStart();
			m_SE->PlaySE(AudioManager::SE_KIND::SE_ENTER);
		}
		else if (Singleton<Fade>::GetInstance().GetEnd())
			Singleton<SceneManager>::GetInstance().ChangeScene<SceneTitle>();
		m_nFCntrr++;
	}
}

void SceneResult::UnInit()
{

}