#include "SceneMng.hxx"

SceneMng::SceneMng()
	: Singleton(UPDATE_ORDER::SECOND_UPDATE)
	, m_NowScene(nullptr)
	, m_NextScene(nullptr)
	, m_LoadScenes()
{

}

SceneMng::~SceneMng()
{
	if (m_NowScene)	{
		delete m_NowScene;
		m_NowScene = nullptr;
	}
	if (m_NextScene) {
		delete m_NextScene;
		m_NextScene = nullptr;
	}
	m_LoadScenes.clear();
}

bool SceneMng::Init()
{
	return true;
}

void SceneMng::Update()
{
	if (m_NextScene){
		delete m_NowScene;
		m_NowScene = m_NextScene;
		m_NextScene = nullptr;
	}
	if(m_NowScene)
		m_NowScene->Update();
}
