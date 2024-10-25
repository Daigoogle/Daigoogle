//	�t�@�C����	�FGameObjectInst.hxx
//	  �T  �v	�F
//	��	��	��	�Fdaigo
//	 �쐬����	�F2024/06/16 11:52:00
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= �C���N���[�h�K�[�h�� =-=-=
#ifndef _____GameObjectInst_HXX_____
#define _____GameObjectInst_HXX_____

// =-=-= �C���N���[�h�� =-=-=
#include <list>
#include <string>
#include <memory>
#include "GameObjectMng.hxx"
#include "Transform.hxx"
#include "DebugRestriction.hxx"

class Component;

class GameObjectInst
{
	friend class GameObjectMng;
	friend class GameObject;
private:
	GameObjectInst();
	~GameObjectInst();

	GameObjectInst& operator=(const GameObjectInst&) = delete;
	GameObjectInst& operator=(GameObjectInst&&) = delete;

	bool Init();
	void Update();

	const bool IsActive();

	template<typename TypeComp>
	TypeComp* AddComponent()
	{
		std::unique_ptr<TypeComp> pComp(new TypeComp);
		pComp->m_GameObject = GameObject(this);
		m_Components.push_back(std::move(pComp));
		return static_cast<TypeComp*>(m_Components.back().get());
	}

	template<typename TypeComp>
	TypeComp* GetComponent()
	{
		for (const auto elem : m_Components)
		{
			if (typeid(TypeComp) == typeid(elem.get()))
				return elem.get();
		}
		DebugBreakPoint_
		return nullptr;
	}

	void Delete();

private:
	static ID ms_ObjectID;

	Name m_Name;					// �I�u�W�F�N�g��
	unsigned m_Tag;						// �^�O
	bool m_IsActive;					// �A�N�e�B�u���ǂ���
	bool m_IsDelete;					// ���̃I�u�W�F�N�g�̍폜�t���O
	std::list<std::unique_ptr<Component>> m_Components;	// �ǉ����ꂽ�R���|�[�l���g
	ID m_ObjectID;					// �I�u�W�F�N�gID
	std::list<GameObjectInst*> m_childs;// �q�I�u�W�F�N�g�Q
	GameObjectInst* m_pParent;			// �e�I�u�W�F�N�g
	SceneBase* m_pScene;				// �����V�[��

	Transform m_Transform;				// �g�����X�t�H�[��
};

#endif // !_____GameObjectInst_HXX_____