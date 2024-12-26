//	�t�@�C����	�FSceneMng.hxx
//	  �T  �v	�F
//	��	��	��	�Fdaigo
//	 �쐬����	�F2024/06/14 23:52:43
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= �C���N���[�h�K�[�h�� =-=-=
#ifndef _____SceneMng_HXX_____
#define _____SceneMng_HXX_____

// =-=-= �C���N���[�h�� =-=-=
#include <vector>
#include <type_traits>
#include "SingletonsMng.hxx"
#include "ThreadPool.hxx"
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
		// ���Ƀ��[�h�ς݃V�[���Ȃ�ΐ������Ȃ�
		for (const auto& elem : m_LoadScenes) {
			if (dynamic_cast<TypeScene*>(elem.get())) {
				return;
			}
		}
		m_LoadScenes.push_back(std::make_unique<TypeScene>());
		
		// �{���͕��񉻁I�I�I
		m_LoadScenes.back()->Init();
	}

	template<typename TypeScene, typename = std::enable_if_t<std::is_base_of_v<SceneBase, TypeScene>>>
	void ChangeScene()
	{
		// ���Ƀ��[�h�ς݂����ׂ�
		for (int i = 0; i < m_LoadScenes.size();i++) {
			if (dynamic_cast<TypeScene*>(m_LoadScenes[i].get())) {
				m_NextScene.swap(m_LoadScenes[i]);
				if (!m_LoadScenes[i].get())
					m_LoadScenes.erase(m_LoadScenes.begin() + i);
				return;
			}
		}
		// ���[�h���Ă��Ȃ��ꍇ�̓��[�h����
		m_NextScene = std::make_unique<TypeScene>();

		//ThreadPoolMng::GetInstance().AddPool([m_NextScene]() {m_NextScene.Init()})

		// �{���͕��񉻁I�I�I
		m_NextScene->Init();
	}

	SceneBase* GetNowScene() const { return m_NowScene.get(); }
private:
	SceneMng();
	~SceneMng();
	
	std::unique_ptr<SceneBase> m_NowScene;
	std::unique_ptr<SceneBase> m_NextScene;
	std::vector<std::unique_ptr<SceneBase>> m_LoadScenes;
};

#endif // !_____SceneMng_HXX_____