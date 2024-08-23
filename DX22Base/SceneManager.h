//	ファイル名：SceneManager.h
//	概要		 ：再生するシーンの管理
//	作成者	 ：伊藤大悟
//	更新記録	 ：2024/01/05	13:49	ItoDaigo	作成
//┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┷┯┫

// =-=-= インクルードガード部 =-=-=
#ifndef _____SCENE_MANAGER_H_____
#define _____SCENE_MANAGER_H_____

// =-=-= インクルード部 =-=-=
#include "SceneBase.h"
#include "SingletonsMng.hxx"

/// @brief 再生するシーンを管理
/// @brief ▼▲▼▲▼▲ シングルトンです ▼▲▼▲▼▲
class SceneManager final :public Singleton<SceneManager>
{
	friend class Singleton<SceneManager>;
public:
	bool Init();
	void Update();
	void Draw();
	void UnInit();

	SceneBase* GetScene();

	template<typename SceneType>
	void ChangeScene()
	{
		if (m_NowScene != nullptr)
		{
			m_NextScene = new SceneType;
			return;
		}
		m_NowScene = new SceneType;
		m_NowScene->Init();
	}

	template<typename SceneType>
	void SetLoadScene()
	{
		if (m_LoadScene) { delete m_LoadScene; m_LoadScene = nullptr; }
		m_LoadScene = new SceneType;
	}

private:
	SceneManager();
	~SceneManager();
	SceneBase* m_NowScene;
	SceneBase* m_NextScene;
	SceneBase* m_LoadScene;
};

#endif // !_____SCENE_MANAGER_H_____