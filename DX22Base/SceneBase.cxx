#include "SceneBase.hxx"

#include "GameObject.hxx"
#include "SceneMng.hxx"

SceneBase::SceneBase()
	: m_LoadComplete(false)
	, m_SceneComponent()
{

}

SceneBase::~SceneBase()
{

}

// ロード処理（並列前提）
void SceneBase::Loading(SceneBase** ppInstantChange)
{
	// 初期化処理
	FalseCheck(this->Init());

	// ロード完了フラグを立てる
	m_LoadComplete = true;

	// このクラスが即チェンジならチェンジさせる
	if (this == *ppInstantChange)
		SceneManager::GetInstance().ChangeScene(this);
}

void SceneBase::ReadFile(const std::string& path)
{
	// ファイル読み込み・オブジェクト生成
}