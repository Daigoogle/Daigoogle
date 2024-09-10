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
			if (dynamic_cast<TypeScene*>(elem)) {
				return;
			}
		}
		m_LoadScenes.push_back(new TypeScene);
		
		// �{���͕��񉻁I�I�I
		m_LoadScenes.back()->Init();
	}

	template<typename TypeScene, typename = std::enable_if_t<std::is_base_of_v<SceneBase, TypeScene>>>
	void ChangeScene()
	{
		// ���Ƀ��[�h�ς݂����ׂ�
		for (int i = 0; i < m_LoadScenes.size();i++) {
			if (dynamic_cast<TypeScene*>(m_LoadScenes[i]) != nullptr) {
				m_NextScene = m_LoadScenes[i];
				m_LoadScenes.erase(m_LoadScenes.begin() + i);
				return;
			}
		}
		// ���[�h���Ă��Ȃ��ꍇ�̓��[�h����
		m_NextScene = new TypeScene;

		// �{���͕��񉻁I�I�I
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