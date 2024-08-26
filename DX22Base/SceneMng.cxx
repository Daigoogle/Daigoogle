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
