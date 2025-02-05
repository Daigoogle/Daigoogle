//	ファイル名	：SceneMng.hxx
//	  概  要	：
//	作	成	者	：daigo
//	 作成日時	：2024/06/14 23:52:43
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____SceneMng_HXX_____
#define _____SceneMng_HXX_____

// =-=-= インクルード部 =-=-=
#include <vector>
#include <type_traits>
#include "SingletonsMng.hxx"
#include "ThreadPool.hxx"
#include "SceneBase.hxx"

class SceneManager: public Singleton<SceneManager>
{
	friend class Singleton<SceneManager>;
	friend class Object;
public:
	bool Init() override;
	void Update() override;

	template<typename SceneObject, typename = std::enable_if_t<std::is_base_of_v<SceneBase, SceneObject>>>
	void StartLoading()
	{
		// 既にロード済みシーンならば生成しない
		for (const auto& elem : m_LoadScenes) {
			if (dynamic_cast<SceneObject*>(elem.get())) {
				return;
			}
		}
		m_LoadScenes.push_back(std::make_unique<SceneObject>());
		
		ThreadPool::GetInstance().AddPool([this]() {m_NextScene->Loading(&m_pInstantChange); });
	}



	template<typename SceneObject, typename = std::enable_if_t<std::is_base_of_v<SceneBase, SceneObject>>>
	void ChangeScene()
	{
		// 既にロード済みか調べる
		for (int i = 0; i < m_LoadScenes.size();i++) {
			if (typeid(SceneObject) == typeid(m_LoadScenes[i].get())) {
				if (m_LoadScenes[i]->m_LoadComplete);
				{
					m_NextScene.swap(m_LoadScenes[i]);
					m_LoadScenes.erase(m_LoadScenes.begin() + i);
					return;
				}
			}
		}
		// ロードしていない場合はロードする
		m_NextScene = std::make_unique<SceneObject>();
		m_NextScene->Init();
		m_NextScene->m_LoadComplete = true;
		
		//m_LoadScenes.push_back(std::make_unique<SceneObject>());
		//m_pInstantChange = m_LoadScenes.back().get();
		//ThreadPool::GetInstance().AddPool([this]() {m_pInstantChange->Loading(&m_pInstantChange); });
	}

	inline void ChangeScene(SceneBase* pScene)
	{
		for (int i = 0; i < m_LoadScenes.size(); i++) {
			if (pScene == m_LoadScenes[i].get()) {
				m_NextScene.swap(m_LoadScenes[i]);
				m_LoadScenes.erase(m_LoadScenes.begin() + i);
				return;
			}
		}
	}

	SceneBase* GetNowScene() const { return m_NowScene.get(); }
private:
	SceneManager();
	~SceneManager();

	SceneBase* m_pInstantChange;
	
	std::unique_ptr<SceneBase> m_NowScene;
	std::unique_ptr<SceneBase> m_NextScene;
	std::vector<std::unique_ptr<SceneBase>> m_LoadScenes;
	std::queue<Object*> m_InitQueue;
};

#endif // !_____SceneMng_HXX_____