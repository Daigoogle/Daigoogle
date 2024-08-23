//	�t�@�C�����FBaseObjectManager.h
//	�T�v		 �F�x�[�X�I�u�W�F�N�g�̊Ǘ�
//	�쐬��	 �F�ɓ����
//	�X�V�L�^	 �F2024/02/17	21:40	�R�����g�ǉ�
//������������������������������������������������������������������������������������������������������

// =-=-= �C���N���[�h�K�[�h�� =-=-=
#ifndef _____BASE_OBJECT_MANAGER_H_____
#define _____BASE_OBJECT_MANAGER_H_____

// =-=-= �C���N���[�h�� =-=-=
#include <memory>
#include <vector>
#include <queue>
#include "BaseObject.h"
#include "BaseObjectInstance.h"
#include "SingletonsMng.hxx"

/// @brief BaseObject�̊Ǘ�
/// @brief ������������ �V���O���g���ł� ������������
class BaseObjectManager final :public Singleton<BaseObjectManager>
{
	friend Singleton<BaseObjectManager>;
public:
	enum class ProcessMode
	{
		MainScene,
		LoadScene,
		_Max
	};

	bool Init();
	void Update();
	void UnInit();

	BaseObject Make(SceneBase*);

	void SetMode(ProcessMode mode);
	ProcessMode GetMode();

	void DeleteMainObject();
	void DeleteLoadObject();

	void InitMainObjects();
private:
	BaseObjectManager();
	~BaseObjectManager();

	static void ResetFirstMainID();
	static void ResetFirstLoadID();

	void InitLoadObjects();
	void UpdateMainObjects();
	void UpdateLoadObjects();

	std::vector<std::unique_ptr<BaseObjectInstance>> m_MainObjects;
	std::queue<BaseObjectInstance*>					 m_InitMainObjQueue;
	static int										 ms_nLastGenerateMainID;

	std::vector<std::unique_ptr<BaseObjectInstance>> m_LoadObjects;
	std::queue<BaseObjectInstance*>					 m_InitLoadObjQueue;
	static int										 ms_nLastGenerateLoadID;

	ProcessMode m_Mode;
};

namespace ObjectManager
{
	BaseObject Make(SceneBase*);
}

#endif // !_____BASE_OBJECT_MANAGER_H_____