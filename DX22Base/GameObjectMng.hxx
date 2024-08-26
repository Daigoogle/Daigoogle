//	�t�@�C����	�FGameObjectMng.hxx
//	  �T  �v 	�F
//	��	��	��	�Fdaigo
//	 �쐬����	�F2024/06/16 11:24:35
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= �C���N���[�h�K�[�h�� =-=-=
#ifndef _____GameObjectMng_HXX_____
#define _____GameObjectMng_HXX_____

// =-=-= �C���N���[�h�� =-=-=
#include <memory>
#include <unordered_map>
#include <vector>
#include <queue>

#include "SingletonsMng.hxx"

class GameObjectInst;
class GameObject;
class SceneBase;

class GameObjectMng: public Singleton<GameObjectMng>
{
	friend class Singleton<GameObjectMng>;
public:
	/// @brief ����������
	/// @return ����������true
	bool Init() override;
	/// @brief �X�V����
	void Update() override;

	/// @brief �I�u�W�F�N�g�̍쐬
	/// @param pScene �쐬����I�u�W�F�N�g�̏����V�[��
	/// @return �쐬�����I�u�W�F�N�g
	GameObject MakeObject(SceneBase* pScene);

	/// @brief �V�[���̃I�u�W�F�N�g�̉��
	/// @param pScene �������V�[��
	void DeleteSceneObjects(SceneBase* pScene);

private:
	/// @brief �R���X�g���N�^
	GameObjectMng();
	/// @brief �f�X�g���N�^
	~GameObjectMng();

	/// @brief �����I�u�W�F�N�g�̏������Ɠo�^
	void InitObjects();
	/// @brief ���V�[���̃I�u�W�F�N�g�̍X�V
	/// @param pScene ���݂̃V�[��
	void UpdateObjects(SceneBase* pScene);

	void DeleteObject();

	/// @brief �I�u�W�F�N�g�̃��[�h�L���[
	std::unordered_map<SceneBase* ,std::queue<GameObjectInst*>> m_ObjectsLoadQueue;
	/// @brief �I�u�W�F�N�g�̍X�V�L���[
	std::unordered_map<SceneBase* , std::vector<GameObjectInst*>> m_ObjectsQueue;
	/// @brief �폜����I�u�W�F�N�g�̃L���[
	std::unordered_map<uint32_t,SceneBase*> m_ObjectsDeleteQueue;
};

#endif // !_____GameObjectMng_HXX_____