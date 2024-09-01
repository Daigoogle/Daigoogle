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
#include "Object.hxx"
#include "Transform.hxx"
#include "GameObjectMng.hxx"

class Component;
class Object;

class GameObjectInst :public Object
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
		pComp->m_pGameObjectInst = this;
		m_Components.push_back(std::move(pComp));
		return pComp.get();
	}

	template<typename TypeComp>
	TypeComp* GetComponent()
	{
		for (const auto elem : m_Components)
		{
			TypeComp* pComp = dynamic_cast<TypeComp*>(elem.get());
			if (pComp != nullptr)
				return pComp;
		}
		return nullptr;
	}

	void Delete();

private:
	static uint32_t ms_ObjectID;

	std::string m_Name;					// ���O
	unsigned m_Tag;						// �^�O
	bool m_IsDelete;					// �폜�t���O
	std::list<std::unique_ptr<Component>> m_Components;	// �R���|�[�l���g
	uint32_t m_ObjectID;		// ID

	bool m_IsFollowParent;				// �e�ɒǏ]���邩�ǂ���

	Transform m_Transform;				// �ʒu���
};

#endif // !_____GameObjectInst_HXX_____