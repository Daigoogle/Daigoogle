#include "SceneMng.hxx"

SceneMng::SceneMng()
	: Singleton(UPDATE_ORDER::SECOND_UPDATE)
	, m_NowScene()
	, m_NextScene()
	, m_LoadScenes()
{

}

SceneMng::~SceneMng()
{
	m_LoadScenes.clear();
}

bool SceneMng::Init()
{
	return true;
}

void SceneMng::Update()
{
	if (m_NextScene){
		m_NowScene.release();
		m_NowScene = std::move(m_NextScene);
	}
	if(m_NowScene)
		m_NowScene->Update();
}
