//	ファイル名	：SceneMng.hxx
//	  概  要	：
//	作	成	者	：daigo
//	 作成日時	：2024/06/14 23:52:43
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____SceneMng_HXX_____
#define _____SceneMng_HXX_____

// =-=-= インクルード部 =-=-=
#include <deque>
#include <type_traits>
#include "SingletonsMng.hxx"

class SceneBase;

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
			if (dynamic_cast<TypeScene>(elem.get())) {
				return;
			}
		}
		m_LoadScenes.push_back(std::make_unique<TypeScene>());
		
		// 本来は並列化！！！
		m_LoadScenes.back()->Init();
	}

	template<typename TypeScene, typename = std::enable_if_t<std::is_base_of_v<SceneBase, TypeScene>>>
	void ChangeScene()
	{
		// 既にロード済みか調べる
		for (const auto& elem : m_LoadScenes) {
			if (dynamic_cast<TypeScene>(elem.get())) {
				m_NextScene = std::move(elem);
				return;
			}
		}
		// ロードしていない場合はロードする
		m_NextScene = std::make_unique<TypeScene>();

		// 本来は並列化！！！
		m_NextScene->Init();
	}

	SceneBase* GetNowScene() const { return m_NowScene.get(); }
private:
	SceneMng();
	~SceneMng();
	
	std::unique_ptr<SceneBase> m_NowScene;
	std::unique_ptr<SceneBase> m_NextScene;
	std::deque<std::unique_ptr<SceneBase>> m_LoadScenes;
};

#endif // !_____SceneMng_HXX_____