//	�t�@�C�����FSceneManager.h
//	�T�v		 �F�Đ�����V�[���̊Ǘ�
//	�쐬��	 �F�ɓ����
//	�X�V�L�^	 �F2024/01/05	13:49	ItoDaigo	�쐬
//������������������������������������������������������������������������������������������������������

// =-=-= �C���N���[�h�K�[�h�� =-=-=
#ifndef _____SCENE_MANAGER_H_____
#define _____SCENE_MANAGER_H_____

// =-=-= �C���N���[�h�� =-=-=
#include "SceneBase.h"
#include "SingletonsMng.hxx"

/// @brief �Đ�����V�[�����Ǘ�
/// @brief ������������ �V���O���g���ł� ������������
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