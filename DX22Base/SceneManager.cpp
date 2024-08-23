//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
//	ファイル名：SceneManager.h
//	概　　　要：再生するシーンの管理
//	製　作　者：ItoDaigo
//
//	＝＝＝更新履歴＝＝＝
//	2024/01/05	13:49	ItoDaigo	作成
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// ---------- インクルード部 ----------
#include "SceneManager.h"
#include "BaseObjectManager.h"
#include "SceneGame.h"

SceneManager::SceneManager()
	:Singleton(UPDATE_ORDER::SECOND_UPDATE)
	,m_NowScene(nullptr)
	,m_NextScene(nullptr)
	,m_LoadScene(nullptr)
{
}

SceneManager::~SceneManager()
{
	UnInit();
}

bool SceneManager::Init()
{
	this->ChangeScene<SceneGame>();
	return true;
}

void SceneManager::Update()
{
	if (m_NextScene != nullptr)
	{
		m_NowScene->UnInit();
		BaseObjectManager::GetInstance().DeleteMainObject();
		m_NowScene = m_NextScene;
		m_NowScene->Init();
		m_NextScene = nullptr;
	}
	m_NowScene->Update();
}

void SceneManager::Draw()
{
	m_NowScene->Draw();
}

void SceneManager::UnInit()
{
	delete m_NowScene;
	m_NowScene = nullptr;
	if (m_NextScene)delete m_NextScene;
	m_NextScene = nullptr;
	if (m_LoadScene)delete m_LoadScene;
	m_LoadScene = nullptr;
}

SceneBase* SceneManager::GetScene()
{
	return m_NowScene;
}