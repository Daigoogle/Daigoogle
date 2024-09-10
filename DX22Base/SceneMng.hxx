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
#include "SceneBase.hxx"

class SceneMng: public Singleton<SceneMng>
{
	friend class Singleton<SceneMng>;
public:
	bool Init() override;
	void Update() override;

	template<typename TypeScene, typename = std::enable_if_t<std::is_base_of_v<SceneBase, TypeScene>>>
	void StartLoading()
	{
		// 既にロード済みシーンならば生成しない
		for (const auto& elem : m_LoadScenes) {
			if (dynamic_cast<TypeScene*>(elem)) {
				return;
			}
		}
		m_LoadScenes.push_back(new TypeScene);
		
		// 本来は並列化！！！
		m_LoadScenes.back()->Init();
	}

	template<typename TypeScene, typename = std::enable_if_t<std::is_base_of_v<SceneBase, TypeScene>>>
	void ChangeScene()
	{
		// 既にロード済みか調べる
		for (int i = 0; i < m_LoadScenes.size();i++) {
			if (dynamic_cast<TypeScene*>(m_LoadScenes[i]) != nullptr) {
				m_NextScene = m_LoadScenes[i];
				m_LoadScenes.erase(m_LoadScenes.begin() + i);
				return;
			}
		}
		// ロードしていない場合はロードする
		m_NextScene = new TypeScene;

		// 本来は並列化！！！
		m_NextScene->Init();
	}

	SceneBase* GetNowScene() const { return m_NowScene; }
private:
	SceneMng();
	~SceneMng();
	
	SceneBase* m_NowScene;
	SceneBase* m_NextScene;
	std::vector<SceneBase*> m_LoadScenes;
};

#endif // !_____SceneMng_HXX_____