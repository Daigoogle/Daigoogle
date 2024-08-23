#include "SceneTitle.h"
#include "BaseObject.h"
#include "BaseObjectManager.h"
#include "Sprite3DManager.h"
#include "Sprite2DManager.h"
#include "CubeManager.h"
#include "CameraDebug.h"
#include "fade.h"
#include "InputDeviceManager.h"
#include "SceneManager.h"
#include "SceneComponentTest.h"
#include "SceneGame.h"
#include "CameraManager.h"
#include "AudioManager.h"
#include "SoundEffectComponent.h"

bool g_PressSpace = false;
int g_nFCnt = 0;

SceneTitle::SceneTitle()
{

}

SceneTitle::~SceneTitle()
{

}

void SceneTitle::Init()
{
	// ÉJÉÅÉâÇçÏê¨
	BaseObject camera = ObjectManager::Make(this);
	m_Camera = camera.AddComponent<CameraDebug>();
	Singleton<CameraManager>::GetInstance().SetCamera(m_Camera);

	BaseObject Haikei = ObjectManager::Make(this);
	BaseObject Gazou = ObjectManager::Make(this);

	m_Sprite = Haikei.AddComponent<Sprite2DComponent>();
	m_SprObj = Gazou.AddComponent<Sprite2DComponent>();
	m_tfBack = Haikei.GetComponent<Transform>();
	m_tfFront = Gazou.GetComponent<Transform>();
	m_SE = Haikei.AddComponent<SoundEffectComponent>();

	m_Sprite->LoadTexture("Assets/Texture/Title1.png");
	m_SprObj->LoadTexture("Assets/Texture/Title2.png");
	m_tfBack->SetLocalScale({1.0f,1.0f,1.0f});
	m_tfBack->SetLocalPosition({0.0f,0.0f,-6.0f});
	m_Sprite->SetColor({ 1.0f,1.0f,1.0f,1.0f });
	m_tfFront->SetLocalScale({0.38f,0.53f,1.0f});
	m_tfFront->SetLocalPosition({0.4f,-0.1f,4.0f});
	Singleton<Fade>::GetInstance().InStart();
	g_PressSpace = false;
	g_nFCnt = 0;

	Singleton<AudioManager>::GetInstance().PlayBGM(AudioManager::BGM_KIND::BGM_TITLE);
}

void SceneTitle::Update()
{
	int ra = rand();
	fVec3 Pos = {((ra & 0xF0)>>4) / 320.0f + 0.2f,(ra & 0xF)/320.0f - 0.1f,((ra & 0xF00) >> 8) / 320.0f + 4.0f}, 
		Rot = { (ra & 0xF) / 2.0f - 4.0f,((ra & 0xF00) >> 8) / 2.0f - 4.0f,((ra & 0xF0) >> 4) / 2.0f - 4.0f };
	m_tfFront->SetLocalPosition(Pos);
	m_tfFront->SetLocalRotation(Rot);
	if (InputDevice::IsPress(KeyCodes::Space))
		g_PressSpace = true;
	if (g_PressSpace)
	{
		if (g_nFCnt == 0)
		{
			Singleton<Fade>::GetInstance().OutStart();
			m_SE->PlaySE(AudioManager::SE_KIND::SE_ENTER);
		}
		else if (Singleton<Fade>::GetInstance().GetEnd())
			Singleton<SceneManager>::GetInstance().ChangeScene<SceneGame>();
		g_nFCnt++;
	}
}

void SceneTitle::UnInit()
{
	
}